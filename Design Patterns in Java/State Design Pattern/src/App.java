public class App {
    public static void main(String[] args) throws Exception {
         // Create context
         VendingMachineContext vendingMachine = new VendingMachineContext();
 
         // Set initial state
         vendingMachine.setState(new ReadyState());
  
         // Request state change
         vendingMachine.request();
  
         // Change state
         vendingMachine.setState(new ProductSelectedState());
  
         // Request state change
         vendingMachine.request();
  
         // Change state
         vendingMachine.setState(new PaymentPendingState());
  
         // Request state change
         vendingMachine.request();
  
         // Change state
         vendingMachine.setState(new OutOfStockState());
  
         // Request state change
         vendingMachine.request();
    }
}
