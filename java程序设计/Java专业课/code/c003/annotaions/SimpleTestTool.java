package C012_Annotations;

import java.lang.reflect.Method;

/**
 * project_name: Java_Ex
 *
 * package_name: C012_Annotations 
 *
 * author:  DarlingKe
 *
 * created Time: 2018-1-16 下午9:38:06 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: SimpleTestTool.java  
 *
 * Description:  
 *
 */
public class SimpleTestTool {

	/**
	 * @param args
	 */
	@SuppressWarnings("rawtypes")
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		MaybeBug object = new MaybeBug();
        Class clazz = object.getClass();
        Method[] method = clazz.getDeclaredMethods();
        StringBuilder sb_log = new StringBuilder();
        int errornum = 0;
        for ( Method m: method ) {
            if ( m.isAnnotationPresent( HelpTest.class )) {
                try {
                    m.setAccessible(true);
                    m.invoke(object);

                } catch (Exception e) {
                    // TODO Auto-generated catch block
                    errornum++;
                    sb_log.append(m.getName());
                    sb_log.append(" ");
                    sb_log.append("有BUG:");
                    sb_log.append("\n\r  原因： ");
                    sb_log.append(e.getCause().getClass().getSimpleName());
                    sb_log.append("\n\r");
                    sb_log.append(e.getCause().getMessage());
                    sb_log.append("\n\r");
                } 
            }
        }
        sb_log.append(clazz.getSimpleName());
        sb_log.append(" 有  ");
        sb_log.append(errornum);
        sb_log.append(" 错误.");
        System.out.println(sb_log.toString());
	}

}

class MaybeBug{
	
	public void method1() {
		System.out.println("100+0="+100+0);
	}
	@HelpTest
	public void method2() {
		System.out.println("100-0="+(100-0));
	}
	@HelpTest
	public void method3() {
		System.out.println("100*0="+100*0);
	}
	@HelpTest
	public void method4() {
		System.out.println("100/0="+100/0);
	}
}


 