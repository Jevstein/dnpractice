
#ifndef MUTIPROCESS_SHM_DATA_H__
#define MUTIPROCESS_SHM_DATA_H__


#define MAX_MSG_SIZE  1024
#define SHARED_BUFFER_KEY 1234
#define SEM_KEY   5678

struct shared_buffer_t
{
    int written;  /* 标志，0 ： 可写， 非0：可读 */
    char buffer[MAX_MSG_SIZE];
};


union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *arry;
};


#endif
