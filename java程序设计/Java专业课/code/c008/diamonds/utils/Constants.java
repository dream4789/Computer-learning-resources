package games.diamonds.utils;

import java.awt.Color;
import java.awt.Font;

public class Constants {

	/**
	 * 一个块占的行数是4行
	 */
	public final static int BOXES_ROWS = 4;
	/**
	 * 一个块占的列数是4列
	 */
	public final static int BOXES_COLS = 4;
	/**
	 * 让升级变化平滑的因子，避免最后几级之间的速度相差近一倍
	 */
	public final static int LEVEL_FLATNESS_GENE = 3;
	/**
	 * 相近的两级之间，块每下落一行的时间差别为多少(毫秒)
	 */
	public final static int BETWEEN_LEVELS_DEGRESS_TIME = 50;
	/**
	 * 方块的样式数目为7
	 */
	public final static int BLOCK_KIND_NUMBER = 7;
	/**
	 * 每一个样式的方块的反转状态种类为4
	 */
	public final static int BLOCK_STATUS_NUMBER = 4;
	/**
	 * 分别对应对7种模型的28种状态
	 */
	public final static int[][] STYLES = {// 共28种状态
		{0x0f00, 0x4444, 0x0f00, 0x4444}, // 长条型的四种状态
		{0x04e0, 0x0464, 0x00e4, 0x04c4}, // 'T'型的四种状态
		{0x4620, 0x6c00, 0x4620, 0x6c00}, // 反'Z'型的四种状态
		{0x2640, 0xc600, 0x2640, 0xc600}, // 'Z'型的四种状态
		{0x6220, 0x1700, 0x2230, 0x0740}, // '7'型的四种状态
		{0x6440, 0x0e20, 0x44c0, 0x8e00}, // 反'7'型的四种状态
		{0x0660, 0x0660, 0x0660, 0x0660}, // 方块的四种状态
	};
	public final static Color[] genColor={new Color(231,22,22),new Color(153,153,255),
			new Color(51,0,204),new Color(255,0,51),new Color(204,0,204),
			new Color(153,153,0),new Color(0,102,102),new Color(102,102,0),
			new Color(255,204,204),new Color(138,128,36),new Color(36,111,10),
			new Color(138,233,172),new Color(26,213,183),new Color(21,187,236),
			new Color(162,235,8),new Color(53,78,131),new Color(133,100,214),
			new Color(146,24,208),new Color(106,20,140),new Color(221,9,200),
			new Color(130,46,99)};
	/**
	 * 画布的行列数
	 * */
	public final static int ROWNUMBERS=30;
	public final static int COLNUMBERS=16;
	
	/**
	 *  每填满一行计多少分
	 */
	public final static int PER_LINE_SCORE = 100;
	/**
	 * 积多少分以后能升级
	 */
	public final static int PER_LEVEL_SCORE = PER_LINE_SCORE * 20;
	/**
	 * 最大级数是10级
	 */
	public final static int MAX_LEVEL = 10;
	/**
	 * 默认级数是5
	 */
	public final static int DEFAULT_LEVEL = 5;
	/**背景音乐路径*/
	public final static String musicStr="/resources/sounds/bgmusic.rmi";
		
	
	
	
	
	public static final Color BackColor=new Color(136,245,236);//俄罗斯方块图背景色
	public static final Color BackcolorDiamonds=new Color(116,225,236);//整体背景色
	public static final int PICTURE_NUM=300;//随机生成的图片序列
	public static final int POINT_NUM=137;//随机生成的点列，用于此消彼长
	public static final int SIZEI=24;//定义棋盘大小竖*********************
	public static final int SIZEJ=10;//定义棋盘大小横 *********************
	public static final int SPEED=800;
	public static final Font Font_Caiyue=new Font("华文彩云",Font.BOLD,20);
	public static final Font Font_Title=new Font("华文彩云",Font.BOLD,35);

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println("hihi.");
	}

}
