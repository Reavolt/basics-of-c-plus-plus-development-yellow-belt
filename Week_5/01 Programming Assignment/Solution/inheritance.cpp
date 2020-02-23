#include <iostream>
#include <string>

//--------------------------------------------------------------------------------------------------
class Animal 
{
public:
    Animal(const std::string& str = "animal") : Name(str)
    {

    }
public:
    const std::string Name;
};
//--------------------------------------------------------------------------------------------------
class Dog : public Animal 
{
public:
    Dog(const std::string& str = "dog") : Animal(str)
    {

    }
    void Bark() 
    {
       std::cout << Name << " barks: woof!" << std::endl;
    }
};
//--------------------------------------------------------------------------------------------------
int main()
{
    Dog dg;
    dg.Bark();
    return 0;
}
//-------------------------------------------------------------------------------------------------