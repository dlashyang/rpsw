#ifndef RPSW_ALARM_SENDER_H
#define RPSW_ALARM_SENDER_H

#include <string>
#include <memory>

class rpsw_alarm_sender
{
    public:
        virtual ~rpsw_alarm_sender() {};

        virtual int send(const std::string& msg)=0;
};

typedef std::auto_ptr<rpsw_alarm_sender> alarm_sender_t;
class rpsw_sender_factory
{
    public:
        virtual alarm_sender_t create_sender()=0;
};

#endif //#ifndef RPSW_ALARM_SENDER_H
