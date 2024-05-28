public class PrinterAdapter implements Printer{

    LagecyPrinter m_old_printer = new LagecyPrinter();
    @Override
    public void print() {
        m_old_printer.printDocument();
    }

}
