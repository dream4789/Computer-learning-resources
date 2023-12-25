import java.util.ArrayList;
import java.util.Iterator;
import java.util.Scanner;

public class Example8_13_2 {

	public static void main(String[] args) {
		// 圆圈报数游戏：n个人围坐一圈，从指定的位置m开始报数，
		//每报到数字k或k的倍数，则该人淘汰。求最后的胜利者。
		Scanner reader = new Scanner(System.in);
		System.out.println("请按顺序输入 玩游戏的人员姓名，输入0结束");		
		ArrayList<String> array=new ArrayList<String>();
		String name;
		name = reader.next();
		while(!name.equals("0")){
			array.add(name);
			name = reader.next();
		}
		System.out.println("请输入报数的开始位置:");
		int begin=reader.nextInt();
		System.out.println("请输入报数值：");
		int step=reader.nextInt();
		System.out.println("游戏开始：");
		int i=0;//步距初始值
		int k=0;//起始位置指针
		while(array.size()>1){//剩余人数多于1人则游戏继续
		Iterator<String> iterator = array.iterator();//定义数组游标
		while(iterator.hasNext()){
			if (k!=begin-1){//确定初始位置
				k++;
				iterator.next();
			}
			else{
				if(i==step-1){//满足间隔条件的人退出游戏圈
					System.out.println("出局："+iterator.next());
					iterator.remove();					
					i=0;//步距清零，重新计步
				}
				else{
					iterator.next();
					i++;
					
				}
			}
		}
	}
		System.out.println("胜利者是： "+array.get(0));
	}

}
