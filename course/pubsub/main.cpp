

#include <stdio.h>
#include <unistd.h>

#include "events_def.h"
#include "DispatchMsgService.h"
#include "LoginEventHandler.h"

class user
{
public:
    bool login()
    {
        printf("try to login.\n");
        
        char msg[] = "{\"cmd\":\"login\",\"sn\":1,\"name\":\"pan jinlian\",\"password\":\"xiao neiku\"}";
        LoginEvent* ev = new LoginEvent(msg);
        ev->decode();

        dms->publish(ev);
        
        return true;
    }
    
    user()
    {
    
    }
    
    virtual ~user(){};
};

int main(int argc, char** argv)
{
    dms->init();
    
    LoginEventHandler handler;
    handler.init();
    
    user panjinlian;
    panjinlian.login();
    
    for(;;)
    {
        sleep(1);
    }

    return 0;
}

