package C011_SwingGui.dialog;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

/**
 * project_name: Java_Ex
 *
 * package_name: C011_SwingGui.dialog 
 *
 * author:  DarlingKe
 *
 * created Time: 2018-1-3 ����4:54:54 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: ColorChooserTest.java  
 *
 * Description:  
 *
 */
public class ColorChooserTest {
	public static void main(String[] args)
	   {
	      ColorChooserFrame frame = new ColorChooserFrame();
	      frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	      frame.setVisible(true);
	   }
	}

	/**
	   A frame with a color chooser panel
	*/
	class ColorChooserFrame extends JFrame
	{
	   /**
		 * 
		 */
		private static final long serialVersionUID = 3098985985787131740L;
	public ColorChooserFrame()
	   {
	      setTitle("ColorChooserTest");
	      setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);

	      // add color chooser panel to frame

	      ColorChooserPanel panel = new ColorChooserPanel();      
	      add(panel);
	   }

	   public static final int DEFAULT_WIDTH = 300;
	   public static final int DEFAULT_HEIGHT = 200;  
	}

	/**
	   A panel with buttons to pop up three types of color choosers
	*/
	class ColorChooserPanel extends JPanel
	{
	   /**
		 * 
		 */
		private static final long serialVersionUID = 7643059081375453767L;

	public ColorChooserPanel()
	   {
	      JButton modalButton = new JButton("Modal");
	      modalButton.addActionListener(new ModalListener());
	      add(modalButton);

	      JButton modelessButton = new JButton("Modeless");
	      modelessButton.addActionListener(new ModelessListener());
	      add(modelessButton);

	      JButton immediateButton = new JButton("Immediate");
	      immediateButton.addActionListener(new ImmediateListener());
	      add(immediateButton);
	   }

	   /**
	      This listener pops up a modal color chooser
	   */
	   private class ModalListener implements ActionListener
	   {
	      public void actionPerformed(ActionEvent event)
	      {
	         Color defaultColor = getBackground();
	         Color selected = JColorChooser.showDialog(
	            ColorChooserPanel.this, 
	            "Set background", 
	            defaultColor);
	         if (selected != null) setBackground(selected);
	      }
	   }

	   /**
	      This listener pops up a modeless color chooser.
	      The panel color is changed when the user clicks the Ok
	      button.
	   */
	   private class ModelessListener implements ActionListener
	   {
	      public ModelessListener()
	      {
	         chooser = new JColorChooser();
	         dialog = JColorChooser.createDialog(
	            ColorChooserPanel.this,
	            "Background Color",
	            false /* not modal */,
	            chooser,
	            new ActionListener() // OK button listener
	               {
	                  public void actionPerformed(ActionEvent event)
	                  {
	                     setBackground(chooser.getColor());
	                  }
	               },
	            null /* no Cancel button listener */);
	      }

	      public void actionPerformed(ActionEvent event)
	      {
	         chooser.setColor(getBackground());
	         dialog.setVisible(true);
	      }

	      private JDialog dialog;
	      private JColorChooser chooser;
	   }

	   /**
	      This listener pops up a modeless color chooser.
	      The panel color is changed immediately when the
	      user picks a new color.
	   */
	   private class ImmediateListener implements ActionListener
	   {
	      public ImmediateListener()
	      {
	         chooser = new JColorChooser();
	         chooser.getSelectionModel().addChangeListener(new
	            ChangeListener()
	            {
	               public void stateChanged(ChangeEvent event)
	               {
	                  setBackground(chooser.getColor());
	               }
	            });

	         dialog = new JDialog(
	            (Frame) null, 
	            false /* not modal */);
	         dialog.add(chooser);
	         dialog.pack();
	      }

	      public void actionPerformed(ActionEvent event)
	      {
	         chooser.setColor(getBackground());
	         dialog.setVisible(true);
	      }

	      private JDialog dialog;
	      private JColorChooser chooser;
	   }
	}


