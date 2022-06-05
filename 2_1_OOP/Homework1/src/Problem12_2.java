import java.util.Scanner;
public class Problem12_2 {

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		System.out.print("연산>>");
		String[] s1 = scan.nextLine().split(" ");
		int n1 = Integer.parseInt(s1[0]);
		int n2 = Integer.parseInt(s1[2]);
		String cal = s1[1];
		switch(cal) {
		case "+":
			System.out.println(n1+s1[1]+n2+"의 계산 결과는 "+(n1+n2));
			break;
		case "-":
			System.out.println(n1+s1[1]+n2+"의 계산 결과는 "+(n1-n2));
			break;
		case "*":
			System.out.println(n1+s1[1]+n2+"의 계산 결과는 "+(n1*n2));
			break;
		case "/":
			if(n2 == 0)
				System.out.println("0으로 나눌 수 없습니다.");
			System.out.println(n1+s1[1]+n2+"의 계산 결과는 "+(n1/n2));
			break;
		}
	}

}
