package C004_Clz_Obj_2;

import java.util.Scanner;

/**
 * project_name: Java_Ex
 * 
 * package_name: C004_Clz_Obj_2
 * 
 * author: DarlingKe
 * 
 * created Time: 2017-12-29 ÉÏÎç9:08:43
 * 
 * version: 1.0
 * 
 * since: JDK 1.7.0_15
 * 
 * FileName: EnumTest.java
 * 
 * Description:
 * 
 */
public class EnumTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		System.out.print("Enter a size: (SMALL, MEDIUM, LARGE, EXTRA_LARGE) ");
		String input = in.next().toUpperCase();
		Size size = Enum.valueOf(Size.class, input);
		System.out.println("size=" + size);
		System.out.println("toString() is: "+ size.toString());
		System.out.println("abbreviation=" + size.getAbbreviation());
		if (size == Size.EXTRA_LARGE)
			System.out.println("Good job--you paid attention to the _.");
		in.close();
		Size[] values = Size.values(); 
		System.out.println("-----------all size list------------");
		for(Size s1:values)
			System.out.println(s1);
	}

}
