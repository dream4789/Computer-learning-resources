package ch7;
import java.util.*;
public class Example7_03
{
	public static void main(String[] args)
	{
		//���ֽ���ַ������������ɿո�Ͷ���
		String s="I am Jame  ,,,  you are Jerry,and he is Tom";
		//��s�ֽ⣬�Կո�򶺺���Ϊ�ָ���
		StringTokenizer fenxi=new StringTokenizer(s," ,");
		int number=fenxi.countTokens();//��ȡ��������
		while(fenxi.hasMoreTokens())//�Ƿ��е���
		{
			String str=fenxi.nextToken();//�У������һ������
			System.out.print(str+",");
			//��ò����ʣ�൥����
			System.out.println("����"+fenxi.countTokens()+"�����ʡ�");
		}
		System.out.println("�ܹ���������"+number);
	}
}
