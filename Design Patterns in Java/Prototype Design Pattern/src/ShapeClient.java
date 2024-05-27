// Client code

// This is like a user of shapes.
// It uses a prototype (a shape) to create new shapes.
public class ShapeClient {
	private Shape shapePrototype;

	// When you create a client, you give it a prototype (a shape).
	public ShapeClient(Shape shapePrototype) {
		this.shapePrototype = shapePrototype;
	}

	// This method creates a new shape using the prototype.
	public Shape createShape() {
		return shapePrototype.clone();
	}
}

