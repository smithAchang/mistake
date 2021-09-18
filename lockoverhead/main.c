#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define USEC_UNIT (1000000)

#ifndef MAX_LOOP
 #define MAX_LOOP  (1000000)
#endif

#ifndef  SIMULATE_OPERS
 #define SIMULATE_OPERS 128
#endif

// global vars
unsigned char ReadWriteBuf[SIMULATE_OPERS];

int main(void)
{
  struct timeval tv_begin, tv_end;
  int sum = 0;
  
  #ifdef USE_LOCK
   const char TEST_CASE_NAME[] = "Test with lock";
   pthread_mutex_t mutex;
   pthread_mutex_init(&mutex, NULL);
  #else
   const char TEST_CASE_NAME[] = "Test without lock";
  #endif

  printf("%s overhead using para:\n|--max loop:%d\n|--simulate operations:%d\n", TEST_CASE_NAME,  MAX_LOOP, SIMULATE_OPERS);
  
  
  gettimeofday(&tv_begin, NULL);

  for(int i = 0; i < MAX_LOOP; ++i)
  {

    #ifdef USE_LOCK
     pthread_mutex_lock(&mutex);
    #endif

    //simulate function const using read operation
    for(int j = 0;j < SIMULATE_OPERS; ++j)
    {
       sum += ReadWriteBuf[j];
    }
    
    //simulate function const using write operation
    for(int j = 0; j < SIMULATE_OPERS; ++j)
    {
       ReadWriteBuf[j] = j;
    }
    
    #ifdef USE_LOCK
     pthread_mutex_unlock(&mutex);
    #endif
  }

  gettimeofday(&tv_end, NULL);
  
  //calc time cost
  long int tv_sec, tv_usec;
  tv_sec      = (tv_end.tv_sec  - tv_begin.tv_sec) * USEC_UNIT;
  tv_usec     = tv_end.tv_usec  - tv_begin.tv_usec;
  double diff = (double)(tv_sec + tv_usec) / USEC_UNIT;

  
  printf("\n**************************************\n");
  #ifdef USE_LOCK
   printf("\nuse lock Time eclipsed,sec:%lf\n",diff);
   pthread_mutex_destroy(&mutex);
  #else
   printf("\nTime eclipsed,sec:%lf\n",diff);
  #endif

  return 0;
}
