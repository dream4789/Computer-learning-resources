class Lader 
{   
    float above,height; //实例变量。
    static float bottom; //类变量。
    void setAbove(float a)
    {  
       above=a;;
    }
    void setBottom(float b)
    {  
       bottom=b;
    }
    float getAbove()
    {  
       return above;
    }
    float getBottom()
    {  
       return bottom;
    }
}
class Example
{   
    public static void main(String args[]) 
    { 
       Lader.bottom=60; //Lader的字节码被加载到内存，通过类名操作类变量。
       System.out.println("现在所有Lader对象的bottom都是"+Lader.bottom);

       Lader laderOne,laderTwo;    
       laderOne=new Lader();  
       laderTwo=new Lader();

       System.out.println("laderOne的bottom:"+laderOne.getBottom());
       System.out.println("laderTwo的bottom:"+laderTwo.getBottom());

       laderOne.setAbove(11);
       laderTwo.setAbove(22);
       laderTwo.setBottom(100);
       System.out.println("现在所有Lader对象的bottom都是"+Lader.bottom);
       System.out.println("laderOne的above:"+laderOne.getAbove());
       System.out.println("laderTwo的above:"+laderTwo.getAbove());
    } 
}
