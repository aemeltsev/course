public class TankMove {
    public static void main(String[] args){
        final int xDest = -10;
        final int yDest = 20;
        Tank tank = new Tank(0,0, Direction.UP);
        tank.addAmmo(20, 10, 5);
        moveTank(tank, xDest, yDest);
        assert tank.getX() == xDest && tank.getY() == yDest;
        tank.getFire(Ammunition.APFSDS);
    }

    public enum Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    }

    public enum Ammunition {
        APFSDS,
        HEAT,
        HE
    }

    public static class Ammo {
        int apfsds = 0;
        int heat = 0;
        int he = 0;

        public void setAmmo(int apfsds, int heat, int he) {
            this.apfsds = apfsds;
            this.heat = heat;
            this.he = he;
        }

        public void toFire(Ammunition amm) {
            if     (amm == Ammunition.APFSDS) {--apfsds;}
            else if(amm == Ammunition.HEAT)   {--heat;}
            else if(amm == Ammunition.HE)     {--he;}
        }

        public void topUp(int num, Ammunition amm) {
            if     (amm == Ammunition.APFSDS) {apfsds += num;}
            else if(amm == Ammunition.HEAT)   {heat += num;}
            else if(amm == Ammunition.HE)     {he += num;}
        }
    }

    public static class Tank {
        int x;
        int y;
        Direction dir;
        private Ammo ammo = new Ammo();

        public Tank(int x, int y, Direction dir) {
            this.x = x;
            this.y = y;
            this.dir = dir;
        }

        public void addAmmo(int a, int b, int c) {
            ammo.setAmmo(a, b, c);
        }

        public Direction getDirection() {return dir;}
        public int getX() {return x;}
        public int getY() {return y;}

        public void turnLeft() {
            if     (dir == Direction.UP)    {dir = Direction.LEFT;}
            else if(dir == Direction.DOWN)  {dir = Direction.RIGHT;}
            else if(dir == Direction.LEFT)  {dir = Direction.DOWN;}
            else if(dir == Direction.RIGHT) {dir = Direction.UP;}
        }

        public void turnRight() {
            if     (dir == Direction.UP)    {dir = Direction.RIGHT;}
            else if(dir == Direction.DOWN)  {dir = Direction.LEFT;}
            else if(dir == Direction.LEFT)  {dir = Direction.UP;}
            else if(dir == Direction.RIGHT) {dir = Direction.DOWN;}
        }

        public void stepForward() {
            if(dir == Direction.UP)    {y++;}
            if(dir == Direction.DOWN)  {y--;}
            if(dir == Direction.LEFT)  {x--;}
            if(dir == Direction.RIGHT) {x++;}
        }

        public void getFire(Ammunition type) {
            ammo.toFire(type);
        }

        public void getAmmo(int value, Ammunition type) {
            ammo.topUp(value, type);
        }
    }

    public static void moveTank(Tank tank, int toX, int toY) {
        while(tank.getDirection() != ((toX > 0) ? Direction.RIGHT : Direction.LEFT)) {
            tank.turnRight();
        }

        while(tank.getX() != toX) {
            tank.stepForward();
        }

        while(tank.getDirection() != ((toY > 0) ? Direction.UP : Direction.DOWN)) {
            tank.turnRight();
        }

        while(tank.getY() != toY) {
            tank.stepForward();
        }
    }
}
