package ch7;
public class Example7_06
{
	public static void main(String[] args)
	{
		//第1个字符必须是$、_、字母或汉字
		String regex="[\\p{Alpha}$_\u4E00-\u9FFF]{1}";
		//其后的若干字符可以是$、_、字母、数字或汉字
		regex+="[$_\\p{Alnum}\u4E00-\u9FFF]*";
		
		String id[]={"$$ab","姓名","-x","i+j","a_12$3",
			"6class","_123_","$年龄","25","a123x","i"};
		
		for(String str:id)
			//matches方法可以判断str是否与regex匹配
if(str.matches(regex)) 
				System.out.println(str+" 合法");
			else
				System.out.println(str+" 不合法");
	}
}
