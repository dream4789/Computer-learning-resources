package games.diamonds.utils;

import java.awt.*;
import java.lang.reflect.Method;
import javax.swing.*;
import javax.swing.border.*;
import javax.swing.plaf.*;
import javax.swing.plaf.metal.*;

/**
 * The theme class for SSRM.
 */

public class CommonMetalTheme extends DefaultMetalTheme {
    public static final ColorUIResource TH_BACK = new ColorUIResource(0, 74, 147);
    public static final ColorUIResource TITLE_BACK = new ColorUIResource(204, 204, 255);
    public static final ColorUIResource CONFIG_BACK = new ColorUIResource(255, 255, 255);
    public static final ColorUIResource CONFIGINPUT_BACK = new ColorUIResource(255, 255, 255);
    public static final ColorUIResource DEFAULT_BACK = new ColorUIResource(255, 255, 255);
    public static final ColorUIResource HINT_BACK = new ColorUIResource(204, 204, 255);
    public static final ColorUIResource HINT_COLOR = new ColorUIResource(0, 0, 0);
    public static final ColorUIResource HINT_BORDER = new ColorUIResource(102, 102, 153);
    public static final ColorUIResource METER_TITLE_BACK = new ColorUIResource(0, 74, 147);
    public static final ColorUIResource METER_TITLE_COLOR = new ColorUIResource(Color.white);
    public static final FontUIResource HINT_FONT = new FontUIResource("Dialog", Font.PLAIN, 12);
    public static final FontUIResource CONFIGTITLE_FONT = new FontUIResource("Dialog", Font.BOLD, 20);
    public static final FontUIResource TITLE2_FONT = new FontUIResource("Dialog", Font.BOLD, 16);
    public static final FontUIResource METER_TITLE_FONT = new FontUIResource("Dialog", Font.PLAIN, 15);
    public static final int SPLITTER_SIZE = 8;
    public static final int DIALOG_MARGIN = 6;
    public static final int BUTTON_GAP = 6;
    private FontUIResource controlFont;
    private FontUIResource systemFont;
    private FontUIResource userFont;
    private FontUIResource smallFont;

    /**
     * The table header border class in SGIL. Default implementation in Swing
     * use control colors. This class uses different colors according to color
     * of current table header.
     */
    public static class SGILTableHeaderBorder extends AbstractBorder
        implements UIResource {
        /**
		 * 
		 */
		private static final long serialVersionUID = 1L;
		protected Insets editorBorderInsets = new Insets(2, 2, 2, 0);

        public void paintBorder(Component c, Graphics g, int x, int y, int w, int h) {
            g.translate(x, y);

            g.setColor(c.getBackground().darker().darker());
            g.drawLine(w - 1, 0, w - 1, h - 1);
            g.drawLine(1, h - 1, w - 1, h - 1);
            g.setColor(c.getBackground().brighter().brighter());
            g.drawLine(0, 0, w - 2, 0);
            g.drawLine(0, 0, 0, h - 2);

            g.translate(-x, -y);
        }

        public Insets getBorderInsets(Component c) {
            return editorBorderInsets;
        }
    }

    /**
     * The tool bar border class in SGIL.
     */
    public static class SGILToolBarBorder extends AbstractBorder
        implements UIResource, SwingConstants {
        /**
		 * 
		 */
		private static final long serialVersionUID = 1L;
		protected Insets borderInsets = new Insets(2, 13, 2, 2);

        public void paintBorder(Component c, Graphics g, int x, int y, int w, int h) {
            g.translate( x, y );
            if (((JToolBar)c).getOrientation() == HORIZONTAL) {
                g.setColor(c.getBackground().brighter().brighter());
                g.drawLine(4, 2, 4, c.getSize().height - 4);
                g.drawLine(7, 2, 7, c.getSize().height - 4);
                g.setColor(c.getBackground().darker().darker());
                g.drawLine(5, 2, 5, c.getSize().height - 4);
                g.drawLine(8, 2, 8, c.getSize().height - 4);
            } else {
                g.setColor(c.getBackground().brighter().brighter());
                g.drawLine(2, 4, c.getSize().width - 4, 4);
                g.drawLine(2, 7, c.getSize().width - 4, 7);
                g.setColor(c.getBackground().darker().darker());
                g.drawLine(2, 5, c.getSize().width - 4, 5);
                g.drawLine(2, 8, c.getSize().width - 4, 8);
            }
            g.translate( -x, -y );
        }

        public Insets getBorderInsets(Component c) {
            Insets margin = ((JToolBar)c).getMargin();

            if (margin == null) {
                return borderInsets;
            } else {
                return new Insets(2 + margin.top, 13 + margin.left,
                                  2 + margin.bottom, 2 + margin.right);
            }
        }
    }


    /**
     * Constructor.
     */
    public CommonMetalTheme() {
        controlFont = new FontUIResource("Dialog", Font.PLAIN, 12);
        systemFont = new FontUIResource("Dialog", Font.PLAIN, 12);
        userFont = new FontUIResource("Dialog", Font.PLAIN, 12);
        smallFont = new FontUIResource("Dialog", Font.PLAIN, 10);
    }

    /**
     * Install a UI class as Swing default. To install a UI class, the following
     * three steps should be performed: 1. Register the class name, key is the
     * UI entry; 2. Register the Class object, key is the class name; 3. Register
     * the Method object to create a new UI, key is the Class object.
     * @param table The property table.
     * @param key The key of UI entry.
     * @param className The full qualified class name of the UI class.
     */
    @SuppressWarnings("unchecked")
	public static void installUIClass(UIDefaults table, String key,
                                      String className) {
        try {
            Class cls = Class.forName(className);
            Method mtd = cls.getMethod("createUI", new Class[] { JComponent.class });

            table.put(key, className);
            table.put(className, cls);
            table.put(cls, mtd);
        } catch (Exception e) {
        }
    }

    /**
     * Get color of system text. We use black in SGIL Suite.
     */
    public ColorUIResource getSystemTextColor() {
        return getBlack();
    }

    /**
     * Add custom entries in property table.
     */
    public void addCustomEntriesToTable(UIDefaults table) {
        // Register UI for JTree.
        installUIClass(table, "TreeUI", "monitorSys.utils.gui.WindowsTreeUI");

        // Register border and color of TableHeader.

        table.put("TableHeader.cellBorder", new SGILTableHeaderBorder());
        table.put("TableHeader.background", TH_BACK);
        table.put("TableHeader.foreground", new ColorUIResource(255, 255, 255));

        // Register border of JToolBar.
        //table.put("ToolBar.border", new SGILToolBarBorder());

        // Register UI for JToolBar.
        installUIClass(table, "ToolBarUI", "monitorSys.utils.gui.MetalToolBarUIEx");

        // Register UI for buttons in JToolBar.
        //installUIClass(table, "ButtonUI", "com.everlasting.sgil.util.FloatButtonUI");

        // Register UI for separators in JToolBar.
        installUIClass(table, "ToolBarSeparatorUI", "monitorSys.utils.gui.EtchedToolBarSeparatorUI");
        table.put("ToolBar.separatorSize", new Dimension(20, 20));
        table.put("ScrollBar.width", new Integer(12));

        // Force using chinese in JOptionPane.

        table.put("OptionPane.okButtonText", "确定");
        table.put("OptionPane.yesButtonText", "昄1�7");
        table.put("OptionPane.noButtonText", "各1�7");
        table.put("OptionPane.cancelButtonText", "取消");

        // Force using chinese in JFileChooser

        table.put("FileChooser.newFolderErrorText", "创建新的文件夹错评1�7");
        table.put("FileChooser.fileDescriptionText", "普�1�7�的文件");
        table.put("FileChooser.directoryDescriptionText", "目录");
        table.put("FileChooser.saveButtonText", "保存");
        table.put("FileChooser.openButtonText", "打开");
        table.put("FileChooser.cancelButtonText", "取消");
        table.put("FileChooser.helpButtonText", "帮助");
        table.put("FileChooser.saveButtonToolTipText", "保存选择的文仄1�7");
        table.put("FileChooser.openButtonToolTipText", "打开选择的文仄1�7");
        table.put("FileChooser.cancelButtonToolTipText", "取消文件选择对话桄1�7");
        table.put("FileChooser.updateButtonToolTipText", "更新目录列表");
        table.put("FileChooser.helpButtonToolTipText", "文件选择器帮劄1�7");
        table.put("FileChooser.acceptAllFileFilterText", "扄1�7有文仄1�7(*.*)");
        table.put("FileChooser.lookInLabelText", "查看＄1�7");
        table.put("FileChooser.fileNameLabelText", "文件名：");
        table.put("FileChooser.filesOfTypeLabelText", "文件类型＄1�7");
        table.put("FileChooser.upFolderToolTipText", "向上丄1�7屄1�7");
        table.put("FileChooser.upFolderAccessibleName", "向上");
        table.put("FileChooser.homeFolderToolTipText", "宿主目录");
        table.put("FileChooser.homeFolderAccessibleName", "宿主目录");
        table.put("FileChooser.newFolderToolTipText", "创建新的文件处1�7");
        table.put("FileChooser.listViewButtonToolTipText", "列表显示");
        table.put("FileChooser.listViewButtonAccessibleName", "列表显示");
        table.put("FileChooser.detailsViewButtonToolTipText", "显示详细信息");
        table.put("FileChooser.detailsViewButtonAccessibleName", "显示详细信息");
    }

    /**
     * Override the method in super class.
     */
    public FontUIResource getSubTextFont() {
        return smallFont;
    }

    /**
     * Override the method in super class.
     */
    public FontUIResource getSystemTextFont() {
        return systemFont;
    }

    /**
     * Override the method in super class.
     */
    public FontUIResource getUserTextFont() {
        return userFont;
    }

    /**
     * Override the method in super class.
     */
    public FontUIResource getWindowTitleFont() {
        return controlFont;
    }

    /**
     * Override the method in super class.
     */
    public FontUIResource getControlTextFont() {
        return controlFont;
    }

    /**
     * Override the method in super class.
     */
    public FontUIResource getMenuTextFont() {
        return controlFont;
    }
}