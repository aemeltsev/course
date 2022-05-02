public class DTest {
    static final double err = 0.0001;
    public static boolean doubleExpression(double a, double b, double c){
        boolean result = false;
        if(Math.abs(c - (a + b)) < err){
            result = true;
        }
        return result;
    }

    public static void main(String[] args){
        boolean out = doubleExpression(0.1, 0.2, 0.3);
        System.out.print(out);
    }
}
