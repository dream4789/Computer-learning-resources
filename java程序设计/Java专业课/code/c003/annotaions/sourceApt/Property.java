package C012_Annotations.sourceApt;

import java.lang.annotation.Documented;
import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;
/**
 * project_name: Java_Ex
 *
 * package_name: C012_Annotations.sourceApt 
 *
 * author:  DarlingKe
 *
 * created Time: 2018-1-23 ионГ9:20:56 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: Property.java  
 *
 * Description:  
 *
 */
@Documented
@Target(ElementType.METHOD)
@Retention(RetentionPolicy.SOURCE)
public @interface Property
{
   String editor() default ""; 
}
