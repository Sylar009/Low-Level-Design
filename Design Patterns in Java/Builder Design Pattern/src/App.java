public class App {
    public static void main(String[] args) throws Exception {
        GamingComputerBuilder gamingBuilder = new GamingComputerBuilder();
        ComputerDirector director = new ComputerDirector();
 
        director.construct(gamingBuilder);
        Computer gamingComputer = gamingBuilder.getResult();
 
        gamingComputer.displayInfo();
    }
}
