public class Arith {
    private static native void raise_sigfpe();

    public static int TestMain( int c ) {
        int r = 0;
        try {
            r += 1;
            if( c > 0 )
                raise_sigfpe();
            else if ( c == 0 ) {
                r += 103;
                throw new ArithmeticException();
            }
            r += 3;
        } catch( ArithmeticException e ) {
            r += 100;
        }
        return r;
    }

    public static void main(String[] args) {
        System.out.println(TestMain(-5));
        System.out.println(TestMain(0));
    }
}
