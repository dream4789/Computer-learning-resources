//import java.sql.Date;
import java.io.File;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

import javax.swing.JFileChooser;
import javax.swing.filechooser.FileNameExtensionFilter;

import com.javatrain.chat.util.ResourceBundler;


public class Test {

	/**
	 * @param args  yyyy-MM-W-D-h:m:s
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		SimpleDateFormat sdf = new SimpleDateFormat("yyyy-M-d-h:m:s");
        System.out.println(sdf.format(new Date())+"  "+"ddd\\ddd\\dd".split(File.separator+File.separator).length);
        JFileChooser chooser = new JFileChooser();
        FileNameExtensionFilter filter = new FileNameExtensionFilter(
            "文本文档(*.txt)","*.txt");
        System.out.println(ResourceBundler.getResourceBundle().getString("ClientFrame.ChatRecord.Msg"));
       // chooser.setAcceptAllFileFilterUsed(false);
       /* chooser.setFileFilter(filter);
        int returnVal = chooser.showSaveDialog(null);
        if(returnVal == JFileChooser.APPROVE_OPTION) {
           System.out.println("You chose to open this file: " +
                chooser.getSelectedFile().getAbsoluteFile());
           System.out.println("You chose to open this file: " +
                   chooser.getSelectedFile().getParent());
           System.out.println("You chose to open this file: " +
                   chooser.getSelectedFile().getName());
        }*/

	}

}
