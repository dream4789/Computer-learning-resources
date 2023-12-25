package C012_Annotations;
/**
 * project_name: Java_Ex
 *
 * package_name: C012_Annotations 
 *
 * author:  DarlingKe
 *
 * created Time: 2018-1-23 ионГ8:52:17 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: BugReport.java  
 *
 * Description:  
 *
 */
public @interface BugReport
{
   enum Status { UNCONFIRMED, CONFIRMED, FIXED, NOTABUG };
   boolean showStopper() default false;
   String assignedTo() default "[none]";
   Class<? extends MaybeBug> testCase() default MaybeBug.class;
   Status status() default Status.UNCONFIRMED;
   //MaybeBug testCase();
   String[] reportedBy();
}



 