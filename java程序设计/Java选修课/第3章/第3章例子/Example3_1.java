import java.util.*;
import java.io.*;
public class Example3_1
{  
    public static void main (String args[ ])
    {
      Student ZHansan=new Student(1369755,"ռɽ");
      System.out.println(ZHansan instanceof Student);
    }
}

class Student{
	
	public int ID;
	public String name;
	Student(int i,String n){
		ID=i;name=n;
	}
}