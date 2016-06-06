#ifndef RPSW_EVENT_SERVER_H
#define RPSW_EVENT_SERVER_H

#include <memory>

class rpsw_event_server
{
    public:
        virtual ~rpsw_event_server() {};
        virtual int init()=0;
        virtual void start()=0;
        virtual void stop()=0;
};

typedef std::auto_ptr<rpsw_event_server> evnt_srv_t;
class rpsw_server_factory
{
    public:
        virtual evnt_srv_t create_server()=0;
};

#endif//#ifndef RPSW_EVENT_SERVER_H
