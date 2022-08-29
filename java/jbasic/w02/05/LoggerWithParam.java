import java.util.logging.*;

public class LoggerWithParam {
    private static final Logger LOGGER1 = Logger.getLogger("org.stepic.java.logging.ClassA");
    private static final Logger LOGGER2 = Logger.getLogger("org.stepic.java.logging.ClassB");
    private static final Logger LOGGER3 = Logger.getLogger("org.stepic.java");

    public static void main(String[] args) {

    }

    private static void configureLogging() {
        LOGGER1.setLevel(Level.ALL);
        LOGGER2.setLevel(Level.WARNING);
        Handler conHdlr = new ConsoleHandler();
        conHdlr.setLevel(Level.ALL);
        conHdlr.setFormatter(new XMLFormatter());
        LOGGER3.addHandler(conHdlr);
        LOGGER3.setUseParentHandlers(false);
    }
}
