public class GamingComputerBuilder implements Builder{
    private Computer m_computer;

    public GamingComputerBuilder() {
        this.m_computer = new Computer();
    }

    @Override
    public void buildCPU() {
        this.m_computer.setCPU("Gaming CPU");
    }

    @Override
    public void buildRAM() {
        this.m_computer.setRam("16GB DDR4");
    }

    @Override
    public void buildStorage() {
        this.m_computer.setCPU("1TB SSD");
    }

    @Override
    public Computer getResult() {
        return this.m_computer;
    }
}
