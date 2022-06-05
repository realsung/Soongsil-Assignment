class Point{
	private int x, y;
	Point(){
		this.x = 0;
		this.y = 0;
	}
	Point(int x, int y){
		this.x = x;
		this.y = y;
	}
	public void move(int x1, int y1) {
		this.x = x1;
		this.y = y1;
	}
	public int getX() { return this.x; }
	public int getY() { return this.y; }
}

class PositivePoint extends Point{
	PositivePoint() {
		super();
	}
	PositivePoint(int x1, int y1){
		if(x1 >= 0 && y1 >= 0)
			super.move(x1, y1);
		else
			super.move(0,  0);
	}
	public String toString() {
		return "("+getX()+","+getY()+")";
	}
	public void move(int x1, int y1) {
		if(x1 >= 0 && y1 >= 0) {
			super.move(x1, y1);
		}else {
			return;
		}
	}   
}

public class Program8 {

	public static void main(String[] args) {
		PositivePoint p = new PositivePoint();
		p.move(10, 10);
		System.out.println(p.toString() + "입니다.");
		
		p.move(-5, 5);
		System.out.println(p.toString() + "입니다.");
		
		PositivePoint p2 = new PositivePoint(-10, -10);
		System.out.println(p2.toString() + "입니다");
	}

}