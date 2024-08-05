#include <QCoreApplication>
#include <iostream>
#include <vector>
using namespace std;

class PageObject {
public:
    virtual void Add(PageObject& a) {}
    virtual void Remove() {}
    virtual void Delete(PageObject&  a) {}
};

class Page : public PageObject {
public:
    void Add(PageObject& a) override
    {
        cout << "something is added to the page" << endl;
    }
    void Remove() override
    {
        cout << "something is removed from the page"
             << endl;
    }
    void Delete(PageObject& a) override
    {
        cout << "something is deleted from page " << endl;
    }
};

class Copy : public PageObject {
    vector<PageObject> copyPages;

public:
    void AddElement(PageObject& a)
    {
        copyPages.push_back(a);
    }

    void Add(PageObject& a) override
    {
        cout << "something is added to the copy" << endl;
    }
    void Remove() override
    {
        cout << "something is removed from the copy"
             << endl;
    }
    void Delete(PageObject& a) override
    {
        cout << "something is deleted from the copy";
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Page p1;
    Page p2;
    Copy allcopy;
    allcopy.AddElement(p1);
    allcopy.AddElement(p2);

    allcopy.Add(p1);
    allcopy.Add(p2);

    allcopy.Remove();
    p2.Remove();

    return a.exec();
}
