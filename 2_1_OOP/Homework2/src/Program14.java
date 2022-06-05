import java.util.Scanner;

public class Program14 {

	public static void main(String[] args) {
		String course[] = {"Java", "C++", "HTML5", "컴퓨터구조", "안드로이드" };
		int score[] = {95,88,76,62,55};
		String s, sub;
		int idx;
		Scanner sc = new Scanner(System.in);
		while(true) {
			System.out.print("과목 이름>>");
			s = sc.next();
			if(s.equals("그만"))
				break;
			idx = -1;
			for(int i=0; i<course.length; i++) {
				if(course[i].equals(s)) {
					idx = i;
					break;
				}
			}
			if(idx != -1) {
				System.out.println(course[idx] + "의 점수는 " + score[idx]);
			}else {
				System.out.println("없는 과목입니다.");
			}
		}

	}

}