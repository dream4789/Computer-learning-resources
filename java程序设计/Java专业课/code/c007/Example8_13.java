import java.util.Scanner;

public class Example8_13 {
	public static void main(String[] args) {
		Scanner scanner=new Scanner(System.in);
		System.out.println("请输入参与人数：");
		//while (scanner.hasNext()){
		
		int number=scanner.nextInt();//参与人数
		System.out.println("请输入起始位置：");
		int start=scanner.nextInt();//起始报数位置
		System.out.println("请输入报数值：");
		int num=scanner.nextInt();//间隔数量
		People [] people=new People[number];
		System.out.println("请输入人员姓名：");
		for (int i=0;i<number;i++){
			people[i]=new People(i,true,scanner.next());
		}
		int count;//剩余的参与人数
		int n=0;//报数值
		int init=(start-1)%number;//报数的初始位置
		count=number;
		//int line=0;
		while (count>1){//如果剩余人数大于1，则继续报数
			
			if (!people[init].isFlag()){//如果当前人已被淘汰，则越过此人
				init=(init+1)%number;
				}
			else if(n<num-1){//如果当前人的报数值不是给定值，则继续
				n++;
				init=(init+1)%number;
			}
			else{people[init].setFlag(false);//如果当前人的报数值是给定值，则淘汰该人
				//line++;
				count--;//将剩余人数减一
				init=(init+1)%number;//继续下一个人报数
				n=0;//下一个人重新开始报数
				}
		}
		for(People a:people){
			if(a.isFlag()){//输出胜利者的位置，姓名
				System.out.println("胜利者是："+(a.getSerial()+1)+" "+a.getName());
			}
		//}
	}
	}
}
class People{
	int serial;
	boolean flag;
	String name;
	public People(){}
	
	public People(int serial, boolean flag, String name) {
		this.serial = serial;
		this.flag = flag;
		this.name = name;
	}

	public boolean isFlag() {
		return flag;
	}
	public void setFlag(boolean flag) {
		this.flag = flag;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public int getSerial(){
		return serial;
	}
	public void setSerial(int serial){
		this.serial=serial;
	}
