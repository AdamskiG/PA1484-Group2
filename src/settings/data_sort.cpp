#include "data_sort.h"

int Data_Sort::clean_id(String id_string)
{
    String cleaned_id{};
    std::reverse(id_string.begin(), id_string.end());
    int counter = 1;
    while(id_string[counter] != '='){
        cleaned_id += id_string[counter];
        counter++;
    }
    return cleaned_id.toInt();
}

std::string Data_Sort::clean_name(String station_name)
{
    std::string cleaned_str;
    for(const char letter : station_name)
    {
        if(letter != '(')
        {
            cleaned_str += letter;
        }
    }
    return cleaned_str;
}

std::string Data_Sort::decipher_transport(int products)
{
    std::string type;
    if((2 & products) != 0 || (4 & products) != 0 || (16 & products) != 0)
    {
        type += "Train\n";
    }

    if((8 & products) != 0 || (128 & products) != 0)
    {
        type += "Bus\n";
    }
    
    if((256 & products) != 0)
    {
        type += "Boat\n";
    }
    type.pop_back();
    return type;
}