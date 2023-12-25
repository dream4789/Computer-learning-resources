package C004_Clz_Obj_2;

import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.SimpleDateFormat;
import java.util.Date;

import javax.swing.JOptionPane;
import javax.swing.Timer;

/**
 * project_name: Java_Ex
 * 
 * package_name: C004_Clz_Obj_2
 * 
 * author: DarlingKe
 * 
 * created Time: 2017-12-29 ÉÏÎç9:44:33
 * 
 * version: 1.0
 * 
 * since: JDK 1.7.0_15
 * 
 * FileName: TimerTest.java
 * 
 * Description:
 * 
 */
public class TimerTest {

	public static void main(String[] args) {
		ActionListener listener = new TimePrinter();

		// construct a timer that calls the listener
		// once every 10 seconds
		Timer t = new Timer(1000, listener);
		t.start();

		JOptionPane.showMessageDialog(null, "Quit program?");
		System.exit(0);
	}
}

class TimePrinter implements ActionListener {
	public void actionPerformed(ActionEvent event) {
		Date now = new Date();
		SimpleDateFormat sdf=new SimpleDateFormat("yyyy-mm-dd hh:mm:ss");
		System.out.println("At the tone, the time is " + sdf.format(now));
		Toolkit.getDefaultToolkit().beep();
	}
}
