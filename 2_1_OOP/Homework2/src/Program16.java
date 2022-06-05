import java.util.Scanner;

public class Program16 {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		String[] str = {"가위", "바위", "보"};
		String s;
		int my = -1, com = -1, res;
		System.out.println("컴퓨터와 가위 바위 보 게임을 합니다.");
		while(true) {
			try {
				System.out.print("가위 바위 보!>>");
				s = sc.next();
				if(s.equals("그만")) break;
				my = -1; com = -1;
				for(int i=0; i<str.length; i++) {
					if(s.equals(str[i])) {
						my = i;
						break;
					}
				}
				if(my != -1) {
					com = (int) (Math.random() * 3);
					// 가위 0, 바위 1, 보 2
					res = (3 + my - com) % 3;
					if (res == 0) {
						System.out.println("사용자 = " + str[my] + " , 컴퓨터 = " + str[com] + ", " + "비겼습니다.");
					} else if (res == 1) {
						System.out.println("사용자 = " + str[my] + " , 컴퓨터 = " + str[com] + ", " + "사용자가 이겼습니다.");
					} else if (res == 2) {
						System.out.println("사용자 = " + str[my] + " , 컴퓨터 = " + str[com] + ", " + "사용자가 졌습니다.");
					}
				}else {
					System.out.println("잘못 입력했습니다 :)");
				}
			}
			catch(Exception e) {
				continue;
			}
		}
		
	}

}