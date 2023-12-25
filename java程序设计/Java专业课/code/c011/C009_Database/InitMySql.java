package C009_Database;

import java.io.File;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.Statement;

import org.apache.commons.io.FileUtils;

/**
 * 
 * Created Time：2013-12-18 上午10:30:49
 * 
 * Project Name：Ex.Proj
 * 
 * @author DarlingKe
 * 
 * @version 1.0
 * 
 * @since JDK 1.7.0_15
 * 
 *        FileName：InitMySql.java
 * 
 *        Description：
 */
public class InitMySql {

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
		createdb();
		createTable();
		initMysql();
	}

	public static void createTable() {
		try {
			File tablef = new File("create_table.sql");
			String createtablesqls = FileUtils
					.readFileToString(tablef, "UTF-8");
			Class.forName("org.gjt.mm.mysql.Driver").newInstance();
			String url = "jdbc:mysql://localhost:3306/testjava?useUnicode=true&characterEncoding=UTF-8";
			conn = DriverManager.getConnection(url, "root", "root");
			conn.setAutoCommit(false);
			Statement stmt = conn.createStatement();
			String[] sqls = createtablesqls.split("######");
			for (int i = 0; i < sqls.length; i++) {
				if (!"".equals(sqls[i])) {
					stmt.execute(sqls[i]);
				}
			}
			conn.commit();
			conn.close();
		} catch (Exception e) {
			try {
				conn.rollback();
			} catch (Exception e1) {
				System.out.println("创建数据表失败，原因：<br/>");
				System.out.println(e);
				return;
			}			
		} finally {
			if (conn != null) {
				try {
					conn.close();
				} catch (Exception e) {
				}
				conn = null;
			}
		}
	}

	public static void initMysql() {
		try {
			File dbf = new File("init-db.sql");
			String initdbqls = FileUtils.readFileToString(dbf, "UTF-8");
			Class.forName("org.gjt.mm.mysql.Driver").newInstance();
			String url = "jdbc:mysql://localhost:3306/testjava?useUnicode=true&characterEncoding=UTF-8";
			conn = DriverManager.getConnection(url, "root", "root");
			conn.setAutoCommit(false);
			Statement stmt = conn.createStatement();
			String[] sqls = initdbqls.split("######");
			for (int i = 0; i < sqls.length; i++) {
				if (!"".equals(sqls[i])) {
					stmt.execute(sqls[i]);
				}
			}
			conn.commit();
			conn.close();
		} catch (Exception e) {
			try {
				conn.rollback();
			} catch (Exception e1) {
				System.out.println("初始化数据库失败，原因：<br/>");
				System.out.println(e);
				return;
			}			
		} finally {
			if (conn != null) {
				try {
					conn.close();
				} catch (Exception e) {
				}
				conn = null;
			}
		}
	}

	public static void createdb() {
		try {
			File cdbf = new File("create_db.sql");
			String createdbsql = FileUtils.readFileToString(cdbf, "UTF-8");

			Class.forName("org.gjt.mm.mysql.Driver").newInstance();
			String url = "jdbc:mysql://localhost:3306/?useUnicode=true&characterEncoding=UTF-8";
			conn = DriverManager.getConnection(url, "root", "root");
			Statement stmt = conn.createStatement();
			stmt.execute(createdbsql);
			stmt.close();
		} catch (Exception e) {
			System.out.println("创建数据库失败，原因：<br/>");
			System.out.println(e);
			return;
		} finally {
			if (conn != null) {
				try {
					conn.close();
				} catch (Exception e) {
				}
				conn = null;
			}
		}
	}

	private static Connection conn = null;

}
