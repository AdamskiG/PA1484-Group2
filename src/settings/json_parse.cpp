#include "json_parse.h"

Json_Parser::Json_Parser()
{
}

Json_Parser::Json_Parser(Json_Data* target)
{
	read(target);
}

Json_Parser::Json_Parser(Json_Data* target, size_t in_token_count, jsmntok_t* in_tokens, size_t in_offset)
{
    json = target;
    token_count = in_token_count;
    tokens = in_tokens;
    offset = in_offset;
}

Json_Parser::~Json_Parser()
{
    delete[] tokens;
}

void Json_Parser::read(Json_Data* target)
{
    json = target;

    // Creates json parser
    jsmn_parser parser;
    jsmn_init(&parser);

    // Parses json to get token count
    token_count = jsmn_parse(&parser, json->data, json->size, NULL, 0);

    // Allocates enough space for the json's tokens
    tokens = new jsmntok_t[token_count];

    // Resets the json parser
    jsmn_init(&parser);

    // Re-parses the json, now saving the token data
    int errorValue = jsmn_parse(&parser, json->data, json->size, tokens, token_count);
}

size_t Json_Parser::find(std::string find_val)
{
    size_t walker = 1;
    size_t token_index = 0;

    bool found;
    while (walker < token_count)
    {
        jsmntok_t target_token = tokens[walker];

        // Determine if target token's specified string matches the search value
        bool is_equal = true;
        for (int i = 0; i < target_token.end - target_token.start; i++)
        {
            if (i > find_val.size() || json->data[i + target_token.start] != find_val[i])
            {
                is_equal = false;
                break;
            }
        }
        // If target token's string is equal to the search value, return the target token's index
        if (is_equal)
            return token_index;

        // Otherwise, skip to the next token after the current token's contents.
        walker += total_subtoken_size(walker) + 1;
        token_index++;
    }

    return -1;
}

bool Json_Parser::contains(std::string find_val)
{
    return find(find_val) != -1;
}

Json_Parser Json_Parser::at_key(std::string enter_val)
{
    size_t inner_origin = find(enter_val);
    if (inner_origin == -1)
        throw std::exception();
    return at_index(inner_origin);
}

Json_Parser Json_Parser::at_index(int enter_val)
{
    size_t inner_origin = 1;
    for (int i = 0; i < enter_val; i++)
        inner_origin += total_subtoken_size(inner_origin) + 1;

    jsmntok_t inner_start_token = tokens[inner_origin];
    jsmntok_t inner_end_token = tokens[inner_origin + inner_start_token.size];

    size_t inner_token_count = total_subtoken_size(inner_origin) + 1;
    jsmntok_t* inner_tokens = tokens + inner_origin;

    size_t inner_char_count = inner_end_token.start - inner_start_token.start;

    return Json_Parser(json, inner_token_count, inner_tokens, inner_start_token.start);
}

size_t Json_Parser::total_subtoken_size(int index)
{
    size_t size = 0;
    size_t walker = index;

    int i = 0;
    do
    {
        size += tokens[walker].size;
        i += tokens[walker].size;
        walker++;
        i--;
    } while (i >= 0 && walker < token_count);

    return size;
}

jsmntok_t& Json_Parser::get_token()
{
    return tokens[0];
}

std::string Json_Parser::get_string()
{
    return std::string(json->data, get_token().start, get_token().end - get_token().start);
}