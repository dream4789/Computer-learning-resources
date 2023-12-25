import java.util.*;
import java.util.Stack; 
import java.awt.BorderLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.beans.Expression;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import javax.swing.*;
public class Calculater extends JFrame implements KeyListener, ActionListener {
	JTextField text;
	String display;
	boolean flag=false;
	void init()
	{
		setTitle("������ʾ��");
		text=new JTextField("0.0");
		text.setEditable(false);
		text.setHorizontalAlignment(JTextField.RIGHT);//������ʾ
        add(text, BorderLayout.NORTH);
        text.addKeyListener(this);
        JPanel p = new JPanel();//����һ��JPanel��������
        GridBagLayout layout = new GridBagLayout();
        p.setLayout(layout);
        String[] name = {"C","��","*","��","7","8","9","-","4","5","6","+","1","2","3","=","0","."};
        JButton [] button=new JButton[name.length];
        for (int i = 0; i < name.length; ++i)
        {
            button[i]=new JButton(name[i]);
            button[i].setActionCommand(name[i]);
            button[i].addActionListener(this);
        }
        GridBagConstraints s= new GridBagConstraints();//����һ��GridBagConstraints��
        s.fill = GridBagConstraints.BOTH;//ʹ���������ʾ����
        for(int i=1;i<16;i++) 
        {
        	if(i%4!=0)
        		s.gridwidth=1;//�������ˮƽ��ռ�õ������������Ϊ0������Ǹ��е����һ��
        	else
        		s.gridwidth=0;
        		s.weightx = 1;//�������ˮƽ��������ȣ�Ϊ0�����죬��Ϊ0�����Ŵ��������������
                s.weighty=1;//���������ֱ��������ȣ�Ϊ0�����죬��Ϊ0�����Ŵ��������������
                p.add(button[i-1],s);//�����ɵİ�ť����GridBagConstraints����λ�ý������
        }
        s.gridwidth=0;
        s.gridheight=2;
        s.weightx = 1;
        s.weighty=1;
        p.add(button[15],s);//����=����ť����Ϊռ������һ��
        s.gridx=0;
        s.gridy=4;
        s.gridheight=1;
        s.gridwidth=2;
        s.weightx = 1;
        s.weighty=1;
        p.add(button[16],s);//����0����ť�����ڵ�4�У���0����ʾ����ռ������һ�У���������
        s.gridx=2;
        s.gridy=4;
        s.gridwidth=1;
        s.gridheight=1;
        s.weightx = 0;
        s.weighty=0;
        p.add(button[17],s);//����.����ť�����ڵ�4�У���2����ʾ����������
        add(p);//��JPanel�������뵽�����У�Ĭ��Ϊ�м�λ��
        setSize(250,250);//���ô��ڴ�СΪ250*250
        setVisible(true);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
	}
	public void actionPerformed(ActionEvent e) {
		if (flag==true){
			text.setText("0.0");
			flag=false;
		}
		String content=text.getText();
		if(!content.equals("0.0")){//������Ϊ�ǳ�ʼ״̬
			if(e.getActionCommand().equals("C")){//�������������
				text.setText("0.0");
				}
			else 
				{
				if((e.getActionCommand().equals("��"))){//ɾ���ַ������һ���ַ�
					if(content.length()>1)
						text.setText(content.substring(0, content.length()-1));
					else
						text.setText("0.0");
					}
				else
					{//���������ַ�
						Pattern pattern=Pattern.compile("\\d$");
						Matcher matcher=pattern.matcher(content);
						if(matcher.find()){//����ַ�����������֣����������κ���Ϣ
							//text.setText(content+e.getActionCommand());
							if(e.getActionCommand().equals("=")){
								String name=text.getText();
								calculate expression = new calculate(name+"#");
						    	  expression.solve();
						    	  double result = expression.operate();
						    	  text.setText(String.valueOf(result));
						    	  flag=true;
							}
							else{
								text.setText(content+e.getActionCommand());
							}
						}
						else{//����ֻ����������
							matcher=pattern.matcher(e.getActionCommand());
							if(matcher.find()){//��������֣���������
								text.setText(content+e.getActionCommand());
							}	
						}
					}
				}
		}
				else{
						Pattern pattern=Pattern.compile("\\d$");
						Matcher matcher=pattern.matcher(e.getActionCommand());
						if(matcher.find()){
							text.setText(e.getActionCommand());
						}
		}
	}
	public void keyTyped(KeyEvent e) {}
	public void keyPressed(KeyEvent e) {}
	public void keyReleased(KeyEvent e) {}
	public static void main(String s[]){
		new Calculater().init();
	}
}

 class calculate {
	Stack<Character> stack = new Stack<Character>();
	char a[]=new char[100];
	char b[]=new char[100];// ��׺���ʽ

	public calculate(String in){
		this.a = in.toCharArray();
		
	}
	public int priority(char operator){
		switch (operator) {//��������ȼ�  
        case '+':  
              return 1;  
        case '-':  
              return 1;  
        case '*':  
              return 2;  
        case '��':  
              return 2; 
        case '(':  
            return 0;
        default:  
              return -1;   
        }
	}
	public void solve() {//�ַ�������
		stack.push('#');
		int la = a.length;
		
		int j = 0;
		boolean flag = true;//������
		for(int i = 0;i < la;i++){
			if(a[i] >= '0' && a[i] <= '9' || a[i] == '.'){
				b[j++] = a[i];
				flag = true;
			}
			else if(a[i] == '('){
				stack.push(a[i]);
			}
			else if(a[i] == ')'){
				if(flag == true){
					b[j++] = ' ';
					flag = false;
				}
				while(stack.peek() !='('){
					 b[j++]=stack.peek();
					 stack.pop();
			    }
				stack.pop();
			}
			else{
				if(flag == true){
					b[j++] = ' ';
					flag = false;
				}
				while( priority(stack.peek()) >= priority(a[i]) && stack.peek() != '#'){
					
				      b[j++] = stack.peek();
				      stack.pop();
				}
				stack.push(a[i]);
			}
		}
		while(stack.peek() != '#'){
			b[j++] = stack.peek();
			stack.pop();
		}
		b[j] = '\n';
	}

	public double operate() {
		double res = 0;
		double sum = 0;
		int position = 0;
		boolean xiaoshu = false;
		double dianwei = 0.1;
		Stack<Double> stack_operate = new Stack<Double>();
		while(b[position] != '\n'){
			if(b[position] >= '0' && b[position] <='9'){
			     if(xiaoshu == false) res = res*10+b[position]-'0';
			     else{
			    	 res = res+dianwei*(b[position]-'0');
			    	 dianwei = dianwei*0.1;
			     }
			     
			}
			else if(b[position] == '.'){
				xiaoshu = true;
			}
			else if(b[position] == ' '){
				xiaoshu = false;
				dianwei = 0.1;
				if(res != 0){
					stack_operate.push(res);
					res = 0;
				}
			}
			else{
				double x1 = stack_operate.peek();
				stack_operate.pop();
				double x2 = stack_operate.peek();
				stack_operate.pop();
				if(b[position] == '+') sum = x1+x2;
				else if(b[position] == '-') sum = x2-x1;
				else if(b[position] == '*') sum = x2*x1;
				else if (b[position] == '��') sum = x2/x1;
				stack_operate.push(sum);
				res = 0;
			}
			position++;
		}
		return sum;
	}
}
