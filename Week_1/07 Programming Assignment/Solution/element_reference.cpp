#include <iostream>
#include <map>

//-------------------------------------------------------------------------------------------------
template<typename key, typename type>
type & GetRefStrict(std::map<key, type> & map_prm, key key_prm)
{
    if (map_prm.count(key_prm) == 0)
    {
        throw std::runtime_error("item by key k in the collection is missing");
    }
    return map_prm[key_prm];
}
//-------------------------------------------------------------------------------------------------
int main()
{
    std::map<int, std::string> m = { {0, "value"} };
    std::string& item = GetRefStrict(m, 0);
    item = "newvalue";
    std::cout << m[0] << std::endl;

    return 0;
}
//-------------------------------------------------------------------------------------------------