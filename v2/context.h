#include "define.h"
#include "data_types.h"

class Context
{
public:
    Context(){};
    ~Context(){};

    void init_context();

    int get_position() { return _position; }
    int set_position(int position) { _position = position; }
    double get_cash() { return _cash; }
    double set_cash(double cash) { _cash = cash; }


private:
    date _current_date;
    date _begin_date;
    date _end_date;
    code _code;
    double _cash;
    int _position;
};