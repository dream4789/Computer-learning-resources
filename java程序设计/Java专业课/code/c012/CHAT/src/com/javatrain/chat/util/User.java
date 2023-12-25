package com.javatrain.chat.util;

//聊天用
public class User {
	private String userName;
	private String userSex;
	private String userIcon;
	private boolean isOpenChatRecord;
	private String userID;
	private int index;
	public String getUserName() {
		return userName;
	}

	public void setUserName(String userName) {
		this.userName = userName;
	}

	public String getUserSex() {
		return userSex;
	}

	public void setUserSex(String userSex) {
		this.userSex = userSex;
	}

	public String getUserIcon() {
		return userIcon;
	}

	public void setUserIcon(String userIcon) {
		this.userIcon = userIcon;
	}

	public boolean isOpenChatRecord() {
		return isOpenChatRecord;
	}

	public void setOpenChatRecord(boolean isOpenChatRecord) {
		this.isOpenChatRecord = isOpenChatRecord;
	}

	public int getIndex() {
		return index;
	}

	public void setIndex(int index) {
		this.index = index;
	}

	public String getUserID() {
		return userID;
	}

	public void setUserID(String userID) {
		this.userID = userID;
	}

	public User(String uName, String uSex, String uIcon) {
		this.userName = uName;
		this.userSex = uSex;
		this.userIcon = uIcon;
	}

	@Override
	public boolean equals(Object obj) {
		// TODO Auto-generated method stub
		if(obj != null){
			String user = (String) obj;
			return user.equals(this.userName);
		}
		return false;
	}
	@Override
	public String toString() {
		// TODO Auto-generated method stub
		return userName + " 〖" + userSex + "〗";
	}
}
