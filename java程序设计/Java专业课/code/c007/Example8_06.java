import java.util.LinkedList;
import java.util.Scanner;
public abstract class Example8_06 {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		System.out.println("Please input a number:");
		int mixNumber = scanner.nextInt();//���������Χ������
		LinkedList<Integer> numbers = new LinkedList<Integer>();//���������б�
		LinkedList<Integer> prim = new LinkedList<Integer>();//���������б�
		for (int i=2;i<mixNumber;i++){
			numbers.add(i);
		}
		
		int first=0;
		while (numbers.size()>0){
			first=numbers.removeFirst();//�������б���׸������Ƶ������б�
			prim.add(first);
			for (int i=0;i<numbers.size();){//ɾ�������б������е�ǰ�����ı�����ֵ
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
