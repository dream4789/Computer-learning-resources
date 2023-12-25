package ch7;
import java.util.*;
public class Example7_03
{
	public static void main(String[] args)
	{
		//被分解的字符串可以有若干空格和逗号
		String s="I am Jame  ,,,  you are Jerry,and he is Tom";
		//对s分解，以空格或逗号作为分隔符
		StringTokenizer fenxi=new StringTokenizer(s," ,");
		int number=fenxi.countTokens();//获取单词总数
		while(fenxi.hasMoreTokens())//是否还有单词
		{
			String str=fenxi.nextToken();//有，获得下一个单词
			System.out.print(str+",");
			//获得并输出剩余单词数
			System.out.println("还有"+fenxi.countTokens()+"个单词。");
		}
		System.out.println("总共单词数："+number);
	}
}
