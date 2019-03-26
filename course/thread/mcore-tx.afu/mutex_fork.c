/**
 * 
 * 父子进程互斥锁
 * 
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> 

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main(void) {//2¸ö½ø³Ì£¬Ò»¸ö½ø³ÌÍê³ÉÃ¿´Î¼Ó1,ÁíÒ»¸ö½ø³ÌÍê³ÉÃ¿´Î¼Ó2,2¸ö½ø³ÌÐ­×÷Íê³ÉÀÛ¼Ó,Ê¹ÓÃ¹²ÏíÄÚ´æ·½Ê½ÔÚ½ø³Ì¼äÍ¨ÐÅ    
   int *x;    
   int rt;    
   int shm_id;    
   char *addnum="myadd";    
   char *ptr;    
      
   pthread_mutex_t mutex;//»¥³â¶ÔÏó    
   pthread_mutexattr_t mutexattr;//»¥³â¶ÔÏóÊôÐÔ    
    
   pthread_mutexattr_init(&mutexattr);//³õÊ¼»¯»¥³â¶ÔÏóÊôÐÔ    
   pthread_mutexattr_setpshared(&mutexattr,PTHREAD_PROCESS_SHARED);//ÉèÖÃ»¥³â¶ÔÏóÎªPTHREAD_PROCESS_SHARED¹²Ïí£¬¼´¿ÉÒÔÔÚ¶à¸ö½ø³ÌµÄÏß³Ì·ÃÎÊ,PTHREAD_PROCESS_PRIVATEÎªÍ¬Ò»½ø³ÌµÄÏß³Ì¹²Ïí    
   rt=fork();//¸´ÖÆ¸¸½ø³Ì£¬²¢´´½¨×Ó½ø³Ì     
//deepfuture.javaeye.com£¬ÉîÎ´À´¼¼ÊõÔ­´´    
   if (rt==0){//×Ó½ø³ÌÍê³Éx+1    
       shm_id=shm_open(addnum,O_RDWR,0);    
       ptr=mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,shm_id,0);/*Á¬½Ó¹²ÏíÄÚ´æÇø*/    
       x=(int *)ptr;      
      
      for (int i=0;i<10;i++){//¼Ó10´Î¡£Ïàµ±ÓÚ¼Ó10    
         pthread_mutex_lock(&mutex);          
         (*x)++;    
         printf("x++:%d/n",*x);    
         pthread_mutex_unlock(&mutex);     
         sleep(1);                     
      }    
   }       
   else {//¸¸½ø³ÌÍê³Éx+2    
       shm_id=shm_open(addnum,O_RDWR|O_CREAT,0644);    
        ftruncate(shm_id,sizeof(int));    
        ptr=mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,shm_id,0);/*Á¬½Ó¹²ÏíÄÚ´æÇø*/    
        x=(int *)ptr;     
              
      for (int i=0;i<10;i++){//¼Ó10´Î£¬Ïàµ±ÓÚ¼Ó20    
         pthread_mutex_lock(&mutex);           
         (*x)+=2;    
         printf("x+=2:%d/n",*x);    
         pthread_mutex_unlock(&mutex);      
         sleep(1);     
      }
   }     
   shm_unlink(addnum);//É¾³ý¹²ÏíÃû³Æ    
   munmap(ptr,sizeof(int));//É¾³ý¹²ÏíÄÚ´æ    
   return(0);    
}   