public class Example6_05
{
	int [] arrays;//声明一个数组
	public static void main(String[] args)
	{
		Calculator aCalculator=new Calculator();
		
		try
		{
			System.out.println(aCalculator.div(25, 6));
			System.out.println(aCalculator.div(25,0));
		}
		catch(CalculatorException e)
		{
			System.out.println(e.getMessage());
		}
	}
}

class CalculatorException extends Exception//自定义异常类
{
	private String errorMess;
	
	public CalculatorException(String mess)
	{
		errorMess=mess;
	}
	public String getMessage()
	{
		return errorMess;
	}	
}
class Calculator
{
	public int div(int x,int y)throws CalculatorException
	{
		if(y==0)
			throw new CalculatorException("被0除了！");//异常产生了
		
		return x/y;
	}
}
