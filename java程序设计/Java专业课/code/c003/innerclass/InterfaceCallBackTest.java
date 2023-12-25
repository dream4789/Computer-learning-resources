package C004_Clz_Obj_2;
/**
 * project_name: Java_Ex
 *
 * package_name: C004_Clz_Obj_2 
 *
 * author:  DarlingKe
 *
 * created Time: 2017-12-29 ����10:10:45 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: InterfaceCallBackTest.java  
 *
 * Description:  
 *
 */
public class InterfaceCallBackTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ShowMessage sm;                 //�����ӿڱ���sm
        sm=new TV();                    //�ӿڱ���sm�д�Ŷ��������
        sm.showTradeMark();              //�ӿ�sm�ص�showTradeMark()����
        sm=new PC();                    //�ӿڱ���sm�д�Ŷ��������
        sm.showTradeMark();              //�ӿڻص�
	}	
}

interface ShowMessage{
    void showTradeMark();
}
class TV implements ShowMessage{
    public void showTradeMark(){
         System.out.println("���ǵ��ӻ�");
    }
}
class PC implements ShowMessage{
     public void showTradeMark(){
         System.out.println("���ǵ���");
    }
}


 