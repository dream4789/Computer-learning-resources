import java.util.HashSet;
import java.util.TreeSet;

public class Example8_07 {

	public static void main(String[] args) {
		HashSet<String> race0 = new HashSet<String>();//������һ����������
		HashSet<String> race1 = new HashSet<String>();//�����ڶ�����������
		race0.add("wu");//���һ�������������Ա����4��
		race0.add("wang");
		race0.add("li");
		race0.add("zhang");
		race1.add("zhao");//��ڶ��������������Ա����4��
		race1.add("wang");
		race1.add("li");
		race1.add("liu");
		HashSet race = new HashSet(race0);
		race.addAll(race1);//�����������ϲ�
		System.out.println("�༶��������Ϊ "+race.size()+" ��");
		TreeSet list = new TreeSet(race);//����Ա��������TreeSet���϶����Զ��������
		System.out.println("������Ա: ");
		for (String s:list){//���������Ա����
			System.out.println(s);
		}
	}

}
