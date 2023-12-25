package C004_Clz_Obj_2;
/**
 * project_name: Java_Ex
 *
 * package_name: C004_Clz_Obj_2 
 *
 * author:  DarlingKe
 *
 * created Time: 2017-12-29 上午10:10:45 
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
		ShowMessage sm;                 //声明接口变量sm
        sm=new TV();                    //接口变量sm中存放对象的引用
        sm.showTradeMark();              //接口sm回调showTradeMark()方法
        sm=new PC();                    //接口变量sm中存放对象的引用
        sm.showTradeMark();              //接口回调
	}	
}

interface ShowMessage{
    void showTradeMark();
}
class TV implements ShowMessage{
    public void showTradeMark(){
         System.out.println("我是电视机");
    }
}
class PC implements ShowMessage{
     public void showTradeMark(){
         System.out.println("我是电脑");
    }
}


 