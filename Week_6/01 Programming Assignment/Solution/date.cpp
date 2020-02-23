#include "date.h"

//----------------------------------------------------------------------------------------------------
Date::Date() noexcept : year(0), month(0), day(0) 
{ 
	//	//Constructor body
}
//----------------------------------------------------------------------------------------------------
Date::Date(int new_year, int new_month, int new_day)
{
	if (new_month > 12 || new_month < 1)
	{
		std::string error = "Month value is invalid: " + std::to_string(new_month);
		throw std::logic_error(error);
	}
	else
	{
		month = new_month;
	}

	if (new_day > 31 || new_day < 1)
	{
		std::string error = "Day value is invalid: " + std::to_string(new_day);
		throw std::logic_error(error);
	}
	else
	{
		day = new_day;
	}
	year = new_year;
}
//----------------------------------------------------------------------------------------------------
int Date::GetYear() const noexcept
{
	return year;
}
//----------------------------------------------------------------------------------------------------
int Date::GetMonth() const noexcept
{
	return month;
}
//----------------------------------------------------------------------------------------------------
int Date::GetDay() const noexcept
{
	return day;
}
//----------------------------------------------------------------------------------------------------
std::string Date::DateToStr() const
{
	std::stringstream ss;
	ss << *this;
	return ss.str();
}
//----------------------------------------------------------------------------------------------------
Date ParseDate(std::istream& is)
{
    std::string str_date;
    is >> str_date;

    std::stringstream str_stream_date(str_date);

    int year = -1;
    str_stream_date >> year;

    if (str_stream_date.fail() || str_stream_date.peek() != '-')
    {
        throw std::logic_error("Wrong date format: " + str_date);
    }
    str_stream_date.ignore();

    int month = -1;
    str_stream_date >> month;

    if (str_stream_date.fail() || str_stream_date.peek() != '-')
    {
        throw std::logic_error("Wrong date format: " + str_date);
    }
    str_stream_date.ignore();

    int day = -1;
    str_stream_date >> day;

    if (str_stream_date.fail() || !str_stream_date.eof())
    {
        throw std::logic_error("Wrong date format: " + str_date);
    }
    return Date(year, month, day);
}
//----------------------------------------------------------------------------------------------------
std::ostream& operator << (std::ostream& os, const Date& date)
{
	os << std::setw(4) << std::setfill('0') << date.GetYear() << '-';
	os << std::setw(2) << std::setfill('0') << date.GetMonth() << '-';
	os << std::setw(2) << std::setfill('0') << date.GetDay();
	return os;
}
//----------------------------------------------------------------------------------------------------
std::ostream& operator << (std::ostream& os, const std::pair<Date, std::string>& pair)
{
	os << pair.first << " " << pair.second;
	return os;
}
//----------------------------------------------------------------------------------------------------
bool operator < (const Date& lhs, const Date& rhs) noexcept
{
	return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) < 
		   std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}
//----------------------------------------------------------------------------------------------------
bool operator <= (const Date& lhs, const Date& rhs) noexcept
{
	return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) <= 
		   std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}
//----------------------------------------------------------------------------------------------------
bool operator > (const Date& lhs, const Date& rhs) noexcept
{
	return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) >
		   std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}
//----------------------------------------------------------------------------------------------------
bool operator >= (const Date& lhs, const Date& rhs) noexcept
{
	return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) >= 
		   std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}
//----------------------------------------------------------------------------------------------------
bool operator == (const Date& lhs, const Date& rhs) noexcept
{
	return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) ==
		   std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}
//----------------------------------------------------------------------------------------------------
bool operator != (const Date& lhs, const Date& rhs) noexcept
{	
	return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) != 
		   std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}
//----------------------------------------------------------------------------------------------------