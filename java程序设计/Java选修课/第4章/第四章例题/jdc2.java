import java.io.*;

public class jdc2
{ 	
	public jdc2(int s,int w,int h){
		speed=s;weight=w;height=h;
	}
     void changSpeed(int newSpeed)          //方法定义。
     {     
       speed=newSpeed;
     } 
     int speed=10;                             //变量定义部分。
     int speed1;
     speed1=10;
     float getWeight()                      //方法定义。
     {  
          return weight;
     }
     float weight=20;                          //变量定义部分。
     float getHeight()                      //方法定义。
     {  
          return height;
     }
     float height=20;  
     	                      //变量定义部分。
     public static void main(String[] args){
     	jdc2 j=new jdc2(10,20,30);
     	j.speed=10998;
     	System.out.println(j.speed);
     	
     }
}

