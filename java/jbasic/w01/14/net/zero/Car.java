package net.zero;

import java.lang.Math;
public abstract class Car implements Serviceable {
    public enum Color {
        WHITE,
        BLACK,
        BLUE,
        GREEN,
        RED,
        UNDEFINED
    }
    private final String car_type;
    private Color color;
    private final int yearOfProduction;
    private final int price;
    private final int weight;

    private int distance = 0;
    protected int lastServiceDistance = 0;

    public Car(String car_type, Color color,
               int yearOfProduction, int price,
               int weight) {
        this.car_type = car_type;
        this.color = color;
        this.yearOfProduction = yearOfProduction;
        this.price = price;
        this.weight = weight;
    }

    public void addDistance(int distance) {
        this.distance += distance;
        this.lastServiceDistance += distance;
    }
    public void addDistance(float distance) {
        addDistance((int)Math.floor(distance));
    }

    public int getDistance() { return distance; }
    public String getCar_type(){
        return car_type;
    }
    public Color getColor() {
        return color;
    }

    @Override
    public String toString() {
        return "Car{" +
                "car_type='" + car_type + '\'' +
                ", color=" + color +
                ", yearOfProduction=" + yearOfProduction +
                ", price=" + price +
                ", weight=" + weight +
                ", distance=" + distance +
                ", lastServiceDistance=" + lastServiceDistance +
                '}';
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;

        result = prime * result + ((car_type == null) ? 0 : car_type.hashCode());
        result = prime * result + ((color == null) ? 0 : color.hashCode());
        result = prime * result + yearOfProduction;
        result = prime * result + price;
        result = prime * result + weight;
        result = prime * result + distance;

        return result;
    }

    @Override
    public boolean equals(Object obj) {
        if(this == obj){ return true; }
        if(obj == null){ return false; }
        if (this.getClass() != obj.getClass()){ return false; }

        Car other = (Car) obj;

        if(color != other.color){ return false;}
        if(car_type == null){
            if(other.car_type == null){
                return false;
            }
        } else if(!this.car_type.equals(other.car_type)) {
            return false;
        }
        if(this.price != other.price){ return false; }
        if(this.weight != other.weight){ return false; }
        if(this.yearOfProduction != other.yearOfProduction) { return false; }

        return true;
    }
}
