#pragma once
#include "jsmn.h"
#include <string>

struct Json_Data
{
    const char* data;
    const size_t size;

    Json_Data(char* inData, size_t inSize);
    Json_Data(const char* inData, const size_t inSize);
};

class Json_Parser
{
private:
    Json_Data* json;
    size_t offset = 0;

    size_t token_count = 0;
    jsmntok_t* tokens = nullptr;

public:
    Json_Parser();
    Json_Parser(Json_Data* target);
    Json_Parser(Json_Data* target, size_t in_token_count, jsmntok_t* in_tokens, size_t in_offset = 0);
    ~Json_Parser();

    // read specified json data
    void read(Json_Data* target);

    // Returns index of subtoken with value
    size_t find(std::string find_val);

    // Returns true if value exists in the greatest json object
    bool contains(std::string find_val);

    // Create new json parser for inner data using the specified key
    Json_Parser at_key(std::string enter_val);
    
    // Create new json parser for the inner data by ID, reading it like an array.
    Json_Parser at_index(int enter_val);

    // Get sum of the sizes for a subtoken, and all of its subtokens
    size_t total_subtoken_size(int index);

    // Get highest-tier token
    jsmntok_t& get_token();

    // Get highest-tier token as a string
    std::string get_string();
};