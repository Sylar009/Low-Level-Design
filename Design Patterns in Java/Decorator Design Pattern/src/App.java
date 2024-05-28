public class App {
    public static void main(String[] args) throws Exception {
         // Plain Coffee
         Coffee coffee = new PlainCoffee();
         System.out.println("Description: " + coffee.getDescription());
         System.out.println("Cost: $" + coffee.getCost());
 
         // Coffee with Milk
         Coffee milkCoffee = new MilkDecorator(new PlainCoffee());
         System.out.println("\nDescription: " + milkCoffee.getDescription());
         System.out.println("Cost: $" + milkCoffee.getCost());
 
         // Coffee with Sugar and Milk
         Coffee sugarMilkCoffee = new SugarDecorator(new MilkDecorator(new PlainCoffee()));
         System.out.println("\nDescription: " + sugarMilkCoffee.getDescription());
         System.out.println("Cost: $" + sugarMilkCoffee.getCost());
    }
}
