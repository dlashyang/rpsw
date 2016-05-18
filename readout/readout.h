#ifndef READOUT_H
#define READOUT_H

#include <stdint.h>
#include <cstddef>
#include <list>

class readout
{
    private:
        inline bool _has_acceptable_roc(int32_t v1, int32_t v2);
        int32_t _push_data(int32_t v);
        int32_t _update_flag(bool f);
        bool _test_flag_any() const;

    public:
        readout(size_t size): _size(size) {};
        int32_t get_value(int32_t& value) const;
        int32_t get_value() const;
        int32_t set_value(int32_t value);

    private:
        size_t _size;
        std::list<int32_t> _raw_data;
        std::list<bool> _flag;
};
#endif //#ifndef READOUT_H
