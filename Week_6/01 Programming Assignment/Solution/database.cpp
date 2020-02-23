#include "database.h"

//----------------------------------------------------------------------------------------------------
void Database::Add(const Date& date, const std::string& event)
{
	if (db.count(date))
	{
		const auto insert_it = db[date].first.insert(event);

		if (insert_it.second)
		{
			db[date].second.push_back(insert_it.first);
		}
	}
	else
	{
		auto insert_result = db[date].first.insert(event);
		db[date].second.push_back(insert_result.first);
	}
}
//----------------------------------------------------------------------------------------------------
void Database::Print(std::ostream& is) const
{
	for (const auto& date_it : db)
	{
		for (const auto& event_it : date_it.second.second)
		{
			is << std::setw(4) << std::setfill('0') << date_it.first.GetYear() << '-';
			is << std::setw(2) << std::setfill('0') << date_it.first.GetMonth() << '-';
			is << std::setw(2) << std::setfill('0') << date_it.first.GetDay();
			is << " " << *event_it << std::endl;
		}
	}
}
//----------------------------------------------------------------------------------------------------
std::string Database::Last(const Date& date) const
{
	const auto itr_upper = db.upper_bound(date);

	if (itr_upper == db.begin())
	{
		throw std::invalid_argument("No entries");
	}
	return std::prev(itr_upper)->first.DateToStr() + " " + *std::prev(itr_upper)->second.second.back();
}
//----------------------------------------------------------------------------------------------------