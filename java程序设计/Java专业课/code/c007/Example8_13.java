import java.util.Scanner;

public class Example8_13 {
	public static void main(String[] args) {
		Scanner scanner=new Scanner(System.in);
		System.out.println("���������������");
		//while (scanner.hasNext()){
		
		int number=scanner.nextInt();//��������
		System.out.println("��������ʼλ�ã�");
		int start=scanner.nextInt();//��ʼ����λ��
		System.out.println("�����뱨��ֵ��");
		int num=scanner.nextInt();//�������
		People [] people=new People[number];
		System.out.println("��������Ա������");
		for (int i=0;i<number;i++){
			people[i]=new People(i,true,scanner.next());
		}
		int count;//ʣ��Ĳ�������
		int n=0;//����ֵ
		int init=(start-1)%number;//�����ĳ�ʼλ��
		count=number;
		//int line=0;
		while (count>1){//���ʣ����������1�����������
			
			if (!people[init].isFlag()){//�����ǰ���ѱ���̭����Խ������
				init=(init+1)%number;
				}
			else if(n<num-1){//�����ǰ�˵ı���ֵ���Ǹ���ֵ�������
				n++;
				init=(init+1)%number;
			}
			else{people[init].setFlag(false);//�����ǰ�˵ı���ֵ�Ǹ���ֵ������̭����
				//line++;
				count--;//��ʣ��������һ
				init=(init+1)%number;//������һ���˱���
				n=0;//��һ�������¿�ʼ����
				}
		}
		for(People a:people){
			if(a.isFlag()){//���ʤ���ߵ�λ�ã�����
				System.out.println("ʤ�����ǣ�"+(a.getSerial()+1)+" "+a.getName());
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
