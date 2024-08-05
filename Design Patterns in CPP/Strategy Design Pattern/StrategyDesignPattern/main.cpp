#include <QCoreApplication>
#include <bits/stdc++.h>

class SortingStrategy {
public:
    virtual void sort(std::vector<int>& arr) = 0;
};

class BubbleSort : public SortingStrategy {
public:
    void sort(std::vector<int>& arr) override
    {
        // Implement Bubble Sort algorithm
        std::cout << "sorting by bubble sort" << std::endl;
    }
};

class QuickSort : public SortingStrategy {
public:
    void sort(std::vector<int>& arr) override
    {
        // Implement Quick Sort algorithm
        std::cout << "sorting by quick sort" << std::endl;
    }
};

// Add more sorting algorithms as needed

class SortContext {
private:
    SortingStrategy* strategy;

public:
    void setStrategy(SortingStrategy* strategy)
    {
        this->strategy = strategy;
    }

    void executeStrategy(std::vector<int>& arr)
    {
        strategy->sort(arr);
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::vector<int> data = { 5, 2, 7, 1, 9 };

    SortContext context;
    BubbleSort bubbleSort;
    QuickSort quickSort;

    context.setStrategy(&bubbleSort);
    context.executeStrategy(data); // Executes Bubble Sort

    context.setStrategy(&quickSort);
    context.executeStrategy(data); // Executes Quick Sort

    return a.exec();
}
