// Concrete receiver for a TV
public class TV implements Device {

    @Override
    public void turnOff() {
        System.out.println("TV is now off");
    }

    @Override
    public void turnOn() {
        System.out.println("TV is now on");
    }

    public void changeChannel() {
        System.out.println("Channel changed");
    }
}
