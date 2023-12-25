package ch7;
class Worker{
    public String name;
    public int age;
    public int height;
     
    public Worker(String name, int age,int height){
        this.name = name;
        this.age = age;
        this.height = height;
    }
     
    @Override
    public boolean equals(Object x){
        if(this.getClass() != x.getClass())
            return false;                       //ͬ�����Ƚ�������
        Worker p = (Worker)x;
        return (this.age == p.age);              //�Ƚϵ����䣬�������������   
    }
 }
 
public class Example7_19{
    public static void main(String [] args){
        Worker p1 = new Worker("Diana",23,183);
        Worker p2 = new Worker("Lily",23,176);
        System.out.println(p1.equals(p2));
    }
}
