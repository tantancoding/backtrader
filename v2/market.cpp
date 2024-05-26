#pragma once
#include <market.h>
#include <fstream>

std::vector<TickInfo*> read_csv(std::string path)
{
    std::vector<TickInfo*> ticks;
    std::vector<std::string> tick_line;
    std::ifstream file(path);
    std::string line;
    while(std::getline(file, line))
    {
        // 解析一行
        std::istringstream ss(line);
        std::string token;
        while(std::getline(ss, token, ','))
        {
            tick_line.push_back(token);
        }
        
        TickInfo* tick = new TickInfo();
        tick->date = tick_line[0];
        tick->code = tick_line[1];
        tick->open = std::stod(tick_line[2]);
        tick->high = std::stod(tick_line[3]);
        tick->low = std::stod(tick_line[4]);
        tick->close = std::stod(tick_line[5]);
        
        ticks.push_back(tick);
    }
    return ticks;
}

void Market::load_data()
{
    std::string path = "./data/" + _code + ".csv";
    _pending_ticks = read_csv(path);
}

TickInfo* Market::get_next_tick()
{
    if(_current_tick < _pending_ticks.size())
    {
        return _pending_ticks[_current_tick++];
    }
    else
    {
        _is_finished = true;
        return nullptr;
    }
}

void Market::publish_tick()
{
    TickInfo* tick = get_next_tick();
    if(tick != nullptr)
    {
        TickEvent* tick_event = new TickEvent();
        tick_event->set_data(*tick);
        _event_manager->add_event(tick_event);
    }
}