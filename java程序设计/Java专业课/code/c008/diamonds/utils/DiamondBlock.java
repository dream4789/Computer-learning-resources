package games.diamonds.utils;

import java.awt.Color;

/**
 * 块类，继承自线程类（Thread）
 * 由 4 * 4 个方格（DiamondCells）构成一个块，
 * 控制块的移动、下落、变形等
 */
public class DiamondBlock extends Thread {

	private GameCanvas canvas;
	private DiamondCells[][] boxes = new DiamondCells[Constants.BOXES_ROWS][Constants.BOXES_COLS];
	public int style, y, x, level;
	private boolean pausing = false, moving = true;	

	/**
	 * 构造函数，产生一个特定的块
	 * @param style 块的样式，对应STYLES的28个值中的一个
	 * @param y 起始位置，左上角在canvas中的坐标行
	 * @param x 起始位置，左上角在canvas中的坐标列
	 * @param level 游戏等级，控制块的下落速度
	 * @param canvas 画板
	 */
	public DiamondBlock(int style, int y, int x, int level, GameCanvas canvas) {
		this.style = style;
		this.y = y;
		this.x = x;
		this.level = level;
		this.canvas = canvas;

		Color fColor=Constants.genColor[(int)(Math.random()*21)];
		int key = 0x8000;
		for (int i = 0; i < boxes.length; i++) {
			for (int j = 0; j < boxes[i].length; j++) {
				boolean isColor = ((style & key) != 0);
				boxes[i][j] = new DiamondCells(isColor);
				boxes[i][j].setforColor(fColor);
				//canvas.
				key >>= 1;
			}
		}
		//canvas.setBlockColor(genColor[(int)Math.random()*6]);

		display();
	}
	
	public DiamondBlock(int style, int y, int x, int level,Color c, GameCanvas canvas) {
		this.style = style;
		this.y = y;
		this.x = x;
		this.level = level;
		this.canvas = canvas;

		//Color fColor=Constants.genColor[(int)(Math.random()*21)];
		int key = 0x8000;
		for (int i = 0; i < boxes.length; i++) {
			for (int j = 0; j < boxes[i].length; j++) {
				boolean isColor = ((style & key) != 0);
				boxes[i][j] = new DiamondCells(isColor);
				boxes[i][j].setforColor(c);
				//canvas.
				key >>= 1;
			}
		}
		//canvas.setBlockColor(genColor[(int)Math.random()*6]);

		display();
	}

	/**
	 * 线程类的run()函数覆盖，下落块，直到块不能再下落
	 */
	public void run() {
		while (moving) {
			try {
				sleep(Constants.BETWEEN_LEVELS_DEGRESS_TIME
				        * (Constants.MAX_LEVEL - level + Constants.LEVEL_FLATNESS_GENE));
			} catch (InterruptedException ie) {
				ie.printStackTrace();
			}
			//后边的moving是表示在等待的100毫秒间，moving没被改变
			if (!pausing) moving = (moveTo(y + 1, x) && moving);
		}
	}

	/**
	 * 块向左移动一格
	 */
	public void moveLeft() {
		moveTo(y, x - 1);
	}

	/**
	 * 块向右移动一格
	 */
	public void moveRight() {
		moveTo(y, x + 1);
	}

	/**
	 * 块向下落一格
	 */
	public void moveDown() {
		moveTo(y + 1, x);
	}

	/**
	 * 块向下落到底部
	 */
	public void moveDownDirect() {
		boolean flags=moveTo(y+1,x);
		while(flags){
			flags=moveTo(y+1,x);
		}
	}
	
	/**
	 * 块变型
	 */
	public void turnNext() {
		for (int i = 0; i < Constants.BLOCK_KIND_NUMBER; i++) {
			for (int j = 0; j < Constants.BLOCK_STATUS_NUMBER; j++) {
				if (Constants.STYLES[i][j] == style) {
					int newStyle = Constants.STYLES[i][(j + 1) % Constants.BLOCK_STATUS_NUMBER];
					turnTo(newStyle);
					return;
				}
			}
		}
	}

	/**
	 * 暂停块的下落，对应游戏暂停
	 */
	public void pauseMove() {
		pausing = true;
	}

	/**
	 * 继续块的下落，对应游戏继续
	 */
	public void resumeMove() {
		pausing = false;
	}

	/**
	 * 停止块的下落，对应游戏停止
	 */
	public void stopMove() {
		moving = false;
	}

	/**
	 * 将当前块从画布的对应位置移除，要等到下次重画画布时才能反映出来
	 */
	private void earse() {
		for (int i = 0; i < boxes.length; i++) {
			for (int j = 0; j < boxes[i].length; j++) {
				if (boxes[i][j].isColorBox()) {
					DiamondCells box = canvas.getBox(i + y, j + x);
					if (box == null) continue;
					box.setColor(false);
				}
			}
		}
	}

	/**
	 * 让当前块放置在画布的对应位置上，要等到下次重画画布时才能看见
	 */
	private void display() {
		for (int i = 0; i < boxes.length; i++) {
			for (int j = 0; j < boxes[i].length; j++) {
				if (boxes[i][j].isColorBox()) {
					DiamondCells box = canvas.getBox(y + i, x + j);
					if (box == null) continue;
					//canvas.boxes[y+i][x+j]=boxes[i][j];
					//canvas.boxes[y+i][x+j].setColor(true);
					box.setforColor(boxes[i][j].getforColor());
					box.setColor(true);
				}
			}
		}
	}

	/**
	 * 当前块能否移动到newRow/newCol所指定的位置
	 * @param newRow int, 目的地所在行
	 * @param newCol int, 目的地所在列
	 * @return boolean, true-能移动，false-不能
	 */
	private boolean isMoveAble(int newRow, int newCol) {
		earse();
		for (int i = 0; i < boxes.length; i++) {
			for (int j = 0; j < boxes[i].length; j++) {
				if (boxes[i][j].isColorBox()) {
					DiamondCells box = canvas.getBox(newRow + i, newCol + j);
					if (box == null || (box.isColorBox())) {
						display();
						return false;
					}
				}
			}
		}
		display();
		return true;
	}

	/**
	 * 将当前画移动到newRow/newCol所指定的位置
	 * @param newRow int, 目的地所在行
	 * @param newCol int, 目的地所在列
	 * @return boolean, true-移动成功，false-移动失败
	 */
	private synchronized boolean moveTo(int newRow, int newCol) {
		if (!isMoveAble(newRow, newCol) || !moving) return false;

		earse();
		y = newRow;
		x = newCol;

		display();
		canvas.repaint();

		return true;
	}

	/**
	 * 当前块能否变成newStyle所指定的块样式，主要是要考虑
	 * 边界以及被其它块挡住、不能移动的情况
	 * @param newStyle int,希望改变的块样式，对应STYLES的28个值中的一个
	 * @return boolean,true-能改变，false-不能改变
	 */
	private boolean isTurnAble(int newStyle) {
		int key = 0x8000;
		earse();
		for (int i = 0; i < boxes.length; i++) {
			for (int j = 0; j < boxes[i].length; j++) {
				if ((newStyle & key) != 0) {
					DiamondCells box = canvas.getBox(y + i, x + j);
					if (box == null || box.isColorBox()) {
						display();
						return false;
					}
				}
				key >>= 1;
			}
		}
		display();
		return true;
	}

	/**
	 * 将当前块变成newStyle所指定的块样式
	 * @param newStyle int,将要改变成的块样式，对应STYLES的28个值中的一个
	 * @return boolean,true-改变成功，false-改变失败
	 */
	private boolean turnTo(int newStyle) {
		if (!isTurnAble(newStyle) || !moving) return false;

		earse();
		int key = 0x8000;
		for (int i = 0; i < boxes.length; i++) {
			for (int j = 0; j < boxes[i].length; j++) {
				boolean isColor = ((newStyle & key) != 0);
				boxes[i][j].setColor(isColor);
				key >>= 1;
			}
		}
		style = newStyle;

		display();
		canvas.repaint();

		return true;
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}
}

