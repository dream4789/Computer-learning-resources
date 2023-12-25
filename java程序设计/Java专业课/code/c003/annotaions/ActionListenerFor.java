package C012_Annotations;

import java.lang.annotation.Target;
import java.lang.annotation.Retention;
import java.lang.annotation.ElementType;
import java.lang.annotation.RetentionPolicy;

/**
 * project_name: Java_Ex
 *
 * package_name: C012_Annotations 
 *
 * author:  DarlingKe
 *
 * created Time: 2018-1-14 ионГ9:45:49 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: ActionListenerFor.java  
 *
 * Description:  
 *
 */

@Target(ElementType.METHOD)
@Retention(RetentionPolicy.RUNTIME)

public @interface ActionListenerFor
{
   String source();
}

 