package ch7;
public class Example7_02 
{
	public static void main(String[] args)
	{
		String str="This is ana book.";
		String subStr="an";
		
		String result="��"+str+"��ɾ��"+subStr;
		result=result+"����ִ�"+delChars(str,subStr);
		
		System.out.println(result);
	}
    private static String delChars(String str,String chars)//��̬����
	{
		int index = 0;
		int len = 0;
         String s1,s2;
		index = str.indexOf(chars);//chars��str�г��ֵ�λ��
        if(index != -1)//str�����Ӵ�chars
		{
              len = chars.length();//chars�ĳ���
			s1 = str.substring(0,index);//��str����ȡ��0��index-1λ���е��Ӵ�
			s2 = str.substring(index+len);//��str����ȡ��index+len��������Ӵ�
			s1 = s1 + s2;//�����Ӵ�����
		}
		else//str��û�����Ӵ�chars
s1 = "No"+chars+"found.";
        
		return s1;
	}
}
