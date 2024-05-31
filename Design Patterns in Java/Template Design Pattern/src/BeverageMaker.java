// Abstract class defining the template method
public abstract class BeverageMaker {
	// Template method defining the overall process
	public final void makeBeverage() {
		boilWater();
		brew();
		pourInCup();
		addCondiments();
	}

	// Abstract methods to be implemented by subclasses
	abstract void brew();
	abstract void addCondiments();

	// Common methods
	void boilWater() {
		System.out.println("Boiling water");
	}

	void pourInCup() {
		System.out.println("Pouring into cup");
	}
}
