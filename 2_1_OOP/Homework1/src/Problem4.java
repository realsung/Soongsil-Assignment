import java.util.Arrays;
import java.util.Scanner;

public class Problem4 {

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		int []n = new int[3];
		System.out.print("정수 3개 입력>>");
		for(int i=0; i<3; i++)
			n[i] = scan.nextInt();
		Arrays.sort(n);
		System.out.println("중간 값은 " + n[1]);
	}

}
