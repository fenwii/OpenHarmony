public class ThreadTest {
    static volatile long flag = 0L;
    static int number = 0;
    static class FirstThread extends Thread {
        public void run() {
            while(flag != Long.MAX_VALUE) {
            }
            System.out.println(number);
        }
    }
    static class SecondThread extends Thread {
        public void run() {
            number = 42;
            flag = Long.MAX_VALUE;
        }
    }

    public static void main(String args[]) {
        FirstThread t1 = new FirstThread();
        SecondThread t2 = new SecondThread();
        t1.start();
        t2.start();
        try {
            t1.join();
            t2.join();
        } catch (InterruptedException e) {
            System.out.println("INTERRUPTED_MESSAGE");
        }
        System.out.println("OK");
    }
}
