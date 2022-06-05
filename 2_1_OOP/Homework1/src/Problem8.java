import java.util.Scanner;

public class Problem8 {

	public static boolean inRect(int x, int y, int rectx1, int recty1, int rectx2, int recty2) {
		if((x >= rectx1 && x <= rectx2) && (y >= recty1 && y <= recty2))
			return true;
		else
			return false;
	}
	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		int x1, y1, x2, y2;
		System.out.print("점 (x1,y1)의 좌표를 입력하시오>>");
		x1 = scan.nextInt();
		y1 = scan.nextInt();
		System.out.print("점 (x2,y2)의 좌표를 입력하시오>>");
		x2 = scan.nextInt();
		y2 = scan.nextInt();
		if(inRect(x1, y1, 100, 100, 200, 200) && inRect(x2, y2, 100, 100, 200, 200)) {
			System.out.println("직사각형과 충돌 안함");
		}else {
			System.out.println("직사각형과 충돌함");
		}
	}

}
