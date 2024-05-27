// Prototype interface
// This is like a blueprint for creating shapes.
// It says every shape should be able to clone itself and draw.
public interface Shape {
	Shape clone(); // Make a copy of itself
	void draw(); // Draw the shape
}
