#pragma once

#ifndef _DATE_H_
#define _DATE_H_

#include <string>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <memory>

//----------------------------------------------------------------------------------------------------
class Date
{
public:
	Date() noexcept;
	Date(int new_year, int new_month, int new_day);

	int GetYear() const noexcept;
	int GetMonth() const noexcept;
	int GetDay() const noexcept;
	std::string DateToStr() const;
private:
	int year;
	int month;
	int day;
};
//----------------------------------------------------------------------------------------------------
Date ParseDate(std::istream& is);
//----------------------------------------------------------------------------------------------------
std::ostream& operator << (std::ostream& os, const Date& date);
std::ostream& operator << (std::ostream& os, const std::pair<Date, std::string>& pair);

bool operator < (const Date& lsh, const Date& rhs) noexcept;
bool operator <= (const Date& lsh, const Date& rhs) noexcept;
bool operator > (const Date& lsh, const Date& rhs) noexcept;
bool operator >= (const Date& lsh, const Date& rhs) noexcept;
bool operator == (const Date& lsh, const Date& rhs) noexcept;
bool operator != (const Date& lsh, const Date& rhs) noexcept;
//----------------------------------------------------------------------------------------------------
#endif // _DATE_H_