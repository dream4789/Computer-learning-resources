
import java.applet.*; 
import java.awt.*;
public class Boy extends Applet
{  
    public void paint(Graphics g)
    {
        g.setColor(Color.blue);   
        g.drawString("Java是一门很优秀的语言",12,30);
        g.setColor(Color.red);
        g.drawString("我一定认真学习Java",22,56);
    }
}     
