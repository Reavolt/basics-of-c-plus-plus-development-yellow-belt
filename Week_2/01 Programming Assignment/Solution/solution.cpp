#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
//-------------------------------------------------------------------------------------------------
enum class QueryType 
{
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};
//-------------------------------------------------------------------------------------------------
struct Query 
{
    QueryType type;
    std::string bus;
    std::string stop;
    std::vector<std::string> stops;
};
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
struct BusesForStopResponse 
{
    std::vector<std::string> buses_to_stop;
};
//-------------------------------------------------------------------------------------------------
std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r) 
{
    if (r.buses_to_stop.empty())
    {
        os << "No stop" << std::endl;
    }
    else 
    {
        for (const std::string& bus : r.buses_to_stop)
        {
            os << bus << " ";
        }
        os << std::endl;
    }
    return os;
}
//-------------------------------------------------------------------------------------------------
struct StopsForBusResponse 
{
    std::string bus;
    std::vector<std::pair<std::string, std::vector<std::string>>> stops_for_buses;
};
//-------------------------------------------------------------------------------------------------
std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r) 
{
    if (r.stops_for_buses.empty())
    {
        os << "No bus" << std::endl;
    }
    else 
    {
        for (const auto& stop : r.stops_for_buses)
        {
            os << "Stop " << stop.first << ": ";
            if (stop.second.size() == 1)
            {
                os << "no interchange";
            }
            else 
            {
                for (const auto& other_bus : stop.second)
                {
                    if (other_bus != r.bus)
                    {
                        os << other_bus << " ";
                    }
                }
            }
            os << std::endl;
        }
    }
    return os;
}
//-------------------------------------------------------------------------------------------------
struct AllBusesResponse
{
    std::map<std::string, std::vector<std::string>> buses_to_stops;
};
//-------------------------------------------------------------------------------------------------
std::ostream& operator << (std::ostream& os, const AllBusesResponse& r) 
{
    if (r.buses_to_stops.empty()) 
    {
        os << "No buses" << std::endl;
    }
    else 
    {
        for (const auto& bus_item : r.buses_to_stops) 
        {
            os << "Bus " << bus_item.first << ": ";
            for (const std::string& stop : bus_item.second)
            {
                os << stop << " ";
            }
            os << std::endl;
        }
    }
    return os;
}
//-------------------------------------------------------------------------------------------------
class BusManager 
{
private:
    std::map<std::string, std::vector<std::string>> buses_to_stops;
    std::map<std::string, std::vector<std::string>> stops_to_buses;
public:
    void AddBus(const std::string& bus, const std::vector<std::string>& stops)
    {
        buses_to_stops[bus] = stops;
        for (const auto& stop : stops) 
        {
            stops_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const std::string& stop) const
    {
        if (stops_to_buses.count(stop) == 0)
        {
            return BusesForStopResponse{ std::vector<std::string>() };
        }
        else
        {
            return BusesForStopResponse{ stops_to_buses.at(stop) };
        }
    }

    StopsForBusResponse GetStopsForBus(const std::string& bus) const
    {
        std::vector<std::pair<std::string, std::vector<std::string>>> result;
        if (buses_to_stops.count(bus) > 0)
        {
            for (const auto& stop : buses_to_stops.at(bus))
            {
                result.push_back(make_pair(stop, stops_to_buses.at(stop)));
            }
        }
        return StopsForBusResponse{ bus, result };
    }

    AllBusesResponse GetAllBuses() const 
    {
        return AllBusesResponse{ buses_to_stops };
    }
};
//-------------------------------------------------------------------------------------------------
int main() 
{
    int query_count;
    Query q;

    std::cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) 
    {
        std::cin >> q;
        switch (q.type) 
        {
        case QueryType::NewBus:
            bm.AddBus(q.bus, q.stops);
            break;
        case QueryType::BusesForStop:
            std::cout << bm.GetBusesForStop(q.stop) << std::endl;
            break;
        case QueryType::StopsForBus:
            std::cout << bm.GetStopsForBus(q.bus) << std::endl;
            break;
        case QueryType::AllBuses:
            std::cout << bm.GetAllBuses() << std::endl;
            break;
        }
    }
    return 0;
}
//-------------------------------------------------------------------------------------------------