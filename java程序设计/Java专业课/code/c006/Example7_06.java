package ch7;
public class Example7_06
{
	public static void main(String[] args)
	{
		//��1���ַ�������$��_����ĸ����
		String regex="[\\p{Alpha}$_\u4E00-\u9FFF]{1}";
		//���������ַ�������$��_����ĸ�����ֻ���
		regex+="[$_\\p{Alnum}\u4E00-\u9FFF]*";
		
		String id[]={"$$ab","����","-x","i+j","a_12$3",
			"6class","_123_","$����","25","a123x","i"};
		
		for(String str:id)
			//matches���������ж�str�Ƿ���regexƥ��
if(str.matches(regex)) 
				System.out.println(str+" �Ϸ�");
			else
				System.out.println(str+" ���Ϸ�");
	}
}
