class Test_A {
    Test_B bb;
    void genCycle() {
        Test_B b = new Test_B();
        bb = b;
        b.aa = this;
    }
}

class Test_B {
    Test_A aa;
}

public class RCCycleTest {
    public static void main (String []args) {
        Test_A a = new Test_A();
        a.genCycle();
        if (a.bb == null) {
	        System.out.println("class B is collected");
        } else {
	        System.out.println("class B is not collected");
        }
    }
}
