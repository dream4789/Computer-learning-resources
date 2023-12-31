package games.diamonds.utils;

import java.awt.*;

/**
 * 方格类，是组成块的基本元素，用自己的颜色来表示块的外观
 */
public class DiamondCells implements Cloneable {
	private boolean isColor;
	private Dimension size = new Dimension();
	private Color forColor;//=Color.red;

	/**
	 * 方格类的构造函数
	 * @param isColor 是不是用前景色来为此方格着色，
	 *      true前景色，false用背景色
	 */
	public DiamondCells(boolean isColor) {
		this.isColor = isColor;
	}

	/**
	 * 此方格是不是用前景色表现
	 * @return boolean,true用前景色表现，false用背景色表现
	 */
	public boolean isColorBox() {
		return isColor;
	}

	/**
	 * 设置方格的颜色，
	 * @param isColor boolean,true用前景色表现，false用背景色表现
	 */
	public void setColor(boolean isColor) {
		this.isColor = isColor;
	}

	/**
	 * 得到此方格的尺寸
	 * @return Dimension,方格的尺寸
	 */
	public Dimension getSize() {
		return size;
	}

	/**
	 * 设置方格的尺寸
	 * @param size Dimension,方格的尺寸
	 */
	public void setSize(Dimension size) {
		this.size = size;
	}
	
	public void setforColor(Color c){
		this.forColor=c;
	}
	
	public Color getforColor(){
		return this.forColor;
	}

	/**
	 * 覆盖Object的Object clone()，实现克隆
	 * @return Object,克隆的结果
	 */
	public Object clone() {
		Object cloned = null;
		try {
			cloned = super.clone();
		} catch (Exception ex) {
			ex.printStackTrace();
		}

		return cloned;
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}
}
