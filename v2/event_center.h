#pragma once
#include <define.h>
#include <data_types.h>

enum EventType
{
    ET_ORDER,
    ET_TICK,
    ET_DEAL,
    ET_ERROR
};

class Event
{
public:
    Event(){};
    ~Event(){};

    EventType type;
    date data;
};

class OrderEvent : public Event
{
public:
    OrderEvent() {type = ET_ORDER;};
    ~OrderEvent(){};

private:
    
    code _code;
    double _price;
    int _volume;
    bool _direction;    // 1: buy, 0: sell
};

class TickEvent : public Event
{
public:
    TickEvent() { type = ET_TICK; };
    ~TickEvent(){};

    void set_data(TickInfo& tick)
    {
        _tick = tick;
    }

    TickInfo get_data()
    {
        return _tick;
    }

private:
    TickInfo _tick;
};

class DealEvent : public Event
{
public:
    DealEvent() { type = ET_DEAL;};

    ~DealEvent(){};

private:
    code _code;
    date _date;
};

class ErrorEvent : public Event
{
public:
    ErrorEvent(){ type = ET_ERROR;};
    ~ErrorEvent(){};

private:
    std::string _error;
};

using Handler = std::function<void(Event*)>;

class EventManager
{
public:
    EventManager(){};
    ~EventManager(){};

    void add_event(Event* event)
    {
        _events.push(event);
    }

    void register_handler(EventType type, Handler handler)
    {
        _handlers[type].push_back(handler);
    }

    // 触发事件
    void trigger_event()
    {
        while(!_events.empty())
        {
            Event* event = _events.front();
            _events.pop();

            for(auto handler : _handlers[event->type])
            {
                handler(event);
            }
        }
    }

private:
    std::map<EventType, std::vector<Handler>> _handlers;
    std::queue<Event*> _events;
    
};