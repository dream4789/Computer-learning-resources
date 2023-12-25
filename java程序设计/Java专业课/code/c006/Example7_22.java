package ch7;
import java.util.* ;  
class Handset extends Observable{ // ��ʾ�ͻ����Թ۲��ֻ��۸�ı�  
    private float price ;// ��Ǯ  
    private boolean state;// �ֻ��Ƿ��л���״̬
    public Handset(float price,boolean state){  
        this.price = price ;  
        this.state = state;
    }  
    public float getPrice(){  
        return this.price ;  
    }  
    
    public void setPrice(float price){  
         
        super.setChanged() ;           // ���ü۸�Ϊ�ı����item to be changed  
        super.notifyObservers(price) ; // ÿһ���޸Ķ�����Ӧ֪ͨ�۲���  
        this.price = price ;           // �۸񱻸ı�
    }  
    public boolean getState(){
    	return state;
    }
    public void setState(boolean state){
    	super.setChanged();              // �����Ƿ��л�״̬Ϊ�ı����item to be changed
    	super.notifyObservers(state);    // ÿһ���޸Ķ�����Ӧ֪ͨ�۲��� 
    	this.state = state;              // ״̬���ı�
    	
    }
    public String toString(){  
        return "�ֻ��ۼ�  " + this.price+"��ǰ"+(state?"�л�":"�޻�" );  
    }  
}  
class HandsetPriceObserver implements Observer{  
    private String name ;  
    public HandsetPriceObserver(String name){ // ����ÿһ���й�������ͻ�����  
        this.name = name ;  
    }  
    public void update(Observable o,Object arg){  
        if(arg instanceof Float){  
            System.out.print(this.name + "�۲쵽�ֻ��۸����Ϊ��") ;  
            System.out.println(((Float)arg).floatValue()) ; 
        }
        if(arg instanceof Boolean){  
                System.out.print(this.name + "�۲쵽�ֻ��л�״̬����Ϊ��") ;  
                System.out.println(((Boolean)arg).booleanValue()) ; 
            
           }  
    } 
} 
public class Example7_22{  
    public static void main(String[] args){  
    	Handset server = new Handset(6000,false) ;  
    	HandsetPriceObserver client1 = new HandsetPriceObserver("�ͻ�1") ;  
    	HandsetPriceObserver client2 = new HandsetPriceObserver("�ͻ�2") ;  
    	HandsetPriceObserver client3 = new HandsetPriceObserver("�ͻ�3") ;  
        server.addObserver(client1) ;  
        server.addObserver(client2) ;  
        server.addObserver(client3) ;  
        System.out.println(server) ; // ���ԭʼ�ֻ��ۼ�  
        server.setPrice(5000) ;    // �޸��ֻ��ۼ� 
        server.setState(true);      //�޸��ֻ����״̬Ϊ�л�
        System.out.println(server) ; // ����޸ĺ��ֻ��ۼ�  
    }  
};    //���벻�ӷֺŶ����� 
