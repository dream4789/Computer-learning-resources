package C010_NetWork;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;

/**
 * project_name: Java_Ex
 *
 * package_name: C010_NetWork 
 *
 * author:  DarlingKe
 *
 * created Time: 2018-1-1 ÏÂÎç8:26:44 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: TctClientTest.java  
 *
 * Description:  
 *
 */
public class TcpClientTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Socket s;
		try {
			s = new Socket("127.0.0.1", 10222);
	        BufferedReader br = new BufferedReader(new InputStreamReader
	            (s.getInputStream()));
	        System.out.println(br.readLine());
	        s.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}        
	}

}


 