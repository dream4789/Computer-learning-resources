
/**
 * project_name: Java_Ex
 * 
 * package_name: C004_Clz_Obj_2
 * 
 * author: DarlingKe
 * 
 * created Time: 2017-12-28 ÏÂÎç2:19:51
 * 
 * version: 1.0
 * 
 * since: JDK 1.7.0_15
 * 
 * FileName: Manager.java
 * 
 * Description:
 * 
 */
public class Manager extends Employee {
	/**
	 * @param n
	 *            the employee's name
	 * @param s
	 *            the salary
	 * @param year
	 *            the hire year
	 * @param month
	 *            the hire month
	 * @param day
	 *            the hire day
	 */
	public Manager(String n, double s, int year, int month, int day) {
		super(n, s, year, month, day);
		bonus = 0;
	}

	public double getSalary() {
		double baseSalary = super.getSalary();
		return baseSalary + bonus;
	}

	public void setBonus(double b) {
		bonus = b;
	}

	public boolean equals(Object otherObject) {
		if (!super.equals(otherObject))
			return false;
		Manager other = (Manager) otherObject;
		// super.equals checked that this and other belong to the same class
		return bonus == other.bonus;
	}

	public int hashCode() {
		return super.hashCode() + 17 * new Double(bonus).hashCode();
	}

	public String toString() {
		return super.toString() + "[bonus=" + bonus + "]";
	}

	public String getName() {
		return "Manager..."+super.getName();
	}
	
	private double bonus;

}
