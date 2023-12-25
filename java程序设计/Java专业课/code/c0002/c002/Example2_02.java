import java.util.Scanner;//必须写上这条语句
public class Example2_02
{
	Public static void main(String args[])
	{
		boolean bool;
		byte b;
		short s;
		int i;
		long lg;
		float f;
		double d;
		String str;
		
		Scanner reader=new Scanner(System.in);
		
		bool=reader.nextBoolean();
		b=reader.nextByte();
		s=reader.nextShort();
		i=reader.nextInt();
		lg=reader.nextLong();
		f=reader.nextFloat();
		d=reader.nextDouble();
		str=reader.nextLine();
		
		System.out.println("输出：");
		System.out.println("\tbool="+bool);
		System.out.println("\tb="+b);
		System.out.println("\ts="+s);
		System.out.println("\ti="+i);
		System.out.println("\tlg="+lg);
		System.out.println("\tf="+f);
		System.out.println("\td="+d);
		System.out.println("\tstr="+str);
	}
}
