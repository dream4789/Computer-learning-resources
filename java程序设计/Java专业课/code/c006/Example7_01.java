package ch7;
public class Example7_01
{
	public static void main(String agrs[])
	{
		String str="People's Republic of China";
		
		String result="字符串"+str+"中有";
		result=result+countUpperCase(str)+"个大写字母。";
		
		System.out.println(result);
	}
    private static int countUpperCase(String str)//静态方法
	{
		int count = 0;
		for(int i = 0;i < str.length(); i++)//方法length()测字串长度
		{
			char ch = str.charAt(i);//获取str中第i个字符
			if(Character.isUpperCase(ch))//用Character类方法判断ch是否为大写
				count++; 
		}
		return count;
	}
}
