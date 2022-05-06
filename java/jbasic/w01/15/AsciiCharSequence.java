import java.lang.CharSequence;
import java.util.Arrays;

public class AsciiCharSequence implements CharSequence {
    private byte[] arr;

    public AsciiCharSequence(byte[] arr){
        this.arr = Arrays.copyOf(arr, arr.length);
    }

    @Override
    public int length() {
        return arr.length;
    }

    @Override
    public char charAt(int index) {
        return (char) arr[index];
    }

    @Override
    public AsciiCharSequence subSequence(int start, int end) {
        return new AsciiCharSequence(Arrays.copyOfRange(arr, start, end));
    }

    @Override
    public String toString() {
        return new String(arr);
    }
}
