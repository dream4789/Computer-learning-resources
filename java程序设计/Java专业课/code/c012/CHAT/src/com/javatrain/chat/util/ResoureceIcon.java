package com.javatrain.chat.util;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.Point;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.List;

import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.SwingUtilities;
import javax.swing.text.StyledDocument;

import com.javatrain.chat.gui.ClientMainFrame;
import com.javatrain.chat.gui.Login;
import com.javatrain.chat.gui.LoginFrame;

//图标面板
public class ResoureceIcon extends JDialog {

	private JPanel jpanelTop;
	private JPanel jpanelBottom;
	private ClientMainFrame cmf;
	private IconBox current;

	public ResoureceIcon() {
		initUI();
	}

	public ResoureceIcon(ClientMainFrame cmf) {
		this.cmf = cmf;
		initUI();

		Point point = new Point(0, 0);
		SwingUtilities.convertPointToScreen(point, cmf);
		point.x = point.x + (int) (cmf.getWidth() - this.getWidth()) / 2;
		point.y = point.y + (int) (cmf.getHeight() - this.getHeight())
				/ 2;

		System.out.println(point);
		setLocation(point);
	}

	private void initUI() {
		// TODO Auto-generated method stub
		setSize(450, 200);
		this.setResizable(false);
		this.setTitle("图标");
		jpanelTop = new ImageJPanel();
		JScrollPane jscrollPane = new JScrollPane(jpanelTop,
				JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,
				JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		add(jscrollPane, BorderLayout.CENTER);

		jpanelBottom = new ControlJPanel();
		add(jpanelBottom, BorderLayout.SOUTH);// , BorderLayout.CENTER

		this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
		setVisible(true);
	}

	public static void main(String[] args) {
		new ResoureceIcon();
	}

	class ImageJPanel extends JPanel {
		private int col = 8;

		ImageJPanel() {
			IconBox jlImage = null;
			int size = 0;
			size = ImageFactory.getInstance().getHm_insertIcon().size();
			ImageIcon imageIcon = null;
			int row = size % col == 0 ? size / col : size / col + 1;
			// System.out.println(size + "  " + row);
			GridLayout gridLayout = new GridLayout(row, col, 10, 10);
			// FlowLayout flowLayou = new FlowLayout(FlowLayout.LEFT, 10, 10);
			setLayout(gridLayout);

			for (int i = 1; i <= size; i++) {
				imageIcon = ImageFactory.getInstance().getinsertIcon(i + "");
				jlImage = new IconBox((i) + "", imageIcon);
				jlImage.setPreferredSize(new Dimension(5, 5));
				jlImage.setBackground(Color.CYAN);
				jlImage.setBorder(BorderFactory.createEtchedBorder());
				jlImage.addMouseListener(new MouseAdapter() {
					@Override
					public void mouseClicked(MouseEvent e) {
						// TODO Auto-generated method stub
						if (current != null) {
							current.setBackground(Color.CYAN);
						}
						current = (IconBox) e.getSource();
						current.setBackground(Color.BLUE);

					}
				});
				this.add(jlImage);
			}
		}
	}

	class ControlJPanel extends JPanel {
		private JButton jbok;
		private JButton jbcancel;

		ControlJPanel() {
			JLabel jlSeparator = new JLabel("");
			jlSeparator.setPreferredSize(new Dimension(20, 20));
			jbok = new JButton("确定");
			jbcancel = new JButton("取消");

			jbok.addActionListener(new ActionListener() {

				@Override
				public void actionPerformed(ActionEvent e) {
					// TODO Auto-generated method stub
					// System.out.println("=========");
					//loginFrame.userImage.setImage(current.image, current.text);
					//cmf.getEditMsgArea().
					EventQueue.invokeLater(new Runnable(){

						@Override
						public void run() {
							// TODO Auto-generated method stub
							if(current == null){
								return ;
							}
							MyJTextJPane editMsgArea = cmf.getEditMsgArea();
							editMsgArea.requestFocus();
							StyledDocument doc = editMsgArea.getStyledDocument();
							editMsgArea.setCaretPosition(doc.getLength()); // 设置插入位置
							editMsgArea.insertIcon(current.imageIcon, current.iconName);
							editMsgArea.setCaretPosition(doc.getLength());
//System.out.println("-------------"+editMsgArea.getText());
						}});
					

					ResoureceIcon.this.dispose();
				}
			});
			jbcancel.addActionListener(new ActionListener() {

				@Override
				public void actionPerformed(ActionEvent e) {
					// TODO Auto-generated method stub
					ResoureceIcon.this.dispose();
				}
			});

			add(jbok);
			add(jlSeparator);
			add(jbcancel);
		}
	}
}
