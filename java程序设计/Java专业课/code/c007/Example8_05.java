import java.util.*;
public class Example8_05 {
public static void main(String[] args) {
		ArrayList<String> roster = new ArrayList<String>();//����һ��ArrayList����
		roster.add("zhang");//��������һ��������
		roster.add("wang");
		roster.add("li");
		roster.add("zhao");
		System.out.print("roster =");//ͨ����һ��ȡ���֣���ʾ��������
		for (int i=0;i<roster.size();i++){
			System.out.print(roster.get(i)+" ");
		}
		System.out.println();
		System.out.println("roster ="+roster);//ֱ����ʾ��̬��������

		int number=1;
		for(int i=0;i<roster.size();i+=2){//��ÿ������ǰ��������
			roster.add(i,String.valueOf(number));
			number++;
		}
		System.out.println("new roster ="+roster);//����µ���������

		roster.remove(0);//ɾ����һ���˵����
		roster.remove(0);//ɾ����һ���˵�����
		System.out.println("remove one person,roster ="+roster);//�����������
	}
}
