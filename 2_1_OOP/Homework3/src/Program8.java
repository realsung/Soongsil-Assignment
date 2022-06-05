import java.util.*;

class PhoneBook{
	private String name;
	private String tel;
	public PhoneBook(String name, String tel) {
		this.name = name;
		this.tel = tel;
	}  
	public String getName() {
		return this.name;
	}
	public String getTel() {
		return this.tel;
	}
}

class Phone{
	Scanner sc = new Scanner(System.in);
	private PhoneBook pb[];
	private int peopleCnt;
	
	public void setPhone() {
		System.out.print("인원수>>");
		peopleCnt = sc.nextInt();
		pb = new PhoneBook[peopleCnt];
		for(int i=0; i<peopleCnt; i++) {
			System.out.print("이름과 전화번호(이름과 번호는 빈 칸없이 입력)>>");
			String name = sc.next();
			String tel = sc.next();
			pb[i] = new PhoneBook(name, tel);
		}
		System.out.println("저장되었습니다...");
	}
	public void searchPhone() {
		while(true) {
			System.out.print("검색할 이름>>");
			String inp = sc.next();
			if(inp.equals("그만")) {
				break;
			}
			int idx = -1;
			for(int i=0; i<pb.length; i++) {
				if(inp.equals(pb[i].getName())) {
					idx = i;
				}
			}
			if(idx != -1) {
				System.out.println(pb[idx].getName() + "의 번호는 " + pb[idx].getTel() + " 입니다.");
			}else {
				System.out.println(inp + " 이 없습니다.");
			}
		}
	}
}

public class Program8 {

	public static void main(String[] args) {
		Phone pb = new Phone();
		pb.setPhone();
		pb.searchPhone();
		
	}

}