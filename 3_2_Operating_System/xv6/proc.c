#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "spinlock.h"
#include "elf.h"

struct {
  struct spinlock lock;
  struct proc proc[NPROC]; // NRPOC = 64 최대 프로세스 개수
} ptable;

static struct proc *initproc;

int nextpid = 1;
extern void forkret(void);
extern void trapret(void);

static void wakeup1(void *chan);

void
pinit(void)
{
  initlock(&ptable.lock, "ptable");
}

// Must be called with interrupts disabled
int
cpuid() {
  return mycpu()-cpus;
}

// Must be called with interrupts disabled to avoid the caller being
// rescheduled between reading lapicid and running through the loop.
struct cpu*
mycpu(void)
{
  int apicid, i;
  
  if(readeflags()&FL_IF)
    panic("mycpu called with interrupts enabled\n");
  
  apicid = lapicid();
  // APIC IDs are not guaranteed to be contiguous. Maybe we should have
  // a reverse map, or reserve a register to store &cpus[i].
  for (i = 0; i < ncpu; ++i) {
    if (cpus[i].apicid == apicid)
      return &cpus[i];
  }
  panic("unknown apicid\n");
}

// Disable interrupts so that we are not rescheduled
// while reading proc from the cpu structure
struct proc*
myproc(void) {
  struct cpu *c;
  struct proc *p;
  pushcli();
  c = mycpu();
  p = c->proc;
  popcli();
  return p;
}

//PAGEBREAK: 32
// Look in the process table for an UNUSED proc.
// If found, change state to EMBRYO and initialize
// state required to run in the kernel.
// Otherwise return 0.
static struct proc*
allocproc(void)
{
  struct proc *p;
  char *sp;

  acquire(&ptable.lock); // lock

  // ptable중 비어있는거 찾음(MAX process: 64)
  // enum procstate { UNUSED, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };
  // enum procstate state;        // Process state
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    if(p->state == UNUSED)
      goto found;

  release(&ptable.lock); // unlock
  return 0;

found:
  p->state = EMBRYO; // 태아? 처음 생성된 프로세스라는 상태
  p->pid = nextpid++; // pid 증가
  p->priority = 5; // priority 5로 초기화
  p->count = 0;

  release(&ptable.lock);

  // Allocate kernel stack.
  if((p->kstack = kalloc()) == 0){
    p->state = UNUSED;
    return 0;
  }
  sp = p->kstack + KSTACKSIZE;

  // Leave room for trap frame.
  sp -= sizeof *p->tf;
  p->tf = (struct trapframe*)sp;

  // Set up new context to start executing at forkret,
  // which returns to trapret.
  sp -= 4;
  *(uint*)sp = (uint)trapret;

  sp -= sizeof *p->context;
  p->context = (struct context*)sp;
  memset(p->context, 0, sizeof *p->context);
  p->context->eip = (uint)forkret;

  return p;
}

//PAGEBREAK: 32
// Set up first user process.
void
userinit(void)
{
  struct proc *p;
  extern char _binary_initcode_start[], _binary_initcode_size[];

  p = allocproc();
  
  initproc = p;
  if((p->pgdir = setupkvm()) == 0)
    panic("userinit: out of memory?");
  inituvm(p->pgdir, _binary_initcode_start, (int)_binary_initcode_size);
  p->sz = PGSIZE;
  memset(p->tf, 0, sizeof(*p->tf));
  p->tf->cs = (SEG_UCODE << 3) | DPL_USER;
  p->tf->ds = (SEG_UDATA << 3) | DPL_USER;
  p->tf->es = p->tf->ds;
  p->tf->ss = p->tf->ds;
  p->tf->eflags = FL_IF;
  p->tf->esp = PGSIZE;
  p->tf->eip = 0;  // beginning of initcode.S

  safestrcpy(p->name, "initcode", sizeof(p->name));
  p->cwd = namei("/");

  // this assignment to p->state lets other cores
  // run this process. the acquire forces the above
  // writes to be visible, and the lock is also needed
  // because the assignment might not be atomic.
  acquire(&ptable.lock);

  p->state = RUNNABLE;

  release(&ptable.lock);
}

// Grow current process's memory by n bytes.
// Return 0 on success, -1 on failure.
int
growproc(int n)
{
  uint sz;
  struct proc *curproc = myproc();

  sz = curproc->sz;
  if(n > 0){
    if((sz = allocuvm(curproc->pgdir, sz, sz + n)) == 0)
      return -1;
  } else if(n < 0){
    if((sz = deallocuvm(curproc->pgdir, sz, sz + n)) == 0)
      return -1;
  }
  curproc->sz = sz;
  switchuvm(curproc);
  return 0;
}

// priority 설정
int
set_proc_priority(int pid, int priority)
{
  struct proc *p;
  // int old_priority = -1;

  acquire(&ptable.lock); // lock

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++) {
    if(p->pid == pid) {
      // old_priority = p->priority;
      p->priority = priority;
      release(&ptable.lock); // unlock
      return 1; // priority 변경 성공
    }
  }

  release(&ptable.lock); // unlock

  return -1; // pid에 해당하는 프로세스가 없을 경우
}

// priority 반환
int
get_proc_priority(int pid)
{
  struct proc *p;
  int priority = -1;

  acquire(&ptable.lock); // lock

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++) {
    if(p->pid == pid) {
      priority = p->priority;
      break;
    }
  }

  release(&ptable.lock); // unlock

  return priority;
}

// Create a new process copying p as the parent.
// Sets up stack to return as if from system call.
// Caller must set state of returned proc to RUNNABLE.
int
fork(void)
{
  int i, pid;
  struct proc *np;
  struct proc *curproc = myproc(); // CPU에서 실행 중인 프로세스에 대한 struct proc 포인터 반환
  // Allocate process.
  if((np = allocproc()) == 0){
    return -1;
  }

  // Copy process state from proc.
  // copyuvm() : 물리적 메모리 할당, 부모 메모리 복사
  if((np->pgdir = copyuvm(curproc->pgdir, curproc->sz)) == 0){
    kfree(np->kstack);
    np->kstack = 0;
    np->state = UNUSED;
    return -1;
  }
  np->sz = curproc->sz; // 새로운 프로세스의 사이즈 = 현재 프로세스 사이즈
  np->parent = curproc; // 새로운 프로세스의 부모 = 현재 프로세스 proc 포인터 가르킴
  *np->tf = *curproc->tf; // cpu x86 레지스터 복사

  // Clear %eax so that fork returns 0 in the child.
  np->tf->eax = 0; // 새로운 프로세스의 리턴값은 0임. $eax 레지스터 0
  
  np->priority = curproc->priority; // 새로운 프로세스의 priority = 현재 프로세스의 priority

  // File Descriptor 복사
  for(i = 0; i < NOFILE; i++) // fd 최대 16개
    if(curproc->ofile[i]) // file 구조체 포인터 배열
      np->ofile[i] = filedup(curproc->ofile[i]); // file* curproc->ofile[i] f->ref++; 해줌
  np->cwd = idup(curproc->cwd); // innode* curproc->cwd ip->ref++; 해줌

  safestrcpy(np->name, curproc->name, sizeof(curproc->name)); // 프로세스 이름 복사

  pid = np->pid; // 새로운 프로세스 pid 리턴하기 위해서

  // race condition 방지
  acquire(&ptable.lock); // ptable lock

  np->state = RUNNABLE; // 새로운 프로세스 상태를 runnable로 변경

  release(&ptable.lock); // ptable unlock

  return pid; // 부모에게 새로 생성된 자식 프로세스 pid return
}

int
forknexec(const char* path, const char **args)
{
  int i, off, wait_result, t;
  // int pid;
  struct proc *np; // 새로운 프로세스
  struct proc *curproc = myproc(); // CPU에서 실행 중인 프로세스에 대한 struct proc 포인터 반환
  struct inode *ip;
  struct elfhdr elf;
  struct proghdr ph;
  pde_t *pgdir;
  //pde_t *oldpgdir;
  char *last, *s;
  uint argc, sz, sp, ustack[3+MAXARG+1];
  
  begin_op();
  
  // inode 찾기
  if((ip = namei((char *)path)) == 0){
    end_op();
    cprintf("exec: fail\n");
    return -1;
  }
  ilock(ip); // inode lock
  pgdir = 0;

  // Check ELF header
  if(readi(ip, (char*)&elf, 0, sizeof(elf)) != sizeof(elf))
    goto bad;

  if(elf.magic != ELF_MAGIC)
    goto bad;

  // 새로운 page directory를 생성
  if((pgdir = setupkvm()) == 0)
    goto bad;

  // Allocate process.
  if((np = allocproc()) == 0){
    return -2;
  }

  // 프로세스 상태 복사, 파일 디스크립터 복사, ELF 프로그램 헤더 로딩
  // Copy process state from proc.
  // copyuvm() : 물리적 메모리 할당, 부모 메모리 복사
  if((np->pgdir = copyuvm(curproc->pgdir, curproc->sz)) == 0){
    kfree(np->kstack);
    np->kstack = 0;
    np->state = UNUSED;
    return -2;
  }
  np->sz = curproc->sz; // 새로운 프로세스의 사이즈 = 현재 프로세스 사이즈
  np->parent = curproc; // 새로운 프로세스의 부모 = 현재 프로세스 proc 포인터 가르킴
  *np->tf = *curproc->tf; // cpu x86 레지스터 복사

  // Clear %eax so that fork returns 0 in the child.
  // np->tf->eax = 0; // 새로운 프로세스의 리턴값은 0임. $eax 레지스터 0

  // File Descriptor 복사
  for(i = 0; i < NOFILE; i++) // fd 최대 16개
    if(curproc->ofile[i]) // file 구조체 포인터 배열
      np->ofile[i] = filedup(curproc->ofile[i]); // file* curproc->ofile[i] f->ref++; 해줌
  np->cwd = idup(curproc->cwd); // innode* curproc->cwd ip->ref++; 해줌

  // safestrcpy(np->name, curproc->name, sizeof(curproc->name)); // 프로세스 이름 복사


  // Load program into memory.
  sz = 0;
  for(i=0, off=elf.phoff; i<elf.phnum; i++, off+=sizeof(ph)){
    if(readi(ip, (char*)&ph, off, sizeof(ph)) != sizeof(ph))
      goto bad;
    if(ph.type != ELF_PROG_LOAD)
      continue;
    if(ph.memsz < ph.filesz)
      goto bad;
    if(ph.vaddr + ph.memsz < ph.vaddr)
      goto bad;
    if((sz = allocuvm(pgdir, sz, ph.vaddr + ph.memsz)) == 0)
      goto bad;
    if(ph.vaddr % PGSIZE != 0)
      goto bad;
    if(loaduvm(pgdir, (char*)ph.vaddr, ip, ph.off, ph.filesz) < 0)
      goto bad;
  }
  iunlockput(ip);
  end_op();
  ip = 0;


  // Allocate two pages at the next page boundary.
  // Make the first inaccessible.  Use the second as the user stack.
  sz = PGROUNDUP(sz);
  if((sz = allocuvm(pgdir, sz, sz + 2*PGSIZE)) == 0)
    goto bad;
  clearpteu(pgdir, (char*)(sz - 2*PGSIZE));
  sp = sz;

  // Push argument strings, prepare rest of stack in ustack.
  for(argc = 0; args[argc]; argc++) {
    if(argc >= MAXARG)
      goto bad;
    sp = (sp - (strlen(args[argc]) + 1)) & ~3;
    if(copyout(pgdir, sp, (char *)args[argc], strlen(args[argc]) + 1) < 0)
      goto bad;
    ustack[3+argc] = sp;
  }
  ustack[3+argc] = 0;

  ustack[0] = 0xffffffff;  // fake return PC
  ustack[1] = argc;
  ustack[2] = sp - (argc+1)*4;  // argv pointer

  sp -= (3+argc+1) * 4;
  if(copyout(pgdir, sp, ustack, (3+argc+1)*4) < 0)
    goto bad;

  // Save program name for debugging.
  for(last=s=(char *)path; *s; s++)
    if(*s == '/')
      last = s+1;
  // safestrcpy(curproc->name, last, sizeof(curproc->name));
  safestrcpy(np->name, last, sizeof(np->name));

  // np->pid = nextpid++;
  np->pgdir = pgdir;
  np->sz = sz;
  np->tf->eip = elf.entry;  // main
  np->tf->esp = sp;
  switchuvm(np);


  // Commit to the user image.
  // oldpgdir = curproc->pgdir;
  // curproc->pgdir = pgdir;
  // curproc->sz = sz;
  // curproc->tf->eip = elf.entry;  // main
  // curproc->tf->esp = sp;
  // switchuvm(curproc);
  // freevm(oldpgdir);

  // race condition 방지
  acquire(&ptable.lock); // ptable lock

  np->state = RUNNABLE; // 새로운 프로세스 상태를 runnable로 변경

  release(&ptable.lock); // ptable unlock

  yield(); // 새 프로세스가 실행될 수 있도록 현재 프로세스를 양보
  t = np->pid; // wait 이후에는 p->pid가 0이 되므로 미리 저장해둠
  wait_result = wait(); // 자식 프로세스 대기
  // cprintf("PID : %d\n", np->pid);
  // cprintf("PID : %d\n", wait_result);

  if(wait_result == t) {  // 자식 프로세스가 성공적으로 실행되었다면
    return t;  // 자식 프로세스의 pid를 반환
  } else {
    return -1; // exec 실패로 인한 오류 ex) ls -m
  }

bad:
  if(pgdir)
    freevm(pgdir);
  if(ip){
    iunlockput(ip);
    end_op();
  }
  return -2;
}


// Exit the current process.  Does not return.
// An exited process remains in the zombie state
// until its parent calls wait() to find out it exited.
void
exit(void)
{
  struct proc *curproc = myproc();
  struct proc *p;
  int fd;

  if(curproc == initproc)
    panic("init exiting");

  // Close all open files.
  for(fd = 0; fd < NOFILE; fd++){
    if(curproc->ofile[fd]){
      fileclose(curproc->ofile[fd]);
      curproc->ofile[fd] = 0;
    }
  }

  begin_op();
  iput(curproc->cwd);
  end_op();
  curproc->cwd = 0;

  acquire(&ptable.lock);

  // Parent might be sleeping in wait().
  wakeup1(curproc->parent);

  // Pass abandoned children to init.
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->parent == curproc){
      p->parent = initproc;
      if(p->state == ZOMBIE)
        wakeup1(initproc);
    }
  }

  // Jump into the scheduler, never to return.
  curproc->state = ZOMBIE;
  sched();
  panic("zombie exit");
}

// Wait for a child process to exit and return its pid.
// Return -1 if this process has no children.
int
wait(void)
{
  struct proc *p;
  int havekids, pid;
  struct proc *curproc = myproc();
  
  acquire(&ptable.lock);
  for(;;){
    // Scan through table looking for exited children.
    havekids = 0;
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
      if(p->parent != curproc)
        continue;
      havekids = 1;
      if(p->state == ZOMBIE){
        // Found one.
        pid = p->pid;
        kfree(p->kstack);
        p->kstack = 0;
        freevm(p->pgdir);
        p->pid = 0;
        p->parent = 0;
        p->name[0] = 0;
        p->killed = 0;
        p->state = UNUSED;
        release(&ptable.lock);
        return pid;
      }
    }

    // No point waiting if we don't have any children.
    if(!havekids || curproc->killed){
      release(&ptable.lock);
      return -1;
    }

    // Wait for children to exit.  (See wakeup1 call in proc_exit.)
    sleep(curproc, &ptable.lock);  //DOC: wait-sleep
  }
}

//PAGEBREAK: 42
// Per-CPU process scheduler.
// Each CPU calls scheduler() after setting itself up.
// Scheduler never returns.  It loops, doing:
//  - choose a process to run
//  - swtch to start running that process
//  - eventually that process transfers control
//      via swtch back to the scheduler.
void scheduler(void) {
  struct proc *p;
  struct cpu *c = mycpu();
  c->proc = 0;

  for(;;) {
    sti();
    acquire(&ptable.lock);

    int highest_priority = 0xff;
    struct proc *selected_proc = 0;

    // 에이징 로직 추가
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++) {
      if(p->state == RUNNABLE) {
        p->count++;
        if (p->count >= 100) {
          p->priority++;
          if(p->priority == 10)
            p->priority = 1;
          p->count = 0;
        }
      }
    }

    // 우선순위 가장 높은 프로세스 선택
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++) {
      if(p->state != RUNNABLE)
        continue;

      if(p->priority < highest_priority) {
        highest_priority = p->priority;
        selected_proc = p;
      }
    }

    if (selected_proc) {
      selected_proc->count += 10;
      c->proc = selected_proc;
      switchuvm(selected_proc);
      selected_proc->state = RUNNING;
      
      swtch(&(c->scheduler), selected_proc->context);
      switchkvm();

      c->proc = 0;
    }

    release(&ptable.lock);
  }
}




// void
// scheduler(void)
// {
//   struct proc *p; // 프로세스 구조체 포인터
//   struct cpu *c = mycpu(); // cpu 구조체 포인터 반환
//   c->proc = 0;
  
//   for(;;){
//     // Enable interrupts on this processor.
//     sti(); // set interrupt flag

//     // Loop over process table looking for process to run.
//     acquire(&ptable.lock); // race condition 방지 위해 lock

//     // priority scheduling  
//     /*
//     - priority는1~10까지의 값을 가질 수 있음
//     - 1 이 가장 높은 priority
//     - 10 이 가장 낮은 priority 임
//     */
//     int min_priority = __INT_MAX__;
//     // int max_priority = 0;
    
//     struct proc *min_priority_proc = 0;
//     // struct proc *max_priority_proc = 0;

//     for(p = ptable.proc; p < &ptable.proc[NPROC]; p++) {
//       if(p->state != RUNNABLE) // 실행 가능한 프로세스 찾기
//         continue;
//       // 우선순위 높은 프로세스 찾기
//       // todo : starvation 방지 필요 (count 사용)

//       if(p->priority < min_priority) {
//         min_priority = p->priority;
//         min_priority_proc = p;
//         min_priority_proc->count++;
//       }

//       if(min_priority_proc->count >= 0x30 && min_priority_proc->pid > 2){ // count가 0x100 이상이면 priority 1 증가
//         if(min_priority_proc->priority >= 1){ // range check
//           min_priority_proc->priority++; // priority 1 증가
//           if(min_priority_proc->priority == 10){
//             min_priority_proc->priority = 1;
//           }
//         }
//         min_priority_proc->count = 0;
//       }

//       // Process is done running for now.
//       // It should have changed its p->state before coming back.
//       c->proc = 0;
//     }

//     if(min_priority_proc != 0) {
//       p = min_priority_proc;
//       c->proc = p; 
//       switchuvm(p);
//       p->state = RUNNING; // 프로세스 상태를 running으로 변경
//       // p->count++;
      
//       swtch(&(c->scheduler), p->context); // context switch
//       switchkvm();

//       // Process is done running for now.
//       // It should have changed its p->state before coming back.
//       c->proc = 0;
//     }
//     release(&ptable.lock);

//   }
// }

// void
// scheduler(void)
// {
//   struct proc *p; // 프로세스 구조체 포인터
//   struct proc *highP, *lowP, *p1; // 프로세스 구조체 포인터
//   struct cpu *c = mycpu(); // cpu 구조체 포인터 반환
//   c->proc = 0;
  
//   for(;;){
//     // Enable interrupts on this processor.
//     sti(); // set interrupt flag

//     // Loop over process table looking for process to run.
//     acquire(&ptable.lock); // race condition 방지 위해 lock
//     for (p = ptable.proc; p < &ptable.proc[NPROC]; p++)
//     {
//       if (p->state != RUNNABLE)
//         continue;
//       highP = p;
//       for (p1 = ptable.proc; p1 < &ptable.proc[NPROC]; p1++)
//       {
//         if (p1->state != RUNNABLE)
//           continue;

//         if (highP->priority < p1->priority)
//           highP = p1;
        
//         if(highP->priority > p1->priority){
//           // gg = highP->priority;
//           lowP = highP;
//         }
//       }

//       // 가장 낮은 priority를 가진 프로세스를 찾아서 count 증가 및 priority 증가
//       if (lowP->count >= 0x10)
//       { // count가 0x100 이상이면 priority 1 증가
//         if (lowP->priority >= 1 && lowP->priority < 10) // range check
//           lowP->priority--;                             // priority 1 증가
//         lowP->count = 0;
//       }

//       p = highP;
//       c->proc = p;
//       switchuvm(p);
//       p->state = RUNNING;
//       p->count++;

//       swtch(&(c->scheduler), p->context);
//       switchkvm();

//       // Process is done running for now.
//       // It should have changed its p->state before coming back.
//       c->proc = 0;
//     }
//     release(&ptable.lock);

//   }
// }

// Enter scheduler.  Must hold only ptable.lock
// and have changed proc->state. Saves and restores
// intena because intena is a property of this
// kernel thread, not this CPU. It should
// be proc->intena and proc->ncli, but that would
// break in the few places where a lock is held but
// there's no process.
void
sched(void)
{
  int intena;
  struct proc *p = myproc();

  if(!holding(&ptable.lock))
    panic("sched ptable.lock");
  if(mycpu()->ncli != 1)
    panic("sched locks");
  if(p->state == RUNNING)
    panic("sched running");
  if(readeflags()&FL_IF)
    panic("sched interruptible");
  intena = mycpu()->intena;
  swtch(&p->context, mycpu()->scheduler);
  mycpu()->intena = intena;
}

// Give up the CPU for one scheduling round.
void
yield(void)
{
  acquire(&ptable.lock);  //DOC: yieldlock
  myproc()->state = RUNNABLE;
  sched();
  release(&ptable.lock);
}

// A fork child's very first scheduling by scheduler()
// will swtch here.  "Return" to user space.
void
forkret(void)
{
  static int first = 1;
  // Still holding ptable.lock from scheduler.
  release(&ptable.lock);

  if (first) {
    // Some initialization functions must be run in the context
    // of a regular process (e.g., they call sleep), and thus cannot
    // be run from main().
    first = 0;
    iinit(ROOTDEV);
    initlog(ROOTDEV);
  }

  // Return to "caller", actually trapret (see allocproc).
}

// Atomically release lock and sleep on chan.
// Reacquires lock when awakened.
void
sleep(void *chan, struct spinlock *lk)
{
  struct proc *p = myproc();
  
  if(p == 0)
    panic("sleep");

  if(lk == 0)
    panic("sleep without lk");

  // Must acquire ptable.lock in order to
  // change p->state and then call sched.
  // Once we hold ptable.lock, we can be
  // guaranteed that we won't miss any wakeup
  // (wakeup runs with ptable.lock locked),
  // so it's okay to release lk.
  if(lk != &ptable.lock){  //DOC: sleeplock0
    acquire(&ptable.lock);  //DOC: sleeplock1
    release(lk);
  }
  // Go to sleep.
  p->chan = chan;
  p->state = SLEEPING;

  sched();

  // Tidy up.
  p->chan = 0;

  // Reacquire original lock.
  if(lk != &ptable.lock){  //DOC: sleeplock2
    release(&ptable.lock);
    acquire(lk);
  }
}

//PAGEBREAK!
// Wake up all processes sleeping on chan.
// The ptable lock must be held.
static void
wakeup1(void *chan)
{
  struct proc *p;

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    if(p->state == SLEEPING && p->chan == chan)
      p->state = RUNNABLE;
}

// Wake up all processes sleeping on chan.
void
wakeup(void *chan)
{
  acquire(&ptable.lock);
  wakeup1(chan);
  release(&ptable.lock);
}

// Kill the process with the given pid.
// Process won't exit until it returns
// to user space (see trap in trap.c).
int
kill(int pid)
{
  struct proc *p;

  acquire(&ptable.lock);
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->pid == pid){
      p->killed = 1;
      // Wake process from sleep if necessary.
      if(p->state == SLEEPING)
        p->state = RUNNABLE;
      release(&ptable.lock);
      return 0;
    }
  }
  release(&ptable.lock);
  return -1;
}

//PAGEBREAK: 36
// Print a process listing to console.  For debugging.
// Runs when user types ^P on console.
// No lock to avoid wedging a stuck machine further.
void
procdump(void)
{
  static char *states[] = {
  [UNUSED]    "unused",
  [EMBRYO]    "embryo",
  [SLEEPING]  "sleep ",
  [RUNNABLE]  "runble",
  [RUNNING]   "run   ",
  [ZOMBIE]    "zombie"
  };
  int i;
  struct proc *p;
  char *state;
  uint pc[10];

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->state == UNUSED)
      continue;
    if(p->state >= 0 && p->state < NELEM(states) && states[p->state])
      state = states[p->state];
    else
      state = "???";
    cprintf("pid\tpriority\tstate\tname\n");
    cprintf("%d\t%d\t\t%s\t%s", p->pid, p->priority, state, p->name);
    if(p->state == SLEEPING){
      getcallerpcs((uint*)p->context->ebp+2, pc);
      for(i=0; i<10 && pc[i] != 0; i++)
        cprintf(" %p", pc[i]);
    }
    cprintf("\n");
  }
  cprintf("=========================================\n");
}
