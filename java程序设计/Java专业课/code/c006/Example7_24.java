package ch7;
import java.util.Arrays;
import java.util.Comparator;
public class Example7_24  implements Comparator {
    public int compare(Object o1, Object o2) {
        return ((User) o2).getAge() - ((User) o1).getAge();  //按从大到小的序
  }
 public static void main(String[] args) {
    User[] users = new User[] { new User("a", 30), new User("c", 40), new User("b", 20) };
    Arrays.sort(users, new UserComparator());
    for (int i = 0; i < users.length; i++) {
       User user = users[i];
       System.out.println(user.getId() + " " + user.getAge());
    }                                                   
  }
}
