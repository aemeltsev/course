package net.zero;

public class Test {
    public static void main(String... args) {
        Car toyota = new PassengerCar("Toyota Prius", Car.Color.GREEN, 2008, 15000, 1200);
        Car renault0 = new Bus("Renault Laguna", Car.Color.WHITE, 2000, 9700, 1600);
        Car renault1 = new PassengerCar("Renault Laguna", Car.Color.WHITE, 2000, 9700, 1600);

        toyota.addDistance(1000);
        toyota.addDistance(2000);
        toyota.addDistance(20.9f);

        System.out.println(toyota);
        System.out.println(renault0);

        System.out.println(toyota.equals(toyota));
        System.out.println(toyota.equals(renault0));
        System.out.println(renault0.equals(renault1));
    }
}
