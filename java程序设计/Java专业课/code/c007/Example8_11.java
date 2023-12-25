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
		ArrayList<Student> stu = new ArrayList<Student>();//����ѧ���б�
		stu.add(st0);//���б������ѧ������
		stu.add(st1);
		stu.add(st2);
		stu.add(st3);
		stu.add(st4);
		System.out.println("����ǰ������");
		for (Student st:stu){
			st.display();
		}
		Collections.sort(stu);//�ڲ���������˳��
		//Collections.sort(stu,new StudentComp());//�ⲿ��������˳��
		System.out.println("�����������");
		for (Student st:stu){
			st.display();
		}
	}
}

class Student implements Comparable<Student>{
//����ѧ���࣬��ʵ��Comparable�ӿڣ���ѧ������
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
	public int compareTo(Student stu){//��д�ӿڷ���
		return (number.compareTo(stu.number));//��ѧ�Ŵ�С��������
	}	
}

class StudentComp implements Comparator<Student>{
//�̳в�ʵ��Comparator�ӿڣ��������ⲿ�Ƚ��������������������
		public int compare(Student stu1,Student stu2){
			if (stu1.getAge()!=stu2.getAge()){
				return (stu1.getAge()-stu2.getAge());
			}
			else{
				return (stu1.getNumber().compareTo(stu2.getNumber()));
			}
		}
	}
