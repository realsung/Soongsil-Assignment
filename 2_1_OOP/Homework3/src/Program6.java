import java.util.Scanner;

class Circle{
	private double x,y;
	private int radius;
	public Circle(double x, double y, int radius) {
		this.x = x;
		this.y = y;
		this.radius = radius;
	}
	public void show() {
		System.out.println("가장 면적인 큰 원은"+ " ("+this.x+","+this.y+")"+this.radius);
	}
	public double getCircle() {
		return (this.radius*this.radius*3.14);
	}
}

public class Program6 {

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		Circle c[] = new Circle[3];
		for(int i=0; i<c.length; i++) {
			System.out.print("x, y, radius >>");
			double x = scanner.nextDouble();
			double y = scanner.nextDouble();
			int r = scanner.nextInt();
			c[i] = new Circle(x, y, r);
		}
		int idx = -1;
		double maxim = 0.0;
		for(int i=0; i<c.length; i++) {
			if(maxim < c[i].getCircle()) {
				idx = i;
			}
		}
		if(idx != -1) c[idx].show();
		scanner.close();
	}

}