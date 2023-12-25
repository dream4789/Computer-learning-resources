package com.javatrain.chat.gui;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.Toolkit;
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
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.io.RandomAccessFile;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Calendar;

import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.DefaultListCellRenderer;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JPopupMenu;
import javax.swing.JProgressBar;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.JTabbedPane;
import javax.swing.JTextPane;
import javax.swing.ListCellRenderer;
import javax.swing.ListSelectionModel;
import javax.swing.LookAndFeel;
import javax.swing.ScrollPaneConstants;
import javax.swing.SwingConstants;
import javax.swing.UIManager;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.filechooser.FileNameExtensionFilter;
import javax.swing.text.BadLocationException;
import javax.swing.text.SimpleAttributeSet;
import javax.swing.text.StyleConstants;
import javax.swing.text.StyledDocument;

import com.javatrain.chat.util.ImageFactory;
import com.javatrain.chat.util.ListtCellRenderer;
import com.javatrain.chat.util.MyJTextJPane;
import com.javatrain.chat.util.ResourceBundler;
import com.javatrain.chat.util.ResoureceIcon;
import com.javatrain.chat.util.User;

public class ClientMainFrame extends JFrame implements ActionListener, Runnable {

	/**
	 * 
	 */
	private static final long serialVersionUID = -1190821488866456566L;

	/**
	 * @param args
	 */
	public static void main(String[] args) {
	}

	public ClientMainFrame(String userName) {
		super(userName + ResourceBundler.getString("ClientFrame.Title"));
		try {
			UIManager.removeAuxiliaryLookAndFeel((LookAndFeel) Class.forName(
					"com.sun.java.swing.plaf.windows.WindowsLookAndFeel")
					.newInstance());
			UIManager.setLookAndFeel("com.jtattoo.plaf.mcwin.McWinLookAndFeel");
		} catch (Exception e) {
			e.printStackTrace();
		}
		this.userName = userName;
		try {
			InetAddress addr = InetAddress.getLocalHost();
			IP = addr.getHostAddress().toString();

		} catch (Exception e) {
			System.out.print("无法获取本地主机");

		}
		// setSize(950, 600);
		setSize(650, 600);
		setLayout(new BorderLayout());
		setIconImage(ImageFactory.getInstance().getIconImage().getImage());
		JSplitPane outPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT,
				createFriendListPanel(), createMainPanel());
		outPane.setContinuousLayout(true);
		outPane.setOneTouchExpandable(true);
		outPane.setDividerLocation(150);
		add(outPane, BorderLayout.CENTER);

		createPopupMenu();// 编辑菜单
		createChatRecordPopupMenu();// 聊天记录菜单
		editMsgArea.requestFocus();

		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent event) {
				shutDown();
			}
		});
		// setSize(800, 600);
		// pack();
		setLoactionCenter(this);
		setVisible(true);

	}

	private void setLoactionCenter(JFrame jf) {
		Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
		jf.setLocation((dim.width - jf.getWidth()) / 2, (dim.height - jf
				.getHeight()) / 2);

	}

	public void shutDown() {
		try {
			out.println("quit");
			out.flush();
		} catch (Exception ee) {
			ee.printStackTrace();
		} finally {
			System.exit(0);
		}
	}

	public String getUserName() {
		return userName;
	}

	public JComboBox getChatToBox() {
		return chatToCombo;
	}

	public void initStream(BufferedReader in, PrintWriter out) {
		this.in = in;
		this.out = out;
		Thread th = new Thread(this);
		th.start();
	}

	public PrintWriter getOutputStream() {
		return out;
	}

	public BufferedReader getInputStream() {
		return in;
	}

	public Box createFontPanel() {
		String[] fontName = { "宋体", "黑体", "Dialog", "Gulim" };
		String[] fontSize = { "12", "14", "18", "22", "30", "40" };
		String[] fontStyle = { "常规", "斜体", "粗体", "粗斜体" };
		String[] fontColor = { "黑色", "红色", "蓝色", "黄色", "绿色" };
		fontNameCombo = new JComboBox(fontName);
		fontSizeCombo = new JComboBox(fontSize);
		fontStyleCombo = new JComboBox(fontStyle);
		fontColorCombo = new JComboBox(fontColor);

		Box box = Box.createVerticalBox();
		Box box_1 = Box.createHorizontalBox();

		box.add(box_1);

		box.setBorder(BorderFactory.createEmptyBorder(8, 8, 8, 8));

		box_1.add(new JLabel("字体："));
		box_1.add(fontNameCombo);
		fontNameCombo.setRenderer(new DefaultListCellRenderer() {
			/**
			 * 
			 */			
			private static final long serialVersionUID = -5358145499163484816L;

			public Component getListCellRendererComponent(JList list,
					Object value, int index, boolean isSelected,
					boolean cellHasFocus) {
				JLabel jlable = (JLabel) super.getListCellRendererComponent(
						list, value, index, isSelected, cellHasFocus);
				String sValue = (String) value;
				jlable.setText(sValue);
				jlable.setFont(new Font(sValue, jlable.getFont().getStyle(),
						jlable.getFont().getSize()));
				return jlable;
			}
		});

		box_1.add(Box.createHorizontalStrut(8));
		box_1.add(new JLabel("样式："));
		box_1.add(fontStyleCombo);
		fontStyleCombo.setRenderer(new DefaultListCellRenderer() {
			/**
			 * 
			 */
			private static final long serialVersionUID = 1L;

			public Component getListCellRendererComponent(JList list,
					Object value, int index, boolean isSelected,
					boolean cellHasFocus) {
				String sValue = (String) value;
				JLabel jlable = (JLabel) super.getListCellRendererComponent(
						list, value, index, isSelected, cellHasFocus);
				jlable.setText(sValue);// "常规", "斜体", "粗体", "粗斜体"
				int i = new FontAttrib().getSytle(sValue);
				Font font = jlable.getFont();
				jlable.setFont(new Font(font.getName(), i, font.getSize()));
				return jlable;
			}
		});
		box_1.add(Box.createHorizontalStrut(8));
		box_1.add(new JLabel("字号："));
		box_1.add(fontSizeCombo);
		//

		fontSizeCombo.setRenderer(new DefaultListCellRenderer() {
			public Component getListCellRendererComponent(JList list,
					Object value, int index, boolean isSelected,
					boolean cellHasFocus) {
				String sValue = (String) value;
				JLabel jlable = (JLabel) super.getListCellRendererComponent(
						list, value, index, isSelected, cellHasFocus);
				jlable.setText(sValue);
				Font font = jlable.getFont();
				jlable.setFont(new Font(font.getName(), font.getStyle(),
						Integer.parseInt(sValue)));
				return jlable;
			}
		});

		//
		box_1.add(Box.createHorizontalStrut(8));
		box_1.add(new JLabel("颜色："));
		box_1.add(fontColorCombo);
		fontColorCombo.setRenderer(new DefaultListCellRenderer() {
			public Component getListCellRendererComponent(JList list,
					Object value, int index, boolean isSelected,
					boolean cellHasFocus) {
				String sValue = (String) value;
				JLabel jlable = (JLabel) super.getListCellRendererComponent(
						list, value, index, isSelected, cellHasFocus);
				jlable.setText(sValue);

				jlable.setForeground(new FontAttrib().getColor(sValue));

				return jlable;
			}
		});
		// 待处理
		box_1.add(new JLabel("     "));
		jbConrolDoOpenUp = new JButton("展开");
		jbConrolDoOpenUp.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				doOpenUp(e.getActionCommand());
			}
		});
		box_1.add(jbConrolDoOpenUp);
		//
		box_1.add(Box.createHorizontalStrut(8));
		box_1.add(Box.createHorizontalStrut(8));

		return box;
	}

	// 伸展
	public void doOpenUp(String command) {
		if (command.equalsIgnoreCase("展开")) {
			setSize(800, 600);
			mainPanel.add(mainRightBox, BorderLayout.EAST);
			jbConrolDoOpenUp.setText("隐藏");
		} else if (command.equalsIgnoreCase("隐藏")) {
			setSize(650, 600);
			mainPanel.remove(mainRightBox);
			jbConrolDoOpenUp.setText("展开");
		}
		mainPanel.validate();
		mainPanel.repaint();
	}

	public Box createMsgPanel() {
		Box box = Box.createVerticalBox();
		JSplitPane jsplitPane = null;
		commonMsgArea = new MyJTextJPane();
		commonMsgArea.setBorder(BorderFactory.createMatteBorder(2, 2, 2, 1,
				Color.DARK_GRAY));
		commonMsgArea.setEditable(false);
		commonMsgArea.getScrollableUnitIncrement(new Rectangle(10, 20),
				SwingConstants.VERTICAL, -2);

		commonMsgAreaScroll = new JScrollPane(commonMsgArea);
		commonMsgAreaScroll
				.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);// 设置滚动条什么时候出现
		commonMsgAreaScroll
				.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
		commonMsgAreaScroll.setBorder(BorderFactory.createTitledBorder("群聊区"));

		jtabdedPane = new JTabbedPane();
		jtabdedPane.addTab("群聊区", commonMsgAreaScroll);
// panel.add(jtabdedPane, BorderLayout.CENTER);
//box.add(jtabdedPane);
// box.add(commonMsgAreaScroll);
		box.add(Box.createVerticalStrut(2));

		privateMsgArea = new MyJTextJPane();
		privateMsgArea.setBorder(BorderFactory.createMatteBorder(2, 2, 2, 1,
				Color.DARK_GRAY));
		privateMsgArea.setEditable(false);
		privateMsgAreaScroll = new JScrollPane(privateMsgArea);
		privateMsgAreaScroll
				.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
		privateMsgAreaScroll
				.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
		privateMsgAreaScroll.setBorder(BorderFactory.createTitledBorder("悄悄话"));

//box.add(privateMsgAreaScroll);

/*       JSplitPane innerPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT,
		 commonMsgAreaScroll, privateMsgAreaScroll);
		 innerPane.setContinuousLayout(true);
		 innerPane.setOneTouchExpandable(true);
*/
		jsplitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT, jtabdedPane, privateMsgAreaScroll);
		jsplitPane.setContinuousLayout(true);
		jsplitPane.setOneTouchExpandable(true);
		jsplitPane.setDividerSize(20);
		jsplitPane.setDividerLocation(this.getHeight()/3);
		box.add(jsplitPane);
		
		
		return box;
	}

	// 抖屏
	private void doShakeFrame() {
		int x = getX();
		int y = getY();
		for (int i = 0; i < 20; i++) {
			if ((i & 1) == 0) {
				x += 10;
				y += 10;
			} else {
				x -= 10;
				y -= 10;
			}
			setLocation(x, y);
			try {
				Thread.sleep(1);
			} catch (InterruptedException e1) {
				e1.printStackTrace();
			}
		}
	}

	public JPanel createEditPanel() {
		JPanel panel = new JPanel();
		panel.setLayout(new BorderLayout());

		JPanel tmpPanel1 = new JPanel(new BorderLayout());
		JPanel tmpPanel2 = new JPanel(new FlowLayout(FlowLayout.LEFT));
		editMsgArea = new MyJTextJPane();
		editMsgArea.setBorder(BorderFactory.createMatteBorder(2, 2, 2, 1,
				Color.LIGHT_GRAY));
		editMsgArea.setBackground(new Color(248, 243, 209));
		//editMsgArea.setLineWrap(true);
		editMsgArea.setPreferredSize(new Dimension(this.getWidth(),100));
		//editMsgArea.setWrapStyleWord(true);
		editMsgArea.addKeyListener(new KeyAdapter() {
			public void keyPressed(KeyEvent e) {
				if (e.getKeyCode() == 10) {
					sendMsg();
				}
			}
		});
		editMsgAreaScroll = new JScrollPane(editMsgArea);
		editMsgAreaScroll
				.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
		editMsgAreaScroll.setBorder(BorderFactory.createTitledBorder("编辑区"));
		tmpPanel1.add(editMsgAreaScroll, BorderLayout.CENTER);

		sentButton = new JButton("发送");
		sentButton.addActionListener(this);

		shakeFrame = new JButton("抖屏");
		shakeFrame.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				// 向对方发送抖屏
				myWords = "抖屏";
				if (withWho.equals("所有人")) {
					outMsg = myWords + "&" + "shakeFrame";
					out.println(outMsg);
					out.flush();
					insert(privateMsgArea, userName + "对所有人发送：" + myWords);
				} else if (isPrivateTalk) {
					outMsg = "withWho" + "&" + "privateTure" + "&" + withWho
							+ "&" + myWords + "&" + "shakeFrame";
					insert(privateMsgArea, "您对『" + withWho + "』发送: " + myWords);
					out.println(outMsg);
					out.flush();
				}

				// 自己抖屏
				doShakeFrame();

			}
		});

		screenCapture = new JButton("截屏");
		screenCapture.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				// TODO Auto-generated method stub

			}

		});
		tmpPanel2.add(new JLabel("对  "));
		chatToCombo = new JComboBox();
		chatToCombo.addItem("所有人");
		chatToCombo.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				// TODO Auto-generated method stub
				withWho = (String) chatToCombo.getSelectedItem();
			}

		});
		jcbPrivate = new JCheckBox("私聊");
		jcbPrivate.addItemListener(new ItemListener() {

			@Override
			public void itemStateChanged(ItemEvent arg0) {
				// TODO Auto-generated method stub
				if (arg0.getSource() == jcbPrivate) {
					if (arg0.getStateChange() == ItemEvent.SELECTED) {
						isPrivateTalk = true;
					} else {
						isPrivateTalk = false;
					}
				}
			}

		});
		// 待处理
		 JButton jbchatRecord = new JButton("插入图标");
		 jbchatRecord.addActionListener(new ActionListener(){

			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				EventQueue.invokeLater(new Runnable(){

					@Override
					public void run() {
						// TODO Auto-generated method stub
						/*//添加图标
						insertIcon();*/
						new ResoureceIcon(ClientMainFrame.this);
					}});
			}});
		//
		tmpPanel2.add(chatToCombo);
		tmpPanel2.add(new JLabel(" "));
		tmpPanel2.add(jcbPrivate);
		tmpPanel2.add(new JLabel("   "));
		tmpPanel2.add(screenCapture);
		tmpPanel2.add(new JLabel("   "));
		tmpPanel2.add(shakeFrame);
		tmpPanel2.add(new JLabel("   "));
		tmpPanel2.add(sentButton);
		
		tmpPanel2.add(new JLabel("   ")); 
		tmpPanel2.add(jbchatRecord);
		 

		panel.add(tmpPanel1, BorderLayout.NORTH);
		panel.add(tmpPanel2, BorderLayout.SOUTH);
		return panel;
	}

/*	//添加图标
	public void insertIcon(){
		
		JFileChooser f = new JFileChooser(); // 查找文件
		f.showOpenDialog(null);
		StyledDocument doc = editMsgArea.getStyledDocument();
		editMsgArea.setCaretPosition(doc.getLength()); // 设置插入位置
		editMsgArea.insertIcon(new ImageIcon(f.getSelectedFile().getPath()),f.getSelectedFile().getName()); // 插入图片
		editMsgArea.setCaretPosition(doc.getLength());
		
		 * try { // 插入文本 FontAttrib attrib = new FontAttrib();
		 * doc.insertString(doc.getLength(), attrib.getText() + "\n", attrib
		 * .getAttrSet()); } catch (BadLocationException e) {
		 * e.printStackTrace(); }
		 // 这样做可以换行
	}*/
	
	public JPanel createFriendListPanel() {
		JPanel friendPanel = new JPanel();
		// friendPanel.setPreferredSize(new Dimension(60,this.getHeight()));
		friendPanel.setLayout(new BorderLayout());

		friendPanel.add(new JLabel(ResourceBundler
				.getString("ClientFrame.friendList")), BorderLayout.NORTH);

		listModel = new DefaultListModel();
		// ListDataListener
		friendList = new JList(listModel);
		// 给每一个用户渲染
		ListCellRenderer listCellRender = new ListtCellRenderer();
		friendList.setCellRenderer(listCellRender);

		// end

		friendList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		friendList.addListSelectionListener(new ListSelectionListener() {

			@Override
			public void valueChanged(ListSelectionEvent arg0) {
				// TODO Auto-generated method stub
				try {
					User select = (User) friendList.getSelectedValue();
					if (select != null) {
						// System.out.println("----------");
						String[] userInfo = select.toString().split("〖");
						String name = userInfo[0].trim();

						if (!name.equals(getUserName())) {
							int count = getChatToBox().getItemCount();
							for (int i = 0; i < count; i++) {
								getChatToBox().setSelectedIndex(i);
								String strName = (String) getChatToBox()
										.getSelectedItem();
								if (name.equals(strName)) {
									return;
								}
							}
							getChatToBox().addItem(name);
						}
					}
				} catch (Exception ee) {
					ee.printStackTrace();
				}
			}

		});
		friendPanel.add(new JScrollPane(friendList), BorderLayout.CENTER);

		refreashButton = new JButton(ResourceBundler
				.getString("ClientFrame.Button.refreshFriend"));
		refreashButton.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				// TODO Auto-generated method stub
				try {
					listModel.clear();
					getOutputStream().println("refurbish");
					getOutputStream().flush();
				} catch (Exception ee) {
				}
			}

		});
		friendPanel.add(refreashButton, BorderLayout.SOUTH);
		return friendPanel;
	}

	public Box createRightUpBox() {
		Box box = Box.createVerticalBox();
		Box box1 = Box.createHorizontalBox();
		acceptfile = new JButton("接收文件");
		acceptfile.addActionListener(this);
		refusefile = new JButton("拒绝文件");
		refusefile.addActionListener(this);
		box1.add(acceptfile, BorderLayout.WEST);
		box1.add(refusefile, BorderLayout.EAST);
		acceptProgressbar = new JProgressBar();
		acceptProgressbar.setOrientation(JProgressBar.HORIZONTAL);
		acceptProgressbar.setValue(0);
		acceptProgressbar.setStringPainted(true);
		box.add(box1);
		box.add(acceptProgressbar);
		return box;
	}

	public Box createRightMiddleBox() {
		Box box = Box.createVerticalBox();
		Box box1 = Box.createHorizontalBox();
		sendfile = new JButton("发送文件");
		sendfile.addActionListener(this);
		cancelsendfile = new JButton("取消发送");
		cancelsendfile.addActionListener(this);
		box1.add(sendfile, BorderLayout.WEST);
		box1.add(cancelsendfile, BorderLayout.EAST);
		sendProgressbar = new JProgressBar();
		sendProgressbar.setOrientation(JProgressBar.HORIZONTAL);
		sendProgressbar.setValue(0);
		sendProgressbar.setStringPainted(true);
		box.add(box1);
		box.add(sendProgressbar);
		return box;
	}

	// 编辑主界面
	public JPanel createMainPanel() {
		// JPanel mainPanel = new JPanel();
		mainPanel = new JPanel();
		mainPanel.setLayout(new BorderLayout());
		mainLeftBox = Box.createVerticalBox();
		mainLeftBox.add(createFontPanel(), BorderLayout.NORTH);
		JPanel panel = new JPanel();
		panel.setLayout(new BorderLayout());

		panel.add(createMsgPanel(), BorderLayout.CENTER);
		panel.add(createEditPanel(), BorderLayout.SOUTH);
		mainLeftBox.add(panel, BorderLayout.CENTER);
		// mainLeftBox.add(createEditPanel(), BorderLayout.SOUTH);

		mainRightBox = Box.createVerticalBox();
		mainRightBox.add(Box.createVerticalStrut(10));
		mainRightBox.add(createRightUpBox());
		mainRightBox.add(Box.createVerticalStrut(10));

		acceptfileArea = new JTextPane();
		acceptfileArea.setEditable(false);

		sendfileArea = new DragbleTextArea();
		sendfileArea.setEditable(false);
		// /
		sendfileArea.setLineWrap(true);
		sendfileArea.setWrapStyleWord(true);
		//
		JScrollPane scrollpane = new JScrollPane(acceptfileArea);
		scrollpane
				.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);

		scrollpane.setBorder(BorderFactory.createTitledBorder("待接收的文件"));
		scrollpane.setBackground(new Color(188, 193, 199));
		mainRightBox.add(scrollpane, BorderLayout.CENTER);
		mainRightBox.setBackground(new Color(250, 0, 2));

		mainRightBox.add(Box.createVerticalStrut(10));
		mainRightBox.add(createRightMiddleBox(), BorderLayout.CENTER);

		JScrollPane scrollpane2 = new JScrollPane(sendfileArea);
		scrollpane2
				.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);

		scrollpane2.setBorder(BorderFactory.createTitledBorder("欲发送的文件"));
		scrollpane2.setBackground(new Color(188, 193, 199));
		mainRightBox.add(scrollpane2, BorderLayout.CENTER);
		mainRightBox.setBackground(new Color(0, 0, 255));

		mainPanel.add(mainLeftBox, BorderLayout.CENTER);
		// mainPanel.add(mainRightBox, BorderLayout.EAST);

		return mainPanel;
	}

	// 创建聊天记录弹出菜单
	public void createChatRecordPopupMenu() {
		final JPopupMenu popup = new JPopupMenu();
		JMenuItem menuItem1 = new JMenuItem(ResourceBundler
				.getString("ClientFrame.MenuItem.title3"));
		menuItem1.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				// TODO Auto-generated method stub
				// commonMsgArea.setText("");
				Object ob = friendList.getSelectedValue();
				if(ob == null){
					return ;
				}
				User user = (User) ob;
				
				if (user.getUserName().compareTo(userName) == 0) {
					return;// jtabdedPane.getTabCount() == 1
					// crateChatRecordPanel()
				} else if (!user.isOpenChatRecord()) {
					user.setOpenChatRecord(true);
					jtabdedPane.addTab(user.getUserName(), new ChatRecordPane(
							user));
					user.setIndex(jtabdedPane.getTabCount() - 1);

					jtabdedPane.setSelectedIndex(user.getIndex());
				} else {
					jtabdedPane.getTabCount();
					jtabdedPane.setSelectedIndex(user.getIndex());
				}
			}

		});
		popup.add(menuItem1);
		friendList.addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e) {
				if (e.isPopupTrigger()) {
					popup.show(e.getComponent(), e.getX(), e.getY());
				}
			}

			public void mouseReleased(MouseEvent e) {
				if (e.isPopupTrigger()) {
					popup.show(e.getComponent(), e.getX(), e.getY());
				}
			}
		});
	}

	// 创建聊天记录面板
	public JPanel crateChatRecordPanel() {
		JPanel chatRecord = new JPanel();
		chatRecord.setLayout(new BorderLayout());
		chatRecordArea = new JTextPane();
		chatRecordArea.setBorder(BorderFactory.createMatteBorder(2, 2, 2, 1,
				Color.DARK_GRAY));
		chatRecordArea.setEditable(false);
		chatRecordArea.getScrollableUnitIncrement(new Rectangle(10, 20),
				SwingConstants.VERTICAL, -2);
		chatRecordArea.setBorder(BorderFactory.createTitledBorder("聊天记录"));
		JScrollPane jscrllPane = new JScrollPane(chatRecordArea);
		jscrllPane
				.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);// 设置滚动条什么时候出现
		jscrllPane
				.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);

		chatRecord.add(jscrllPane, BorderLayout.CENTER);
		chatRecord.add(createControlPanel(), BorderLayout.SOUTH);

		return chatRecord;
	}

	// 创建控制面板
	public JPanel createControlPanel() {
		JPanel jpanelControl = new JPanel();
		JLabel spaceLabel = new JLabel("");

		JButton jbSave = new JButton("保存记录");
		jbSave.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub

			}
		});

		JButton jbQuery = new JButton("查询");
		jbQuery.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				// 发送查询命令
				// 命令格式 command&sql&fromname&toname
				User user = (User) friendList.getSelectedValue();
				String command = "command&sql&" + userName + "&"
						+ user.getUserName() + "&" + "msg_Date";
				out.println(command);
				out.flush();

			}
		});

		JButton jbCancel = new JButton("取消");
		jpanelControl.setLayout(new FlowLayout(FlowLayout.RIGHT, 20, 10));
		jbCancel.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				jtabdedPane.remove(1);
			}
		});

		spaceLabel.setPreferredSize(new Dimension(10, 10));
		jpanelControl.add(jbSave);
		jpanelControl.add(spaceLabel);
		jpanelControl.add(jbQuery);
		jpanelControl.add(jbCancel);

		return jpanelControl;
	}

	// 创建编辑区的弹出菜单
	public void createPopupMenu() {

		final JPopupMenu popup = new JPopupMenu();
		JMenuItem menuItem1 = new JMenuItem(ResourceBundler
				.getString("ClientFrame.MenuItem.title1"));
		menuItem1.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				// TODO Auto-generated method stub
				commonMsgArea.setText("");
			}

		});
		popup.add(menuItem1);
		JMenuItem MenuItem2 = new JMenuItem(ResourceBundler
				.getString("ClientFrame.MenuItem.title2"));
		MenuItem2.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				// TODO Auto-generated method stub
				privateMsgArea.setText("");
			}

		});
		popup.add(MenuItem2);

		commonMsgArea.addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e) {
				if (e.isPopupTrigger()) {
					popup.show(e.getComponent(), e.getX(), e.getY());
				}
			}

			public void mouseReleased(MouseEvent e) {
				if (e.isPopupTrigger()) {
					popup.show(e.getComponent(), e.getX(), e.getY());
				}
			}
		});
		privateMsgArea.addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e) {
				if (e.isPopupTrigger()) {
					popup.show(e.getComponent(), e.getX(), e.getY());
				}
			}

			public void mouseReleased(MouseEvent e) {
				if (e.isPopupTrigger()) {
					popup.show(e.getComponent(), e.getX(), e.getY());
				}
			}
		});
	}

	// 插入聊天记录
	private void insertChatRecord(ChatRecordPane chrp, String sqlMsg) {
		if (chrp == null) {
			return;
		}
		JTextPane j = chrp.getChatRecordArea();
		StyledDocument styleDocument = j.getStyledDocument();
		try { // 插入文本
			styleDocument.insertString(styleDocument.getLength(), sqlMsg,
					getFontAttrib().getAttrSet());
			// this.editMsgArea.setText("");
			int dx = (int) j.getBounds().getCenterX();
			int dy = (int) (j.getBounds().getCenterX() + j.getBounds()
					.getHeight());
			Point p = new Point(dx, dy);
			chrp.getJscrllPane().getViewport().setViewPosition(p);
		} catch (BadLocationException e) {
			e.printStackTrace();
		}
	}

	// 插入普通聊天信息
	private void insert(JTextPane j, String words) {
		// Date noeTime = new Date();
		// SimpleDateFormat matter = new SimpleDateFormat("HH:mm:ss ");
		// @SuppressWarnings("unused")
		int y, mi, d, h, m, s;
		Calendar cal = Calendar.getInstance();
		y = cal.get(Calendar.YEAR);
		mi = cal.get(Calendar.MONTH);
		d = cal.get(Calendar.DATE);
		h = cal.get(Calendar.HOUR_OF_DAY);
		m = cal.get(Calendar.MINUTE);
		s = cal.get(Calendar.SECOND);
		MyJTextJPane jj = (MyJTextJPane) j;
		styleDocument = jj.getStyledDocument();
		try { // 插入文本
			/*
			 * styleDocument.insertString(styleDocument.getLength(), h + ":" + m
			 * + ":" + s + " " + words + "\r\n", getFontAttrib() .getAttrSet());
			 */
			System.out.println("-------" + words);
			String sMsg[] = words.split("/");
			jj.setCaretPosition(styleDocument.getLength());
			if (sMsg != null) {
				int length = sMsg.length;
				for (int i = 0; i < length; i++) {

					int start = sMsg[i].indexOf("[");
					int last = sMsg[i].lastIndexOf("]");

					if (start != -1 && last != -1) {
						// String msgHand = words.substring(0, start);
						String key = sMsg[i].substring(start + 1, last);
						// String msgTail = words.substring(last + 1);
						// System.out.println("icon   :["+key+"]");
						// styleDocument.insertString(styleDocument.getLength(),
						// h
						// + ":" + m + ":" + s + " " + msgHand,
						// getFontAttrib().getAttrSet());
						jj.setCaretPosition(styleDocument.getLength());
						jj.insertIcon(ImageFactory.getInstance().getinsertIcon(
								key.trim()), "");

						/*
						 * styleDocument.insertString(styleDocument.getLength(),
						 * msgTail + "\r\n", getFontAttrib().getAttrSet());
						 */
					} else {
						if (i == 0) {
							styleDocument.insertString(styleDocument
									.getLength(), h + ":" + m + ":" + s + " "
									+ sMsg[0], getFontAttrib().getAttrSet());
						} else if (!sMsg[i].equals("")) {
							styleDocument.insertString(styleDocument
									.getLength(), sMsg[i], getFontAttrib()
									.getAttrSet());
						}
					}
				}
				styleDocument.insertString(styleDocument.getLength(), " \r\n",
						getFontAttrib().getAttrSet());
			} else {
				styleDocument.insertString(styleDocument.getLength(), h + ":"
						+ m + ":" + s + " " + words + "\r\n", getFontAttrib()
						.getAttrSet());
			}

			// styleDocumen
			// j.getcom
			this.editMsgArea.setText("");

			int dx = (int) j.getBounds().getCenterX();
			int dy = (int) (j.getBounds().getCenterX() + j.getBounds()
					.getHeight());
			Point p = new Point(dx, dy);
			// if()
			if (j == privateMsgArea) {
				privateMsgAreaScroll.getViewport().setViewPosition(p);
			} else if (j == commonMsgArea) {
				commonMsgAreaScroll.getViewport().setViewPosition(p);
			}
		} catch (BadLocationException e) {
			e.printStackTrace();
		}

	}

	private FontAttrib getFontAttrib() {
		FontAttrib att = new FontAttrib();
		att.setText(editMsgArea.getText());
		att.setName((String) fontNameCombo.getSelectedItem());
		att.setSize(Integer.parseInt((String) fontSizeCombo.getSelectedItem()));
		String temp_style = (String) fontStyleCombo.getSelectedItem();
		if (temp_style.equals("常规")) {
			att.setStyle(FontAttrib.GENERAL);
		} else if (temp_style.equals("粗体")) {
			att.setStyle(FontAttrib.BOLD);
		} else if (temp_style.equals("斜体")) {
			att.setStyle(FontAttrib.ITALIC);
		} else if (temp_style.equals("粗斜体")) {
			att.setStyle(FontAttrib.BOLD_ITALIC);
		}
		String temp_color = (String) fontColorCombo.getSelectedItem();
		if (temp_color.equals("黑色")) {
			att.setColor(new Color(0, 0, 0));
		} else if (temp_color.equals("红色")) {
			att.setColor(new Color(255, 0, 0));
		} else if (temp_color.equals("蓝色")) {
			att.setColor(new Color(0, 0, 255));
		} else if (temp_color.equals("黄色")) {
			att.setColor(new Color(255, 255, 0));
		} else if (temp_color.equals("绿色")) {
			att.setColor(new Color(0, 255, 0));
		}

		return att;
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		if (e.getSource() == acceptfile) { // 接收文件传输按钮
			if (this.acceptfileArea.getText().length() == 0) {
				this.insert(privateMsgArea, "没有文件需要接受");
			} else {
				EventQueue.invokeLater(new Runnable() {
					@Override
					public void run() {
						// TODO Auto-generated method stub
						// 接受文件
						acceptFile();
					}
				});
			}

		}
		if (e.getSource() == refusefile) {// 拒绝文件传输按钮
			if (this.acceptfileArea.getText().length() == 0) {
				this.insert(privateMsgArea, "没有文件需要接收，拒绝无效");
			} else {
				String[] acpfile = fileMsg.split("&");
				out.println("refusefile" + "&" + acpfile[1]);
				out.flush();
				this.insert(privateMsgArea, "你取消了 " + acpfile[1] + " 发来的文件");
				this.acceptfileArea.setText("");
				acceptboolean = false;
				acceptfile.setEnabled(true);
			}
		}
		if (e.getSource() == sendfile) {// 发送文件按钮
			if (withWho.endsWith("所有人")) {
				this.insert(privateMsgArea, "请选择要发送的目标");
			} else {
				nameOfSendFile = "";
				// System.out.println("-----");

				if (this.sendfileArea.getText().length() != 0) {
					nameOfSendFile = this.sendfileArea.getText();
//System.out.println("file name: " + nameOfSendFile);
				}
/*else {

					JFileChooser chooser = new JFileChooser();
					FileNameExtensionFilter filter = new FileNameExtensionFilter(
							"JPG & GIF Images", "jpg", "gif");
					chooser.setFileFilter(filter);
					int returnVal = chooser.showOpenDialog(null);
					if (returnVal == JFileChooser.APPROVE_OPTION) {
						System.out.println("You chose to open this file: "
								+ chooser.getSelectedFile().getName());
						sendfileArea.append(chooser.getSelectedFile()
								.getAbsolutePath());
					}
                      return;
}*/
				if (nameOfSendFile.length() == 0)// 没有获得需要发送的文件
				{
					// 加载文件 避免程序出现假死
					EventQueue.invokeLater(new Runnable() {
						@Override
						public void run() {
							// TODO Auto-generated method stub
							addSendFile();
						}
					});				
					
		    	} else { // 发送文件
					sendFileThread = new SendFileThread();
					sendboolean = true;
					sendfile.setEnabled(false);
					sendFileThread.start();
				}
			}
		}
		if (e.getSource() == cancelsendfile) {// 取消文件发送按钮
			if (this.sendfileArea.getText().length() == 0) {
				this.insert(privateMsgArea, "没有文件发送，不需要取消");
			} else {

				this.insert(privateMsgArea, "你取消了文件发送");
				this.sendfileArea.setText("");

				if (this.sendboolean) {
					out.println("cancelsendfile" + "&" + withWho);
					out.flush();
					sendboolean = false;
					sendfile.setEnabled(true);
				}
			}
		}
		if (e.getSource() == sentButton) {
			sendMsg();
		}
	}
	
	// 添加文件
	private void addSendFile() {
		JFileChooser chooser = new JFileChooser();
		FileNameExtensionFilter filter = new FileNameExtensionFilter(
				"JPG & GIF Images", "jpg", "gif");
		// chooser.setFileFilter(filter);
		int returnVal = chooser.showOpenDialog(null);
		if (returnVal == JFileChooser.APPROVE_OPTION) {
			System.out.println("You chose to open this file: "
					+ chooser.getSelectedFile().getName());
			sendfileArea.append(chooser.getSelectedFile().getAbsolutePath());
		} else {
			insert(privateMsgArea, "没有文件发送，请选择欲发送的文件或将其拖入待发送文件框");
		}
	}
	//接收文件

	// 接收文件
	private void acceptFile() {
		String[] acpfile = fileMsg.split("&");
		System.out.println("accepted FileName: " + acpfile[1]);
		out.println("acceptfile" + "&" + acpfile[1]);
		out.flush();
		acceptFileThread = new AcceptFileThread();
		acceptboolean = true;
		String filepath = "F:\\java.train";

		JFileChooser jfc = new JFileChooser();
		int result = jfc.showSaveDialog(this);
		File file = null;
		if (result == JFileChooser.APPROVE_OPTION) {
			file = jfc.getSelectedFile();
		}

		filepath = file.getPath();

		acceptFileThread.initIpPort(acpfile[3], (Integer.parseInt(acpfile[4])),
				filepath);
		acceptfile.setEnabled(false);
		acceptFileThread.start();// 
	}

	//发送信息
	public void sendMsg() {
		try {
			myWords = editMsgArea.getText().replaceAll("//", "/");
			if ((myWords.trim()).length() != 0) {
				if (withWho.equals("所有人")) {
					outMsg = myWords;
					out.println(outMsg);
					out.flush();
					insert(privateMsgArea, userName + "：" + myWords);
				} else {
					outMsg = "withWho" + "&" + "privateFalse" + "&" + withWho
							+ "&" + myWords;
					if (isPrivateTalk) {
						outMsg = "withWho" + "&" + "privateTure" + "&"
								+ withWho + "&" + myWords;
						insert(privateMsgArea, "您对『" + withWho + "』说: "
								+ myWords);

					} else {
						insert(privateMsgArea, userName + " 对『" + withWho
								+ "』说: " + myWords);
					}
					out.println(outMsg);
					out.flush();
				}
			}
		} catch (Exception ee) {
			System.out.println(ee);
			insert(privateMsgArea, "与服务器连接中断,请重新登录！");
		} finally {
			editMsgArea.setText("");
		}
	}

	@Override
	public void run() {
		// TODO Auto-generated method stub
		String inMsg;
		acceptFileThread = new AcceptFileThread();
		while (true) {
			try {
				if ((inMsg = in.readLine()) != null) {

					/** 已经在聊天室里的人显示到列表中 */
					if (inMsg.startsWith("old")) {
						String[] userInfo = inMsg.split("&");
						User user = new User(userInfo[1], userInfo[2],
								userInfo[3]);
						user.setUserID(userInfo[4]);
						/*
						 * listModel.addElement(userInfo[1] + " 〖" + userInfo[2]
						 * + "〗" + userInfo[3]);
						 */
						listModel.addElement(user);

					} else if (inMsg.startsWith("new")) { // 接收第一次服务器发送欢迎信息
						String[] userInfo = inMsg.split("&");
						// System.out.println("---" + inMsg);
						User user = new User(userInfo[1], userInfo[2],
								userInfo[3]);
						user.setUserID(userInfo[4]);
						/*
						 * listModel.addElement(userInfo[1] + " 〖" + userInfo[2]
						 * + "〗");
						 */
						listModel.addElement(user);
						insert(commonMsgArea, userInfo[1] + "上线了");
						insert(privateMsgArea, userInfo[1] + "上线了");

					} else if (inMsg.startsWith("quit")) {
						String[] userInfo = inMsg.split("&");
						System.out.println(" --- " + userInfo[1]);
						int size = listModel.getSize();
						User user = null;
						for (int i = 0; i < size; i++) {
							user = (User) listModel.get(i);
							if (user.equals(userInfo[1])) {
								listModel.remove(i);
								System.out.println("删除");
								break;
							}
						}

					} else if (inMsg != null) {
						/** 一般消息 */
						String[] sendfile = inMsg.split("&");
						if (sendfile[0].compareTo("cancelsendfile") == 0) {
							insert(privateMsgArea, sendfile[1] + "取消了文件发送");
							acceptboolean = false;

							acceptfile.setEnabled(true);
							acceptfileArea.setText("");
							// this.acceptfileArea.s
						} else if (sendfile[0].compareTo("sendfile") == 0) {
							/** 如果是传送文件请求 */
							if (jbConrolDoOpenUp.getText().compareTo("展开") == 0) {
								doOpenUp("展开");
//System.out.println("------------------------");
							}
							// acceptfileArea.setW

							String[] sprit = sendfile[2].split(File.separator
									+ File.separator);
							int length = sprit.length;
							StringBuffer text = new StringBuffer();
							for (int i = 0; i < length; i++) {
								text.append(sprit[i] + "\n");

							}
							acceptfileArea.setText(text.toString());
							// acceptfileArea.setText(sendfile[2]);
							insert(privateMsgArea, sendfile[1] + " 发来文件");
							fileMsg = inMsg;
						} else if (sendfile[0].compareTo("acceptfile") == 0) {
							// String[] acceptfile = inmsg.split("&");
							// acceptfileArea.setText(sendfile[2]);
							insert(privateMsgArea, sendfile[1] + " 接收了你发的文件");

						} else if (sendfile[0].compareTo("refusefile") == 0) {

							insert(privateMsgArea, sendfile[1] + " 拒绝了你发的文件");
							sendboolean = false;
							this.sendfile.setEnabled(true);
							this.sendfileArea.setText("");

						} else if (sendfile[0].compareTo("withWho") == 0) {
							if (sendfile[2].equals(userName)) { // 如果是发给自己的消息

								insert(privateMsgArea, sendfile[1] + "对『"
										+ sendfile[2] + "』说:" + sendfile[3]);

							}
							insert(commonMsgArea, sendfile[1] + "对『"
									+ sendfile[2] + "』说:" + sendfile[3]);

							// System.out.println("=============" + inMsg);

						} else if (inMsg.startsWith("Command")) {// 接受sql查询语句
							// System.out.println(inMsg);
							String sqlMsg[] = inMsg.split("&");
							String sMsg = "";
							String id = null;
							if (sqlMsg[1].compareTo("sql") == 0) {
								sMsg = sqlMsg[5] + "\n" + sqlMsg[2] + " 对 "
										+ sqlMsg[3] + " 说: " + sqlMsg[4] + "\n";
								id = sqlMsg[6];
								// chatRecordArea.
							} else if (sqlMsg[1].compareTo("Nosql") == 0) {
								sMsg = sqlMsg[2] + "\n";
								id = sqlMsg[3];
							}
							// System.out.println("----"+id);
							// getChatRecordAreaFromID(id);
							insertChatRecord(getChatRecordAreaFromID(id), sMsg);
						} else if (inMsg.startsWith("privateTalk")) {

//System.out.println("icon --"+inMsg);
							String showmsg[] = inMsg.split("&");

							if (showmsg[1].equals(userName)) {// 如果接收到的是我自己发送的消息
		
								//}else{
								insert(commonMsgArea, "您对『" + showmsg[2]
										+ "』说: " + showmsg[3]);
								//}
								// commonArea.setCaretPosition(commonArea.getText
								// ().length());
							} else { // 接收到的是别人发给我的消息（悄悄话）
								insert(privateMsgArea, "『" + showmsg[1]
										+ "』对您说: " + showmsg[3]);
								if (showmsg.length >= 5) {
									if (showmsg[4].compareTo("shakeFrame") == 0) {
										doShakeFrame();
									}
								}
							}
							// myMsgArea.setCaretPosition(myMsgArea.getText().
							// length());
						} else {
							int itage = inMsg.indexOf("&");
							if (itage != -1) {
								String command[] = inMsg.split("&");
								if (command[1].compareTo("shakeFrame") == 0) {
									doShakeFrame();
								}
								inMsg = inMsg.substring(0, itage);
							}
							insert(commonMsgArea, inMsg);
						}
					}
				}
			} catch (Exception ee) {
				ee.printStackTrace();
				insert(privateMsgArea, "与服务器中断，请重新登录！");
				in = null;
				out = null;
				return;
			}
		}
	}

	// 获取相应的组件
/*	public JTextPane getChatRecordAreaFromID(String id) {
		int index = jtabdedPane.getSelectedIndex();
		// for (int i = 0; i < size; i++) {
		ChatRecordPane crp = (ChatRecordPane) jtabdedPane
				.getSelectedComponent();
		// System.out.println(crp + "[   ]" + id);
		if (crp.user.getUserID().equals(id)) {
			jtabdedPane.setSelectedIndex(index);
			return crp.getChatRecordArea();
		}
		// }
		return null;
	}*/
	public ChatRecordPane getChatRecordAreaFromID(String id) {
		int index = jtabdedPane.getSelectedIndex();
		// for (int i = 0; i < size; i++) {
		ChatRecordPane crp = (ChatRecordPane) jtabdedPane
				.getSelectedComponent();
		// System.out.println(crp + "[   ]" + id);
		if (crp.user.getUserID().equals(id)) {
			jtabdedPane.setSelectedIndex(index);
			return crp;
		}
		// }
		return null;
	}
	// 显示聊天记录面板
	class ChatRecordPane extends JPanel {
		JTextPane chatRecordArea;
		JScrollPane jscrllPane;
		User user;

		public JTextPane getChatRecordArea() {
			return chatRecordArea;
		}

		ChatRecordPane() {

		}

		ChatRecordPane(User user) {
			this.user = user;
			init();
		}

		public JScrollPane getJscrllPane() {
			return jscrllPane;
		}

		private void init() {
			// TODO Auto-generated method stub
			setLayout(new BorderLayout());
			chatRecordArea = new JTextPane();
			chatRecordArea.setBorder(BorderFactory.createMatteBorder(2, 2, 2,
					1, Color.DARK_GRAY));
			chatRecordArea.setEditable(false);
			chatRecordArea.getScrollableUnitIncrement(new Rectangle(10, 20),
					SwingConstants.VERTICAL, -2);
			chatRecordArea.setBorder(BorderFactory.createTitledBorder("聊天记录"));
			jscrllPane = new JScrollPane(chatRecordArea);
			jscrllPane
					.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);// 设置滚动条什么时候出现
			jscrllPane
					.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);

			add(jscrllPane, BorderLayout.CENTER);
			add(createControlPanel(), BorderLayout.SOUTH);
		}

		// 控制面板
		public JPanel createControlPanel() {
			JPanel jpanelControl = new JPanel();
			JLabel spaceLabel = new JLabel("");

			JButton jbSave = new JButton("保存记录");
			jbSave.addActionListener(new ActionListener() {

				@Override
				public void actionPerformed(ActionEvent e) {
					// TODO Auto-generated method stub
					EventQueue.invokeLater(new Runnable() {
						@Override
						public void run() {
							// TODO Auto-generated method stub
							// 保存聊天记录
							saveChatRecord();
						}
					});

				}

			});

			JButton jbQuery = new JButton("查询");
			jbQuery.addActionListener(new ActionListener() {

				@Override
				public void actionPerformed(ActionEvent e) {
					// TODO Auto-generated method stub
					// 发送查询命令
					// 命令格式 command&sql&fromname&toname
					// User user = (User) friendList.getSelectedValue();
					chatRecordArea.setText("");
//ChatRecordPane.this.requestFocus();
					String command = "command&sql&" + userName + "&"
							+ user.getUserName() + "&" + "msg_Date" + "&"
							+ user.getUserID();
					out.println(command);
					out.flush();

				}
			});

			JButton jbCancel = new JButton("取消");
			jpanelControl.setLayout(new FlowLayout(FlowLayout.RIGHT, 20, 10));
			jbCancel.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					// TODO Auto-generated method stub
					jtabdedPane.remove(ChatRecordPane.this);
					user.setOpenChatRecord(false);
				}
			});

			spaceLabel.setPreferredSize(new Dimension(10, 10));
			jpanelControl.add(jbSave);
			jpanelControl.add(spaceLabel);
			jpanelControl.add(jbQuery);
			jpanelControl.add(jbCancel);

			return jpanelControl;
		}

		// 保存聊天记录
		private void saveChatRecord() {
			String path = "";
			String file = "";
			int index;
			String tail = "";
			JFileChooser chooser = new JFileChooser();
			FileNameExtensionFilter filter = new FileNameExtensionFilter(
					"文本文档(*.txt)", "*.txt");
			// chooser.setAcceptAllFileFilterUsed(false);
			chooser.setFileFilter(filter);
			int returnVal = chooser.showSaveDialog(null);
			if (returnVal == JFileChooser.APPROVE_OPTION) {
				System.out.println("You chose to open this file: "
						+ chooser.getSelectedFile().getAbsolutePath());
				path = chooser.getSelectedFile().getAbsolutePath();
				index = path.lastIndexOf(".");
				if (index >= path.length() - 1 || index == -1) {
					tail = ".txt";
				}
				path = path + tail;
				FileOutputStream out = null;
				System.out.println(path);
				String msg = chatRecordArea.getText();
				if(msg.contains(ResourceBundler.getResourceBundle().getString("ClientFrame.ChatRecord.Msg"))){
					JOptionPane.showConfirmDialog(this, "没有聊天记录！保存失败", "聊天记录",
							JOptionPane.DEFAULT_OPTION,
							JOptionPane.INFORMATION_MESSAGE);
					return ;
				}
				byte[] b = msg.getBytes();
				try {
					out = new FileOutputStream(path);
					out.write(b);
					out.flush();
					JOptionPane.showConfirmDialog(this, "聊天记录保存成功", "聊天记录",
							JOptionPane.DEFAULT_OPTION,
							JOptionPane.INFORMATION_MESSAGE);
					// JOptionPane.showConfirmDialog(parentComponent, message)
				} catch (FileNotFoundException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				} catch (IOException e2) {
					// TODO Auto-generated catch block
					e2.printStackTrace();
				} finally {
					try {
						out.close();
					} catch (IOException e3) {
						// TODO Auto-generated catch block
						e3.printStackTrace();
					}
				}

			}
		}
	}
    
	//
	class AcceptFileThread extends Thread {

		public void initIpPort(String ipp, int portt, String filepathh) {
			ip = ipp;
			port = portt;
			filepath = filepathh;
		}

		public AcceptFileThread() {
		}

		public void run() {
			File file = new File(filepath);
			RandomAccessFile raf = null;
			try {
				file.createNewFile();
				raf = new RandomAccessFile(file, "rw");
			} catch (IOException e1) {
				System.out.print("接收文件新建文件并打开异常");
			}

			try {
				acceptFileSocket = new Socket(ip, port);
			} catch (IOException e1) {
				System.out.print("接收文件通过Socket连接文件服务器异常");
			}

			String[] tem = fileMsg.split("&");
			acceptProgressbar.setMaximum(Integer.parseInt(tem[5]));
			acceptProgressbar.setMinimum(0);

			// 创建网络接受流接受服务器文件数据

			InputStream netIn = null;
			InputStream in = null;

			try {
				netIn = acceptFileSocket.getInputStream();
				in = new DataInputStream(new BufferedInputStream(netIn));
			} catch (IOException e1) {
				System.out.print("接收文件创建网络接受流接受服务器文件数据异常");
			}
			// 创建缓冲区缓冲网络数据
			byte[] buf = new byte[8000000];
			int num = -1;
			try {
				num = in.read(buf);
			} catch (IOException e1) {
				System.out.print("接收文件创建缓冲区缓冲网络数据异常");
			}
			int temleng = num / 1000;
			while (num != (-1) && acceptboolean) {// 是否读完所有数据
				temleng = temleng + num / 1000;
				acceptProgressbar.setValue(temleng);

				try {
					raf.write(buf, 0, num);// 将数据写往文件
					raf.skipBytes(num);// 顺序写文件字节
					num = in.read(buf);// 继续从网络中读取文件
				} catch (IOException e1) {
					System.out.print("接收文件将数据写往文件或继续从网络中读取文件异常");
				}
			}
			if (acceptboolean) {
				insert(privateMsgArea, "文件接收完毕");
			} else {
				insert(privateMsgArea, "文件接收中断");
			}
			acceptProgressbar.setValue(0);
			try {
				in.close();
				raf.close();
			} catch (IOException e1) {
				System.out.print("接收文件关闭读写失败异常");
			}
			try {
				acceptFileSocket.close();
			} catch (IOException e1) {
				System.out.print("接收文件关闭连接异常");
			}

			acceptfileArea.setText("");
			acceptfile.setEnabled(true);
			return;

		}

		private String ip, filepath;
		private int port;
	}

	class SendFileThread extends Thread {
		public SendFileThread() {
		}

		public void run() {
			File file = new File(nameOfSendFile);
			FileInputStream fos = null;

			try {
				fos = new FileInputStream(file);
			} catch (IOException e1) {
				System.out.print("发送文件打开文件异常");
			}
			out.println("sendfile" + "&" + withWho + "&"
					+ sendfileArea.getText() + "&" + IP + "&" + port + "&"
					+ (int) file.length() / 1000);
			out.flush();
			// 创建网络服务器接受客户请求
			try {
				fileServerSocket = new ServerSocket(port);
			} catch (IOException e1) {
				System.out.print("发送文件创建服务器错误异常");
			}
			try {
				sendFileSocket = fileServerSocket.accept();
			} catch (IOException e1) {
				System.out.print("发送文件监听连接异常");
			}
			sendProgressbar.setMaximum((int) file.length() / 1000);
			sendProgressbar.setMinimum(0);
			// 创建网络输出流并提供数据包装器
			int filetemp = 0;

			OutputStream netOut = null;
			OutputStream doc = null;
			try {
				netOut = sendFileSocket.getOutputStream();
				doc = new DataOutputStream(new BufferedOutputStream(netOut));
			} catch (IOException e1) {
				System.out.print("发送文件创建网络输出流并提供数据包装器异常");
			}
			// 创建文件读取缓冲区
			byte[] buf = new byte[8000000];
			int num = -1;
			try {
				num = fos.read(buf);
			} catch (IOException e1) {
				System.out.print("发送文件读文件异常");
			}

			while (num != (-1) && sendboolean) {// 是否读完文件
				filetemp = filetemp + num / 1000;
				sendProgressbar.setValue(filetemp);
				try {
					doc.write(buf, 0, num);// 读文件
					doc.flush();
				} catch (IOException e1) {
					System.out.print("发送文件把文件数据写出网络缓冲区异常");
				}
				try {
					num = fos.read(buf);// 继续从文件中读取数据
				} catch (IOException e1) {
					System.out.print("发送文件继续从文件中读取数据异常");
				}
			}
			if (num == (-1) && sendboolean) {
				insert(privateMsgArea, "文件发送完毕");
			} else {
				insert(privateMsgArea, "文件发送中断");
			}
			sendProgressbar.setValue(0);

			try {
				fos.close();
				doc.close();
			} catch (IOException e1) {
				System.out.print("发送文件关闭读或写异常");
			}

			try {
				sendFileSocket.close();
				fileServerSocket.close();
			} catch (IOException e1) {
				System.out.print("发送文件关闭连接或服务器异常");
			}
			sendfileArea.setText("");
			sendfile.setEnabled(true);
			return;

		}
	}
/*
	public JTextArea getEditMsgArea() {
		return editMsgArea;
	}
*/
	public MyJTextJPane getEditMsgArea(){
		return editMsgArea;
	}
	private class FontAttrib {
		public static final int GENERAL = 0; // 常规

		public static final int BOLD = 1; // 粗体

		public static final int ITALIC = 2; // 斜体

		public static final int BOLD_ITALIC = 3; // 粗斜体

		private SimpleAttributeSet attrSet = null; // 属性集

		private String text = null, name = null; // 要输入的文本和字体名称

		private int style = 0, size = 0; // 样式和字号

		private Color color = null, backColor = null; // 文字颜色和背景颜色

		public FontAttrib() {
		}

		public SimpleAttributeSet getAttrSet() {
			attrSet = new SimpleAttributeSet();
			if (name != null)
				StyleConstants.setFontFamily(attrSet, name);
			if (style == FontAttrib.GENERAL) {
				StyleConstants.setBold(attrSet, false);
				StyleConstants.setItalic(attrSet, false);
			} else if (style == FontAttrib.BOLD) {
				StyleConstants.setBold(attrSet, true);
				StyleConstants.setItalic(attrSet, false);
			} else if (style == FontAttrib.ITALIC) {
				StyleConstants.setBold(attrSet, false);
				StyleConstants.setItalic(attrSet, true);
			} else if (style == FontAttrib.BOLD_ITALIC) {
				StyleConstants.setBold(attrSet, true);
				StyleConstants.setItalic(attrSet, true);
			}
			StyleConstants.setFontSize(attrSet, size);
			if (color != null)
				StyleConstants.setForeground(attrSet, color);
			if (backColor != null)
				StyleConstants.setBackground(attrSet, backColor);
			return attrSet;
		}

		public int getSytle(String name) {
			if (name.compareTo("斜体") == 0) {
				return BOLD;
			} else if (name.compareTo("粗体") == 0) {
				return ITALIC;
			} else if (name.compareTo("粗斜体") == 0) {
				return BOLD_ITALIC;
			} else {
				return GENERAL;
			}
		}

		public Color getColor(String name) {
			Color color = null;
			if (name.equals("黑色")) {
				color = new Color(0, 0, 0);
			} else if (name.equals("红色")) {
				color = new Color(255, 0, 0);
			} else if (name.equals("蓝色")) {
				color = new Color(0, 0, 255);
			} else if (name.equals("黄色")) {
				color = new Color(255, 255, 0);
			} else if (name.equals("绿色")) {
				color = new Color(0, 255, 0);
			}
			return color;
		}

		public void setAttrSet(SimpleAttributeSet attrSet) {
			this.attrSet = attrSet;
		}

		public String getText() {
			return text;
		}

		public void setText(String text) {
			this.text = text;
		}

		public Color getColor() {
			return color;
		}

		public void setColor(Color color) {
			this.color = color;
		}

		public Color getBackColor() {
			return backColor;
		}

		public void setBackColor(Color backColor) {
			this.backColor = backColor;
		}

		public String getName() {
			return name;
		}

		public void setName(String name) {
			this.name = name;
		}

		public int getSize() {
			return size;
		}

		public void setSize(int size) {
			this.size = size;
		}

		public int getStyle() {
			return style;
		}

		public void setStyle(int style) {
			this.style = style;
		}

	}

	private String userName;
	private String withWho = "所有人";
	private String outMsg;
	private String myWords;
	private BufferedReader in;
	private PrintWriter out;
	//
	private JTextPane chatRecordArea;
	//
	//private JTextPane commonMsgArea = null;
	//private JTextPane privateMsgArea = null;
	//private JTextArea editMsgArea = null;
	//
	private MyJTextJPane commonMsgArea = null;
	private MyJTextJPane privateMsgArea = null;
	private MyJTextJPane editMsgArea = null;
	
	//
	private JScrollPane commonMsgAreaScroll;
	private JScrollPane privateMsgAreaScroll;
	private JScrollPane editMsgAreaScroll;
	private JComboBox fontNameCombo, fontSizeCombo, fontStyleCombo,
			fontColorCombo, chatToCombo;
	private JCheckBox jcbPrivate;
	private boolean isPrivateTalk = false;
	private DragbleTextArea sendfileArea = null;
	private JTextPane acceptfileArea = null;
	//
	JButton jbConrolDoOpenUp;
	private JPanel mainPanel;
	private JTabbedPane jtabdedPane;
	//

	private JProgressBar acceptProgressbar;
	private JProgressBar sendProgressbar;
	private Box mainLeftBox = null;
	private Box mainRightBox = null;

	private JButton sendfile;
	private JButton cancelsendfile;
	private JButton acceptfile;
	private JButton refusefile;
	private JButton sentButton;
	private JButton shakeFrame;
	private JButton screenCapture;

	private JList friendList;
	private JButton refreashButton;
	public DefaultListModel listModel;
	private StyledDocument styleDocument = null;

	private SendFileThread sendFileThread;// 发送文件线程;
	private AcceptFileThread acceptFileThread;// 接收文件线程
	private Socket acceptFileSocket; // 接收文件传输连接
	private Socket sendFileSocket; // 发送文件传输连接
	private ServerSocket fileServerSocket; // 传输文件服务器
	private String fileMsg = null; // 保存文件输入流
	private String nameOfSendFile = null;// 保存欲发送的文件名
	private String IP;
	private int port = 9999;
	private Boolean acceptboolean = false;
	private Boolean sendboolean = false;

}
