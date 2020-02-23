#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <cmath>

//--------------------------------------------------------------------------------------------------
class Figure
{
public:
    virtual std::string Name() const = 0;
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;
};
//--------------------------------------------------------------------------------------------------
class Triangle : public Figure
{
private:
    double side_a = 0.0;
    double side_b = 0.0;
    double side_c = 0.0;
public:
    Triangle(const double& a, const double& b, const double& c) : side_a(a), side_b(b), side_c(c)
    {

    }

    std::string Name() const override
    {
        return "TRIANGLE";
    }

    double Perimeter() const override
    {
        return side_a + side_b + side_c;
    }

    double Area() const override
    {
        double p_2 = (side_a + side_b + side_c) / 2;
        return std::sqrt(p_2 * (p_2 - side_a) * (p_2 - side_b) * (p_2 - side_c));
    }
};
//--------------------------------------------------------------------------------------------------
class Rect : public Figure
{
private:
    double width = 0;
    double height = 0;
public:
    Rect(const double& wdth, const double& hght) : width(wdth), height(hght)
    {

    }

    std::string Name() const override
    {
        return "RECT";
    }

    double Perimeter() const override
    {
        return (width + height) * 2;
    }

    double Area() const override
    {
        return width * height;
    }
};
//--------------------------------------------------------------------------------------------------
class Circle : public Figure
{
private:
    double rad = 0;
public:
    Circle(const double& r) : rad(r)
    {

    }

    std::string Name() const override
    {
        return "CIRCLE";
    }

    double Perimeter() const override
    {
        return (2 * 3.14) * rad;
    }

    double Area() const override
    {
        return 3.14 * rad * rad;
    }
};
//--------------------------------------------------------------------------------------------------
std::shared_ptr<Figure> CreateFigure(std::istringstream& is)
{
    std::string type;
    is >> type;

    if (type == "TRIANGLE")
    {
        double a = 0.0;
        is >> a;

        double b = 0.0;
        is >> b;       

        double c = 0.0;
        is >> c;

        return std::make_shared<Triangle>(a, b, c);
    }
    else
    if (type == "RECT")
    {
        double width = 0.0;
        is >> width;

        double height = 0.0;
        is >> height;

        return std::make_shared<Rect>(width, height);
    }
	else
	{
		double r = 0.0;
		is >> r;

		return std::make_shared<Circle>(r);
	}
}
//--------------------------------------------------------------------------------------------------
int main()
{
    std::vector<std::shared_ptr<Figure>> figures;
    for (std::string line; std::getline(std::cin, line);) 
    {
        std::istringstream is(line);

        std::string command;
        is >> command;
        if (command == "ADD") 
        {
            figures.push_back(CreateFigure(is));
        }
        else if (command == "PRINT") 
        {
            for (const auto& current_figure : figures)
            {
                std::cout << std::fixed << std::setprecision(3)
                << current_figure->Name() << " "
                << current_figure->Perimeter() << " "
                << current_figure->Area() << std::endl;
            }
        }
    }
    return 0;
}
//-------------------------------------------------------------------------------------------------