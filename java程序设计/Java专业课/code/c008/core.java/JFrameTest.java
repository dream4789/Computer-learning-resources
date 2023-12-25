package C011_SwingGui;

import javax.swing.JFrame;

/**
 * project_name: Java_Ex
 *
 * package_name: C011_SwingGui 
 *
 * author:  DarlingKe
 *
 * created Time: 2018-1-3 ����10:20:26 
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
		JFrame frame1 = new JFrame("��һ������");
		JFrame frame2 = new JFrame("�ڶ�������");
		frame1.setBounds(60, 100, 188, 108); // ���ô�������Ļ�ϵ�λ�ü���С
		frame2.setBounds(260, 100, 188, 108);
		frame1.setVisible(true);
		frame1.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE); // �ͷŵ�ǰ����
		frame2.setVisible(true);
		frame2.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // �˳�����
	}

}


 