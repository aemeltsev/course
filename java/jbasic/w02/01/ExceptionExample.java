public class ExceptionExample {

    public static double sqrt(double x){
        if(x<0){
            throw new IllegalArgumentException("The value is the negative!");
        }
        int psq = 0;
        int N = 0;

        for (int i = (int) x; i > 0; --i){
            for (int j = 1; j < i; ++j){
                if (j*j == i)
                {
                    psq = i;
                    N = j;
                    break;
                }
            }
            if (psq > 0) break;;
        }
        double d = x - (double) psq;
        double P = d/(2.0*N);
        double A = N+P;
        double sqrtOfX = A-((P*P)/(2.0*A));
        return sqrtOfX;
    }

    public static void main(String[] args) {

        System.out.println(sqrt(25));
        //System.out.println(sqrt(-25));

    }
}
