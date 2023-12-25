package C009_Database;

import java.sql.Connection;
import java.util.ArrayList;
import java.util.List;

/**
* project_name:Java_Ex
*
* package_name:C009_Database
*
* author DarlingKe
* 
* version Created Time：2018年5月21日 下午4:37:24
*
* FileName:TestMyPool.java
*
* Description:
*/
public class TestMyPool {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		MyPool pool = MyPool.getInstance();
		List<Connection> conn = new ArrayList<Connection>();
		for(int i=0;i<15;i++){
			conn.add(pool.getConnection());
		}
		System.out.println("-------------after get 15 connections--------------");
		System.out.println("Active Num:"+pool.getNumOfActive());
		System.out.println("Free Num:"+pool.getNumOfFree());
		System.out.println("Max Num:"+pool.getnumOfMax());
		for(int i=0;i<5;i++){
			pool.freeConnection(conn.get(i));
		}
		System.out.println("-------------after release 5 connections--------------");
		System.out.println("Active Num:"+pool.getNumOfActive());
		System.out.println("Free Num:"+pool.getNumOfFree());
		System.out.println("Max Num:"+pool.getnumOfMax());
		pool.release();
		System.out.println("-------------after release all connections--------------");
		System.out.println("Active Num:"+pool.getNumOfActive());
		System.out.println("Free Num:"+pool.getNumOfFree());
		System.out.println("Max Num:"+pool.getnumOfMax());
		System.out.println("GameOver.");
	}

}
