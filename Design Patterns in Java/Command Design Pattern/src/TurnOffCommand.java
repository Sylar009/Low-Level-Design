// Concrete command for turning a device off
public class TurnOffCommand implements Command{
    
    private Device m_device;
 
    public TurnOffCommand(Device device) {
        this.m_device = device;
    }
 
    @Override
    public void execute() {
        this.m_device.turnOff();
    }

}
