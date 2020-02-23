#include <map>
#include <tuple>
#include <vector>

//-------------------------------------------------------------------------------------------------
/*
enum class Lang
{
    DE, FR, IT
};
*/
//-------------------------------------------------------------------------------------------------
/*
struct Region 
{
    std::string std_name;
    std::string parent_std_name;
    std::map<Lang, std::string> names;
    int64_t population;
};
*/
//-------------------------------------------------------------------------------------------------
bool operator<(const Region& lhs, const Region& rhs) 
{
	return std::tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) <
		   std::tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}
//-------------------------------------------------------------------------------------------------
int FindMaxRepetitionCount(const vector<Region>& regions)
{
	int result = 0;
	map<Region, int> repetition_count;
	
	for (const Region& region : regions) 
	{
		result = std::max(result, ++repetition_count[region]);
	}
	return result;
}
//-------------------------------------------------------------------------------------------------
/*
int main()
{
    std::cout << FindMaxRepetitionCount({
     {
         "Moscow",
         "Russia",
         {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
         89
     }, {
         "Russia",
         "Eurasia",
         {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
         89
     }, {
         "Moscow",
         "Russia",
         {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
         89
     }, {
         "Moscow",
         "Russia",
         {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
         89
     }, {
         "Russia",
         "Eurasia",
         {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
         89
     },
        }) << std::endl;

    std::cout << FindMaxRepetitionCount({
        {
            "Moscow",
            "Russia",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
            89
        }, {
            "Russia",
            "Eurasia",
            {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
            89
        }, {
            "Moscow",
            "Russia",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
            89
        }, {
            "Moscow",
            "Toulouse",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
            89
        }, {
            "Moscow",
            "Russia",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
            31
        },
        }) << std::endl;

	return 0;
}
*/
//-------------------------------------------------------------------------------------------------