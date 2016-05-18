#include <limits>

#include "readout.h"

int32_t readout::get_value(int32_t& value) const
{
    int32_t ret = -1;
    value = 0;

    if (_test_flag_any()) {
        value = _raw_data.front();
        ret = 0;
    }

    return ret;
}

int32_t readout::get_value() const
{
    int32_t value = std::numeric_limits<int32_t>::max();

    if (_test_flag_any()) {
        value = _raw_data.front();
    }

    return value;
}

int32_t readout::set_value(int32_t value)
{
    if (_has_acceptable_roc(value, _raw_data.front())) {
        _update_flag(true);
    } else {
        _update_flag(false);
    }

    _push_data(value);

    return 0;
}

bool readout::_has_acceptable_roc(int32_t v1, int32_t v2)
{
    if (v1 > v2) {
        return ( (2*(v1-v2)) <= v2);
    } else {
        return ( (2*(v2-v1)) <= v2);
    }
}

int32_t readout::_push_data(int32_t v)
{
    _raw_data.push_front(v);

    while (_raw_data.size() > _size) {
        _raw_data.pop_back();
    }

    return 0;
}

int32_t readout::_update_flag(bool f)
{
    _flag.push_front(f);

    while (_flag.size() > _size-1) {
        _flag.pop_back();
    }

    return 0;
}

bool readout::_test_flag_any() const
{
    bool ret = true;

    for (std::list<bool>::const_iterator it = _flag.begin();
            it != _flag.end(); ++it) {
        if (*it == false) {
            ret = false;
            break;
        }
    }

    return ret;
}
