#include "./uuid.h"

BEGIN_NS_AD
static std::random_device rd;
static std::mt19937 generate(rd());
static std::uniform_int_distribution<> distribute(0, 15);
static std::uniform_int_distribution<> distribute_2(8, 11);

std::string UUID::generate_uuid()
{
    std::stringstream ss;
    int i;
    ss << std::hex;
    for (i = 0; i < 8; i++)
    {
        ss << distribute(generate);
    }
    ss << "-";
    for (i = 0; i < 4; i++)
    {
        ss << distribute(generate);
    }
    ss << "-4";
    for (i = 0; i < 3; i++)
    {
        ss << distribute(generate);
    }
    ss << "-";
    ss << distribute_2(generate);
    for (i = 0; i < 3; i++)
    {
        ss << distribute(generate);
    }
    ss << "-";
    for (i = 0; i < 12; i++)
    {
        ss << distribute(generate);
    };
    std::string str = ss.str();
    ss.clear();
    ss.str("");
    return str;
}
END_NS_AD
