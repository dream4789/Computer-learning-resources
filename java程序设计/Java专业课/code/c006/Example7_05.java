package ch7;
import java.util.Scanner;
public class Example7_05 {
	public static void main(String[] args)
	{
		String bill="����3200.00Ԫ���ֻ�2200.00Ԫ���ʼǱ�4200.00Ԫ�����120.25Ԫ";
		Scanner reader=new Scanner(bill);//���ַ�����Ϊ�����豸
		double total=0;//�ܻ���
		//������ʽ�����ݷָ����
		reader.useDelimiter("[^0-7.]+");                     
		while(reader.hasNextDouble())//���л������ݣ�
			total+=reader.nextDouble();//�У���������ۼ�
				System.out.println("�ܻ��ѣ�"+total+"Ԫ");
	}                                                   
}
