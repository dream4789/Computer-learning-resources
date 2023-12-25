package com.javatrain.chat.gui;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Cursor;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

import javax.swing.BorderFactory;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JTextField;
import javax.swing.UIManager;

import com.javatrain.chat.util.ImageBox;
import com.javatrain.chat.util.ImageFactory;
import com.javatrain.chat.util.ResourceBundler;
import com.javatrain.chat.util.ResoureceImage;

public class LoginFrame extends JFrame {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1810345102117746990L;

	public LoginFrame() {//com.jtattoo.plaf.mcwin.McWinLookAndFeel
		super(ResourceBundler.getString("Login.Title"));//
		try {  com.sun.java.swing.plaf.windows.WindowsLookAndFeel d;
			UIManager
					.setLookAndFeel("com.sun.java.swing.plaf.windows.WindowsLookAndFeel");
		} catch (Exception e) {
			e.printStackTrace();
		}
		setLayout(new BorderLayout());
		setIconImage(ImageFactory.getInstance().getIconImage().getImage());
		//		
		// Dimension scrSize = Toolkit.getDefaultToolkit().getScreenSize();
		// setLocation((scrSize.width - getSize().width) / 2,
		// (scrSize.height - getSize().height) / 2);
		//		
		add(createMainPanel(), BorderLayout.CENTER);
		add(createButtonPanel(), BorderLayout.SOUTH);

		// initUI();
		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		});
		// setPreferredSize(new Dimension(450, 200));
		// setMaximumSize(new Dimension(450, 200));
		setLocationRelativeTo(null);
		pack();
		setResizable(false);
	}

	public JPanel createMainPanel() {
		JPanel mainPanel = new JPanel(new GridLayout(1, 2));
		mainPanel.setBorder(BorderFactory.createLineBorder(Color.DARK_GRAY));

		JPanel userPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
		userPanel.add(new JLabel(ResourceBundler.getString("Login.lbl.user")));
		txtUserName = new JTextField(16);
		txtUserName.addKeyListener(new PanelKeyListener());
		userPanel.add(txtUserName);

		JPanel saddr = new JPanel(new FlowLayout(FlowLayout.RIGHT));
		JPanel sport = new JPanel(new FlowLayout(FlowLayout.RIGHT));
		JPanel serverPanel = new JPanel(new GridLayout(2, 1));

		saddr.add(new JLabel(ResourceBundler.getString("Login.lbl.serverIP")));
		txtServerAddress = new JTextField(10);
		txtServerAddress.setText(serverAddress);
		txtServerAddress.addKeyListener(new PanelKeyListener());
		saddr.add(txtServerAddress);

		sport
				.add(new JLabel(ResourceBundler
						.getString("Login.lbl.serverPort")));
		txtServerPort = new JTextField(10);
		txtServerPort.setText(Integer.toString(serverPort));
		txtServerPort.addKeyListener(new PanelKeyListener());
		sport.add(txtServerPort);

		serverPanel.add(saddr);
		serverPanel.add(sport);

		JPanel sexPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
		rbtnBoy = new JRadioButton(ResourceBundler
				.getString("Login.lbl.rbtnBoy"));
		rbtnBoy.addKeyListener(new PanelKeyListener());
		rbtnBoy.addItemListener(new ItemListener() {

			
			public void itemStateChanged(ItemEvent arg0) {
				// TODO Auto-generated method stub
				selectSex(arg0);
			}

		});
		rbtnGirl = new JRadioButton(ResourceBundler
				.getString("Login.lbl.rbtnGirl"));
		rbtnGirl.addItemListener(new ItemListener() {

			
			public void itemStateChanged(ItemEvent arg0) {
				// TODO Auto-generated method stub
				selectSex(arg0);
			}

		});
		rbtnSecret = new JRadioButton(ResourceBundler
				.getString("Login.lbl.rbtnSecret"));
		rbtnSecret.addItemListener(new ItemListener() {

			
			public void itemStateChanged(ItemEvent arg0) {
				// TODO Auto-generated method stub
				selectSex(arg0);
			}

		});
		ButtonGroup sexGroup = new ButtonGroup();
		sexGroup.add(rbtnBoy);
		sexGroup.add(rbtnGirl);
		sexGroup.add(rbtnSecret);
		sexPanel.add(rbtnBoy);
		sexPanel.add(rbtnGirl);
		sexPanel.add(rbtnSecret);

		JPanel upperPanel = new JPanel(new GridLayout(2, 1));

		upperPanel.add(userPanel);
		upperPanel.add(sexPanel);

		mainPanel.add(upperPanel);
		mainPanel.add(serverPanel);

		mainPanel.addKeyListener(new PanelKeyListener());
		return mainPanel;
	}

	public JPanel createButtonPanel() {
		JPanel buttonPanel = new JPanel();
		buttonPanel.setLayout(new FlowLayout(FlowLayout.RIGHT, 20, 10));
		JLabel spaceLabel = null;
		// 新添加的代码
		userImage = new ImageBox("1", ImageFactory.getInstance().getImageIndex(
				"1"));
		userImage.setTextVisible(false);
		userImage.setPreferredSize(new Dimension(40, 60));
		userImage.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
		userImage.setToolTipText("单击选择图标");
		userImage.addMouseListener(new MouseAdapter() {
			
			public void mouseClicked(MouseEvent e) {
				// TODO Auto-generated method stub
				new ResoureceImage(LoginFrame.this);
			}

		});
		// 结束
		btnOK = new JButton(ResourceBundler.getString("Login.Button.OK"));
		btnOK.addActionListener(new ActionListener() {

			
			public void actionPerformed(ActionEvent arg0) {
				// TODO Auto-generated method stub
				doOK();
			}

		});
		btnCancel = new JButton(ResourceBundler
				.getString("Login.Button.Cancel"));
		btnCancel.addActionListener(new ActionListener() {

			
			public void actionPerformed(ActionEvent arg0) {
				// TODO Auto-generated method stub
				doCancel();
			}

		});
		/*
		 * JButton jbselect = new JButton("选择图像");
		 * 
		 * //buttonPanel.add(jbselect); jbselect.addActionListener(new
		 * ActionListener() {
		 * 
		 * @Override public void actionPerformed(ActionEvent e) { // TODO
		 * Auto-generated method stub new ResoureceImage(LoginFrame.this); } });
		 * spaceLabel = new JLabel("");
		 * 
		 * spaceLabel.setPreferredSize(new Dimension(20, 20));
		 * //buttonPanel.add(spaceLabel); buttonPanel.add(btnOK);
		 * //buttonPanel.add(spaceLabel); buttonPanel.add(btnCancel);
		 */

		spaceLabel = new JLabel("");
		spaceLabel.setPreferredSize(new Dimension(90, 20));
		buttonPanel.add(userImage);
		buttonPanel.add(spaceLabel);
		buttonPanel.add(btnOK);
		buttonPanel.add(btnCancel);
		return buttonPanel;
	}

	public void login() throws Exception {
		serverAddress = txtServerAddress.getText().trim();
		serverPort = Integer.parseInt(txtServerPort.getText());
		clientSocket = new Socket(serverAddress, serverPort);

		in = new BufferedReader(new InputStreamReader(clientSocket
				.getInputStream()));
		out = new PrintWriter(clientSocket.getOutputStream());
		out.println(txtUserName.getText() + "&" + userSex + "&"
				+ userImage.getText());
		out.flush();
	}

	public void doOK() {
		if ((txtUserName.getText()).trim().length() == 0) {
			JOptionPane.showMessageDialog(this, ResourceBundler
					.getString("Login.Option.OKMessage"), ResourceBundler
					.getString("Login.Option.Title"),
					JOptionPane.INFORMATION_MESSAGE);
			return;
		} else if (userSex.length() == 0) {
			JOptionPane.showMessageDialog(this, ResourceBundler
					.getString("Login.Option.SexMessage"), ResourceBundler
					.getString("Login.Option.Title"),
					JOptionPane.INFORMATION_MESSAGE);
			return;
		} else {
			try {
				login();
				ClientMainFrame cmf = new ClientMainFrame(txtUserName.getText());
				cmf.initStream(in, out);
				btnOK.setEnabled(false);
				this.dispose();
			} catch (Exception ee) {
				JOptionPane.showMessageDialog(this, ResourceBundler
						.getString("Login.Option.FailMsg"), ResourceBundler
						.getString("Login.Option.Login.Option.FailTitle"),
						JOptionPane.ERROR_MESSAGE);
				return;
			}
		}
	}

	public void doCancel() {
		System.exit(0);
	}

	public void selectSex(ItemEvent e) {
		if (e.getSource() == rbtnBoy) {
			userSex = "Boy";
		}
		if (e.getSource() == rbtnGirl) {
			userSex = "Girl";
		}
		if (e.getSource() == rbtnSecret) {
			userSex = "Secret";
		}
	}

	class PanelKeyListener extends KeyAdapter {

		public PanelKeyListener() {
		}

		public void keyPressed(KeyEvent e) {
			if (e.getKeyCode() == 10) {
				doOK();
			}
		}
	}

	private Socket clientSocket;
	private String serverAddress = "127.0.0.1";
	private int serverPort = 9998;

	private JTextField txtUserName;
	private JRadioButton rbtnBoy, rbtnGirl, rbtnSecret;
	private String userSex = "";

	private JTextField txtServerAddress;
	private JTextField txtServerPort;
	private JButton btnCancel;
	private JButton btnOK;
	// 新添加的代码
	public ImageBox userImage;
	//
	private BufferedReader in;
	private PrintWriter out;

}
