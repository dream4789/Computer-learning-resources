/**  

 * Created Time��2014-8-31 ����10:49:57  

 * Project Name��JavaCourse14  

 * @author DarlingKe  

 * @version 1.0   

 * @since JDK 1.7.0_15  

 * FileName��Welcome.java  

 * Description��  

 */
public class Welcome {

	/**
	
	 * <p>Title: main</p>
	
	 * <p>Description: This program display strings in console.</p>
	
	 * @param args
	
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String[] greeting = new String[3];
		greeting[0] = "Welcome to Core Java";
		greeting[1] = "by Cay Horstmann";
		greeting[2] = "and Gary Cornell";

		for (String g : greeting)
			System.out.println(g);
	}

}
