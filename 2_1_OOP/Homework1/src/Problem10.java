import java.util.Scanner;

public class Problem10 {

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		int x1, y1, x2, y2;
		int radius1, radius2, res;
		System.out.print("첫번째 원의 중심과 반지름 입력>>");
		x1 = scan.nextInt();
		y1 = scan.nextInt();
		radius1 = scan.nextInt();
		System.out.print("두번째 원의 중심과 반지름 입력>>");
		x2 = scan.nextInt();
		y2 = scan.nextInt();
		radius2 = scan.nextInt();
		if(Math.sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)) <= radius1 + radius2) {
			System.out.println("두 원은 서로 겹친다.");
		}else {
			System.out.println("두 원은 서로 안겹친다.");
		}
	}

}
