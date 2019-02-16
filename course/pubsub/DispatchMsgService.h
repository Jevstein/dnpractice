

#ifndef NS_DISPATCH_MSG_SERVICE_H_
#define NS_DISPATCH_MSG_SERVICE_H_

#include <map>
#include <vector>

#include <pthread.h>

#include "event.h"
#include "eventid.h"
#include "MsgQueue.h"
#include "iEventHandler.h"

class DispatchMsgService
{   
    public:
        static DispatchMsgService* getInstance(){ return &instance_; };

        virtual bool init();
        virtual bool uninit();

        virtual bool subscribe(u16 eid, iEventHandler* handler);
        virtual bool unsubscribe(u16 eid, iEventHandler* handler);
        virtual bool publish(iEvent* ev);
        
    protected:
        DispatchMsgService();
        virtual ~DispatchMsgService();

    protected:
        static void* svc(void *);
        virtual bool process(const iEvent* ev);

        typedef std::vector<iEventHandler*> T_EventHandlers;
        typedef std::map<u16, T_EventHandlers > T_EventHandlersMap;
        T_EventHandlersMap subscribers_;
        PosixQueue<iEvent> msg_queue_;
        bool svr_exit_;
    
    private:
        pthread_t thread_hdl_;
        
        static DispatchMsgService instance_;
};

#define dms DispatchMsgService::getInstance()

#endif

