package C012_Annotations;

import java.lang.annotation.Annotation;
import java.lang.reflect.Method;

/**
 * project_name: Java_Ex
 *
 * package_name: C012_Annotations 
 *
 * author:  DarlingKe
 *
 * created Time: 2018-1-16 ����8:23:45 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: AnnotationTest.java  
 *
 * Description:  
 *
 */
public class AnnotationTest {

	/**
	 * @param args
	 */
	public static void main(String[] args)throws Exception{
		// TODO Auto-generated method stub
		Class <?> c = null ;  
        c = Class.forName("C012_Annotations.TestAnno") ;  
        Method m = c.getMethod("toString") ;  // �ҵ�toString()����  
        Annotation anno[] = m.getAnnotations() ;    // ȡ��ȫ����Annotation  
        for(Annotation a:anno)
            System.out.println(a) ;  
    }

}

class TestAnno{
    //@SuppressWarnings("unchecked") //�ñ�ע��Retention��RetentionPolicy.RUNTIME  
    @Deprecated  //RetentionPolicy.SOURCE
    @Override  //RetentionPolicy.SOURCE
    public String toString(){  
        return "Hello World!!!" ;  
    }  
};

 