package net.zero;

public class PassengerCar extends Car{

    public PassengerCar(String str, Car.Color color,
               int yearOfProduction, int price,
               int weight) {
        super(str, color, yearOfProduction, price, weight);
    }

    @Override
    public boolean isNeedToService() {
        if(lastServiceDistance > 10000) {
            return true;
        }
        return false;
    }
}
