public class App {
    public static void main(String[] args) throws Exception {
        AirTrafficControlTower controlTower = new AirportControlTower();
 
        // Instantiate Concrete Colleagues (Commercial Airplanes)
        Airplane airplane1 = new CommercialAirplane(controlTower);
        Airplane airplane2 = new CommercialAirplane(controlTower);
 
        // Set up the association between Concrete Colleagues and the Mediator
        airplane1.requestTakeoff();
        airplane2.requestLanding();
    }
}
