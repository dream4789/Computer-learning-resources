package ch7;
import java.util.Date;
import java.util.Formatter; 
public class Example7_10
{ 
	public static void main(String[] args) 
	{
		Formatter formatter =new Formatter(System.out);//ע�����
		//��ʽ������ַ���������,%��������ʽ������
		//-: ָ��Ϊ����룬Ĭ���Ҷ��� 
		//10��������Ϊ10,ʵ������ռ����������ո���������ȫ����� 
		//.6���ڴ˱�ʾ�������6������ַ�����������Ǹ������֣����ʾ
		//С��������ʾ��λ�� 
		//s����ʾ����������ַ�����1$��ȡ��һ����������123
		System.out.println("���������ʽ����");
		formatter.format("%1$2s %2$10.6s\n", "123", "456.678");
		System.out.println("-----------------------");
		
		Date date = new Date();
		System.out.println("��ǰ���ڣ�"+date);
		//���ڵĸ�ʽ����������ʽ������洢��һ���ַ���������
		//1$��ȡ��һ����������date��t���ڣ�Y��m��e�ֱ�Ϊ�ꡢ�¡���
		String s = String.format("��ǰ���ڸ�ʽ��:%1$tY-%1$tm-%1$te", date);
		System.out.println(s);
		System.out.println("-----------------------");
		
		//����ʽ���Ľ���洢���ַ���
		String fs = String.format("���տ���(%.2f,%d)", 173.278, 65);
		System.out.println(fs);
	} 
}
