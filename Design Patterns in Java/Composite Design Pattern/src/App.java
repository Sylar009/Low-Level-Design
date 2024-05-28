public class App {
    public static void main(String[] args) throws Exception {
        // Create leaf objects (files) 
        FileSystemComponent file1 = new File("document.txt", 1024); 
        FileSystemComponent file2 = new File("image.jpg", 2048); 
  
        // Create a composite object (directory) 
        Directory directory = new Directory("My Documents"); 
  
        // Add leaf objects to the directory 
        directory.addComponent(file1); 
        directory.addComponent(file2); 
  
        // Display the directory (including its contents) 
        directory.display(); 
    }
}
