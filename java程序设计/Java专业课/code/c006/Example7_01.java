package ch7;
public class Example7_01
{
	public static void main(String agrs[])
	{
		String str="People's Republic of China";
		
		String result="�ַ���"+str+"����";
		result=result+countUpperCase(str)+"����д��ĸ��";
		
		System.out.println(result);
	}
    private static int countUpperCase(String str)//��̬����
	{
		int count = 0;
		for(int i = 0;i < str.length(); i++)//����length()���ִ�����
		{
			char ch = str.charAt(i);//��ȡstr�е�i���ַ�
			if(Character.isUpperCase(ch))//��Character�෽���ж�ch�Ƿ�Ϊ��д
				count++; 
		}
		return count;
	}
}
