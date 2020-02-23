#include <iostream>
#include <string>
#include <map>

//-------------------------------------------------------------------------------------------------
class Person 
{
public:
	void ChangeFirstName(int year, const std::string & first_name)
	{
		// добавить факт изменения имени на first_name в год year
		first_names[year] = first_name;
	}
	
	void ChangeLastName(int year, const std::string & last_name) 
	{
		// добавить факт изменения фамилии на last_name в год year
		last_names[year] = last_name;
	}
	
	std::string GetFullName(int year) 
	{
		// получить имя и фамилию по состоянию на конец года year
		const std::string first_name = find_name(first_names,year);
		const std::string last_name = find_name(last_names, year);

		if (first_name.empty() && last_name.empty())
		{
			return "Incognito";
		}
		else
		if (first_name.empty())
		{
			
			return last_name + " with unknown first name";
		}
		else
		if (last_name.empty())
		{
			
			return first_name + " with unknown last name";
		}
		return first_name + " " + last_name;
	}
private:
	std::string find_name(std::map<int, std::string>& names, int year)
	{
		auto itr_name = names.upper_bound(year);

		if (itr_name != names.begin())
		{
			return std::prev(itr_name)->second;
		}
		return std::string("");
	}
	std::map<int, std::string> first_names;
	std::map<int, std::string> last_names;
};
//-------------------------------------------------------------------------------------------------
int main()
{
	Person person;

	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	for (int year : {1900, 1965, 1990}) 
	{
		std::cout << person.GetFullName(year) << std::endl;
	}

	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : {1969, 1970})
	{
		std::cout << person.GetFullName(year) << std::endl;
	}

	person.ChangeLastName(1968, "Volkova");
	for (int year : {1969, 1970}) 
	{
		std::cout << person.GetFullName(year) << std::endl;
	}
	return 0;
}
//-------------------------------------------------------------------------------------------------