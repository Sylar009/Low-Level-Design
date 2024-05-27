public class Computer {
    private String m_cpu;
    private String m_ram;
    private String m_storage;
    
    public void setCPU(String cpu) {
        this.m_cpu = cpu;
    }
    
    public void setRam(String ram) {
        this.m_ram = ram;
    }
    
    public void setStorage(String storage) {
        this.m_storage = storage;
    }

    public void displayInfo() {
        System.out.println("Computer Configuration: \nCPU: " + this.m_cpu + "\nRAM: " + this.m_ram + "\nStorage: " + this.m_storage + "\n\n");
    }
}
