interface Inter {
    public default void foo() {
        System.out.println("Inter.foo()");
    }
}

class Base implements Inter {
    public void foo() {
        System.out.println("Base.foo()");
    }
}

class Derived extends Base {
    public void foo() {
        System.out.println("Derived.foo()");
    }
}

public class InterfaceTest {
    public static void main(String[] args) {
        Derived o1 = new Derived();
        o1.foo();
        Base o2 = new Derived();
        o2.foo();
        Inter o3 = new Derived();
        o3.foo();
    }
}
