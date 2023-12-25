package C012_Annotations.sourceApt;

import java.beans.PropertyEditorSupport;

/**
 * project_name: Java_Ex
 *
 * package_name: C012_Annotations.sourceApt 
 *
 * author:  DarlingKe
 *
 * created Time: 2018-1-23 ÉÏÎç9:29:05 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: TitlePositionEditor.java  
 *
 * Description: A custom editor for the titlePosition property of the
 * ChartBean. The editor lets the user choose between 
 * Left, Center, and Right
 *
 */
public class TitlePositionEditor extends PropertyEditorSupport
{  
	   public String[] getTags() { return options; }
	   private String[] options = { "Left", "Center", "Right" };
	   public String getJavaInitializationString() { return "" + getValue(); }

	   public String getAsText()
	   {  
	      int value = (Integer) getValue();
	      return options[value];
	   }

	   public void setAsText(String s)
	   {  
	      for (int i = 0; i < options.length; i++)
	      {  
	         if (options[i].equals(s))
	         {  
	            setValue(new Integer(i));
	            return;
	         }
	      }
	   }
	}


 