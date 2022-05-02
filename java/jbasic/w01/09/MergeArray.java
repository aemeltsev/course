public class MergeArray {
    public static int[] mergeArrays(int[] a1, int[] a2) {
        int[] result = new int[a1.length + a2.length];
        int i = 0, j = 0, k = 0;

        while (i < a1.length & j < a2.length)
            result[k++] = a1[i] < a2[j] ? a1[i++] : a2[j++];

        while (i < a1.length)
            result[k++] = a1[i++];

        while (j < a2.length)
            result[k++] = a2[j++];
        return result;
    }

    public static void main(String[] args){
        int[] arr_1 = {0, 2, 2};
        int[] arr_2 = {1, 3};
        int[] arr = mergeArrays(arr_1, arr_2);

        for (int i : arr){
            System.out.println(i);
        }
    }
}
