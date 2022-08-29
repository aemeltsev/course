public class FBit {
    public static int flipBit(int value, int bitIndex) {
        int result;
        result = value ^ (1 << (bitIndex - 1));
        return result;
    }

    public static void main(String[] args){
        int out = flipBit(13, 2);
        System.out.println(out);
    }
}
