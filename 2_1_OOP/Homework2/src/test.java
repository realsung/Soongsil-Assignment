import java.util.Scanner;
public class test {
    public static void main(String[] args) {
        String course [] = {"java", "C++", "HTML5", "컴퓨터구조", "안드로이드"};
        int score [] = {95, 88, 76, 62, 55};
        Scanner a = new Scanner(System.in);
        String s = "";
        int i;
        while(true){
            System.out.print("과목 이름>>");
            s = a.next();
            if(s.equals("그만")) break;
            int idx = -1;
            for(i = 0; i<5; i++){
                if(course[i].equals(s)){
                	idx = i;
                	break;
                }
            }
            if(idx == -1) {
            	System.out.println("없는 과목입니다.");
            }else {
            	System.out.println(course[i]+ "의 점수는" + score[i] );
            }

        }
    }
}