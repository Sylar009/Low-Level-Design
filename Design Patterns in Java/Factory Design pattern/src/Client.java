public class Client {
    private Vehicle m_vehicle;

    public  Client(VehicleFactory factory){
        m_vehicle = factory.createVehicle();
    }  

    public Vehicle getVehicle() {
        return m_vehicle;
    }
}
