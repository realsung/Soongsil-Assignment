import java.util.Scanner;

public class Problem6 {

	public static void main(String[] args) {
		int n, cnt=0;
		int []m = {3, 6, 9};
		Scanner scan = new Scanner(System.in);
		System.out.print("1~99 사이의 정수를 입력하시오>>");
		n = scan.nextInt();
		
		for(int i : m) {
			if((n / 10) == i) {
				cnt++;
				break;
			}
		}
		for(int i: m) {
			if((n % 10) == i) {
				cnt++;
				break;
			}
		}
		if(cnt == 1)
			System.out.println("박수짝");
		else if(cnt == 2)
			System.out.println("박수짝짝");
	}

}
