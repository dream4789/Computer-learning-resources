package C004_Clz_Obj_2;

/**
 * project_name: Java_Ex
 * 
 * package_name: C004_Clz_Obj_2
 * 
 * author: DarlingKe
 * 
 * created Time: 2017-12-29 上午10:13:22
 * 
 * version: 1.0
 * 
 * since: JDK 1.7.0_15
 * 
 * FileName: InterfaceParamTest.java
 * 
 * Description:
 * 
 */
public class InterfaceParamTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		C c=new C();
        c.f(new A());
        c.f(new B());   
	}

}

interface Show {
	void show();
}

class A implements Show {
	public void show() {
		System.out.println("I love This Game");
	}
}

class B implements Show {
	public void show() {
		System.out.println("我喜欢看NBA");
	}
}

class C {
	public void f(Show s) { // 接口作为参数
		s.show();
	}
}
