public class RemoteRobot {

    public interface RobotConnection extends AutoCloseable {
        void moveRobotTo(int x, int y);
        @Override
        void close();
    }

    public interface RobotConnectionManager {
        RobotConnection getConnection();
    }

    public class RobotConnectionException extends RuntimeException {
        public RobotConnectionException(String message) {
            super(message);
        }
        public RobotConnectionException(String message, Throwable cause) {
            super(message, cause);
        }
    }

    public class MyRobotConnection implements RobotConnection{

        @Override
        public void moveRobotTo(int x, int y) {
            System.out.println("connection got command to move");
            if (1 == 1) {
                throw new RobotConnectionException("connection thrown exception");
            }
            System.out.println("moved successfully");
        }

        @Override
        public void close() {
            System.out.println("connection got command to close");
        }
    }


    public class MyRobotConnectionManager implements RobotConnectionManager {
        @Override
        public RemoteRobot.RobotConnection getConnection() {
            System.out.println("creating new connection");

            if (1 == 2) {
                throw new RobotConnectionException("connection manager thrown exception");
            }
            return new MyRobotConnection();
        }
    }

    public static void moveRobot(RobotConnectionManager robotConnectionManager, int toX, int toY) {
        final int RETRY_NUM = 3;
        boolean conectionEstablished = false;
        RobotConnection rc = robotConnectionManager.getConnection();
        for(int i=0; i<RETRY_NUM && !conectionEstablished; ++i){
            try(rc){
                rc.moveRobotTo(toX, toY);
                conectionEstablished = true;
            }
            catch (RobotConnectionException re){
                if (i == RETRY_NUM-1)
                    throw re;
            }
        }
    }

}
