public class App {
    public static void main(String[] args) throws Exception {
        WeatherStation weatherStation = new WeatherStation();
 
        Observer phoneDisplay = new PhoneDisplay();
        Observer tvDisplay = new TVDisplay();
 
        weatherStation.addObserver(phoneDisplay);
        weatherStation.addObserver(tvDisplay);
 
        // Simulating weather change
        weatherStation.setWeather("Sunny");
    }
}
