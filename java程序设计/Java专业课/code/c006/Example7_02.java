package ch7;
public class Example7_02 
{
	public static void main(String[] args)
	{
		String str="This is ana book.";
		String subStr="an";
		
		String result="从"+str+"中删除"+subStr;
		result=result+"后的字串"+delChars(str,subStr);
		
		System.out.println(result);
	}
    private static String delChars(String str,String chars)//静态方法
	{
		int index = 0;
		int len = 0;
         String s1,s2;
		index = str.indexOf(chars);//chars在str中出现的位置
        if(index != -1)//str中有子串chars
		{
              len = chars.length();//chars的长度
			s1 = str.substring(0,index);//在str中提取从0到index-1位置中的子串
			s2 = str.substring(index+len);//在str中提取从index+len后的所有子串
			s1 = s1 + s2;//两个子串连接
		}
		else//str中没有有子串chars
s1 = "No"+chars+"found.";
        
		return s1;
	}
}
