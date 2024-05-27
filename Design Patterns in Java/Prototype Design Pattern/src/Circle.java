// Concrete prototype

// This is a specific shape, a circle, implementing the Shape interface.
// It can create a copy of itself (clone) and draw in its own way.
public class Circle implements Shape {
	private String color;

	// When you create a circle, you give it a color.
	public Circle(String color) {
		this.color = color;
	}

	// This creates a copy of the circle.
	@Override
	public Shape clone() {
		return new Circle(this.color);
	}

	// This is how a circle draws itself.
	@Override
	public void draw() {
		System.out.println("Drawing a " + color + " circle.");
	}
}

