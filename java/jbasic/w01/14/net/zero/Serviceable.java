package net.zero;

public interface Serviceable {

    public abstract boolean isNeedToService();
    public int getDistance();
    public void addDistance(int distance);
    public void addDistance(float distance);
}
