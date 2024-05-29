// Concrete command for adjusting the volume of a stereo
public class AdjustVolumeCommand implements Command {
    private Stereo m_stereo;
 
    public AdjustVolumeCommand(Stereo stereo) {
        this.m_stereo = stereo;
    }
 
    @Override
    public void execute() {
        this.m_stereo.adjustVolume();
    }
}
