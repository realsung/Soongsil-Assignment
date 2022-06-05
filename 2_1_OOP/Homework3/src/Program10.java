import java.util.Scanner;

class Dictionary{
	private static String[] kor = {"사랑", "아기", "돈", "미래", "희망" };
	private static String[] eng = {"love", "baby", "money", "future", "hope" };
	public static String kor2Eng(String word) {
		int idx = 0;
		for(String i: kor) {
			if(i.equals(word)) {
				return eng[idx];
			}
			idx++;
		}
		return null;
	}
}

class DicApp{
	
}

public class Program10 {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		System.out.println("한영 단어 검색 프로그램입니다.");
		while(true) {
			System.out.print("한글 단어?");
			String inp = sc.next();
			if(inp.equals("그만")) break;
			String get = Dictionary.kor2Eng(inp);
			if(get != null){
				System.out.println(inp + "은 " + Dictionary.kor2Eng(inp));
			}else {
				System.out.println(inp + "은 저의 사전에 없습니다.");
			}
		}
	}
}