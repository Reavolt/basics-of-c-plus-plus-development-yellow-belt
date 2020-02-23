#include "responses.h"

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