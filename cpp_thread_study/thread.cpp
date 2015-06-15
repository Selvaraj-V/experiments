#include <thread>
#include <chrono>
#include <iostream>
#include <mutex>
#include <vector>
#include <cstring>
#include <pthread.h>

void function_1(void)
{
  int test(5);

  while (test--){
      std::this_thread::sleep_for(std::chrono::seconds(2));
      std::cout << std::this_thread::get_id() << std::endl;
  }
}

void function_2(void)
{
  int test(2);

  while (test--){
      std::this_thread::sleep_for(std::chrono::seconds(5));
      std::cout << std::this_thread::get_id() << std::endl;
  }
}

void terminate_handler(void)
{
    std::cout << "terminate called " << std::endl;
}

void test_1(void)
{
    std::set_terminate(terminate_handler);

    std::thread my_thread(function_1);
    std::thread my_thread_2(function_2);

    my_thread.detach();

    std::cout << "before joining " <<std::endl;
    //my_thread.join();

    std::cout << "after joining " <<std::endl;
    my_thread_2.join();
    std::cout << "exit" <<std::endl;
}

void test_2(void)
{
    std::set_terminate(terminate_handler);

    std::thread *pthread = new std::thread(function_1);
    std::thread *pthread_2 = new std::thread(function_2);

    pthread->detach();
    pthread_2->detach();

    std::this_thread::sleep_for(std::chrono::seconds(5));
    delete pthread;
    delete pthread_2;

    std::cout << "exit" <<std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(15));
}

std::mutex iomutex;

void function_3(int num)
{
  std::this_thread::sleep_for(std::chrono::seconds(1));

  sched_param sch;
  int policy; 
  pthread_getschedparam(pthread_self(), &policy, &sch);
  std::lock_guard<std::mutex> lk(iomutex);
  std::cout << "Thread " << num << " is executing at priority "
    << sch.sched_priority << '\n';

  sch.sched_priority = 4 ;
  pthread_setschedparam(pthread_self(), SCHED_RR, &sch); 
  std::cout << "Thread " << num << " is executing at priority "
    << sch.sched_priority << '\n';
}

void function_4(int num)
{
  std::this_thread::sleep_for(std::chrono::seconds(1));

  sched_param sch;
  int policy; 
  pthread_getschedparam(pthread_self(), &policy, &sch);
  std::lock_guard<std::mutex> lk(iomutex);
  std::cout << "Thread " << num << " is executing at priority "
    << sch.sched_priority << '\n';

}


void test_3(void)
{
  std::thread *pthread = new std::thread(function_3,1);
  std::thread *pthread_2 = new std::thread(function_4,2);

  pthread->detach();
  pthread_2->detach();

  std::this_thread::sleep_for(std::chrono::seconds(15));

  delete pthread;
  delete pthread_2;

  {
    int num = 0;
    sched_param sch;
    int policy; 
    pthread_getschedparam(pthread_self(), &policy, &sch);
    std::lock_guard<std::mutex> lk(iomutex);
    std::cout << "Thread " << num << " is executing at priority "
      << sch.sched_priority << '\n';
  } 

  std::cout << "exit" <<std::endl;
}

class test {

    public : 
        void set_thread_func(int num)
        {
          std::this_thread::sleep_for(std::chrono::seconds(1));

          sched_param sch;
          int policy; 
          pthread_getschedparam(pthread_self(), &policy, &sch);
          std::lock_guard<std::mutex> lk(iomutex);
          std::cout << "Thread " << num << " is executing at priority "
            << sch.sched_priority << '\n';

        }
};


void set_thread_func(int num)
{
  std::this_thread::sleep_for(std::chrono::seconds(1));

  sched_param sch;
  int policy; 

  pthread_getschedparam(pthread_self(), &policy, &sch);
  std::lock_guard<std::mutex> lk(iomutex);
  std::cout << "Thread " << num << " is executing at priority "
    << sch.sched_priority << '\n';
#if 0
  sch.sched_priority = 4 ;
  if(pthread_setschedparam(pthread_self(), policy, &sch))
  {
    std::cout << "Failed to setschedparam: " << std::strerror(errno) << '\n';
  }

  memset(&sch,sizeof (sch), 0);

  if(pthread_getschedparam(pthread_self(), &policy, &sch))
  {
    std::cout << "Failed to setschedparam: " << std::strerror(errno) << '\n';
  }

  std::cout << "Thread " << num << " priority is "
    << sch.sched_priority << '\n';
#endif

  std::this_thread::sleep_for(std::chrono::seconds(1));
}

void test_4(void)
{
  std::cout << SCHED_OTHER << "\n";
  std::cout << SCHED_BATCH << "\n";
  std::cout << SCHED_IDLE << "\n";
  std::cout << SCHED_RR << "\n";
  std::cout << SCHED_FIFO << "\n";

  std::cout << sched_get_priority_max(SCHED_OTHER) << "\n";
  std::cout << sched_get_priority_min(SCHED_OTHER) << "\n";

  std::cout << sched_get_priority_max(SCHED_BATCH) << "\n";
  std::cout << sched_get_priority_min(SCHED_BATCH) << "\n";

  std::cout << sched_get_priority_max(SCHED_IDLE) << "\n";
  std::cout << sched_get_priority_min(SCHED_IDLE) << "\n";

  std::cout << sched_get_priority_max(SCHED_RR) << "\n";
  std::cout << sched_get_priority_min(SCHED_RR) << "\n";

  std::cout << sched_get_priority_max(SCHED_FIFO) << "\n";
  std::cout << sched_get_priority_min(SCHED_FIFO) << "\n";


  std::vector<std::thread> thread_list ;

  std::thread t1(set_thread_func, 1), t2(set_thread_func, 2);

  sched_param sch;
  int policy; 
  pthread_getschedparam(t1.native_handle(), &policy, &sch);
  sch.sched_priority = 20;
  if(pthread_setschedparam(t1.native_handle(), SCHED_FIFO, &sch)) {
      std::cout << "Failed to setschedparam: " << std::strerror(errno) << '\n';
  }

  t1.join(); t2.join();

  /*
    for ( int i = 0; i < 3; i++ ) {
    thread_list.push_back(std::thread(set_thread_func,i));
    }

    for ( std::vector<std::thread>::iterator it = thread_list.begin() ;
    it < thread_list.end() ;
    it++ ) {
    it->join();
    }

    for ( std::vector<std::thread>::iterator it = thread_list.begin() ;
    it < thread_list.end() ;
    it++ ) {
    thread_list.pop_back();
    }
    */
  std::cout << "exit" <<std::endl;
}


int main (int argc , char * argv[])
{
  //test_1();
  //test_2();
  //test_3();
  test_4();
}
