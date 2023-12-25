import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public class Example8_11 {
	public static void main(String[] args) {
		Student st0 = new Student("1604010510","zhang",18,"male","computer");
		Student st1 = new Student("1604010501","wang",19,"male","computer");
		Student st2 = new Student("1503010201","li",18,"male","math");
		Student st3 = new Student("1605010315","zhao",18,"female","software");
		Student st4 = new Student("1604010513","liu",17,"male","computer");
		ArrayList<Student> stu = new ArrayList<Student>();//创建学生列表
		stu.add(st0);//向列表中添加学生对象
		stu.add(st1);
		stu.add(st2);
		stu.add(st3);
		stu.add(st4);
		System.out.println("排序前名单：");
		for (Student st:stu){
			st.display();
		}
		Collections.sort(stu);//内部定义排序顺序
		//Collections.sort(stu,new StudentComp());//外部定义排序顺序
		System.out.println("排序后名单：");
		for (Student st:stu){
			st.display();
		}
	}
}

class Student implements Comparable<Student>{
//定义学生类，并实现Comparable接口，按学号排序
	private String number;
	private String name;
	private int age;
	private String sex;
	private String major;
	public Student(String number, String name, int age, String sex,String major) {
		super();
		this.number = number;
		this.name = name;
		this.age = age;
		this.sex = sex;
		this.major = major;
	}
	public String getNumber() {
		return number;
	}
	public String getName() {
		return name;
	}
	public int getAge() {
		return age;
	}
	public void display(){
		System.out.printf("number:%s; name:%-6s; age:%d; 
						major:%-8s\n",number,name,age,major);
	}
	public int compareTo(Student stu){//重写接口方法
		return (number.compareTo(stu.number));//按学号从小到大排序
	}	
}

class StudentComp implements Comparator<Student>{
//继承并实现Comparator接口，来创建外部比较器，按年龄和姓名排序
		public int compare(Student stu1,Student stu2){
			if (stu1.getAge()!=stu2.getAge()){
				return (stu1.getAge()-stu2.getAge());
			}
			else{
				return (stu1.getNumber().compareTo(stu2.getNumber()));
			}
		}
	}
