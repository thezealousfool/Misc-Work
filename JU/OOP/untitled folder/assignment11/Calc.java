import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

class Calculator extends JFrame
{
    MyPanel p;
    public Calculator()
    {
        super("Java Swing Calculator");
        setSize(280, 260);
        p=new MyPanel();
        add(p,BorderLayout.CENTER);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }
}
class MyPanel extends JPanel
{
    JTextField tf;
    JMenuBar menu_bar;
	JMenu menu;
	JMenuItem menu_item;
	String sx,sy;
	double x,y;
	char operator;
    JButton b[],bbs,bce,bc,bdiv,bsqrt,bmul,bi,bsub,bmod,bcs,bp,badd,bequal;
    
    MyPanel()
    {
        super();
        setLayout(new FlowLayout(FlowLayout.LEFT));
        tf=new JTextField(20);
        tf.setPreferredSize(new Dimension(260, 25));
        menu_bar = new JMenuBar();
		menu=new JMenu("File");
		menu_bar.add(menu);
		menu=new JMenu("Help");
		menu_bar.add(menu);
	    b=new JButton[10];
		for(int i=0;i<10;i++)
			b[i]=new JButton(Integer.toString(i));
        bbs=new JButton("Backspace");
		bbs.setPreferredSize(new Dimension(150, 25));
		bce=new JButton("CE");
		bc=new JButton("C");
		bdiv=new JButton("/");
		bsqrt=new JButton("sqrt");
		bmul=new JButton("*");
		bi=new JButton("1/x");
		bsub=new JButton("-");
		bmod=new JButton("%");
		bcs=new JButton("+/-");
		bp=new JButton(".");
        badd=new JButton("+");
		bequal=new JButton("=");
		sx="";
		sy="";
		x=y=0;
		operator='+';
        add(menu_bar);
        add(tf);
		add(bbs);
        add(bce);
        add(bc);
        add(b[7]);
        add(b[8]);
        add(b[9]);
        add(bdiv);
        add(bsqrt);
        add(b[4]);
        add(b[5]);
        add(b[6]);
        add(bmul);
        add(bi);
        add(b[1]);
        add(b[2]);
        add(b[3]);
        add(bsub);
        add(bmod);
        add(b[0]);
        add(bcs);
        add(bp);
        add(badd);
        add(bequal);
        for(int i=0;i<=9;i++)
			b[i].addActionListener(new MyListenerDigit());
        bbs.addActionListener(new MyListenerbs());
        //bce.addActionListener(new MyListenerce);
        bc.addActionListener(new MyListenerc());
        bdiv.addActionListener(new MyListenerdiv());
        bsqrt.addActionListener(new MyListenersqrt());
        bmul.addActionListener(new MyListenermul());
        bi.addActionListener(new MyListeneri());
        bsub.addActionListener(new MyListenersub());
        bmod.addActionListener(new MyListenermod());
        bcs.addActionListener(new MyListenercs());
        bp.addActionListener(new MyListenerp());
        badd.addActionListener(new MyListeneradd());
        bequal.addActionListener(new MyListenerequal());
    }
    private class MyListenerDigit implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
			String num=((JButton) e.getSource()).getActionCommand();
			tf.setText(tf.getText().concat(num));
        }
    }
    private class MyListenerbs implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
			String s=tf.getText();
			tf.setText(s.substring(0,s.length()-1));
        }
    }
    /*private class MyListenerce implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {

        }
    }*/
    private class MyListenerc implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
			tf.setText("");
        }
    }
    private class MyListenerdiv implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
			operator='/';
			tf.setText(tf.getText().concat("/"));
        }
    }
    private class MyListenersqrt implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
			String s=tf.getText();
			try
			{
				double text=Double.parseDouble(s);
				double result=Math.sqrt(text);
				tf.setText(Double.toString(result));
			}
			catch(Exception ex)
			{
                tf.setText("Invalid Input");
            }
        }
    }
    private class MyListenermul implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
			operator='*';
			tf.setText(tf.getText().concat("*"));
        }
    }
    private class MyListeneri implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
			String s=tf.getText();
			try
			{
				double text=Double.parseDouble(s);
				double result=1/text;
				tf.setText(Double.toString(result));
			}
			catch(Exception ex)
			{
                tf.setText("Invalid Input");
            }
        }
    }
    private class MyListenersub implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
			operator='-';
			tf.setText(tf.getText().concat("-"));
        }
    }
    private class MyListenermod implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
			operator='%';
			tf.setText(tf.getText().concat("%"));
        }
    }
    private class MyListenercs implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
			String s=tf.getText();
			try
			{
				double text=Double.parseDouble(s);
				if(text>0)
                    tf.setText("-".concat(Double.toString(Math.abs(text))));
                else if(text<0)
                    tf.setText(Double.toString(Math.abs(text)));
			}
			catch(Exception ex)
			{
                tf.setText("Invalid Input");
            }
        }
    }
    private class MyListenerp implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
			tf.setText(tf.getText().concat("."));
        }
    }
    private class MyListeneradd implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
			operator='+';
			tf.setText(tf.getText().concat("+"));
        }
    }
    private class MyListenerequal implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
			String s=tf.getText();
			try{
				//double text=Double.parseDouble(tf.getText());
				sx=s.substring(0,s.indexOf(operator));
				x=Double.parseDouble(sx);
				sy=s.substring(s.indexOf(operator)+1,s.length());
				y=Double.parseDouble(sy);
				double result=0.0;
				int res=0;
				switch(operator){
				    case '+':
	                	result=x+y;
	                    tf.setText(Double.toString(result));
				        break;
			        case '-':
			            result=x-y;
			            tf.setText(Double.toString(result));
			            break;
			        case '*':
			            result=x*y;
			            tf.setText(Double.toString(result));
			            break;
			        case '/':
			            result=x/y;
			            tf.setText(Double.toString(result));
	                    break;
	                case '%':
	                	res=(int)(x%y);
	                    tf.setText(Integer.toString(res));
	                    break;
			        default:
			            result=0;
			            tf.setText(Double.toString(result));
			            break;
			    }
			}
			catch(Exception ex){
			    tf.setText("Invalid Input");
			}
        }
    }
}
public class Calc
{
    public static void main(String args[])
    {
        new Calculator();
    }
}
