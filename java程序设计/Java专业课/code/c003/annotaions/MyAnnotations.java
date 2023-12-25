package C012_Annotations;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

/**
 * project_name: Java_Ex
 *
 * package_name: C012_Annotations 
 *
 * author:  DarlingKe
 *
 * created Time: 2018-1-16 обнГ8:37:20 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: MyAnnotations.java  
 *
 * Description:  
 *
 */
@Retention(value=RetentionPolicy.RUNTIME) 
public @interface MyAnnotations {
	public String key() default "keyOne" ;  
    public String value() default "keyOneValue" ; 
}


 