class 学生//父类
{
	String 学号;//学生共有的属性
	String 姓名;
	char 性别;
	int 年龄;
	
	//共有的操作
	void 设置学生信息(String no,String name,char gender,int age)
	{
		学号=no;
		姓名=name;
		性别=gender;
		年龄=age;
	}
	public String 学生信息()
	{
		String str=学号+" "+姓名+" ";
		str+=(性别=='m'?"男":"女")+年龄+"岁";
		return str;
	}	
}
class 中学生 extends 学生//子类定义
{
	int 数学,语文;//中学生课程
	
	void 填写中学生成绩(int math,int chinese)
	{
		数学=math;
		语文=chinese;
	}
	
	public String 中学生成绩()
	{
		String str="数学："+数学+",语文"+语文;
		return str;
	}
	void print()
	{
		System.out.print(学生信息()+" ");
		System.out.println(中学生成绩());
	}
}
class 大学生 extends 学生//子类定义
{
	int 高数,Java;//大学生课程
	
	void 填写大学生成绩(int math,int prog)
	{
		高数=math;
		Java=prog;
	}
	
	public String 大学生成绩()
	{
		String str="高等数学："+高数+",Java："+Java;
		return str;
	}
	
	void print()
	{
		System.out.print(学生信息()+" ");
		System.out.println(大学生成绩());
	}
}
public class Example5_02
{
	public static void main(String args[])
	{
		中学生张三=new 中学生();
		张三.设置学生信息("160101", "张三", 'f', 15);
		张三.填写中学生成绩(90, 91);
		
		大学生李四=new 大学生();
		李四.设置学生信息("0416010101", "李四", 'm', 19);
		李四.填写大学生成绩(80, 81);
		
		张三.print();
		李四.print();
	}
}
