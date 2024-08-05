#include <QCoreApplication>
#include <iostream>
#include <string>

// Context
class Context {
    // Any global information needed for interpretation can be added here
};

// Abstract Expression Interface
class Expression {
public:
    virtual int interpret(Context& context) = 0;
    virtual ~Expression() {} // Virtual destructor for correct polymorphic behavior
};

// Terminal Expression (NumberExpression)
class NumberExpression : public Expression {
private:
    int number;

public:
    NumberExpression(int number) : number(number) {}

    int interpret(Context& context) override {
        return number;
    }
};

// Non-Terminal Expression (AdditionExpression)
class AdditionExpression : public Expression {
private:
    Expression* left;
    Expression* right;

public:
    AdditionExpression(Expression* left, Expression* right) : left(left), right(right) {}

    int interpret(Context& context) override {
        return left->interpret(context) + right->interpret(context);
    }

    ~AdditionExpression() {
        delete left;
        delete right;
    }
};

// Non-Terminal Expression (MultiplicationExpression)
class MultiplicationExpression : public Expression {
private:
    Expression* left;
    Expression* right;

public:
    MultiplicationExpression(Expression* left, Expression* right) : left(left), right(right) {}

    int interpret(Context& context) override {
        return left->interpret(context) * right->interpret(context);
    }

    ~MultiplicationExpression() {
        delete left;
        delete right;
    }
};

// Interpreter
class Interpreter {
private:
    Context* context;

public:
    Interpreter(Context* context) : context(context) {}

    int interpret(const std::string& expression) {
        // For simplicity, assuming expression is parsed and directly creating the expression tree
        Expression* expressionTree = buildExpressionTree(expression);

        // Interpret expression tree
        int result = expressionTree->interpret(*context);

        delete expressionTree;

        return result;
    }

private:
    Expression* buildExpressionTree(const std::string& expression) {
        // Logic to parse expression and create expression tree
        // For simplicity, hardcoding an expression tree
        return new AdditionExpression(
            new NumberExpression(2),
            new MultiplicationExpression(
                new NumberExpression(3),
                new NumberExpression(4)
                )
            );
    }
};

// Client (Main function)
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Input expression
    std::string expression = "2 + 3 * 4";

    // Create interpreter
    Context* context = new Context();
    Interpreter interpreter(context);

    // Interpret expression
    int result = interpreter.interpret(expression);
    std::cout << "Result: " << result << std::endl;

    delete context;

    return a.exec();
}
