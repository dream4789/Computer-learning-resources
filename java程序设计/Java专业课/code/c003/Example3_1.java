class Circle
{
    double x,y,r;//圆的位置坐标x、y、半径
    
Circle(double x1,double y1,double r1)
{
    x = x1;
    y = y1;
    r = r1;
}

double area()
{
    return 3.14*r*r;
}
}

class Rectangle
{
    double width,height;//矩形长、宽

Rectangle(double a,double b)
{
    width = a;
    height = b;
}

double area()
{
    return width*height;
}
}

class Triangle
{
    double a,b,c;//三角形三条边

Triangle(double a1,double b1,double c1)
{
    a = a1;
    b = b1;
    c = c1;
}

double area()
{
    double s = (a + b + c)/2;
    return Math.sqrt(s*(s-a)*(s-b)*(s-c));//用海伦公式求三角形面积，sqrt（）是计算平方根的方法
}
}


public class Example3_1
{
public static void main(String[] para)
{
    Circle c = new Circle(100,50,2.866);
    Rectangle rect = new Rectangle(5,4);
    Triangle tr = new Triangle(6,6,6);
    System.out.println("The area of the circle is: "+c.area());
    System.out.println("The area of the rectangle is: "+rect.area());
    System.out.println("The area of the triangle is: "+tr.area());
}
}
