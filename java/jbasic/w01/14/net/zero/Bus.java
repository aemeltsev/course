package net.zero;

public class Bus extends Car{
    public Bus(String str, Car.Color color,
               int yearOfProduction, int price,
               int weight) {
        super(str, color, yearOfProduction, price, weight);
    }

    @Override
    public boolean isNeedToService() {
        if(lastServiceDistance > 50000) {
            return true;
        }
        return false;
    }
}
