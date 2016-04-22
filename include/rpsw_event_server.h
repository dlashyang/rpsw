#ifndef RPSW_EVENT_SERVER_H
#define RPSW_EVENT_SERVER_H

class rpsw_event_server
{
    public:
        virtual ~rpsw_event_server() {};
        virtual int init()=0;
        virtual void start()=0;
        virtual void stop()=0;
};

class rpsw_server_factory
{
    public:
        virtual rpsw_event_server* create_server()=0;
};

#endif//#ifndef RPSW_EVENT_SERVER_H
