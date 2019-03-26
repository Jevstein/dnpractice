
/**
 * 
 * 累加测试
 * 
*/
/*�����̣߳�ÿ���߳��ۼ�500���*/
#include <stdio.h>
#include <pthread.h>

#define MAX_NUM 5000000

int num = 0;  //����1  5315953
//volatile int num = 0;  //����2  5431651

void* thread_func(void* param)
{
  for (int i=0; i<MAX_NUM; ++i)
  {
    //__sync_synchronize();  ����3  7443185
    ++num;
    //__sync_add_and_fetch(&num, 1);  ����4  10000000
  }
  return NULL;
}

int main()
{
  pthread_t t1, t2;
  pthread_create(&t1, NULL, thread_func, NULL);
  pthread_create(&t2, NULL, thread_func, NULL);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  printf("%d\n", num);
  return 1;
}

