import java.util.Scanner;

public class Program4 {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		System.out.print("소문자 알파벳 하나를 입력하시오>>");
		char b = sc.next().charAt(0);
		while(b != 'a'){
	      	for(int i = 'a'; i<=b; i++){
        		System.out.print((char)i);
      		}
      		b--;
      		System.out.println();
    	}
    	System.out.println('a'); 
	}
}