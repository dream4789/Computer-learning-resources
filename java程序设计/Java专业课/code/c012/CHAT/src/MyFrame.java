import java.awt.Toolkit;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;


public class MyFrame extends JFrame{

	MyFrame(){
		Toolkit tk = Toolkit.getDefaultToolkit();
		ClassLoader cl = this.getClass().getClassLoader();//获得类加载器		
		JFrame jf = new JFrame();
		jf.setSize(300,300);
		JLabel jl = new JLabel("pppppppppp");
		ImageIcon icon = new ImageIcon(tk.getImage(cl.getResource("images/3.gif")));
		jl.setIcon(icon);
		jf.add(jl);
		jf.setVisible(true);
		jf.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
           new MyFrame();
		
	}

}
