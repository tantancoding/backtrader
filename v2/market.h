#pragma once
#include <define.h>
#include <data_types.h>
#include <event_center.h>

class Market
{
public:
    Market(EventManager){};
    ~Market(){};

    void init_market(code _code);

    void load_data();
    void publish_tick(); 
    TickInfo* get_next_tick();

    bool is_finished()
    {
        return _is_finished;
    }

private:
    bool _is_finished = false;
    int _current_tick = -1; // 为了方便统一在get_next_tick获取第一个tick
    EventManager* _event_manager;
    code _code;
    std::vector<TickInfo*> _pending_ticks;
};