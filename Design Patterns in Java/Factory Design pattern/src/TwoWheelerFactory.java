public class TwoWheelerFactory extends VehicleFactory {

    @Override
    public Vehicle createVehicle() {
        return new TwoWheeler();
    }
    
}
