import java.math.BigInteger;

public class Factorial {
    public static BigInteger Factorial(int value){
        BigInteger result;

        if((value < 0) | (value == 0)){
            return BigInteger.ZERO;
        } else if (value == 1) {
            return BigInteger.ONE;
        }
        else {
            result = BigInteger.valueOf(1);
            for(int i = 1; i <= value; ++i){
                result = result.multiply(BigInteger.valueOf(i));
            }
        }
        return result;
    }

    public static void main(String[] args){
        System.out.println(Factorial(0));
    }
}
