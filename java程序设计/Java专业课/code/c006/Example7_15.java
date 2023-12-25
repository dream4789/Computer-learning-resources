package ch7；
public class Example7_15 {  
    public static void main(String[] args) {  
        // 定义数组  
        int[] arr = { 11, 22, 33, 44, 55 };  
        int[] arr2 = { 6, 7, 8, 9, 10 };  
         System.arraycopy(arr, 1, arr2, 2, 2);         //参数比较多，注意其含义
         System.out.println(Arrays.toString(arr));    // [11, 22, 33, 44, 55]  
         System.out.println(Arrays.toString(arr2));   //[6, 7, 22, 33, 10]  
    }  
}  
