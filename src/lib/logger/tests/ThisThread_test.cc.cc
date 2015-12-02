
#include <thread>
#include <iostream>
#include <functional>

#include <Logger/ThisThread.h>

void my_thread()
{
  printf("%d\n", sugen::ThisThread::getId());
  printf("%d\n", getpid());
}

int main(int argc, char *argv[])
{
  printf("%d %s\n", sugen::ThisThread::getId(), strerror(errno));
  printf("%d\n", getpid());

  std::thread t1(my_thread), t2(my_thread);
  t1.join();
  t2.join();
  return 0;
}