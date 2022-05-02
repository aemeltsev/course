public class Palindrome {
    public static boolean isPalindrome(String str){
        String input = str.replaceAll("[^a-zA-Z0-9]", "").toLowerCase();
        char[] ch = input.toCharArray();
        String rev = "";

        for(int i = ch.length-1; i >= 0; --i){
            rev += ch[i];
        }
        return input.equals(rev);
    }

    public static void main(String[] args){
        String in = "Madam, I'm Adam!";
        boolean out = isPalindrome(in);
        System.out.print(out);
    }
}
