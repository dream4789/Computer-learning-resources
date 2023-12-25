package games.diamonds.utils;

import javax.swing.*;
import javax.swing.border.EtchedBorder;
import java.awt.*;

/**
 * 画布类，内有<行数> * <列数>个方格类实例。
 * 继承自JPanel类。
 * DiamondBlock线程类动态改变画布类的方格颜色，画布类通过
 * 检查方格颜色来体现DiamondBlock块的移动情况。
 */
public class GameCanvas extends JPanel {
	private static final long serialVersionUID=0L;
	private Color backColor = Color.black, frontColor=Color.blue;// = Color.orange;
	//private Color[] genColor={Color.orange,Color.black,Color.blue,Color.red,Color.cyan,Color.green};
	private int rows, cols, score = 0, scoreForLevelUpdate = 0;
	public DiamondCells[][] boxes;
	private boolean isfanning=false;
	private int boxWidth, boxHeight;

	/**
	 * 画布类的构造函数
	 * @param rows int, 画布的行数
	 * @param cols int, 画布的列数
	 * 行数和列数决定着画布拥有方格的数目
	 */
	public GameCanvas(int rows, int cols) {
		this.rows = rows;
		this.cols = cols;

		boxes = new DiamondCells[rows][cols];
		for (int i = 0; i < boxes.length; i++) {
			for (int j = 0; j < boxes[i].length; j++) {
				boxes[i][j] = new DiamondCells(false);
			}
		}

		setBorder(new EtchedBorder(
		        EtchedBorder.RAISED, Color.white, new Color(148, 145, 140)));		
	}

	/**
	 * 画布类的构造函数
	 * @param rows 与public GameCanvas(int rows, int cols)同
	 * @param cols 与public GameCanvas(int rows, int cols)同
	 * @param backColor Color, 背景色
	 * @param frontColor Color, 前景色
	 */
	public GameCanvas(int rows, int cols,
	                  Color backColor, Color frontColor) {
		this(rows, cols);
		this.backColor = backColor;
		this.frontColor = frontColor;
	}

	/**
	 * 设置游戏背景色彩
 	 * @param backColor Color, 背景色彩
	 */
	public void setBackgroundColor(Color backColor) {
		this.backColor = backColor;
	}

	/**
	 * 取得游戏背景色彩
 	 * @return Color, 背景色彩
	 */
	public Color getBackgroundColor() {
		return backColor;
	}

	/**
	 * 设置游戏方块色彩
 	 * @param frontColor Color, 方块色彩
	 */
	public void setBlockColor(Color frontColor) {
		this.frontColor = frontColor;
	}

	/**
	 * 取得游戏方块色彩
 	 * @return Color, 方块色彩
	 */
	public Color getBlockColor() {
		return frontColor;
	}

	/**
	 * 取得画布中方格的行数
	 * @return int, 方格的行数
	 */
	public int getRows() {
		return rows;
	}

	/**
	 * 取得画布中方格的列数
	 * @return int, 方格的列数
	 */
	public int getCols() {
		return cols;
	}

	/**
	 * 取得游戏成绩
	 * @return int, 分数
	 */
	public int getScore() {
		return score;
	}

	/**
	 * 取得自上一次升级后的积分
	 * @return int, 上一次升级后的积分
	 */
	public int getScoreForLevelUpdate() {
		return scoreForLevelUpdate;
	}

	/**
	 * 升级后，将上一次升级以来的积分清0
	 */
	public void resetScoreForLevelUpdate() {
		scoreForLevelUpdate -= Constants.PER_LEVEL_SCORE;
	}

	/**
	 * 得到某一行某一列的方格引用。
	 * @param row int, 要引用的方格所在的行
	 * @param col int, 要引用的方格所在的列
	 * @return ErsBox, 在row行col列的方格的引用
	 */
	public DiamondCells getBox(int row, int col) {
		if (row < 0 || row > boxes.length - 1
		        || col < 0 || col > boxes[0].length - 1)
			return null;
		return (boxes[row][col]);
	}

	/**
	 * 覆盖JComponent类的函数，画组件。
	 * @param g 图形设备环境
	 */
	public void paintComponent(Graphics g) {
		super.paintComponent(g);

		if(!isfanning) fanning();
		for (int i = 0; i < boxes.length; i++) {
			for (int j = 0; j < boxes[i].length; j++) {
				//g.setColor(boxes[i][j].isColorBox() ? frontColor : backColor);
				g.setColor(boxes[i][j].isColorBox() ? boxes[i][j].getforColor() : backColor);
				g.fill3DRect(j * boxWidth, i * boxHeight,
				        boxWidth, boxHeight, true);
			}
		}
	}

	/**
	 * 根据窗口的大小，自动调整方格的尺寸
	 */
	public void fanning() {
		boxWidth = getSize().width / cols;
		boxHeight = getSize().height / rows;
		isfanning=true;
	}

	/**
	 * 当一行被游戏者叠满后，将此行清除，并为游戏者加分
	 * @param row int, 要清除的行，是由MainFrame类计算的
	 */
	public synchronized void removeLine(int row) {
		for (int i = row; i > 0; i--) {
			for (int j = 0; j < cols; j++)
				boxes[i][j] = (DiamondCells) boxes[i - 1][j].clone();
		}

		score += Constants.PER_LINE_SCORE;
		scoreForLevelUpdate += Constants.PER_LINE_SCORE;
		repaint();
	}
	
	/**
	 * 在画布底部随机添加几行
	 * @param row int,要添加的行数
	 * */
	public synchronized void addLine(int row){
		for(int i=0;i<Constants.ROWNUMBERS -row;i++){
			for(int j=0;j<Constants.COLNUMBERS ;j++){
				boxes[i][j]=(DiamondCells)boxes[i+row][j].clone() ;
			}
		}/**当前画布中的boxes提升row行*/
		
		boolean isColor;
		for(int i=Constants.ROWNUMBERS -row;i<Constants.ROWNUMBERS;i++){
			for(int j=0;j<Constants.COLNUMBERS;j++){
				boxes[i][j].setColor(false);
				boxes[i][j].setforColor(Color.BLACK);
				isColor = ((int) (Math.random() * 4) == 1) ? false : true;
				if (isColor) {
					boxes[i][j]=new DiamondCells(isColor);
					boxes[i][j].setforColor(Constants.genColor[(int)(Math.random()*21)]);
				}
			}
		}
	}

	/**
	 * 重置画布，置积分为0
	 */
	public void reset() {
		score = 0;
		scoreForLevelUpdate = 0;
		for (int i = 0; i < boxes.length; i++) {
			for (int j = 0; j < boxes[i].length; j++)
				boxes[i][j].setColor(false);
		}

		repaint();
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}
}

