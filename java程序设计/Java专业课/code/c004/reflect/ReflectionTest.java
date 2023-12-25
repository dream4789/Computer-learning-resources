package C004_Clz_Obj_2;

import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.util.Scanner;

/**
 * project_name: Java_Ex
 *
 * package_name: C004_Clz_Obj_2 
 *
 * author:  DarlingKe
 *
 * created Time: 2017-12-28 ÏÂÎç2:17:05 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: ReflectionTest.java  
 *
 * Description:  
 *
 */
public class ReflectionTest {

	@SuppressWarnings("rawtypes")
	public static void main(String[] args) {
		String name;
		if (args.length > 0)
			name = args[0];
		else {
			Scanner in = new Scanner(System.in);
			System.out.println("Enter class name (e.g. java.util.Date): ");
			name = in.next();
			in.close();
		}
		try {
			Class cl = Class.forName(name);
			Class supercl = cl.getSuperclass();
			System.out.print("class " + name);
			if (supercl != null && supercl != Object.class)
				System.out.print(" extends " + supercl.getName());
			System.out.print("\n{\n");
			printConstructors(cl);
			System.out.println();
			printMethods(cl);
			System.out.println();
			printFields(cl);
			System.out.println("}");
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
		System.exit(0);
	}

	/**
	 * Prints all constructors of a class
	 * 
	 * @param cl
	 *            a class
	 */
	@SuppressWarnings("rawtypes")
	public static void printConstructors(Class cl) {
		Constructor[] constructors = cl.getDeclaredConstructors();
		for (Constructor c : constructors) {
			String name = c.getName();
			System.out.print("   " + Modifier.toString(c.getModifiers()));
			System.out.print(" " + name + "(");
			Class[] paramTypes = c.getParameterTypes();
			for (int j = 0; j < paramTypes.length; j++) {
				if (j > 0)
					System.out.print(", ");
				System.out.print(paramTypes[j].getName());
			}
			System.out.println(");");
		}
	}

	/**
	 * Prints all methods of a class
	 * 
	 * @param cl
	 *            a class
	 */
	@SuppressWarnings("rawtypes")
	public static void printMethods(Class cl) {
		Method[] methods = cl.getDeclaredMethods();
		for (Method m : methods) {
			Class retType = m.getReturnType();
			String name = m.getName();
			System.out.print("   " + Modifier.toString(m.getModifiers()));
			System.out.print(" " + retType.getName() + " " + name + "(");
			Class[] paramTypes = m.getParameterTypes();
			for (int j = 0; j < paramTypes.length; j++) {
				if (j > 0)
					System.out.print(", ");
				System.out.print(paramTypes[j].getName());
			}
			System.out.println(");");
		}
	}

	/**
	 * Prints all fields of a class
	 * 
	 * @param cl
	 *            a class
	 */
	@SuppressWarnings("rawtypes")
	public static void printFields(Class cl) {
		Field[] fields = cl.getDeclaredFields();
		for (Field f : fields) {
			Class type = f.getType();
			String name = f.getName();
			System.out.print("   " + Modifier.toString(f.getModifiers()));
			System.out.println(" " + type.getName() + " " + name + ";");
		}
	}

}


 