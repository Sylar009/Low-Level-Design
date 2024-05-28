public class File implements FileSystemComponent{
    private String m_name;
    private int m_size;

    public File(String name, int size) {
        this.m_name = name;
        this.m_size = size;
    }

    @Override
    public void display() {
        System.out.println("File: " + this.m_name + " (size: " + this.m_size + ")" );
    }
}
