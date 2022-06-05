import java.util.Scanner;

class Reservation{
	private String name;
	public Reservation() { this.name = null; };
	public Reservation(String name) { this.name = name; }
	public void setName(String name) { this.name = name; };
	public String getName() { return this.name; }
}

class Seat{
	private Reservation[] reserve;
	public Seat() {
		this.reserve = new Reservation[10];
		for(int i=0; i<10; i++) {
			this.reserve[i] = new Reservation();
		}	
	}
	public void setSeat(int idx, String name) {
		this.reserve[idx].setName(name);
	}
	public void showSeat() {
		for(int i=0; i<reserve.length; i++) {
			if(reserve[i].getName() == null) System.out.print(" --- ");
			else System.out.print(" " + reserve[i].getName() + " ");
		}
		System.out.println();
	}
	public void deleteSeat(String delName) {
		for(int i=0; i<reserve.length; i++) {
			if(delName.equals(reserve[i].getName())) reserve[i].setName(null);
		}
	}
}


public class Program12 {

	public static void Reserve(Seat seats[]) {
		Scanner sc = new Scanner(System.in);
		System.out.print("좌석구분 S(1), A(2), B(3)>>");
		int sab = sc.nextInt();
		switch(sab) {
			case 1: System.out.print("S>> "); break;
			case 2: System.out.print("A>> "); break;
			case 3: System.out.print("B>> "); break;
			default: return;
		}
		seats[sab-1].showSeat();
		System.out.print("이름>>");
		String reserveName = sc.next();
		System.out.print("번호>>");
		int reserveNumber = sc.nextInt();
		if(reserveNumber >= 1 && reserveNumber <= 10) 
			seats[sab-1].setSeat(reserveNumber-1, reserveName);
		return;
	}
	public static void Show(Seat seats[]) {
		for(int i=0; i<3; i++) {
			seats[i].showSeat();
		}
		System.out.println("<<<조회를 완료하였습니다.>>>");
		return;
	}
	public static void Cancle(Seat seats[]) {
		Scanner sc = new Scanner(System.in);
		System.out.print("좌석 S:1, A:2, B:3>>");
		int sab = sc.nextInt();
		switch(sab) {
			case 1: System.out.print("S>> "); break;
			case 2: System.out.print("A>> "); break;
			case 3: System.out.print("B>> "); break;
			default: return;
		}
		seats[sab-1].showSeat();
		System.out.print("이름>>");
		String cancleName = sc.next();
		seats[sab-1].deleteSeat(cancleName);
		return;
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		Seat[] seats = new Seat[3];
		for(int i=0; i<3; i++) {
			seats[i] = new Seat();
		}
		System.out.println("명품콘서트홀 예약 시스템입니다.");
		while(true) {
			System.out.print("예약:1, 조회:2, 취소:3, 끝내기:4>>");
			int n = sc.nextInt();
			switch(n) {
				case 1:
					Reserve(seats); break;
				case 2:
					Show(seats); break;
				case 3:
					Cancle(seats); break;
				case 4:
					System.exit(0);
				default:
					break;
			}
		}
	}

}