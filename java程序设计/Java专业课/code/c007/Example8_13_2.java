import java.util.ArrayList;
import java.util.Iterator;
import java.util.Scanner;

public class Example8_13_2 {

	public static void main(String[] args) {
		// ԲȦ������Ϸ��n����Χ��һȦ����ָ����λ��m��ʼ������
		//ÿ��������k��k�ı������������̭��������ʤ���ߡ�
		Scanner reader = new Scanner(System.in);
		System.out.println("�밴˳������ ����Ϸ����Ա����������0����");		
		ArrayList<String> array=new ArrayList<String>();
		String name;
		name = reader.next();
		while(!name.equals("0")){
			array.add(name);
			name = reader.next();
		}
		System.out.println("�����뱨���Ŀ�ʼλ��:");
		int begin=reader.nextInt();
		System.out.println("�����뱨��ֵ��");
		int step=reader.nextInt();
		System.out.println("��Ϸ��ʼ��");
		int i=0;//�����ʼֵ
		int k=0;//��ʼλ��ָ��
		while(array.size()>1){//ʣ����������1������Ϸ����
		Iterator<String> iterator = array.iterator();//���������α�
		while(iterator.hasNext()){
			if (k!=begin-1){//ȷ����ʼλ��
				k++;
				iterator.next();
			}
			else{
				if(i==step-1){//���������������˳���ϷȦ
					System.out.println("���֣�"+iterator.next());
					iterator.remove();					
					i=0;//�������㣬���¼Ʋ�
				}
				else{
					iterator.next();
					i++;
					
				}
			}
		}
	}
		System.out.println("ʤ�����ǣ� "+array.get(0));
	}

}
