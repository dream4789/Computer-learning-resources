package C004_Clz_Obj_2;

import java.lang.reflect.AccessibleObject;
import java.lang.reflect.Array;
import java.lang.reflect.Field;
import java.lang.reflect.Modifier;
import java.util.ArrayList;

/**
 * project_name: Java_Ex
 * 
 * package_name: C004_Clz_Obj_2
 * 
 * author: DarlingKe
 * 
 * created Time: 2017-12-28 ÏÂÎç2:20:45
 * 
 * version: 1.0
 * 
 * since: JDK 1.7.0_15
 * 
 * FileName: ObjectAnalyzerTest.java
 * 
 * Description:
 * 
 */
public class ObjectAnalyzerTest {

	public static void main(String[] args) {
		ArrayList<Integer> squares = new ArrayList<Integer>();
		for (int i = 1; i <= 5; i++)
			squares.add(i * i);
		System.out.println(new ObjectAnalyzer().toString(squares));
		String s1 = new String("DarlingKe");
		System.out.println(new ObjectAnalyzer().toString(s1));
		Employee e1 = new Employee("Harry Hacker", 50000, 1989, 10, 1);
		System.out.println(new ObjectAnalyzer().toString(e1));
		Manager boss = new Manager("Carl Cracker", 80000, 1987, 12, 15);
		System.out.println(new ObjectAnalyzer().toString(boss));

	}
}

class ObjectAnalyzer {
	/**
	 * Converts an object to a string representation that lists all fields.
	 * 
	 * @param obj
	 *            an object
	 * @return a string with the object's class name and all field names and
	 *         values
	 */
	@SuppressWarnings("rawtypes")
	public String toString(Object obj) {
		if (obj == null)
			return "null";
		if (visited.contains(obj))
			return "...";
		visited.add(obj);
		Class cl = obj.getClass();
		if (cl == String.class)
			return (String) obj;
		if (cl.isArray()) {
			String r = cl.getComponentType() + "[]{";
			for (int i = 0; i < Array.getLength(obj); i++) {
				if (i > 0)
					r += ",";
				Object val = Array.get(obj, i);
				if (cl.getComponentType().isPrimitive())
					r += val;
				else
					r += toString(val);
			}
			return r + "}";
		}

		String r = cl.getName();
		// inspect the fields of this class and all superclasses
		do {
			r += "[";
			Field[] fields = cl.getDeclaredFields();
			AccessibleObject.setAccessible(fields, true);
			// get the names and values of all fields
			for (Field f : fields) {
				if (!Modifier.isStatic(f.getModifiers())) {
					if (!r.endsWith("["))
						r += ",";
					r += f.getName() + "=";
					try {
						Class t = f.getType();
						Object val = f.get(obj);
						if (t.isPrimitive())
							r += val;
						else
							r += toString(val);
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			}
			r += "]";
			cl = cl.getSuperclass();
		} while (cl != null);

		return r;
	}

	private ArrayList<Object> visited = new ArrayList<Object>();
}
