class Lader 
{   
    float above,height; //ʵ��������
    static float bottom; //�������
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
       Lader.bottom=60; //Lader���ֽ��뱻���ص��ڴ棬ͨ�����������������
       System.out.println("��������Lader�����bottom����"+Lader.bottom);

       Lader laderOne,laderTwo;    
       laderOne=new Lader();  
       laderTwo=new Lader();

       System.out.println("laderOne��bottom:"+laderOne.getBottom());
       System.out.println("laderTwo��bottom:"+laderTwo.getBottom());

       laderOne.setAbove(11);
       laderTwo.setAbove(22);
       laderTwo.setBottom(100);
       System.out.println("��������Lader�����bottom����"+Lader.bottom);
       System.out.println("laderOne��above:"+laderOne.getAbove());
       System.out.println("laderTwo��above:"+laderTwo.getAbove());
    } 
}
