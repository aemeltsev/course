public class TypeConv {
    public static char charExpression(int a) {
        char result = (char) ('\\' + a);
        return result;
    }

    public static void main(String[] argv){
        char out = charExpression(29);
        System.out.println(out);
    }
}
