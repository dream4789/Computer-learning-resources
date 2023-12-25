package com.javatrain.chat.gui;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import com.javatrain.chat.util.ResourceBundler;

public class FriendPanel extends JPanel{

	/**
	 * 
	 */
	private static final long serialVersionUID = 2021193759608759271L;

	public FriendPanel(ClientMainFrame cmf){
		clientMainFrame=cmf;
		
		setLayout(new BorderLayout());
		
		add(new JLabel(ResourceBundler.getString("ClientFrame.friendList")), BorderLayout.NORTH);
		
		listModel = new DefaultListModel();
		// ListDataListener
		friendList = new JList(listModel);
		friendList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		friendList.addListSelectionListener(new ListSelectionListener(){

			@Override
			public void valueChanged(ListSelectionEvent arg0) {
				// TODO Auto-generated method stub
				try
				{
					String select = (String) friendList.getSelectedValue();
					if (select != null)	{ 
						String[] userInfo = select.split("〖");
						String name = userInfo[0].trim(); 

						if (!name.equals(clientMainFrame.getUserName())){ 
							int count = clientMainFrame.getChatToBox().getItemCount();
							for (int i = 0; i < count; i++)
							{
								clientMainFrame.getChatToBox().setSelectedIndex(i);
								String strName = (String) clientMainFrame.getChatToBox().getSelectedItem();
								if (name.equals(strName))
								{ 
									return;
								}
							}							
							clientMainFrame.getChatToBox().addItem(name);
						}
					}
				} catch (Exception ee)
				{
					ee.printStackTrace();
				}
			}
			
		});
		add(new JScrollPane(friendList),BorderLayout.CENTER);
		
		refreashButton = new JButton(ResourceBundler.getString("ClientFrame.Button.refreshFriend"));
		refreashButton.addActionListener(new ActionListener(){

			@Override
			public void actionPerformed(ActionEvent arg0) {
				// TODO Auto-generated method stub
				try
				{
					listModel.clear(); 
					clientMainFrame.getOutputStream().println("refurbish"); 
					clientMainFrame.getOutputStream().flush();
				} catch (Exception ee)
				{
				}
			}
			
		});
		add(refreashButton, BorderLayout.SOUTH);
	}
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}
	
	private JList friendList; 
	private JButton refreashButton;
	public DefaultListModel listModel;// 用户列表
	public final ClientMainFrame clientMainFrame;	

}
