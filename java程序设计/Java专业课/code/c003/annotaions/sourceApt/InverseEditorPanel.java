package C012_Annotations.sourceApt;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.PropertyEditorSupport;

import javax.swing.ButtonGroup;
import javax.swing.JPanel;
import javax.swing.JRadioButton;

/**
 * project_name: Java_Ex
 *
 * package_name: C012_Annotations.sourceApt 
 *
 * author:  DarlingKe
 *
 * created Time: 2018-1-23 ÉÏÎç9:27:01 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: InverseEditorPanel.java  
 *
 * Description: The panel for setting the inverse property. It contains
 * radio buttons to toggle between normal and inverse coloring.
 *
 */
public class InverseEditorPanel extends JPanel
{  
	   /**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	public InverseEditorPanel(PropertyEditorSupport ed)
	   {  
	      editor = ed;
	      ButtonGroup g = new ButtonGroup();
	      boolean isInverse = (Boolean) editor.getValue();
	      normal = new JRadioButton("Normal", !isInverse);
	      inverse = new JRadioButton("Inverse", isInverse);

	      g.add(normal);
	      g.add(inverse);
	      add(normal);
	      add(inverse);

	      ActionListener buttonListener =
	         new ActionListener()
	         {  
	            public void actionPerformed(ActionEvent event)
	            {  
	               editor.setValue(
	                  new Boolean(inverse.isSelected()));
	               editor.firePropertyChange();
	            }
	         };

	      normal.addActionListener(buttonListener);
	      inverse.addActionListener(buttonListener);
	   }

	   private JRadioButton normal;
	   private JRadioButton inverse;
	   private PropertyEditorSupport editor;
	}


 