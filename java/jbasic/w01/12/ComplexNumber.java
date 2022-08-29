public final class ComplexNumber {
    private final double re;
    private final double im;

    public ComplexNumber(double re, double im) {
        this.re = re;
        this.im = im;
    }

    public double getRe() {
        return re;
    }

    public double getIm() {
        return im;
    }

    @Override
    public boolean equals(Object obj) {
        if(this == obj)
            return true;
        if(obj == null)
            return false;
        if(getClass() != obj.getClass())
            return false;
        ComplexNumber other = (ComplexNumber) obj;
        if(re != other.re)
            return false;
        if(im != other.im)
            return false;
        return true;
    }

    @Override
    public int hashCode() {
        return Double.hashCode(re + im);
    }
}
