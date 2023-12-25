public class Example6_05
{
	int [] arrays;//����һ������
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

class CalculatorException extends Exception//�Զ����쳣��
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
			throw new CalculatorException("��0���ˣ�");//�쳣������
		
		return x/y;
	}
}
