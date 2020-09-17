import java.util.*;
public class IteratorAndTemplateTest {
    public static void main(String args[]) {
        testIterator();
        testTemplate();
    }

    public static void testIterator(){
        AbstractCollection<String> l = new ArrayList<String>();
        l.add(new String("Hello"));
        l.add(new String(" World"));
        System.out.println(l.size());
        System.out.println(l.toString());
    }

    public static void testTemplate(){
        List<Integer> wholeChain = new ArrayList<Integer>();
        wholeChain.add(1);
        wholeChain.add(2);
        for (Integer i : wholeChain) {
            System.out.println(i);
        }
    }
}

