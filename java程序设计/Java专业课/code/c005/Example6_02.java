import java.util.InputMismatchException;
import java.util.Scanner;
public class Example6_02 {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		double sum = 0;
		int i=1;
		try{
			System.out.println("请输入前6个月的工资输入:");
		while (i<=6){
			double in = scanner.nextDouble();
			sum+=in;
			i++;
		}		
		}
		catch(InputMismatchException e){
		System.out.println("第"+i+"个月的数据输入错误!");
		}
		finally{
		System.out.println("当前共输入 "+(i-1)+" 个月的数据，平均收入为: "+sum/(i-1));
		}
	}
}
