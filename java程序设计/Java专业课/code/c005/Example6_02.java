import java.util.InputMismatchException;
import java.util.Scanner;
public class Example6_02 {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		double sum = 0;
		int i=1;
		try{
			System.out.println("������ǰ6���µĹ�������:");
		while (i<=6){
			double in = scanner.nextDouble();
			sum+=in;
			i++;
		}		
		}
		catch(InputMismatchException e){
		System.out.println("��"+i+"���µ������������!");
		}
		finally{
		System.out.println("��ǰ������ "+(i-1)+" ���µ����ݣ�ƽ������Ϊ: "+sum/(i-1));
		}
	}
}
