#include <vector>
#include <iostream>
#include <string>
#include <sstream>

//-------------------------------------------------------------------------------------------------
std::vector<std::string> SplitIntoWords(const std::string& s)
{
    std::vector<std::string> str;

    std::istringstream i_stream(s);
    std::string tmp;

    while (i_stream >> tmp)
    {
        str.push_back(tmp);
    }
    return str;
}
//-------------------------------------------------------------------------------------------------
int main() 
{
    std::string s = "C Cpp Java Python";

    std::vector<std::string> words = SplitIntoWords(s);
    std::cout << words.size() << " ";

    for (auto it = begin(words); it != end(words); ++it) 
    {
        if (it != begin(words))
        {
            std::cout << "/";
        }
        std::cout << *it;
    }
    std::cout << std::endl;

    return 0;
}
//-------------------------------------------------------------------------------------------------