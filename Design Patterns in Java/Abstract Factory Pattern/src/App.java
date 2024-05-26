public class App {
    public static void main(String[] args) throws Exception {
        // Creating cars for North America
        CarFactory northAmericaFactory = new NorthAmericaCarFactory();
        Car northAmericaCar = northAmericaFactory.createCar();
        CarSpecification northAmericaSpec = northAmericaFactory.createSpecification();
 
        northAmericaCar.assemble();
        northAmericaSpec.display();
 
        // Creating cars for Europe
        CarFactory europeFactory = new EuropeCarFactory();
        Car europeCar = europeFactory.createCar();
        CarSpecification europeSpec = europeFactory.createSpecification();
 
        europeCar.assemble();
        europeSpec.display();
    }
}
