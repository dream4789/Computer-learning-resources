class RECT  
{  
    double sideA=0.0,sideB=0.0;
    RECT()                  //�޲������췽����
    {
    	
    }
    RECT(double a,double b)  //�в������췽����
    {
       sideA=a;
       sideB=b;
    }
    double computerArea()
    {
      return sideA*sideB;
    }
    double computerGirth()
    {
       return (sideA+sideB)*2;
    }
    public static void main(String[] args){
    	RECT r=new RECT();
    	System.out.println(r.computerArea());
    }
}
