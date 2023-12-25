package C009_Database;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DatabaseMetaData;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.Properties;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
/**  

 * Created Time£º2013-12-18 ÉÏÎç10:19:40  

 * Project Name£ºEx.Proj  

 * @author DarlingKe  

 * @version 1.0   

 * @since JDK 1.7.0_15  

 * FileName£ºTestMySqlDB.java  

 * Description£º  

 */
public class SimpleMysqlClient {

	/**
	
	 * <p>Title: main</p>
	
	 * <p>Description: </p>
	
	 * @param args
	
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		JFrame frame = new ViewDBFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}
}
class ViewDBFrame extends JFrame {
	/**
	 * 
	 */
	private static final long serialVersionUID = 8054895866176743249L;

	public ViewDBFrame() {
		setTitle("ViewDB");
		setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);

		tableNames = new JComboBox();
		tableNames.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				showTable((String) tableNames.getSelectedItem());
			}
		});
		add(tableNames, BorderLayout.NORTH);

		try {
			conn = getConnection();
			meta = conn.getMetaData();
			createStatement();
			getTableNames();
		} catch (SQLException e) {
			JOptionPane.showMessageDialog(this, e);
		} catch (IOException e) {
			JOptionPane.showMessageDialog(this, e);
		}

		JPanel buttonPanel = new JPanel();
		add(buttonPanel, BorderLayout.SOUTH);

		if (scrolling) {
			previousButton = new JButton("Previous");
			previousButton.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent event) {
					showPreviousRow();
				}
			});
			buttonPanel.add(previousButton);
		}

		nextButton = new JButton("Next");
		nextButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				showNextRow();
			}
		});
		buttonPanel.add(nextButton);

		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent event) {
				try {
					if (conn != null)
						conn.close();
				} catch (SQLException e) {
					while (e != null) {
						e.printStackTrace();
						e = e.getNextException();
					}
				}
			}
		});
	}

	/**
	 * Creates the statement object used for executing queries. If the database
	 * supports scrolling cursors, the statement is created to yield them.
	 */
	public void createStatement() throws SQLException {
		if (meta.supportsResultSetType(ResultSet.TYPE_SCROLL_INSENSITIVE)) {
			stat = conn.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,
					ResultSet.CONCUR_READ_ONLY);
			scrolling = true;
		} else {
			stat = conn.createStatement();
			scrolling = false;
		}
	}

	/**
	 * Gets all table names of this database and adds them to the combo box.
	 */
	public void getTableNames() throws SQLException {
		ResultSet mrs = meta.getTables(null, null, null,
				new String[] { "TABLE" });
		while (mrs.next())
			tableNames.addItem(mrs.getString(3));
		mrs.close();
	}

	/**
	 * Prepares the text fields for showing a new table, and shows the first
	 * row.
	 * 
	 * @param tableName
	 *            the name of the table to display
	 */
	public void showTable(String tableName) {
		try {
			if (rs != null)
				rs.close();
			rs = stat.executeQuery("SELECT * FROM " + tableName);
			if (scrollPane != null)
				remove(scrollPane);
			dataPanel = new DataPanel(rs);
			scrollPane = new JScrollPane(dataPanel);
			add(scrollPane, BorderLayout.CENTER);
			validate();
			showNextRow();
		} catch (SQLException e) {
			JOptionPane.showMessageDialog(this, e);
		}
	}

	/**
	 * Moves to the previous table row.
	 */
	public void showPreviousRow() {
		try {
			if (rs == null || rs.isFirst())
				return;
			rs.previous();
			dataPanel.showRow(rs);
		} catch (SQLException e) {
			JOptionPane.showMessageDialog(this, e);
		}
	}

	/**
	 * Moves to the next table row.
	 */
	public void showNextRow() {
		try {
			if (rs == null || scrolling && rs.isLast())
				return;

			if (!rs.next() && !scrolling) {
				rs.close();
				rs = null;
				return;
			}

			dataPanel.showRow(rs);
		} catch (SQLException e) {
			JOptionPane.showMessageDialog(this, e);
		}
	}

	/**
	 * Gets a connection from the properties specified in the file
	 * database.properties
	 * 
	 * @return the database connection
	 */
	public static Connection getConnection() throws SQLException, IOException {
		Properties props = new Properties();
		FileInputStream in = new FileInputStream("mysql.properties");
		props.load(in);
		in.close();

		String drivers = props.getProperty("jdbc.drivers");
		if (drivers != null)
			System.setProperty("jdbc.drivers", drivers);
		String url = props.getProperty("jdbc.url");
		String username = props.getProperty("jdbc.username");
		String password = props.getProperty("jdbc.password");

		return DriverManager.getConnection(url, username, password);
	}

	public static final int DEFAULT_WIDTH = 300;
	public static final int DEFAULT_HEIGHT = 200;

	private JButton previousButton;
	private JButton nextButton;
	private DataPanel dataPanel;
	private Component scrollPane;
	private JComboBox tableNames;

	private Connection conn;
	private Statement stat;
	private DatabaseMetaData meta;
	private ResultSet rs;
	private boolean scrolling;
}

/**
 * This panel displays the contents of a result set.
 */
class DataPanel extends JPanel {
	/**
	 * 
	 */
	private static final long serialVersionUID = 2513591420188597766L;

	/**
	 * Constructs the data panel.
	 * 
	 * @param rs
	 *            the result set whose contents this panel displays
	 */
	public DataPanel(ResultSet rs) throws SQLException {
		fields = new ArrayList<JTextField>();
		setLayout(new GridBagLayout());
		GridBagConstraints gbc = new GridBagConstraints();
		gbc.gridwidth = 1;
		gbc.gridheight = 1;

		ResultSetMetaData rsmd = rs.getMetaData();
		for (int i = 1; i <= rsmd.getColumnCount(); i++) {
			gbc.gridy = i - 1;

			String columnName = rsmd.getColumnLabel(i);
			gbc.gridx = 0;
			gbc.anchor = GridBagConstraints.EAST;
			add(new JLabel(columnName), gbc);

			int columnWidth = rsmd.getColumnDisplaySize(i);
			JTextField tb = new JTextField(columnWidth);
			fields.add(tb);

			gbc.gridx = 1;
			gbc.anchor = GridBagConstraints.WEST;
			add(tb, gbc);
		}
	}

	/**
	 * Shows a database row by populating all text fields with the column
	 * values.
	 */
	public void showRow(ResultSet rs) throws SQLException {
		for (int i = 1; i <= fields.size(); i++) {
			String field = rs.getString(i);
			JTextField tb = (JTextField) fields.get(i - 1);
			tb.setText(field);
		}
	}

	private ArrayList<JTextField> fields;
}

