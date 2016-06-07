#ifndef RPSW_ALARM_OBJECT_H
#define RPSW_ALARM_OBJECT_H

#include <string>

enum alarm_level_e
{
    alarm_unknown = 0,
    alarm_warning = 1,
    alarm_minor = 2,
    alarm_major = 3,
    alarm_critical = 4,
    alarm_max,
};

class rpsw_alarm_obj
{
    public:
        rpsw_alarm_obj(const std::string& src);
        rpsw_alarm_obj(const std::string& s, alarm_level_e l, int32_t v);
        std::string to_json();

    private:
        alarm_level_e _level;
        std::string _source;
        int32_t _value;

    private:
        std::string get_alarm_level(alarm_level_e l);
};

#endif //#ifndef RPSW_ALARM_OBJECT_H
