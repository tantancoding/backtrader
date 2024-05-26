#pragma once
#include <define.h>

typedef std::string code;
typedef std::string date; // YYYY-MM-DD

class TickInfo
{
public:
    TickInfo(){};
    ~TickInfo(){};
    
    code code;
    date date;
    double open;
    double high;
    double low;
    double close;
};