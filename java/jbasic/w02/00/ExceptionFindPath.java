public class ExceptionFindPath {

    public static void main(String[] args) {
        System.out.println(getCallerClassAndMethodName());
        anotherMethod();
    }

    private static void anotherMethod()  {
        System.out.println(getCallerClassAndMethodName());
    }

    public static String getCallerClassAndMethodName()  {
        //StackTraceElement[] methods = Thread.currentThread().getStackTrace();
        StackTraceElement[] methods = new Exception().getStackTrace();
        String message = "";
        if(methods.length >= 3) {
            var element = methods[2];
            var className = element.getClassName();
            var methodName = element.getMethodName();
            message = className + "#" + methodName;
        } else {
            return null;
        }
        return message;
    }
}
