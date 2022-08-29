public class Main {

    public static void main(String[] args) {

        System.out.println("Hello!");

        RemoteRobot.MyRobotConnectionManager robotConnectionManager = new RemoteRobot().new MyRobotConnectionManager();
        RemoteRobot.moveRobot(robotConnectionManager, 10, 10);
    }



}
