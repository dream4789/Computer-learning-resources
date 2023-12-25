import java.util.Scanner;

/**  

 * Created Time£º2014-9-1 ÉÏÎç8:39:39  

 * Project Name£ºJavaCourse14  

 * @author DarlingKe  

 * @version 1.0   

 * @since JDK 1.7.0_15  

 * FileName£ºArgTest.java  

 * Description£º  

 */
public class ArgTest {

	/**
	
	 * <p>Title: main</p>
	
	 * <p>Description: </p>
	
	 * @param args
	
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String arg1,arg2;
		if (args.length > 0){
			arg1 = args[0];
			arg2= args[1];
		}
		else {
			Scanner in = new Scanner(System.in);
			System.out.println("Enter two integer (e.g. 10 20): ");
			arg1 = in.next();
			arg2=in.next();
			in.close();
		}
		int result=Integer.valueOf(arg1)+Integer.valueOf(arg2);
		System.out.println(arg1 +"+"+arg2+"="+result);
	}

}
