public classExample2_28
{
	public static void main(String args[])
	{
		int i;
		int a[]={10,20,30,40,50};
		int b[]={-15,-25,-35,-45,-55,-65,-75};
		
		System.out.println("数组a和数组b的元素：");
		
		for(i=0;i<a.length;i++)
			System.out.printf("%4d", a[i]);
		System.out.println();
		
		for(i=0;i<b.length;i++)
			System.out.printf("%4d", b[i]);
		System.out.println();
		
		a=b;//赋值后，a的值与b的值相同，都表示第2个数组
		
		System.out.println("执行\"a=b;\"后,数组a和数组b的元素：");
		
		for(int x:a)//增强型循环
			System.out.printf("%4d", x);
		System.out.println();
		
		for(int x:b)//增强型循环
			System.out.printf("%4d", x);
		System.out.println();		
	}
}
