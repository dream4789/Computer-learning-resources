package C012_Annotations.sourceApt;

import java.awt.Color;
import java.awt.Component;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.font.FontRenderContext;
import java.awt.geom.Rectangle2D;
import java.beans.PropertyEditorSupport;
/**
 * project_name: Java_Ex
 *
 * package_name: C012_Annotations.sourceApt 
 *
 * author:  DarlingKe
 *
 * created Time: 2018-1-23 ÉÏÎç9:27:57 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: InverseEditor.java  
 *
 * Description: The property editor for the inverse property of the ChartBean.
 * The inverse property toggles between colored graph bars 
 * and colored background. 
 *
 */
public class InverseEditor extends PropertyEditorSupport
{  
	   public Component getCustomEditor() { return new InverseEditorPanel(this); }
	   public boolean supportsCustomEditor() { return true; }
	   public boolean isPaintable() { return true; }
	   public String getAsText() { return null; }
	   public String getJavaInitializationString() { return "" + getValue(); }

	   public void paintValue(Graphics g, Rectangle box)
	   {  
	      Graphics2D g2 = (Graphics2D) g;
	      boolean isInverse = (Boolean) getValue();
	      String s = isInverse ? "Inverse" : "Normal";
	      g2.setPaint(isInverse ? Color.black : Color.white);
	      g2.fill(box);
	      g2.setPaint(isInverse ? Color.white : Color.black);
	      FontRenderContext context = g2.getFontRenderContext();
	      Rectangle2D stringBounds = g2.getFont().getStringBounds(s, context);
	      double w = stringBounds.getWidth();
	      double x = box.x;
	      if (w < box.width) x += (box.width - w) / 2;
	      double ascent = -stringBounds.getY();
	      double y = box.y + (box.height - stringBounds.getHeight()) / 2 + ascent;
	      g2.drawString(s, (float) x, (float) y);
	   }
	}

 