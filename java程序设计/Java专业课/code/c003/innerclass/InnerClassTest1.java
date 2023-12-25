package C004_Clz_Obj_2;

/**
 * project_name: Java_Ex
 *
 * package_name: C004_Clz_Obj_2 
 *
 * author:  DarlingKe
 *
 * created Time: 2017-12-30 下午12:01:30 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: InnerClassTest1.java  
 *
 * Description:  
 *
 */
public class InnerClassTest1 {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		China china=new China();
        china.f();
        china.dalian.g();
	}

}
class NorthEast{
    String land="黑土地";
}
class China{
    int x=10,y=10;
    LiaoNing dalian;             //内部类声明对象的作为外嵌类的成员
    China(){
        dalian=new LiaoNing();
    }
    void f(){
        System.out.println("我是中国");
        dalian.speak();
    } 
    class LiaoNing extends NorthEast{      //内部类的声明
        int z;
        void speak(){
            System.out.println("我是大连,z="+z+":"+land);
        }
        void g(){
            z=x+y;                    //使用外嵌类中的x,y
            f();                       //调用外嵌类中的方法f()
        }   
    }                                 //内部类结束
}

 