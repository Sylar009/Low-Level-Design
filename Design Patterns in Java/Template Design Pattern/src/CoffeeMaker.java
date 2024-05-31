// Concrete subclass for making coffee
public class CoffeeMaker extends BeverageMaker {
	// Implementing abstract methods
	@Override
	void brew() {
		System.out.println("Dripping coffee through filter");
	}

	@Override
	void addCondiments() {
		System.out.println("Adding sugar and milk");
	}
}
