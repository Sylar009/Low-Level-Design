// Concrete Class EuropeCarFactory

public class EuropeCarFactory implements CarFactory{
    public Car createCar() {
        return new HatchBack();
    }

    public CarSpecification createSpecification() {
        return new EuropeanSpecification();
    }
}
