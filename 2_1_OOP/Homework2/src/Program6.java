import java.util.Scanner;

public class Program6 {

	public static void main(String[] args) {
		int[] unit = {50000, 10000, 1000, 500, 100, 50, 10, 1};
		Scanner sc = new Scanner(System.in);
		System.out.print("금액을 입력하시오>>");
		int money = sc.nextInt();
		for(int i : unit) {
			if(money / i != 0) {
				System.out.println(i + "원 짜리 : " + money / i);
				money %= i;
			}
		}

	}

}