import java.io.*;

public class jdc2
{ 	
	public jdc2(int s,int w,int h){
		speed=s;weight=w;height=h;
	}
     void changSpeed(int newSpeed)          //�������塣
     {     
       speed=newSpeed;
     } 
     int speed=10;                             //�������岿�֡�
     int speed1;
     speed1=10;
     float getWeight()                      //�������塣
     {  
          return weight;
     }
     float weight=20;                          //�������岿�֡�
     float getHeight()                      //�������塣
     {  
          return height;
     }
     float height=20;  
     	                      //�������岿�֡�
     public static void main(String[] args){
     	jdc2 j=new jdc2(10,20,30);
     	j.speed=10998;
     	System.out.println(j.speed);
     	
     }
}

