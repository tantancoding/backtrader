#pragma once
#include <define.h>
#include <data_types.h>
#include <context.h>

class Strategy
{
public:
    Strategy(){};
    ~Strategy(){};

    void init();
    void on_trade();
    void on_tick(TickInfo* tick);
    void on_order();

    void try_buy(double price, int volume);
    void try_sell(double price, int volume);

public:
    Context* context;


private:
    code _code;
    
};