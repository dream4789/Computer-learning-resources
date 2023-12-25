package C004_Clz_Obj_2;

import java.lang.reflect.Method;

/**
 * project_name: Java_Ex
 * 
 * package_name: C004_Clz_Obj_2
 * 
 * author: DarlingKe
 * 
 * created Time: 2017-12-28 ÏÂÎç2:22:32
 * 
 * version: 1.0
 * 
 * since: JDK 1.7.0_15
 * 
 * FileName: MethodPointerTest.java
 * 
 * Description:
 * 
 */
public class MethodPointerTest {

	public static void main(String[] args) throws Exception {
		// get method pointers to the square and sqrt methods
		Method square = MethodPointerTest.class.getMethod("square",
				double.class);
		Method sqrt = Math.class.getMethod("sqrt", double.class);
		Employee e1 = new Employee("Harry Hacker", 50000, 1989, 10, 1);
		Method getSalary = e1.getClass().getMethod("getSalary");

		Manager m1 = new Manager("Carl Cracker", 50000, 1987, 12, 15);
		Method setBonus = m1.getClass().getMethod("setBonus", double.class);
		Method m_getSalary = m1.getClass().getMethod("getSalary");

		System.out.println(square);
		System.out.println(square.invoke(null, 3.0));
		System.out.println(sqrt);
		System.out.println(sqrt.invoke(null, 9.0));
		System.out.println(getSalary);
		System.out.println(getSalary.invoke(e1));
		System.out.println(setBonus);
		setBonus.invoke(m1, 30000);
		System.out.println(m_getSalary);
		System.out.println(m_getSalary.invoke(m1));

		// print tables of x- and y-values

		// printTable(1, 10, 10, square);
		// printTable(1, 10, 10, sqrt);
	}

	/**
	 * Returns the square of a number
	 * 
	 * @param x
	 *            a number
	 * @return x squared
	 */
	public static double square(double x) {
		return x * x;
	}

	/**
	 * Prints a table with x- and y-values for a method
	 * 
	 * @param from
	 *            the lower bound for the x-values
	 * @param to
	 *            the upper bound for the x-values
	 * @param n
	 *            the number of rows in the table
	 * @param f
	 *            a method with a double parameter and double return value
	 */
	public static void printTable(double from, double to, int n, Method f) {
		// print out the method as table header
		System.out.println(f);

		// construct formatter to print with 4 digits precision

		double dx = (to - from) / (n - 1);

		for (double x = from; x <= to; x += dx) {
			try {
				double y = (Double) f.invoke(null, x);
				System.out.printf("%10.4f | %10.4f%n", x, y);
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}
}
