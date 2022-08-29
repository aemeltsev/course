public class PType {
    /**
     * <p> booleanExpression </p>
     * <p>
     * a b c d | f
     * 0 0 0 0 | 0
     * 0 0 0 1 | 0
     * 0 0 1 0 | 0
     * 0 0 1 1 | 1 <- !a!bcd
     * </p>
     * <p>
     * 0 1 0 0 | 0
     * 0 1 0 1 | 1 <- !ab!cd
     * 0 1 1 0 | 1 <- !abc!d
     * 0 1 1 1 | 0
     * </p>
     * <p>
     * 1 0 0 0 | 0
     * 1 0 0 1 | 1 <- a!b!cd
     * 1 0 1 0 | 1 <- a!bc!d
     * 1 0 1 1 | 0
     * </p>
     * <p>
     * 1 1 0 0 | 1 <- ab!c!d
     * 1 1 0 1 | 0
     * 1 1 1 0 | 0
     * 1 1 1 1 | 0
     * </p>
     *
     * @param a input boolean value
     * @param b input boolean value
     * @param c input boolean value
     * @param d input boolean value
     * @return true - if in expression exist two true values
     */
    public static boolean booleanExpression(boolean a, boolean b, boolean c, boolean d) {
        return (!a & !b & c & d) | (!a & b & !c & d) |
                (!a & b & c & !d) | (a & !b & !c & d) |
                (a & !b & c & !d) | (a & b & !c & !d);
    }

    public static void main(String[] args){
        boolean ffff = booleanExpression(false, false, false, false);
        boolean ffft = booleanExpression(false, false, false, true);
        boolean fftf = booleanExpression(false, false, true, false);
        boolean fftt = booleanExpression(false, false, true, true); //Searching for this

        boolean ftff = booleanExpression(false, true, false, false);
        boolean ftft = booleanExpression(false, true, false, true); //Searching for this
        boolean fttf = booleanExpression(false, true, true, false); //Searching for this
        boolean fttt = booleanExpression(false, true, true, true);

        boolean tfff = booleanExpression(true, false, false, false);
        boolean tfft = booleanExpression(true, false, false, true); //Searching for this
        boolean tftf = booleanExpression(true, false, true, false); //Searching for this
        boolean tftt = booleanExpression(true, false, true, true);

        boolean ttff = booleanExpression(true, true, false, false); //Searching for this
        boolean ttft = booleanExpression(true, true, false, true);
        boolean tttf = booleanExpression(true, true, true, false);
        boolean tttt = booleanExpression(true, true, true, true);

        System.out.println("ffff " + ffff);
        System.out.println("ffft " + ffft);
        System.out.println("fftf " + fftf);
        System.out.println("fftt " + fftt + " <- ");

        System.out.println("ftff " + ftff);
        System.out.println("ftft " + ftft + " <- ");
        System.out.println("fttf " + fttf + " <- ");
        System.out.println("fttt " + fttt);

        System.out.println("tfff " + tfff);
        System.out.println("tfft " + tfft + " <- ");
        System.out.println("tftf " + tftf + " <- ");
        System.out.println("tftt " + tftt);

        System.out.println("ttff " + ttff + " <- ");
        System.out.println("ttft " + ttft);
        System.out.println("tttf " + tttf);
        System.out.println("tttt " + tttt);
    }
}
