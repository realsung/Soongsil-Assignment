import java.util.ArrayList;
import java.util.Scanner;

public class Program8 {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		System.out.print("정수 몇개?");
		int n = sc.nextInt();
		int t;
		ArrayList<Integer> l = new ArrayList<>();
		while(l.size() != n) {
			t = (int)(Math.random()*100 + 1);
			if(!l.contains(t)) {
				l.add(t);
			}
		}
		for(int i=0; i<l.size(); i++) {
			if(i != 0 && i % 10 == 0)
				System.out.println();
			System.out.print(l.get(i) + " ");
		}
		
	}
}