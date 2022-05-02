public class PowOf2 {
    public static boolean isPowerOfTwo(int value) {
        return (value != 0) && (Math.abs(value) & (Math.abs(value) - 1)) == 0;
    }

    public static void main(String[] args){
        boolean out = isPowerOfTwo(1);
        System.out.print(out);
    }
}
