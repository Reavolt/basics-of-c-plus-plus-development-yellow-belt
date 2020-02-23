#include <iostream>
#include <string>
#include <vector>

//--------------------------------------------------------------------------------------------------
class Person
{
public:
    Person(const std::string& name, const std::string& occupation)
        : Name(name), Occupation(occupation)
    {

    }

    std::string get_name() const
    {
        return Name;
    }

    std::string get_occupation() const
    {
        return Occupation;
    }

    virtual void Walk(const std::string& destination) const = 0;
private:
    std::string Name;
    std::string Occupation;
};
//--------------------------------------------------------------------------------------------------
class Student : public Person
{
public:
    Student(const std::string& name, const std::string& favouriteSong)
        : Person(name, "Student"), FavouriteSong(favouriteSong)
    {

    }

    void Learn() const
    {
        std::cout << "Student: " << get_name() << " learns" << std::endl;
    }

    void Walk(const std::string& destination) const override
    {
        std::cout << "Student: " << get_name() << " walks to: " << destination << std::endl;
        SingSong();
    }

    void SingSong() const
    {
        std::cout << "Student: " << get_name() << " sings a song: " << FavouriteSong << std::endl;
    }
public:
    std::string FavouriteSong;
};
//--------------------------------------------------------------------------------------------------
class Teacher : public Person
{
public:
    Teacher(std::string name, std::string subject)
        : Person(name, "Teacher"), Subject(subject)
    {

    }

    void Teach() const
    {
        std::cout << "Teacher: " << get_name() << " teaches: " << Subject << std::endl;
    }

    void Walk(const std::string& destination) const override
    {
        std::cout << "Teacher: " << get_name() << " walks to: " << destination << std::endl;
    }
public:
    std::string Subject;
};
//--------------------------------------------------------------------------------------------------
class Policeman : public Person
{
public:
    Policeman(const std::string& name)
        : Person(name, "Policeman")
    {

    }

    void Check(const Person& p) const
    {
        std::cout << "Policeman: " << get_name() << " checks " << p.get_occupation() << ". "
            << p.get_occupation() << "'s name is: " << p.get_name() << std::endl;
    }

    void Walk(const std::string& destination) const override
    {
        std::cout << "Policeman: " << get_name() << " walks to: " << destination << std::endl;
    }
};
//--------------------------------------------------------------------------------------------------
void VisitPlaces(const Person& pers, const std::vector<std::string>& places)
{
    for (const auto& p : places)
    {
        pers.Walk(p);
    }
}
//--------------------------------------------------------------------------------------------------
int main()
{
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, { "Moscow", "London" });
    p.Check(s);
    VisitPlaces(s, { "Moscow", "London" });
    return 0;
}
//--------------------------------------------------------------------------------------------------