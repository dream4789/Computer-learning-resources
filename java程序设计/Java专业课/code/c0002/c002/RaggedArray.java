package C002_Syntax;

/**
 * 
 * Created Time£º2014-9-17 ÉÏÎç9:14:07
 * 
 * Project Name£ºJavaCourse14
 * 
 * @author DarlingKe
 * 
 * @version 1.0
 * 
 * @since JDK 1.7.0_15
 * 
 *        FileName£ºRaggedArray.java
 * 
 *        Description£º
 */
public class RaggedArray {

	/**
	 * 
	 * <p>
	 * Title: main
	 * </p>
	 * 
	 * <p>
	 * Description:
	 * </p>
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		final int RMAX = 6;

		// allocate triangular array
		int[][] yhTriangular = new int[RMAX + 1][];
		for (int n = 0; n <= RMAX; n++)
			yhTriangular[n] = new int[n + 1];

		// fill triangular array
		for (int n = 0; n < yhTriangular.length; n++) {
			yhTriangular[n][0] = 1;
			yhTriangular[n][n] = 1;

		}
		for (int n = 2; n < yhTriangular.length; n++)
			for (int k = 1; k < yhTriangular[n].length - 1; k++) {
				yhTriangular[n][k] = yhTriangular[n - 1][k - 1]
						+ yhTriangular[n - 1][k];
			}

		// print triangular array
		for (int[] row : yhTriangular) {
			for (int element : row)
				System.out.printf("%4d", element);
			System.out.println();
		}
	}

}
