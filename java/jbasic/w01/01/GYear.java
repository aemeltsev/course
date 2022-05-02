public class GYear {

    public static int leapYearCount(int year){
        int result = 0;
        for(int i = 1; i<=year; ++i){
            if(((i % 4 == 0)&(i % 100 != 0)) | (i % 400 == 0)){
                ++result;
            }
        }
        return result;
    }

    public static void main(String[] args){
        int a = leapYearCount(1);
        int b = leapYearCount(4);
        int c = leapYearCount(100);

        System.out.println(a);
        System.out.println(b);
        System.out.println(c);
    }
}
