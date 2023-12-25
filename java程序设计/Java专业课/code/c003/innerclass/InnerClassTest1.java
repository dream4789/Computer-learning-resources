package C004_Clz_Obj_2;

/**
 * project_name: Java_Ex
 *
 * package_name: C004_Clz_Obj_2 
 *
 * author:  DarlingKe
 *
 * created Time: 2017-12-30 ����12:01:30 
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
    String land="������";
}
class China{
    int x=10,y=10;
    LiaoNing dalian;             //�ڲ��������������Ϊ��Ƕ��ĳ�Ա
    China(){
        dalian=new LiaoNing();
    }
    void f(){
        System.out.println("�����й�");
        dalian.speak();
    } 
    class LiaoNing extends NorthEast{      //�ڲ��������
        int z;
        void speak(){
            System.out.println("���Ǵ���,z="+z+":"+land);
        }
        void g(){
            z=x+y;                    //ʹ����Ƕ���е�x,y
            f();                       //������Ƕ���еķ���f()
        }   
    }                                 //�ڲ������
}

 