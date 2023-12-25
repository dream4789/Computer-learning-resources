package games.diamonds.gui;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.Color;
import games.diamonds.utils.*;

/**
 * 单机版游戏主类，继承自JFrame类，负责游戏的全局控制。
 * 内含
 * 1, 一个GameCanvas画布类的实例引用，
 * 2, 一个保存当前活动块(DiamondBlock)实例的引用，
 * 3, 一个保存当前控制面板（ControlPanel）实例的引用;
 */
public class MainFrame extends JFrame {
	private static final long serialVersionUID=0L;

	private GameCanvas canvas;
	private DiamondBlock block;
	private boolean playing = false;
	public ControlPanel ctrlPanel;

	private JMenuBar bar = new JMenuBar();
	private JMenu
	        mGame = new JMenu("游戏"),
			mControl = new JMenu("控制"),
			mWindowStyle = new JMenu("风格"),
			mInfo = new JMenu("帮助"),
			mHidden=new JMenu("隐藏菜单命令");
	
	private JMenuItem
	        miNewGame = new JMenuItem("新游戏"),
			miSetBlockColor = new JMenuItem("设置方块颜色 ..."),
			miSetBackColor = new JMenuItem("设置背景色 ..."),
			miTurnHarder = new JMenuItem("增加难度"),
			miTurnEasier = new JMenuItem("降低难度"),			
			miExit = new JMenuItem("退出"),

			miPlay = new JMenuItem("开始"),
			miPause = new JMenuItem("暂停"),
			miResume = new JMenuItem("继续"),
			miStop = new JMenuItem("停止"),			

			miAuthor = new JMenuItem("Author : kedl@ahut.edu.cn"),
			miSourceInfo = new JMenuItem("关于"),
	
			menuItemSave=new JMenuItem("救助"),
			menuItemAdd=new JMenuItem("捣乱");

	private JCheckBoxMenuItem
	        miAsWindows = new JCheckBoxMenuItem("Windows"),
			miAsMotif = new JCheckBoxMenuItem("Motif"),
			miAsMetal = new JCheckBoxMenuItem("Metal", true),
			miBgMusic=new JCheckBoxMenuItem("开音效",true);
	
	private java.net.URL fullURL;	
	private java.applet.AudioClip audioClip;	
	private java.applet.AudioClip bgaudioClip;
	private boolean bgMusic=true;		
	
	public void initUI(){
		UIManager.put("Button.font", new Font("宋体", Font.PLAIN, 14));
        UIManager.put("Label.font", new Font("宋体", Font.PLAIN, 14));
        UIManager.put("Table.font", new Font("宋体", Font.PLAIN, 14));
        UIManager.put("TextField.font", new Font("宋体", Font.PLAIN, 14));
        UIManager.put("ScrollPane.font", new Font("宋体", Font.PLAIN, 14));
        UIManager.put("ComboBox.font", new Font("宋体", Font.PLAIN, 14));
        UIManager.put("CheckBox.font", new Font("宋体", Font.PLAIN, 14));
        UIManager.put("TitledBorder.font", new Font("宋体", Font.PLAIN, 14));
        UIManager.put("RadioButton.font", new Font("宋体", Font.PLAIN, 14));
        UIManager.put("ToolTip.font", new Font("宋体", Font.PLAIN, 14));
        UIManager.put("TextPane.font", new Font("宋体", Font.PLAIN, 14));
        UIManager.put("TextArea.font", new Font("宋体", Font.PLAIN, 14));
        UIManager.put("Tree.font", new Font("宋体", Font.PLAIN, 14));
        UIManager.put("List.font", new Font("宋体", Font.PLAIN, 14));
        UIManager.put("MenuBar.font", new Font("宋体", Font.PLAIN, 14));
        UIManager.put("Menu.font", new Font("宋体", Font.PLAIN, 14));
        UIManager.put("MenuItem.font", new Font("宋体", Font.PLAIN, 14));
        UIManager.put("TableHeader.font", new Font("宋体", Font.PLAIN, 12));
        UIManager.put("TabbedPane.font", new Font("宋体", Font.PLAIN, 14));
        UIManager.put("InternalFrame.font", new Font("宋体", Font.PLAIN, 14));
        UIManager.put("CheckBoxMenuItem.font",new Font("宋体", Font.PLAIN, 14));
        CommonMetalTheme theme = new CommonMetalTheme();
        javax.swing.plaf.metal.MetalLookAndFeel.setCurrentTheme(theme);
        try {
            UIManager.setLookAndFeel("javax.swing.plaf.metal.MetalLookAndFeel");
        } catch (Exception e) {
        	e.printStackTrace();        	
        }
	}
	
	/**
	 * 建立并设置窗口菜单
	 */
	private void createMenu() {
		bar.add(mGame);
		bar.add(mControl);
		bar.add(mWindowStyle);
		bar.add(mInfo);
		bar.add(mHidden);	

		mGame.add(miNewGame);
		mGame.addSeparator();
		mGame.add(miSetBlockColor);
		mGame.add(miSetBackColor);
		mGame.addSeparator();
		mGame.add(miTurnHarder);
		mGame.add(miTurnEasier);
		mGame.addSeparator();
		mGame.add(miBgMusic);		
		mGame.addSeparator();
		mGame.add(miExit);

		mControl.add(miPlay);
		mControl.add(miPause);
		mControl.add(miResume);
		mControl.add(miStop);		

		mWindowStyle.add(miAsWindows);
		mWindowStyle.add(miAsMotif);
		mWindowStyle.add(miAsMetal);

		mInfo.add(miAuthor);
		mInfo.add(miSourceInfo);
		
		mHidden.add(menuItemSave);
		mControl.addSeparator() ;
		mControl.add(menuItemAdd);

		setJMenuBar(bar);
		
		miPause.setAccelerator(
		        KeyStroke.getKeyStroke(KeyEvent.VK_P, KeyEvent.CTRL_MASK));
		miResume.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_ENTER, 0));

		miNewGame.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				stopGame();
				reset();
				setLevel(Constants.DEFAULT_LEVEL);
			}
		});
		miSetBlockColor.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				Color newFrontColor =
				        JColorChooser.showDialog(MainFrame.this,
				                "Set color for block", canvas.getBlockColor());
				if (newFrontColor != null)
					canvas.setBlockColor(newFrontColor);
			}
		});
		miSetBackColor.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				Color newBackColor =
				        JColorChooser.showDialog(MainFrame.this,
				                "Set color for block", canvas.getBackgroundColor());
				if (newBackColor != null)
					canvas.setBackgroundColor(newBackColor);
			}
		});
		miTurnHarder.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				int curLevel = getLevel();
				if (curLevel < Constants.MAX_LEVEL) setLevel(curLevel + 1);
			}
		});
		miTurnEasier.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				int curLevel = getLevel();
				if (curLevel > 1) setLevel(curLevel - 1);
			}
		});
		miExit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				System.exit(0);
			}
		});
		miPlay.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				playGame();
			}
		});
		miPause.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				pauseGame();
			}
		});
		miResume.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				resumeGame();
			}
		});
		miStop.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				stopGame();
			}
		});
		menuItemAdd.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_I,KeyEvent.CTRL_MASK ));
		menuItemAdd.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent ae){
				insertRows();
			}
		});
		menuItemSave.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S,KeyEvent.CTRL_MASK ));
		menuItemSave.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent ae){
				deleteRows();
			}
		});
		miAsWindows.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				String plaf = "com.sun.java.swing.plaf.windows.WindowsLookAndFeel";
				setWindowStyle(plaf);
				canvas.fanning();
				ctrlPanel.fanning();
				miAsWindows.setState(true);
				miAsMetal.setState(false);
				miAsMotif.setState(false);
			}
		});
		miAsMotif.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				String plaf = "com.sun.java.swing.plaf.motif.MotifLookAndFeel";
				setWindowStyle(plaf);
				canvas.fanning();
				ctrlPanel.fanning();
				miAsWindows.setState(false);
				miAsMetal.setState(false);
				miAsMotif.setState(true);
			}
		});
		miAsMetal.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				String plaf = "javax.swing.plaf.metal.MetalLookAndFeel";
				setWindowStyle(plaf);
				canvas.fanning();
				ctrlPanel.fanning();
				miAsWindows.setState(false);
				miAsMetal.setState(true);
				miAsMotif.setState(false);
			}
		});
		miBgMusic.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent ae){
				boolean state=miBgMusic.getState();
				if(state){
					miBgMusic.setState(true);
					bgMusic=true;
					bgaudioClip.loop();				
				}else{
					miBgMusic.setState(false);
					bgMusic=false;
					bgaudioClip.stop();
				}							
			}
		});		
	}
	/**
	 * 主游戏类的构造函数
	 * @param title String，窗口标题
	 */
	public MainFrame(String title) {		
		super(title);
		canvas = new GameCanvas(Constants.ROWNUMBERS ,Constants.COLNUMBERS );		
		ctrlPanel = new ControlPanel(this);			
		
		GamePanel gamePanel=new GamePanel();
		gamePanel.setLayout(new BorderLayout(10,0));	
		bgaudioClip = java.applet.Applet.newAudioClip(getClass().getResource(
				Constants.musicStr));
		fullURL = getClass().getResource("/resources/sounds/explode1.au");
		if(fullURL!=null)
			audioClip=java.applet.Applet.newAudioClip(fullURL);		
		setIconImage(ImageFactory.getInstance().getIconImage().getImage());
		setSize(394, 574);
		Dimension scrSize = Toolkit.getDefaultToolkit().getScreenSize();
		setLocation((scrSize.width - getSize().width) / 2,
		        (scrSize.height - getSize().height) / 2);
		initUI();
		createMenu();

		gamePanel.add(canvas,BorderLayout.CENTER );
		gamePanel.add(ctrlPanel,BorderLayout.EAST );
		getContentPane().add(gamePanel,BorderLayout.CENTER );
		
		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent we) {
				stopGame();
				System.exit(0);
			}
		});

		addComponentListener(new ComponentAdapter() {
			public void componentResized(ComponentEvent ce) {
				canvas.fanning();
				System.out.println("(width:height)="+"("+getSize().width +":"+getSize().height+")" );
			}
		});	
		
		canvas.fanning();	
		canvas.repaint() ;
		if(bgMusic){		
			
		}		
	}

	/**
	 * 程序入口函数
	 * @param args String[], 附带的命令行参数
	 */
	public static void main(String[] args) {
		System.out.println("now begin loading MainFrame...");
		/***
		try {
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		} catch (Exception ignore) {}
		*/
		JSplashWindow.setInstance("Darling Ke",ImageFactory.getInstance().getSplashImage()) ;
		/**
		try{
		Thread.currentThread().sleep(2000);
		}catch(Exception e){}
		*/
		@SuppressWarnings("unused") MainFrame app=new MainFrame("Russia Blocks V1.0");
		JSplashWindow.getInstance().dispose();		
		
		/**
		 * Main.addStartupListener(new StartUpListener() {
				public void startUpComplete() {
					SplashWindow.disposeSplash();
				}
			});
			SplashWindow.splash(ClassLoader
					.getSystemResource("weka/gui/images/weka_splash.gif"));

			// start GUI
			Thread nt = new Thread() {
				public void run() {
					weka.gui.SplashWindow.invokeMethod("weka.gui.Main",
							"createSingleton", new String[1]);
				}
			};

		 * 
		 * 
		 * */
	}
	
	/**
	 * 让游戏“复位”
	 */
	public void reset() {
		ctrlPanel.reset();
		canvas.reset();
	}

	/**
	 * 判断游戏是否还在进行
	 * @return boolean, true-还在运行，false-已经停止
	 */
	public boolean isPlaying() {
		return playing;
	}

	/**
	 * 得到当前活动的块
	 * @return ErsBlock, 当前活动块的引用
	 */
	public DiamondBlock getCurBlock() {
		return block;
	}

	/**
	 * 得到当前画布
	 * @return GameCanvas, 当前画布的引用
	 */
	public GameCanvas getCanvas() {
		return canvas;
	}

	/**
	 * 开始游戏
	 */
	public void playGame() {
		play();
		ctrlPanel.setPlayButtonEnable(false);
		miPlay.setEnabled(false);
		ctrlPanel.requestFocus();
	}

	/**
	 * 游戏暂停
	 */
	public void pauseGame() {
		if (block != null) block.pauseMove();

		ctrlPanel.setPauseButtonLabel(false);
		miPause.setEnabled(false);
		miResume.setEnabled(true);
	}

	/**
	 * 让暂停中的游戏继续
	 */
	public void resumeGame() {
		if (block != null) block.resumeMove();
		ctrlPanel.setPauseButtonLabel(true);
		miPause.setEnabled(true);
		miResume.setEnabled(false);
		ctrlPanel.requestFocus();
		bgaudioClip.stop();
	}

	/**
	 * 用户停止游戏
	 */
	public void stopGame() {
		playing = false;
		if (block != null) block.stopMove();
		miPlay.setEnabled(true);
		miPause.setEnabled(true);
		miResume.setEnabled(false);
		ctrlPanel.setPlayButtonEnable(true);
		ctrlPanel.setPauseButtonLabel(true);
		bgaudioClip.stop();
	}
	
	/**
	 * 增加底部的行
	 * */

	public synchronized void insertRows(){		
		if (block != null) {
			block.pauseMove();
		}
		canvas.addLine(4);
		/** 擦除被复制的block */
		eraseAboveBlock();
		if (block != null) {			
			block.resumeMove();
		}
	}

	/**
	 * 删除底部的行
	 * */
	public synchronized void deleteRows(){
		if (block != null) {
			block.pauseMove();
		}		
		for(int i=0;i<4;i++){
			for (int row = Constants.ROWNUMBERS - 1; row > 0; row--)
				for (int j = 0; j < Constants.COLNUMBERS; j++)
					canvas.boxes[row][j] = (DiamondCells) canvas.boxes[row - 1][j]
							.clone();
		}
		eraseBelowBlock();
		if (block != null) {
			block.resumeMove();
		}
	}
	public synchronized void eraseBelowBlock(){
		if (block != null) {
			int rowNumber=Constants.ROWNUMBERS -1-block.y-4;
			if (rowNumber>=4) rowNumber=4;
			
			for (int row = 0; row <rowNumber; row++)
				for (int col = 0; col <  4; col++)
					canvas.boxes[block.y+4+row][block.x+col].setColor(false);
		}
	}
	
	public synchronized void eraseAboveBlock(){
		if (block != null) {
			int i = block.x, j = block.y;
			if ((j - 4) < 0)
				j = 0;
			else
				j = j - 4;
			for (int row = j; row < block.y; row++)
				for (int col = block.x; col < i + 4; col++)
					canvas.boxes[row][col].setColor(false);
		}
	}
	
	/**
	 * 得到当前游戏者设置的游戏难度
	 * @return int, 游戏难度1－MAX_LEVEL
	 */
	public int getLevel() {
		return ctrlPanel.getLevel();
	}

	/**
	 * 让用户设置游戏难度
	 * @param level int, 游戏难度1－MAX_LEVEL
	 */
	public void setLevel(int level) {
		if (level < 11 && level > 0) ctrlPanel.setLevel(level);
	}

	/**
	 * 得到游戏积分
	 * @return int, 积分。
	 */
	public int getScore() {
		if (canvas != null) return canvas.getScore();
		return 0;
	}

	/**
	 * 得到自上次升级以来的游戏积分，升级以后，此积分清零
	 * @return int, 积分。
	 */
	public int getScoreForLevelUpdate() {
		if (canvas != null) return canvas.getScoreForLevelUpdate();
		return 0;
	}

	/**
	 * 当分数累计到一定的数量时，升一次级
	 * @return boolean, ture-update successufl, false-update fail
	 */
	public boolean levelUpdate() {
		int curLevel = getLevel();
		if (curLevel < Constants.MAX_LEVEL) {
			setLevel(curLevel + 1);
			canvas.resetScoreForLevelUpdate();
			return true;
		}
		return false;
	}

	/**
	 * 游戏开始
	 */
	private void play() {
		reset();
		playing = true;	
		new Thread(new Game()).start();
		if(bgMusic)
		{
			bgaudioClip.play();
			//bgaudioClip.loop();
			//System.out.println("play bg music.");
			//mp3.initMedia();
			
		}
			
	}

	/**
	 * 报告游戏结束了
	 */
	private void reportGameOver() {
		JOptionPane.showMessageDialog(this, "Game Over!");
	}	

	/**
	 * 根据字串设置窗口外观
	 * @param plaf String, 窗口外观的描述
	 */
	private void setWindowStyle(String plaf) {
		try {
			UIManager.setLookAndFeel(plaf);
			SwingUtilities.updateComponentTreeUI(this);
		} catch (Exception e) {
		}
	}

	/**
	 * 一轮游戏过程，实现了Runnable接口
	 * 一轮游戏是一个大循环，在这个循环中，每隔100毫秒，
	 * 检查游戏中的当前块是否已经到底了，如果没有，
	 * 就继续等待。如果到底了，就看有没有全填满的行，
	 * 如果有就删除它，并为游戏者加分，同时随机产生一个
	 * 新的当前块，让它自动下落。
	 * 当新产生一个块时，先检查画布最顶上的一行是否已经
	 * 被占了，如果是，可以判断Game Over了。
	 */
	private class Game implements Runnable {
		public void run() {
			//int col = (int) (Math.random() * (canvas.getCols() - 3));
			int col = (int) (canvas.getCols()/2 -2);
			int style = Constants.STYLES[(int) (Math.random() * 7)][(int) (Math.random() * 4)];

			while (playing) {
				if (block != null) {    //第一次循环时，block为空
					if (block.isAlive()) {
						try {
							//Thread.currentThread().sleep(100);
							Thread.sleep(100);
						} catch (InterruptedException ie) {
							ie.printStackTrace();
						}
						continue;
					}
				}

				checkFullLine();        //检查是否有全填满的行

				if (isGameOver()) {     //检查游戏是否应该结束了
					miPlay.setEnabled(true);
					miPause.setEnabled(true);
					miResume.setEnabled(false);
					ctrlPanel.setPlayButtonEnable(true);
					ctrlPanel.setPauseButtonLabel(true);

					reportGameOver();
					return;
				}

				Color fColor=Constants.genColor[(int)(Math.random()*21)];
				block = new DiamondBlock(style, -1, col, getLevel(),fColor, canvas);
				block.start();

				col = (int) (Math.random() * (canvas.getCols() - 3));
				style = Constants.STYLES[(int) (Math.random() * 7)][(int) (Math.random() * 4)];

				ctrlPanel.setTipStyle(style);
				ctrlPanel.setTipforeColor(fColor);
			}
		}

		/**
		 * 检查画布中是否有全填满的行，如果有就删除之
		 */
		public void checkFullLine() {
			for (int i = 0; i < canvas.getRows(); i++) {
				int row = -1;
				boolean fullLineColorBox = true;
				for (int j = 0; j < canvas.getCols(); j++) {
					if (!canvas.getBox(i, j).isColorBox()) {
						fullLineColorBox = false;
						break;
					}
				}
				if (fullLineColorBox) {
					row = i--;
					canvas.removeLine(row);
					//播放声音
					audioClip.play();
				}
			}
		}

		/**
		 * 根据最顶行是否被占，判断游戏是否已经结束了。
		 * @return boolean, true-游戏结束了，false-游戏未结束
		 */
		private boolean isGameOver() {
			for (int i = 0; i < canvas.getCols(); i++) {
				DiamondCells box = canvas.getBox(0, i);
				if (box.isColorBox()) return true;
			}
			return false;
		}
	}

	private class GamePanel extends JPanel{

		private static final long serialVersionUID = 2272042383160351906L;
		
		public GamePanel(){
			super();
			addComponentListener(new ComponentAdapter() {
				public void componentResized(ComponentEvent ce) {
					canvas.fanning();
				}
			});			
		}
		public void paintComponent(Graphics g){
			Graphics2D comp=(Graphics2D)g;
			comp.setBackground(Color.BLUE );
			comp.fillRect(0,0,getSize().width ,getSize().height );
			ctrlPanel.setBounds(getSize().width -100, 0, 100, getSize().height );
			canvas.setBounds(0,0,getSize().width-102 ,getSize().height );
		}		
	}
	
}
