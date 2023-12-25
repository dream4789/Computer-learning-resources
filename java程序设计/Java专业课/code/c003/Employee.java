
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.GregorianCalendar;

/**
 * project_name: Java_Ex
 * 
 * package_name: C004_Clz_Obj_2
 * 
 * author: DarlingKe
 * 
 * created Time: 2017-12-28 ÏÂÎç2:18:45
 * 
 * version: 1.0
 * 
 * since: JDK 1.7.0_15
 * 
 * FileName: Employee.java
 * 
 * Description:
 * 
 */
public class Employee implements Cloneable, Comparable<Employee> {
	
	public Employee(String n, double s, int year, int month, int day) {
		name = n;
		salary = s;
		GregorianCalendar calendar = new GregorianCalendar(year, month - 1, day);
		hireDay = calendar.getTime();
		hireDay =  new Date();
	}

	public String getName() {
		return "Employee..." + name;
	}

	public double getSalary() {
		return salary;
	}

	public void setHireDay(int year, int month, int day) {
		this.hireDay = new GregorianCalendar(year, month - 1, day).getTime();
	}

	public String getHireDay() {
		SimpleDateFormat smt = new SimpleDateFormat("yyyy-MM-dd");
		return smt.format(hireDay);
	}

	public void raiseSalary(double byPercent) {
		double raise = salary * byPercent / 100;
		salary += raise;
	}

	public boolean equals(Object otherObject) {
		// a quick test to see if the objects are identical
		if (this == otherObject)
			return true;

		// must return false if the explicit parameter is null
		if (otherObject == null)
			return false;

		// if the classes don't match, they can't be equal
		if (getClass() != otherObject.getClass())
			return false;

		// now we know otherObject is a non-null Employee
		Employee other = (Employee) otherObject;

		// test whether the fields have identical values
		return name.equals(other.name) && salary == other.salary
				&& hireDay.equals(other.hireDay);
	}

	public int hashCode() {
		return 7 * name.hashCode() + 11 * new Double(salary).hashCode() + 13
				* hireDay.hashCode();
	}

	public String toString() {
		SimpleDateFormat sdf=new SimpleDateFormat("yyyy-mm-dd hh:mm:ss");
		return getClass().getName() + "[name=" + name + ",salary=" + salary
				+ ",hireDay=" + sdf.format(hireDay) + "]";
	}

	public Employee clone() throws CloneNotSupportedException {
		// call Object.clone()
		Employee cloned = (Employee) super.clone();

		// clone mutable fields
		//cloned.hireDay = (Date) hireDay.clone();

		return cloned;
	}

	/**
	 * Compares employees by salary
	 * 
	 * @param other
	 *            another Employee object
	 * @return a negative value if this employee has a lower salary than
	 *         otherObject, 0 if the salaries are the same, a positive value
	 *         otherwise
	 */
	public int compareTo(Employee other) {
		if (salary < other.salary)
			return -1;
		if (salary > other.salary)
			return 1;
		return 0;
	}

	private String name;
	private double salary;
	private Date hireDay;
}
