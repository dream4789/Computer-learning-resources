package games.diamonds.utils;

import javax.swing.*;
import javax.swing.border.EtchedBorder;
import java.awt.*;

/**
 * �����࣬����<����> * <����>��������ʵ����
 * �̳���JPanel�ࡣ
 * DiamondBlock�߳��ද̬�ı仭����ķ�����ɫ��������ͨ��
 * ��鷽����ɫ������DiamondBlock����ƶ������
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
	 * ������Ĺ��캯��
	 * @param rows int, ����������
	 * @param cols int, ����������
	 * ���������������Ż���ӵ�з������Ŀ
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
	 * ������Ĺ��캯��
	 * @param rows ��public GameCanvas(int rows, int cols)ͬ
	 * @param cols ��public GameCanvas(int rows, int cols)ͬ
	 * @param backColor Color, ����ɫ
	 * @param frontColor Color, ǰ��ɫ
	 */
	public GameCanvas(int rows, int cols,
	                  Color backColor, Color frontColor) {
		this(rows, cols);
		this.backColor = backColor;
		this.frontColor = frontColor;
	}

	/**
	 * ������Ϸ����ɫ��
 	 * @param backColor Color, ����ɫ��
	 */
	public void setBackgroundColor(Color backColor) {
		this.backColor = backColor;
	}

	/**
	 * ȡ����Ϸ����ɫ��
 	 * @return Color, ����ɫ��
	 */
	public Color getBackgroundColor() {
		return backColor;
	}

	/**
	 * ������Ϸ����ɫ��
 	 * @param frontColor Color, ����ɫ��
	 */
	public void setBlockColor(Color frontColor) {
		this.frontColor = frontColor;
	}

	/**
	 * ȡ����Ϸ����ɫ��
 	 * @return Color, ����ɫ��
	 */
	public Color getBlockColor() {
		return frontColor;
	}

	/**
	 * ȡ�û����з��������
	 * @return int, ���������
	 */
	public int getRows() {
		return rows;
	}

	/**
	 * ȡ�û����з��������
	 * @return int, ���������
	 */
	public int getCols() {
		return cols;
	}

	/**
	 * ȡ����Ϸ�ɼ�
	 * @return int, ����
	 */
	public int getScore() {
		return score;
	}

	/**
	 * ȡ������һ��������Ļ���
	 * @return int, ��һ��������Ļ���
	 */
	public int getScoreForLevelUpdate() {
		return scoreForLevelUpdate;
	}

	/**
	 * �����󣬽���һ�����������Ļ�����0
	 */
	public void resetScoreForLevelUpdate() {
		scoreForLevelUpdate -= Constants.PER_LEVEL_SCORE;
	}

	/**
	 * �õ�ĳһ��ĳһ�еķ������á�
	 * @param row int, Ҫ���õķ������ڵ���
	 * @param col int, Ҫ���õķ������ڵ���
	 * @return ErsBox, ��row��col�еķ��������
	 */
	public DiamondCells getBox(int row, int col) {
		if (row < 0 || row > boxes.length - 1
		        || col < 0 || col > boxes[0].length - 1)
			return null;
		return (boxes[row][col]);
	}

	/**
	 * ����JComponent��ĺ������������
	 * @param g ͼ���豸����
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
	 * ���ݴ��ڵĴ�С���Զ���������ĳߴ�
	 */
	public void fanning() {
		boxWidth = getSize().width / cols;
		boxHeight = getSize().height / rows;
		isfanning=true;
	}

	/**
	 * ��һ�б���Ϸ�ߵ����󣬽������������Ϊ��Ϸ�߼ӷ�
	 * @param row int, Ҫ������У�����MainFrame������
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
	 * �ڻ����ײ������Ӽ���
	 * @param row int,Ҫ��ӵ�����
	 * */
	public synchronized void addLine(int row){
		for(int i=0;i<Constants.ROWNUMBERS -row;i++){
			for(int j=0;j<Constants.COLNUMBERS ;j++){
				boxes[i][j]=(DiamondCells)boxes[i+row][j].clone() ;
			}
		}/**��ǰ�����е�boxes����row��*/
		
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
	 * ���û������û���Ϊ0
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

