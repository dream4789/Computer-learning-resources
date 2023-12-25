Public class Example2_01
{
	Public static void main(String args[])
	{
		//注意下面两条语句的不同
		System.out.println("He said:\"I'm learning Java.\"");
		System.out.print("He said:\"I\'m learning Java.\"\n");
		
		int a=123,b=456;//下面用3个退格转义字符将789删除
		System.out.println(a+"+"+b+"=789"+"\b\b\b"+(a+b));
		
		System.out.println();//只输出一个换行
		//利用制表符控制间距
		System.out.println("\t学号\t姓名\t年龄\t专业\t通讯地址");
		System.out.println("\n\t0001\t张三\t18  \t计算机\t学府路1号");
		System.out.println("\t0002\t李四\t19  \t计算机\t学府路1号");
	}
}
