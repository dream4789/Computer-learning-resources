package C004_Clz_Obj_2;

import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
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
 * created Time: 2017-12-30 ÏÂÎç12:07:46
 * 
 * version: 1.0
 * 
 * since: JDK 1.7.0_15
 * 
 * FileName: InnerClassTest2.java
 * 
 * Description:
 * 
 */
public class InnerClassTest2 {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		TalkingClock clock = new TalkingClock(1000, true);
		clock.start();

		// keep program running until user selects "Ok"
		JOptionPane.showMessageDialog(null, "Quit program?");
		System.exit(0);
	}

}

/**
 * A clock that prints the time in regular intervals.
 */
class TalkingClock {
	/**
	 * Constructs a talking clock
	 * 
	 * @param interval
	 *            the interval between messages (in milliseconds)
	 * @param beep
	 *            true if the clock should beep
	 */
	public TalkingClock(int interval, boolean beep) {
		this.interval = interval;
		this.beep = beep;
	}

	/**
	 * Starts the clock.
	 */
	public void start() {
		ActionListener listener = new TimePrinter();
		Timer t = new Timer(interval, listener);
		t.start();
	}

	private int interval;
	private boolean beep;

	private class TimePrinter implements ActionListener {
		// public TimePrinter(TalkingClock clock) {
		// outer = clock;
		// }

		public void actionPerformed(ActionEvent event) {
			Date now = new Date();
			System.out.println("At the tone, the time is " + now);
			if (beep)
				Toolkit.getDefaultToolkit().beep();
			// if(outer.beep)...
			// if(TalkingClock.this.beep)Toolkit.getDefaultToolkit().beep();
		}
	}
}
