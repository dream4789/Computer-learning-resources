package C011_SwingGui;

import javax.swing.JFrame;

/**
 * project_name: Java_Ex
 *
 * package_name: C011_SwingGui 
 *
 * author:  DarlingKe
 *
 * created Time: 2018-1-3 上午10:20:26 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: JFrameTest.java  
 *
 * Description:  
 *
 */
public class JFrameTest {

	public static void main(String args[]) {
		JFrame frame1 = new JFrame("第一个窗口");
		JFrame frame2 = new JFrame("第二个窗口");
		frame1.setBounds(60, 100, 188, 108); // 设置窗口在屏幕上的位置及大小
		frame2.setBounds(260, 100, 188, 108);
		frame1.setVisible(true);
		frame1.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE); // 释放当前窗口
		frame2.setVisible(true);
		frame2.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // 退出程序
	}

}


 