#include <iostream>
#include <memory>

class Resource 
{
public:
    Resource() { std::cerr << "Resource acquired\n"; }
    ~Resource() { std::cerr << "Resource destroyed\n"; }
};

//Returns a std::weak_ptr tp an invalid object
std::weak_ptr<Resource> getWeakPtr()
{
    auto ptr{ std::make_shared<Resource>() };
    return std::weak_ptr<Resource>{ ptr };
}

//Returns a dumb pointer to an invalid object
Resource* getDumbPtr()
{
    auto ptr{ std::make_unique<Resource>() };
    return ptr.get();
}

int main()
{
    auto dumb{ getDumbPtr() };
    std::cout << "Our dumb ptr is: " << ((dumb == nullptr) ? "nullptr\n" : "non-null\n");

    auto weak{ getWeakPtr() };
    std::cout << "Our weak ptr is: " << ((weak.expired()) ? "expired\n" : "valid\n");
}