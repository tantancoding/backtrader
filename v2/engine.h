#pragma once
#include <define.h>
#include <data_types.h>
#include <event_center.h>
#include <market.h>
#include <strategy.h>

class Engine
{
public:
    Engine(Market* market, Strategy* strategy, EventManager* event_manager):
    _market(market), _strategy(strategy), _event_manager(event_manager){};
    ~Engine(){};

    void init_engine();
    void run();

private:
    Market* _market;
    Strategy* _strategy;
    EventManager* _event_manager;

};