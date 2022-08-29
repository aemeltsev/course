/**
 * LOGGER.log(Level.INFO, “I am logging ”)
 *
 * //SEVERE совсем ужас ужас)
 * //WARNING предупреждение
 * //INFO информационное сообщение о нормальном ходе исполнения программы
 * //CONFIC логирование конфигурационных параметров
 * //FINE совсем детальное логгирование
 * //FiINER
 * //FINEST
 *
 * На каждый уровень логгирования есть одноимённый метод :
 * LOGGER.warning("We have a problem ! ");
 *
 * Логгер можно сконфигурировать таким образом чтобы он игнорировал сообщения уровня ниже заданного
 *
 * Пример: Логер настроенные на уровень WARNING будет принимать сообщения уровня WARNING и SEVERE игнорировать всё остальные
 * Настройку можно делать в коде:
 * .setLevekl(Level.WARNING)
 * а можно в конфигурационном файле
 *
 * Логирование с параметрами ( используя символы подстановки в сообщение):
 *
 * LOGGER.log(Level.INFO, “I am logging x = {0}”, x) ;
 * LOGGER.log(Level.INFO, “I am logging x, y ({0}, {1})”, new Object[] {x, y}) ;
 *
 * Если нужно передать в log stacktrase исключение, то
 *
 * LOGGER.log(Level.INFO, “I am logging ошибка”, e) ;
 *
 * Тот факт что логгер использует только константные строки с местами для подстановки позволяет провести локализацию
 */

import com.sun.tools.javac.Main;

import java.io.FileInputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.*;

public class LogDemo {
    private static Logger LOGGER;
    static {
        try(FileInputStream ins = new FileInputStream("C:\\log.config")){
            LogManager.getLogManager().readConfiguration(ins);
            LOGGER = Logger.getLogger(Main.class.getName());
        } catch (Exception ignore){
            ignore.printStackTrace();
        }
    }

    public static void main(String[] args) {
        try {
            LOGGER.log(Level.INFO, "Main, create list with Integer types");
            List<Integer> ints = new ArrayList<Integer>();
            LOGGER.log(Level.INFO,"Assigning of Integers list to the list without type");
            List empty = ints;
            LOGGER.log(Level.INFO,"Assigning of the list without type to the list of the strings");
            List<String> string = empty;
            LOGGER.log(Level.WARNING,"Adding the string \"blah blah\" to our reassigned list, a possible error");
            string.add("blah blah");
            LOGGER.log(Level.WARNING,"Adding the string \"blah 23\" to our reassigned list, a possible error");
            string.add("blah 23");
            LOGGER.log(Level.WARNING,"Adding the string \"blah 34\" to our reassigned list, a possible error");
            string.add("blah 34");

            LOGGER.log(Level.INFO,"Output all the list elements with Integers types to a console");
            for (Object anInt : ints) {
                System.out.println(anInt);
            }

            LOGGER.log(Level.INFO,"Size to " + ints.size());
            LOGGER.log(Level.INFO,"Get first element");
            Integer integer = ints.get(0);
            LOGGER.log(Level.INFO,"Output it to the console");
            System.out.println(integer);
        } catch (Exception e){
            LOGGER.log(Level.WARNING, "Something went wrong", e);
        }
    }
}