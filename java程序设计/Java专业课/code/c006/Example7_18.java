package ch7;
class Point{
	int x,y;
	Point(){}
	Point(int x,int y){
		this.x = x;
		this.y = y;
	}
	
	@Override
	public String toString() {
		return "[ "+ x +" , " +y+" ]";
	}
}
public class Example7_18 {
	public static void main(String[] args) {
		Point p1 = new Point();
		Point p2 = new Point(10,20);
		System.out.println(p1);
		System.out.println(p2);
}                                         
}
