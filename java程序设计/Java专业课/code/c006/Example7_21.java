package ch7;
import java.lang.reflect.Field;
 public class Example7_21{
     public static void main(String[] args) throws SecurityException, NoSuchMethodException, NoSuchFieldException, IllegalArgumentException, Exception {
         Person p1 = new Person("danard","trump");
         changeInitialLetter(p1);
         System.out.println(p1);
         
     }
     
     private static void changeInitialLetter(Object obj) throws RuntimeException, Exception {
         Field[] fields = obj.getClass().getFields();
         for(Field field : fields) {
               if(field.getType()==String.class) {
                 String oldValue = (String)field.get(obj);
                 char initialLetter = oldValue.charAt(0);
                 if(initialLetter<='z'&initialLetter>='a') initialLetter-=32;
                 String newValue = initialLetter+oldValue.substring(1);
                 field.set(obj,newValue);
             }
         }
     }
 }
 
 class Person {
     public String firstName ;
     public String lastName ;
         
     public Person(String str1,String str2) { 
         super();
         firstName = str1;
         lastName = str2;
      }
 
     @Override
     public String toString() {
         return "Person [FirstName =" + firstName + ", LastName = " + lastName+"]";
     }
 }
