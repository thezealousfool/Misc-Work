import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.math.*;

class Operations
{
	private static BigInteger mod = BigInteger.ZERO;

	public static BigInteger fact(BigInteger n) {
		if(n.compareTo(BigInteger.ZERO) <= 0)
			return BigInteger.ONE;
		if(!n.equals(BigInteger.ONE)) {
			if(mod.equals(BigInteger.ZERO))
				return n.multiply(fact(n.subtract(BigInteger.ONE)));
			else
				return (n.multiply(fact(n.subtract(BigInteger.ONE)))).mod(mod);				
		}
		return BigInteger.ONE;
	}

	public static BigInteger xCy(BigInteger x, BigInteger y) {
		if(y.compareTo(x) > 0) {
			return BigInteger.ZERO;
		}
		if(y.compareTo(x) == 0) {
			return BigInteger.ONE;
		}
		if(y.compareTo(BigInteger.ZERO) == 0) {
			return BigInteger.ONE;
		}
		if(y.compareTo(BigInteger.ZERO) < 0) {
			return BigInteger.ZERO;
		}
		if(mod.compareTo(BigInteger.ZERO) == 0) {
			return (xCy(x.subtract(BigInteger.ONE),
				y.subtract(BigInteger.ONE))).add(
				xCy(x.subtract(BigInteger.ONE), y));
		} else {
			return ((xCy(x.subtract(BigInteger.ONE),
				y.subtract(BigInteger.ONE))).add(
				xCy(x.subtract(BigInteger.ONE), y))).mod(mod);
		}
	}

	public static void setMod(BigInteger mod) {
		Operations.mod = mod;
	}

	public static BigInteger getMod() {
		return Operations.mod;
	}

	public static BigInteger setBit(BigInteger value, BigInteger position) {
		BigInteger val = (BigInteger.ONE).shiftLeft(position.intValue());
		val = val.or(value);
		return val;
	}

	public static BigInteger clearBit(BigInteger value, BigInteger position) {
		BigInteger val = (BigInteger.ONE).shiftLeft(position.intValue());
		val = val.not();
		val = val.or(value);
		return val;
	}

	private static BigInteger appxRoot(BigInteger n) {
		BigInteger half = n.shiftRight(1);
		while (half.multiply(half).compareTo(n) > 0) {
			half = half.shiftRight(1);
		}
		return half.shiftLeft(1);
	}

	public static boolean isPrime(BigInteger n) {

		if (!n.isProbablePrime(10)) {
			return false;
		}

		if (n.compareTo(BigInteger.ONE) == 0 || n.compareTo(BigInteger.valueOf(2)) == 0) {
			return true;
		}
		BigInteger root = appxRoot(n);

		int cnt = 0;
		for (BigInteger i = BigInteger.valueOf(3); i.compareTo(root) <= 0; i = i
				.nextProbablePrime()) {
			cnt++;
			if (n.mod(i).equals(BigInteger.ZERO)) {
				return false;
			}
		}
		return true;
	}

	public static BigInteger nextPrime(BigInteger n) {
		n.add(BigInteger.ONE);
		if(n.mod(BigInteger.valueOf(2)).equals(BigInteger.ZERO))
			n.add(BigInteger.ONE);
		while(!isPrime(n)) {
			n.add(BigInteger.valueOf(2));
		}
		return n;
	}

	public static BigInteger randomPrime() {
		Random rand = new Random();
		long num = 2;
		do {
			num = rand.nextInt(1000) + 1;
		} while(!isPrime(BigInteger.valueOf(num)));
		return BigInteger.valueOf(num);
	}

	public static BigInteger random() {
		Random rand = new Random();
		return BigInteger.valueOf(rand.nextInt(1000) + 1);
	}

	public static BigInteger inv(double val) {
		return (BigDecimal.valueOf(1/val)).toBigInteger();
	}

	public static BigInteger power(BigInteger base, BigInteger exp) {
		if(!mod.equals(BigInteger.ZERO)) {
			return base.modPow(exp, mod);
		} else {
			return base.pow(exp.intValue());
		}
	}

	public static BigInteger gcd(BigInteger a, BigInteger b) {
		BigInteger gcd = a.gcd(b);
		if(mod.equals(BigInteger.ZERO))
			return gcd;
		else
			return gcd.mod(mod);
	}

	public static String convertBase(String no, int fromBase, int toBase) {
		return (new BigInteger(no, fromBase)).toString(toBase);
	}

	public static double ln(BigInteger val) {
		int blex = val.bitLength() - 1022;
		if (blex > 0)
			val = val.shiftRight(blex);
		double res = Math.log(val.doubleValue());
		return blex > 0 ? res + blex * Math.log(2.0) : res;
	}

	public static double log2(BigInteger val) {
		return ln(val) / Math.log(2.0);
	}

	public static double log10(BigInteger val) {
		return ln(val) / Math.log(10.0);
	}
}

class MyAdvCalc extends JFrame {
	private int base;
	private BigInteger memory;
	Object focus, operation;

	private JScrollPane xDisplay, yDisplay, infoDisplay;
	private JTextArea xDisplayText, yDisplayText, infoDisplayText;
	private GridLayout buttonGrid;
	private JPanel verticalLayout, buttonLayout;
	private JButton about, store, recall, clear, ac, fact, xCy, x_y, setmod,
		setbase, log2, ln, log10, getmod, p_m, and, or, not, xor,
		setbit, clearbit, nextp, randp, random, d, e, f, a, b, c, seven,
		eight, nine, four, five, six, one, two, three, zero,
		openbrac, closebrac, exp, mult, inv, div, mod, add, sub, gcd,
		del, equal;

	public MyAdvCalc(String name) {
		super(name);

		base = 10;
		memory = BigInteger.ZERO;
		operation = null;

		xDisplayText = new JTextArea("x = 0");
		xDisplayText.setEditable(false);
		yDisplayText = new JTextArea("y = 0");
		yDisplayText.setEditable(false);
		infoDisplayText = new JTextArea("Base = 10\nMod = 0\nOperation = null\nStore = null\n\nX:\nBits = 0\nPrime = No\n\nY:\nBits = 0\nPrime = No");
		infoDisplayText.setEditable(false);

		xDisplay = new JScrollPane(xDisplayText);
		xDisplay.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
		xDisplay.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
		yDisplay = new JScrollPane(yDisplayText);
		yDisplay.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
		yDisplay.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
		infoDisplay = new JScrollPane(infoDisplayText);
		infoDisplay.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
		infoDisplay.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);

		buttonGrid = new GridLayout(11, 5);
		
		buttonLayout = new JPanel();
		buttonLayout.setLayout(buttonGrid);
		verticalLayout = new JPanel();
		verticalLayout.setLayout(new BoxLayout(verticalLayout, BoxLayout.PAGE_AXIS));
		
		about = new JButton("About");
		store = new JButton("Store");
		recall = new JButton("Recall");
		clear = new JButton("Clear");
		ac = new JButton("AC");
		fact = new JButton("!");
		xCy = new JButton("xCy");
		x_y = new JButton("x<->y");
		setmod = new JButton("SetMod");
		log2 = new JButton("log2");
		ln = new JButton("ln");
		log10 = new JButton("log10");
		getmod = new JButton("GetMod");
		p_m = new JButton("+/-");
		and = new JButton("and");
		or = new JButton("or");
		not = new JButton("not");
		xor = new JButton("xor");
		clearbit = new JButton("ClearBit");
		nextp = new JButton("Next p");
		randp = new JButton("Rand p");
		random = new JButton("Random");
		d = new JButton("D");
		e = new JButton("E");
		f = new JButton("F");
		a = new JButton("A");
		b = new JButton("B");
		c = new JButton("C");
		seven = new JButton("7");
		nine = new JButton("9");
		four = new JButton("4");
		five = new JButton("5");
		six = new JButton("6");
		one = new JButton("1");
		two = new JButton("2");
		three = new JButton("3");
		zero = new JButton("0");
		closebrac = new JButton(")");
		exp = new JButton("x**y");
		mult = new JButton("*");
		inv = new JButton("1/x");
		div = new JButton("/");
		mod = new JButton("mod");
		add = new JButton("+");
		sub = new JButton("-");
		gcd = new JButton("gcd");
		equal = new JButton("=");
		setbase = new JButton("SetBase");
		setbit = new JButton("SetBit");
		eight = new JButton("8");
		openbrac = new JButton("(");
		del = new JButton("del");

		about.addActionListener(new MyActionHandler());
		store.addActionListener(new MyActionHandler());
		recall.addActionListener(new MyActionHandler());
		clear.addActionListener(new MyActionHandler());
		ac.addActionListener(new MyActionHandler());
		fact.addActionListener(new MyActionHandler());
		xCy.addActionListener(new MyActionHandler());
		x_y.addActionListener(new MyActionHandler());
		setmod.addActionListener(new MyActionHandler());
		log2.addActionListener(new MyActionHandler());
		ln.addActionListener(new MyActionHandler());
		log10.addActionListener(new MyActionHandler());
		getmod.addActionListener(new MyActionHandler());
		p_m.addActionListener(new MyActionHandler());
		and.addActionListener(new MyActionHandler());
		or.addActionListener(new MyActionHandler());
		not.addActionListener(new MyActionHandler());
		xor.addActionListener(new MyActionHandler());
		clearbit.addActionListener(new MyActionHandler());
		nextp.addActionListener(new MyActionHandler());
		randp.addActionListener(new MyActionHandler());
		random.addActionListener(new MyActionHandler());
		d.addActionListener(new MyActionHandler());
		e.addActionListener(new MyActionHandler());
		f.addActionListener(new MyActionHandler());
		a.addActionListener(new MyActionHandler());
		b.addActionListener(new MyActionHandler());
		c.addActionListener(new MyActionHandler());
		seven.addActionListener(new MyActionHandler());
		nine.addActionListener(new MyActionHandler());
		four.addActionListener(new MyActionHandler());
		five.addActionListener(new MyActionHandler());
		six.addActionListener(new MyActionHandler());
		one.addActionListener(new MyActionHandler());
		two.addActionListener(new MyActionHandler());
		three.addActionListener(new MyActionHandler());
		zero.addActionListener(new MyActionHandler());
		closebrac.addActionListener(new MyActionHandler());
		exp.addActionListener(new MyActionHandler());
		mult.addActionListener(new MyActionHandler());
		inv.addActionListener(new MyActionHandler());
		div.addActionListener(new MyActionHandler());
		mod.addActionListener(new MyActionHandler());
		add.addActionListener(new MyActionHandler());
		sub.addActionListener(new MyActionHandler());
		gcd.addActionListener(new MyActionHandler());
		equal.addActionListener(new MyActionHandler());
		setbase.addActionListener(new MyActionHandler());
		setbit.addActionListener(new MyActionHandler());
		eight.addActionListener(new MyActionHandler());
		openbrac.addActionListener(new MyActionHandler());
		del.addActionListener(new MyActionHandler());

		buttonLayout.add(about);
		buttonLayout.add(store);
		buttonLayout.add(recall);
		buttonLayout.add(clear);
		buttonLayout.add(ac);
		buttonLayout.add(fact);
		buttonLayout.add(xCy);
		buttonLayout.add(x_y);
		buttonLayout.add(setmod);
		buttonLayout.add(setbase);
		buttonLayout.add(log2);
		buttonLayout.add(ln);
		buttonLayout.add(log10);
		buttonLayout.add(getmod);
		buttonLayout.add(new JButton());
		buttonLayout.add(p_m);
		buttonLayout.add(and);
		buttonLayout.add(or);
		buttonLayout.add(xor);
		buttonLayout.add(not);
		buttonLayout.add(setbit);
		buttonLayout.add(clearbit);
		buttonLayout.add(nextp);
		buttonLayout.add(randp);
		buttonLayout.add(random);
		buttonLayout.add(d);
		buttonLayout.add(e);
		buttonLayout.add(f);
		buttonLayout.add(openbrac);
		buttonLayout.add(closebrac);
		buttonLayout.add(a);
		buttonLayout.add(b);
		buttonLayout.add(c);
		buttonLayout.add(exp);
		buttonLayout.add(mult);
		buttonLayout.add(seven);
		buttonLayout.add(eight);
		buttonLayout.add(nine);
		buttonLayout.add(inv);
		buttonLayout.add(div);
		buttonLayout.add(four);
		buttonLayout.add(five);
		buttonLayout.add(six);
		buttonLayout.add(mod);
		buttonLayout.add(add);
		buttonLayout.add(one);
		buttonLayout.add(two);
		buttonLayout.add(three);
		buttonLayout.add(gcd);
		buttonLayout.add(sub);
		buttonLayout.add(new JButton());
		buttonLayout.add(zero);
		buttonLayout.add(new JButton());
		buttonLayout.add(del);
		buttonLayout.add(equal);

		verticalLayout.add(xDisplay);
		verticalLayout.add(yDisplay);
		verticalLayout.add(infoDisplay);
		verticalLayout.add(buttonLayout);

		super.add(verticalLayout);

		focus = xDisplayText;
	}

	public MyAdvCalc getObject() {
		return this;
	}

	private BigInteger getXData() {
		String data = xDisplayText.getText();
		return new BigInteger(data.substring(data.indexOf(" = ") + " = ".length()), base);
	}

	private BigInteger getYData() {
		String data = yDisplayText.getText();
		return new BigInteger(data.substring(data.indexOf(" = ") + " = ".length()), base);
	}

	private void setXData(BigInteger b) {
		String data = b.toString();
		xDisplayText.setText("x = " + data);
		updateXParams();
	}

	private void setYData(BigInteger b) {
		String data = b.toString();
		yDisplayText.setText("y = " + data);
		updateYParams();
	}

	private void setData(BigInteger b) {
		if(focus == xDisplayText)
			setXData(b);
		else if(focus == yDisplayText)
			setYData(b);
	}

	private void appendToX(String s) {
		String data = xDisplayText.getText();
		if(data.indexOf(" = 0") != -1) {
			data = data.substring(0, data.indexOf("0"));
		}
		xDisplayText.setText(data + s);
		updateXParams();
	}

	private void appendToY(String s) {
		String data = yDisplayText.getText();
		if(data.indexOf(" = 0") != -1) {
			data = data.substring(0, data.indexOf("0"));
		}
		yDisplayText.setText(data + s);
		updateYParams();
	}

	private void append(String s) {
		if(focus == xDisplayText)
			appendToX(s);
		else if(focus == yDisplayText)
			appendToY(s);
	}

	private void setOperation(String s) {
		String text = infoDisplayText.getText();
		String header = text.substring(0, text.indexOf("Operation") + "Operation = ".length());
		String footer = text.substring(text.indexOf("\nStore"));
		infoDisplayText.setText(header + s + footer);
	}

	private void updateXBits() {
		String s = String.valueOf(getXData().bitLength());
		String text = infoDisplayText.getText();
		String header = text.substring(0, text.indexOf("X:\nBits") + "X:\nBits = ".length());
		String footer = text.substring(text.indexOf("\nPrime"));
		infoDisplayText.setText(header + s + footer);
	}

	private void updateYBits() {
		String s = String.valueOf(getYData().bitLength());
		String text = infoDisplayText.getText();
		String header = text.substring(0, text.indexOf("Y:\nBits") + "Y:\nBits = ".length());
		String footer = text.substring(text.lastIndexOf("\nPrime"));
		infoDisplayText.setText(header + s + footer);
	}

	private void updateBits() {
		if(focus == xDisplayText)
			updateXBits();
		else if (focus == yDisplayText)
			updateYBits();
	}

	private void updateBothBits() {
		updateXBits();
		updateYBits();
	}

	private void updateBase(int base) {
		String s = String.valueOf(base);
		String text = infoDisplayText.getText();
		String header = text.substring(0, text.indexOf("Base = ") + "Base = ".length());
		String footer = text.substring(text.indexOf("\nMod"));
		infoDisplayText.setText(header + s + footer);
	}

	private void updateMod() {
		String s = Operations.getMod().toString();
		String text = infoDisplayText.getText();
		String header = text.substring(0, text.indexOf("Mod = ") + "Mod = ".length());
		String footer = text.substring(text.indexOf("\nOperation"));
		infoDisplayText.setText(header + s + footer);
	}

	private void setXPrime() {
		String s = "No";
		if(Operations.isPrime(getXData()))
			s = "Yes";
		String text = infoDisplayText.getText();
		String header = text.substring(0, text.indexOf("Prime = ") + "Prime = ".length());
		String footer = text.substring(text.indexOf("\n\nY:\n"));
		infoDisplayText.setText(header + s + footer);
	}

	private void setYPrime() {
		String s = "No";
		if(Operations.isPrime(getYData()))
			s = "Yes";
		String text = infoDisplayText.getText();
		String header = text.substring(0, text.lastIndexOf("Prime = ") + "Prime = ".length());
		infoDisplayText.setText(header + s);
	}

	private void setPrime() {
		if(focus == xDisplayText)
			setXPrime();
		else if(focus == yDisplayText)
			setYPrime();
	}

	private void setBothPrime() {
		setXPrime();
		setYPrime();
	}

	private void updateXParams() {
		setXPrime();
		updateXBits();
	}

	private void updateYParams() {
		setYPrime();
		updateYBits();
	}

	private void updateParams() {
		if(focus == xDisplayText)
			updateXParams();
		else if(focus == yDisplayText)
			updateYParams();
	}
// Base = 10\nMod = 0\nOperation = null\nStore = null\n\nX:\nBits = 0\nPrime = No\n\nY:\nBits = 0\nPrime = No
	private void updateStore() {
		String s = getObject().memory.toString();
		String text = infoDisplayText.getText();
		String header = text.substring(0, text.lastIndexOf("\nStore = ") + "\nStore = ".length());
		String footer = text.substring(text.indexOf("\n\nX:\n"));
		infoDisplayText.setText(header + s + footer);
	}

	private void callEquals() {
		if(operation == null) {
			return;
		}
		if(operation == xCy) {
			setYData(Operations.xCy(getXData(), getYData()));
			operation = null;
			focus = xDisplayText;
			return;
		}
		if(operation == and) {
			setYData(getXData().and(getYData()));
			operation = null;
			focus = xDisplayText;
			return;
		}
		if(operation == or) {
			setYData(getXData().or(getYData()));
			operation = null;
			focus = xDisplayText;
			return;
		}
		if(operation == xor) {
			setYData(getXData().xor(getYData()));
			operation = null;
			focus = xDisplayText;
			return;
		}
		if(operation == about) {
			operation = null;
			return;
		}
		if(operation == store) {
			operation = null;
			return;
		}
		if(operation == recall) {
			operation = null;
			return;
		}
		if(operation == clear) {
			operation = null;
			return;
		}
		if(operation == ac) {
			operation = null;
			return;
		}
		if(operation == fact) {
			operation = null;
			return;
		}
		if(operation == x_y) {
			operation = null;
			return;
		}
		if(operation == setmod) {
			operation = null;
			return;
		}
		if(operation == log2) {
			operation = null;
			return;
		}
		if(operation == ln) {
			operation = null;
			return;
		}
		if(operation == log10) {
			operation = null;
			return;
		}
		if(operation == getmod) {
			operation = null;
			return;
		}
		if(operation == p_m) {
			operation = null;
			return;
		}
		if(operation == not) {
			operation = null;
			return;
		}
		if(operation == clearbit) {
			setYData(Operations.clearBit(getXData(), getYData()));
			operation = null;
			focus = xDisplayText;
			return;
		}
		if(operation == nextp) {
			operation = null;
			return;
		}
		if(operation == randp) {
			operation = null;
			return;
		}
		if(operation == random) {
			operation = null;
			return;
		}
		if(operation == d) {
			operation = null;
			return;
		}
		if(operation == e) {
			operation = null;
			return;
		}
		if(operation == f) {
			operation = null;
			return;
		}
		if(operation == a) {
			operation = null;
			return;
		}
		if(operation == b) {
			operation = null;
			return;
		}
		if(operation == c) {
			operation = null;
			return;
		}
		if(operation == seven) {
			operation = null;
			return;
		}
		if(operation == nine) {
			operation = null;
			return;
		}
		if(operation == four) {
			operation = null;
			return;
		}
		if(operation == five) {
			operation = null;
			return;
		}
		if(operation == six) {
			operation = null;
			return;
		}
		if(operation == one) {
			operation = null;
			return;
		}
		if(operation == two) {
			operation = null;
			return;
		}
		if(operation == three) {
			operation = null;
			return;
		}
		if(operation == zero) {
			operation = null;
			return;
		}
		if(operation == closebrac) {
			operation = null;
			return;
		}
		if(operation == exp) {
			setYData(Operations.power(getXData(), getYData()));
			operation = null;
			focus = xDisplayText;
			return;
		}
		if(operation == mult) {
			setYData(getXData().multiply(getYData()));
			focus = xDisplayText;
			operation = null;
			return;
		}
		if(operation == inv) {
			operation = null;
			return;
		}
		if(operation == div) {
			setYData(getXData().divide(getYData()));
			focus = xDisplayText;
			operation = null;
			return;
		}
		if(operation == mod) {
			setYData(getXData().mod(getYData()));
			focus = xDisplayText;
			operation = null;
			return;
		}
		if(operation == add) {
			setYData(getXData().add(getYData()));
			focus = xDisplayText;
			operation = null;
			return;
		}
		if(operation == sub) {
			setYData(getXData().subtract(getYData()));
			focus = xDisplayText;
			operation = null;
			return;
		}
		if(operation == gcd) {
			setYData(Operations.gcd(getXData(),getYData()));
			focus = xDisplayText;
			operation = null;
			return;
		}
		if(operation == equal) {
			operation = null;
			return;
		}
		if(operation == setbase) {
			operation = null;
			return;
		}
		if(operation == setbit) {
			operation = null;
			return;
		}
		if(operation == eight) {
			operation = null;
			return;
		}
		if(operation == openbrac) {
			operation = null;
			return;
		}
		if(operation == del) {
			operation = null;
			return;
		}
		setYData(getXData().mod(Operations.getMod()));
	}

	private void deleteY() {
		String text = yDisplayText.getText();
		if(text.length() > (text.indexOf(" = ") + " = ".length()))
			text = text.substring(0, text.length() - 1);
		yDisplayText.setText(text);
	}

	private void deleteX() {
		String text = xDisplayText.getText();
		if(text.length() > (text.indexOf(" = ") + " = ".length()))
			text = text.substring(0, text.length() - 1);
		xDisplayText.setText(text);
	}

	private void delete() {
		if(focus == xDisplayText)
			deleteX();
		else if(focus == yDisplayText)
			deleteY();
	}

	private class MyActionHandler implements ActionListener
	{
		public void actionPerformed(ActionEvent e) {
			if(e.getSource() == about) {
				// if(operation != null) {
				// 	callEquals();
				// }
				JOptionPane.showMessageDialog(getObject(), "Advanced Calculator by Vivek Roy",
					"About", JOptionPane.INFORMATION_MESSAGE);
			}
			if(e.getSource() == store) {
				// if(operation != null) {
				// 	callEquals();
				// }
				getObject().memory = getXData();
				setOperation("Store");
				updateStore();
			}
			if(e.getSource() == recall) {
				// if(operation != null) {
				// 	callEquals();
				// }
				setXData(getObject().memory);
				setOperation("Recall");
			}
			if(e.getSource() == clear) {
				// if(operation != null) {
				// 	callEquals();
				// }
				setOperation("Clear");
				setData(BigInteger.ZERO);
			}
			if(e.getSource() == ac) {
				// if(operation != null) {
				// 	callEquals();
				// }
				setOperation("AC");
				setXData(BigInteger.ZERO);
				setYData(BigInteger.ZERO);
			}
			if(e.getSource() == fact) {
				// if(operation != null) {
				// 	callEquals();
				// }
				setYData(Operations.fact(getXData()));
				operation = fact;
				setOperation("!");
			}
			if(e.getSource() == xCy) {
				// if(operation != null) {
				// 	callEquals();
				// }
				operation = xCy;
				focus = yDisplayText;
				setOperation("xCy");
			}
			if(e.getSource() == x_y) {
				// if(operation != null) {
				// 	callEquals();
				// }
				BigInteger b1 = getXData();
				setXData(getYData());
				setYData(b1);
				setOperation("x<->y");
			}
			if(e.getSource() == setmod) {
				// if(operation != null) {
				// 	callEquals();
				// }
				BigInteger b1 = getXData();
				Operations.setMod(b1);
				updateMod();
				operation = setmod;
				setOperation("SetMod");
			}
			if(e.getSource() == log2) {
				// if(operation != null) {
				// 	callEquals();
				// }
				operation = log2;
				setOperation("log2");
				BigInteger b1 = getXData();
				yDisplayText.setText("y = " + Operations.log2(b1));
			}
			if(e.getSource() == ln) {
				// if(operation != null) {
				// 	callEquals();
				// }
				operation = ln;
				setOperation("ln");
				BigInteger b1 = getXData();
				yDisplayText.setText("y = " + Operations.ln(b1));
			}
			if(e.getSource() == log10) {
				// if(operation != null) {
				// 	callEquals();
				// }
				operation = log10;
				setOperation("log10");
				BigInteger b1 = getXData();
				yDisplayText.setText("y = " + Operations.log10(b1));
			}
			if(e.getSource() == getmod) {
				// if(operation != null) {
				// 	callEquals();
				// }
				setXData(Operations.getMod());
				setOperation("GetMod");
			}
			if(e.getSource() == p_m) {
				// if(operation != null) {
				// 	callEquals();
				// }
				setOperation("+/-");
				setXData(getXData().multiply(BigInteger.valueOf(-1)));
			}
			if(e.getSource() == and) {
				// if(operation != null) {
				// 	callEquals();
				// }
				operation = and;
				setOperation("and");
				focus = yDisplayText;
			}
			if(e.getSource() == or) {
				// if(operation != null) {
				// 	callEquals();
				// }
				operation = or;
				setOperation("or");
				focus = yDisplayText;
			}
			if(e.getSource() == not) {
				// if(operation != null) {
				// 	callEquals();
				// }
				operation = not;
				setOperation("not");
				setYData(getXData().not());
			}
			if(e.getSource() == xor) {
				// if(operation != null) {
				// 	callEquals();
				// }
				operation = xor;
				setOperation("xor");
				focus = yDisplayText;
			}
			if(e.getSource() == clearbit) {
				// if(operation != null) {
				// 	callEquals();
				// }
				operation = clearbit;
				setOperation("ClearBit");
				focus = yDisplayText;
			}
			if(e.getSource() == nextp) {
				// if(operation != null) {
				// 	callEquals();
				// }
				operation = nextp;
				setOperation("Next p");
				setYData(Operations.nextPrime(getXData()));
			}
			if(e.getSource() == randp) {
				// if(operation != null) {
				// 	callEquals();
				// }
				operation = randp;
				setOperation("Rand p");
				setYData(Operations.randomPrime());
			}
			if(e.getSource() == random) {
				// if(operation != null) {
				// 	callEquals();
				// }
				operation = random;
				setOperation("Random");
				setYData(Operations.random());
			}
			if(e.getSource() == d) {
				// if(operation != null) {
				// 	callEquals();
				// }
				setOperation("D");
				append("D");
				updateParams();
			}
			if(e.getSource() == e) {
				// if(operation != null) {
				// 	callEquals();
				// }
				setOperation("E");
				append("E");
				updateParams();
			}
			if(e.getSource() == f) {
				// if(operation != null) {
				// 	callEquals();
				// }
				setOperation("F");
				append("F");
				updateParams();
			}
			if(e.getSource() == a) {
				// if(operation != null) {
				// 	callEquals();
				// }
				setOperation("A");
				append("A");
				updateParams();
			}
			if(e.getSource() == b) {
				// if(operation != null) {
				// 	callEquals();
				// }
				setOperation("B");
				append("B");
				updateParams();
			}
			if(e.getSource() == c) {
				// if(operation != null) {
				// 	callEquals();
				// }
				setOperation("C");
				append("C");
				updateParams();
			}
			if(e.getSource() == seven) {
				// if(operation != null) {
				// 	callEquals();
				// }
				setOperation("7");
				append("7");
				updateParams();
			}
			if(e.getSource() == nine) {
				// if(operation != null) {
				// 	callEquals();
				// }
				setOperation("9");
				append("9");
				updateParams();
			}
			if(e.getSource() == four) {
				// if(operation != null) {
				// 	callEquals();
				// }
				setOperation("4");
				append("4");
				updateParams();
			}
			if(e.getSource() == five) {
				// if(operation != null) {
				// 	callEquals();
				// }
				setOperation("5");
				append("5");
				updateParams();
			}
			if(e.getSource() == six) {
				// if(operation != null) {
				// 	callEquals();
				// }
				setOperation("6");
				append("6");
				updateParams();
			}
			if(e.getSource() == one) {
				// if(operation != null) {
				// 	callEquals();
				// }
				setOperation("1");
				append("1");
				updateParams();
			}
			if(e.getSource() == two) {
				// if(operation != null) {
				// 	callEquals();
				// }
				setOperation("2");
				append("2");
				updateParams();
			}
			if(e.getSource() == three) {
				// if(operation != null) {
				// 	callEquals();
				// }
				setOperation("3");
				append("3");
				updateParams();
			}
			if(e.getSource() == zero) {
				// if(operation != null) {
				// 	callEquals();
				// }
				setOperation("0");
				append("0");
				updateParams();
			}
			if(e.getSource() == closebrac) {
				// if(operation != null) {
				// 	callEquals();
				// }
				setOperation(")");
				append(")");
				updateParams();
			}
			if(e.getSource() == exp) {
				// if(operation != null) {
				// 	callEquals();
				// }
				operation = exp;
				setOperation("x**y");
				focus = yDisplayText;
			}
			if(e.getSource() == mult) {
				// if(operation != null) {
				// 	callEquals();
				// }
				operation = mult;
				focus = yDisplayText;
				setOperation("*");
			}
			if(e.getSource() == inv) {
				// if(operation != null) {
				// 	callEquals();
				// }
				setYData(Operations.inv(getXData().doubleValue()));
				operation = inv;
				setOperation("1/x");
			}
			if(e.getSource() == div) {
				// if(operation != null) {
				// 	callEquals();
				// }
				operation = div;
				setOperation("/");
				focus = yDisplayText;
			}
			if(e.getSource() == mod) {
				// if(operation != null) {
				// 	callEquals();
				// }
				operation = mod;
				setOperation("mod");
				focus = yDisplayText;
			}
			if(e.getSource() == add) {
				// if(operation != null) {
				// 	callEquals();
				// }
				operation = add;
				setOperation("+");
				focus = yDisplayText;
			}
			if(e.getSource() == sub) {
				// if(operation != null) {
				// 	callEquals();
				// }
				operation = sub;
				setOperation("-");
				focus = yDisplayText;
			}
			if(e.getSource() == gcd) {
				// if(operation != null) {
				// 	callEquals();
				// }
				operation = gcd;
				setOperation("gcd");
				focus = yDisplayText;
			}
			if(e.getSource() == equal) {
				// if(operation != null) {
				// 	callEquals();
				// }
				getObject().callEquals();
			}
			if(e.getSource() == setbase) {
				// if(operation != null) {
				// 	callEquals();
				// }
				operation = setbase;
				setOperation("SetBase");
				updateBase(getXData().intValue());
			}
			if(e.getSource() == setbit) {
				// if(operation != null) {
				// 	callEquals();
				// }
			}
			if(e.getSource() == eight) {
				// if(operation != null) {
				// 	callEquals();
				// }
				operation = eight;
				setOperation("8");
				append("8");
				updateBits();
			}
			if(e.getSource() == openbrac) {
				// if(operation != null) {
				// 	callEquals();
				// }
				operation = openbrac;
				setOperation("(");;
				append("(");
				updateBits();
			}
			if(e.getSource() == del) {
				// if(operation != null) {
				// 	callEquals();
				// }
				setOperation("del");
				delete();
				updateParams();
			}
		}
	}
}

public class AdvCalc
{
	public static void main(String[] args) {
		MyAdvCalc myWindow = new MyAdvCalc("Advanced Calculator");
		myWindow.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		myWindow.setSize(500,700);
		myWindow.setVisible(true);
	}
}