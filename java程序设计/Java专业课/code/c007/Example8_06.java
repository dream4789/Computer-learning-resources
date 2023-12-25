import java.util.LinkedList;
import java.util.Scanner;
public abstract class Example8_06 {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		System.out.println("Please input a number:");
		int mixNumber = scanner.nextInt();//输入给定范围正整数
		LinkedList<Integer> numbers = new LinkedList<Integer>();//创建待查列表
		LinkedList<Integer> prim = new LinkedList<Integer>();//创建素数列表
		for (int i=2;i<mixNumber;i++){
			numbers.add(i);
		}
		
		int first=0;
		while (numbers.size()>0){
			first=numbers.removeFirst();//将待查列表的首个数字移到素数列表
			prim.add(first);
			for (int i=0;i<numbers.size();){//删除待查列表中所有当前素数的倍数数值
				int num =numbers.get(i);
				if (num % first==0){
					numbers.remove(i);
				}
				else{
					i++;
				}					
			}
		}
		System.out.println(prim);
	}
}
