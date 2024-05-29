// Concrete command for changing the channel of a TV
public class ChangeChannelCommand implements Command {
    private TV m_tv;
 
    public ChangeChannelCommand(TV tv) {
        this.m_tv = tv;
    }
 
    @Override
    public void execute() {
        this.m_tv.changeChannel();
    }
}