// Concrete command for turning a device on
public class TurnOnCommand implements Command{

    private Device m_device;

    public TurnOnCommand(Device device){
        this.m_device = device;
    }

    @Override
    public void execute() {
        this.m_device.turnOn();
    }

}
