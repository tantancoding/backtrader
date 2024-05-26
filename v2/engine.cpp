#pragma once
#include "engine.h"

void Engine::init_engine()
{
    _market->load_data();
}

void Engine::run()
{
    while(!_market->is_finished())
    {
        _market->publish_tick();
        _event_manager->trigger_event();
    }
}