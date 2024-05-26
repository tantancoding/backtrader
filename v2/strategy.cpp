#include "strategy.h"

void Strategy::try_buy(double price, int volume)
{
    double cost = price * volume;
    if (cost > context->get_cash())
    {
        volume = context->get_cash() / price;
    }
    context->set_cash(context->get_cash() - price);
    context->set_position(context->get_position() + volume);

}

void Strategy::try_sell(double price, int volume)
{
    if (volume > context->get_position())
    {
        volume = context->get_position();
    }
    context->set_cash(context->get_cash() + price * volume);
    context->set_position(context->get_position() - volume);
}



void Strategy::on_tick(TickInfo* tick)
{
    // 计算信号

    // 生成信号事件


    cal_single_ma();
    // do something
}

void Strategy::on_order