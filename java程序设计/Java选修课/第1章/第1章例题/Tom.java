public class Tom
{
     int leg; 
     String head;
     void cry(String s)
     { 
         System.out.println(s);
     }
}
class Example
{ 
    public static void main(String args[])
    {
        Tom cat;
        cat=new Tom();
        cat.leg=4;    
        cat.head="èͷ";
        System.out.println("��:"+cat.leg+"��");
        System.out.println("ͷ:"+cat.head);
        cat.cry("�ҽ���Ҫ��Jerryƴ��");
    }
}
