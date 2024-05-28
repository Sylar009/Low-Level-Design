public class App {
    public static void main(String[] args) throws Exception {
        Printer adapter = new PrinterAdapter();
        adapter.print();
    }
}
