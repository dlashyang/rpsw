#include "rpsw_alarm_object.h"
#include "Poco/JSON/Object.h"

rpsw_alarm_obj::rpsw_alarm_obj(const std::string& src):
    _level(alarm_unknown), _source(src), _value(0)
{
}

rpsw_alarm_obj::rpsw_alarm_obj(const std::string& s, alarm_level_e l, int32_t v):
    _level(l), _source(s), _value(v)
{
}

std::string rpsw_alarm_obj::to_json()
{
    Poco::JSON::Object alarm(true);
    alarm.set("level", get_alarm_level(_level).c_str());

    Poco::JSON::Object alarm_detail(true);
    alarm_detail.set("source", _source.c_str());
    alarm_detail.set("readout", _value);
    alarm.set("detail", alarm_detail);

    std::ostringstream output;
    alarm.stringify(output);
    std::cout<<output.str()<<std::endl;

    return output.str();
}

std::string rpsw_alarm_obj::get_alarm_level(alarm_level_e l)
{
    static std::string map[alarm_max] = {
        "alarm_unknown",
        "alarm_warning",
        "alarm_minor",
        "alarm_major",
        "alarm_critical",
    };

    return map[l];
}
