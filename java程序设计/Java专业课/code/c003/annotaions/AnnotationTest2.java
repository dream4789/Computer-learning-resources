package C012_Annotations;

import java.lang.reflect.Method;

/**
 * project_name: Java_Ex
 *
 * package_name: C012_Annotations 
 *
 * author:  DarlingKe
 *
 * created Time: 2018-1-16 ÏÂÎç8:35:53 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: AnnotationTest2.java  
 *
 * Description:  
 *
 */
public class AnnotationTest2 {

	/**
	 * @param args
	 */
	public static void main(String[] args)throws Exception{
		// TODO Auto-generated method stub
		Class <?> claz = null ;  
		claz = Class.forName("C012_Annotations.TestAnno2") ;  
        for (Method m : claz.getDeclaredMethods()) {
        	if(m.isAnnotationPresent(MyAnnotations.class)){
            	MyAnnotations annotations = null ;  
            	annotations = m.getAnnotation(MyAnnotations.class) ; 
                String key = annotations.key() ;    
                String value = annotations.value() ;    
                System.out.print(m.getName()+":key = " + key+",") ;  
                System.out.println("value = " + value) ;  
            } 
        }        
	}

}

class TestAnno2{  
	@MyAnnotations
    public String method0(){  
        return "method1!" ;  
    } 
    @MyAnnotations(key="ahut",value="www.ahut.edu.cn")  
    public String method1(){  
        return "method1!" ;  
    }  
};

 