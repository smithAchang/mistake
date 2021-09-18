#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <unordered_map>
using namespace std;

#define USEC_UNIT (1000000)

#ifndef MAX_ITEM
 #define MAX_ITEM  (10000000)
#endif

//global var
int g_Pool[MAX_ITEM];

#ifdef USE_MAP
 typedef unordered_map<int,int> TESTMAP;
 typedef pair<int,int> TESTMAP_ITEM;
 typedef unordered_map<int,int>::const_iterator TESTMAP_CONST_ITERATOR;
 TESTMAP g_Map;
#endif

int main(void)
{
  struct timeval tv_begin, tv_end;
  int sum = 0,index = 0;

  #ifdef USE_MAP
   const char TEST_CASE_NAME[] = "Test with hash map";
   g_Map.reserve(MAX_ITEM);
   for(int i=0;i < MAX_ITEM;++i)
   {
     g_Map.insert(TESTMAP_ITEM(i,i));
   }

  #else
   const char TEST_CASE_NAME[] = "Test without hashmap";
  #endif

  printf("%s overhead using para:\n|--max pool items:%d", TEST_CASE_NAME,  MAX_ITEM);
  
  
  gettimeofday(&tv_begin, NULL);

  for(int i = 0; i < MAX_ITEM; ++i)
  {

    #ifdef USE_MAP
     TESTMAP_CONST_ITERATOR cit   = g_Map.find(i);     
     if(cit != g_Map.end())
     {
      index = cit->second;	    
     }
     else
     {
      index = 0;
     }
   #else
     index = i & 0xFFFFFFFF; //32bits as the quick design
   #endif

    //simulate function const using read operation
   sum += g_Pool[index];
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
