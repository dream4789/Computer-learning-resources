public class Example2_04
{
	publicstaticvoid main(String args[])
	{
		int a=123,b=456;
		
		System.out.printf("1:a>b=%b,a<b=%B%n",a>b,a<b);//注意换行
		System.out.printf("2:%-8d,%8d",a,b);//无换行
		System.out.print('\n');//换行
		System.out.printf("3:%d,%o,%x\n", -1,-1,-1);
		System.out.printf("4:%(d,%#o,%#x\n",-1,-1,-1);
		System.out.printf("5:%2d,%8d,%08d\n", a,b,b);
		
		double d=1234.45678901;
		System.out.printf("6:%f,%.2f,%8.5f\n",d,d,d);
		System.out.printf("7:%E,%8.2e,%15.6E\n",d,d,d);
		System.out.printf("8:%a\n",99.0);
		
		String str="Beijing";
		System.out.printf("9:addr——%s\n",str);//注意大小写
		System.out.printf("10:addr——%20S\n",str);
		
		long l=123456778899L;
		System.out.printf("11:%,+d\n",l);
	}
}
