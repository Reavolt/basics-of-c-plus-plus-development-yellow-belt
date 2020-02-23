#include "phone_number.h"
#include <sstream>

//-------------------------------------------------------------------------------------------------
PhoneNumber::PhoneNumber(const string& international_number)
{
	std::istringstream in_string(international_number);
	const char sign = in_string.get();

	if (in_string)
	{
		std::getline(in_string, country_code_, '-');
		std::getline(in_string, city_code_, '-');
		std::getline(in_string, local_number_, '\n');
	}
	
	if (sign != '+' || country_code_.empty())
	{
		throw invalid_argument("The country code must begin with a + sign and be at least one character");
	}

	if (city_code_.empty())
	{
		throw invalid_argument("Area code cannot be empty");
	}

	if (local_number_.empty())
	{
		throw invalid_argument("Phone number cannot be empty");
	}
}
//-------------------------------------------------------------------------------------------------
string PhoneNumber::GetCountryCode() const
{
	return country_code_;
}
//-------------------------------------------------------------------------------------------------
string PhoneNumber::GetCityCode() const
{
	return city_code_;
}
//-------------------------------------------------------------------------------------------------
string PhoneNumber::GetLocalNumber() const
{
	return local_number_;
}
//-------------------------------------------------------------------------------------------------
string PhoneNumber::GetInternationalNumber() const
{
	return ("+" + country_code_ + "-" + city_code_ + "-" + local_number_);
}
//-------------------------------------------------------------------------------------------------