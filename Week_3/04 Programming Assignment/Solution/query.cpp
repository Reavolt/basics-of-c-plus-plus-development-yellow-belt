#include "query.h"

//-------------------------------------------------------------------------------------------------
std::istream& operator >> (std::istream& is, Query& q) 
{
    std::string operation_code;
    is >> operation_code;

    if (operation_code == "NEW_BUS")
    {      
        q.type = QueryType::NewBus;
        is >> q.bus;

        size_t stop_count = 0;
        is >> stop_count;

        q.stops.resize(stop_count);
        for (auto & item : q.stops)
        {
            is >> item;
        }
    }
    else 
    if (operation_code == "BUSES_FOR_STOP")
    {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    }
    else
    if (operation_code == "STOPS_FOR_BUS")
    {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    }
    else
    if (operation_code == "ALL_BUSES")
    {
        q.type = QueryType::AllBuses;
    }
    return is;
}
//-------------------------------------------------------------------------------------------------