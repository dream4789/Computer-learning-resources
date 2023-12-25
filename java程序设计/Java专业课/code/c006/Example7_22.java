package ch7;
import java.util.* ;  
class Handset extends Observable{ // 表示客户可以观察手机价格改变  
    private float price ;// 价钱  
    private boolean state;// 手机是否有货的状态
    public Handset(float price,boolean state){  
        this.price = price ;  
        this.state = state;
    }  
    public float getPrice(){  
        return this.price ;  
    }  
    
    public void setPrice(float price){  
         
        super.setChanged() ;           // 设置价格为改变的项item to be changed  
        super.notifyObservers(price) ; // 每一次修改动作都应通知观察者  
        this.price = price ;           // 价格被改变
    }  
    public boolean getState(){
    	return state;
    }
    public void setState(boolean state){
    	super.setChanged();              // 设置是否有货状态为改变的项item to be changed
    	super.notifyObservers(state);    // 每一次修改动作都应通知观察者 
    	this.state = state;              // 状态被改变
    	
    }
    public String toString(){  
        return "手机售价  " + this.price+"当前"+(state?"有货":"无货" );  
    }  
}  
class HandsetPriceObserver implements Observer{  
    private String name ;  
    public HandsetPriceObserver(String name){ // 设置每一个有购机意向客户名字  
        this.name = name ;  
    }  
    public void update(Observable o,Object arg){  
        if(arg instanceof Float){  
            System.out.print(this.name + "观察到手机价格更改为：") ;  
            System.out.println(((Float)arg).floatValue()) ; 
        }
        if(arg instanceof Boolean){  
                System.out.print(this.name + "观察到手机有货状态更改为：") ;  
                System.out.println(((Boolean)arg).booleanValue()) ; 
            
           }  
    } 
} 
public class Example7_22{  
    public static void main(String[] args){  
    	Handset server = new Handset(6000,false) ;  
    	HandsetPriceObserver client1 = new HandsetPriceObserver("客户1") ;  
    	HandsetPriceObserver client2 = new HandsetPriceObserver("客户2") ;  
    	HandsetPriceObserver client3 = new HandsetPriceObserver("客户3") ;  
        server.addObserver(client1) ;  
        server.addObserver(client2) ;  
        server.addObserver(client3) ;  
        System.out.println(server) ; // 输出原始手机售价  
        server.setPrice(5000) ;    // 修改手机售价 
        server.setState(true);      //修改手机存货状态为有货
        System.out.println(server) ; // 输出修改后手机售价  
    }  
};    //加与不加分号都可以 
