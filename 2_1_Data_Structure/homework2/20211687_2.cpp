#include <iostream>
#include <cstring>
#include <ctime>

using namespace std;
using ll = long long;

class Bizcard{
private:
    char *name;
    char *address;
    ll office_phone;
    ll mobile_phone;

public:
    Bizcard() {};
    Bizcard(char *, char *, ll , ll );
    Bizcard(const Bizcard &); // copy constructor
    ~Bizcard();
    Bizcard& operator=(const Bizcard &);
    void ShowInfo() const;
};

template <class T>
class Bag{
private:
    T *array;
    int capacity;
    int top;
public:
    Bag(int bagCapacity = 3);
    ~Bag();

    int Size() const;  
    bool IsEmpty() const; 
    T& Element() const;  

    void Push(const T&); 
    void Pop(); 

};

template <class T>
void ChangeSize1D(T*& a, const int oldSize, const int newSize)
{
    if (newSize < 0) throw "New length must be >= 0";

    T* temp = new T[newSize];                                  // new array
    int number = min(oldSize, newSize);  // number to copy
    copy(a, a + number, temp);
    delete [] a;                             // deallocate old memory
    a = temp;
}

Bizcard::Bizcard(char *name, char *address, ll office_phone, ll mobile_phone){
    this->name = new char[strlen(name) + 1];
    this->address = new char[strlen(address) + 1];
    strcpy(this->name, name); 
    strcpy(this->address, address);
    this->office_phone = office_phone;
    this->mobile_phone = mobile_phone;
}

Bizcard::Bizcard(const Bizcard& origin){
    this->name = new char[strlen(origin.name) + 1];
    this->address = new char[strlen(origin.address) + 1];
    strcpy(this->name, origin.name);
    strcpy(this->address, origin.address);
    this->mobile_phone = origin.mobile_phone;
    this->office_phone = origin.office_phone;
}

Bizcard::~Bizcard(){
    delete [] this->name;
    this->name = NULL;
    delete [] this->address;
    this->address = NULL;
    this->office_phone = 0;
    this->mobile_phone = 0;
}

Bizcard& Bizcard::operator=(const Bizcard &origin){
    delete [] this->name;
    delete [] this->address;
    this->mobile_phone = origin.mobile_phone;
    this->office_phone = origin.office_phone;
    this->name = new char[strlen(origin.name) + 1];
    this->address = new char[strlen(origin.address) + 1];
    strcpy(this->name, origin.name);
    strcpy(this->address, origin.address);
    return *this;
}

void Bizcard::ShowInfo() const{
    cout << "====================" << endl;
    cout << this->name << endl;
    cout << this->address << endl;
    cout << this->office_phone << endl;
    cout << this->mobile_phone << endl;
    cout << "====================" << endl;
}

template <class T>
Bag<T>::Bag (int bagCapacity): capacity(bagCapacity){
    if (capacity < 1) throw "Capacity must be > 0";
    array = new T[capacity];
    top = -1;
}

template <class T>
Bag<T>::~Bag() { delete [] array; }

template <class T>
inline int Bag<T>::Size() const { return top+1; }

template <class T>
inline bool Bag<T>::IsEmpty() const { return Size() == 0; }

template <class T>
inline T& Bag<T>::Element() const{
    if(IsEmpty()) throw "Bag is empty";
    return array[rand()%(top+1)]; // Select random location
}

template <class T>
void Bag<T>::Push(const T& x) {
    if (capacity == top+1){
        ChangeSize1D(array, capacity, 2 * capacity);
        capacity *=2;
    }
    array[++top] = x;
}

template <class T>
void Bag<T>::Pop() {
    if (IsEmpty()) throw "Bag is empty, cannot delete";
    // int deletePos = top / 2;
    int deletePos = rand()%(top+1); // Delete random location 
    copy(array+deletePos+1,array+top+1,array+deletePos);
        // compact array
    array[top--].~T();   // destructor for T
}

int main(){
    srand(time(NULL)); // or /dev/urandom
    Bag<Bizcard> obj;
    cout << "[*] 빈 Bag에 대해 Size(), IsEmpty(), Element() 연산 결과 출력 확인" << endl;
    cout << obj.Size() << endl;
    if(obj.IsEmpty()){
        cout << "obj is empty" << endl;
    }else{
        cout << "obj is not empty" << endl;
    }
    try{
        obj.Element().ShowInfo();
    }catch(char const *except){
        cout << except << endl;
    }

    cout << "[*] Push()연산을 3번 수행하여 Bizcard 객체를 3개 추가한 후, Size(), IsEmpty(), Element() 연산 결과 출력 확인" << endl;
    Bizcard *biz1 = new Bizcard("A", "AA", 9331234, 11071459814);
    Bizcard *biz2 = new Bizcard("B", "BB", 9335678, 11012345678);
    Bizcard *biz3 = new Bizcard("C", "CC", 9330405, 11056781234);
    obj.Push(*biz1);
    obj.Push(*biz2);
    obj.Push(*biz3);
    cout << obj.Size() << endl;
    if(obj.IsEmpty()){
        cout << "obj is empty" << endl;
    }else{
        cout << "obj is not empty" << endl;
    }
    try{
        obj.Element().ShowInfo();
    }catch(char const *msg){
        cout << msg << endl;
    }
    
    cout << "[*] Push()연산을 4번 수행하여 Bizcard 객체를 총 7개 추가한 후, Size(), IsEmpty(), Element() 연산 결과 출력 확인" << endl;
    Bizcard *biz4 = new Bizcard("D", "DD", 9330405, 11056781234);
    Bizcard *biz5 = new Bizcard("E", "EE", 9330405, 11056781234);
    Bizcard *biz6 = new Bizcard("F", "FF", 9330405, 11056781234);
    Bizcard *biz7 = new Bizcard("G", "GG", 9330405, 11056781234);
    obj.Push(*biz4);
    obj.Push(*biz5);
    obj.Push(*biz6);
    obj.Push(*biz7);
    cout << obj.Size() << endl;
    if(obj.IsEmpty()){
        cout << "obj is empty" << endl;
    }else{
        cout << "obj is not empty" << endl;
    }
    try{
        obj.Element().ShowInfo();
    }catch(char const *msg){
        cout << msg << endl;
    }

    cout << "[*]Pop()연산을 2번 수행하여 Bizcard 객체를 2개 삭제한 후, Size(), IsEmpty(), Element() 연산 결과 출력 확인" << endl;
    try{
        obj.Pop();
        obj.Pop();
    }catch(char const *msg){
        cout << msg << endl;
    }
    cout << obj.Size() << endl;
    if(obj.IsEmpty()){
        cout << "obj is empty" << endl;
    }else{
        cout << "obj is not empty" << endl;
    }
    try{
        obj.Element().ShowInfo();
    }catch(char const *msg){
        cout << msg << endl;
    }

    return 0;
}