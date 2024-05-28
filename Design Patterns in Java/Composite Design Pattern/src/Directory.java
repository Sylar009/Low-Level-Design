import java.util.Vector;

public class Directory implements FileSystemComponent{
    private Vector<FileSystemComponent> m_component = new Vector<FileSystemComponent>();
    private String m_name;

    public Directory(String name) {
        this.m_name = name;
    }

    @Override
    public void display() {
        System.out.println("Director name: " + this.m_name);
        for (FileSystemComponent component : m_component) {
            System.out.print("----> ");
            component.display();
        }
        
    }

    public void addComponent(FileSystemComponent component) {
        m_component.add(component);
    }

}
