#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <osapi/Thread.hpp>
#include <osapi/ThreadFunctor.hpp>
#include <osapi/Utility.hpp>
#include <osapi/Mutex.hpp>

#define BUFFER_LENGTH 8


osapi::Mutex mut;


class spi_req_function : public osapi::ThreadFunctor{

public:
  spi_req_function(){}

private:
  void run(){

    while(1){

      unsigned int data;
      FILE * fp;
      fp = fopen("/dev/spi_drv0","r");

      fscanf(fp,"%d",&data);
      mut.lock();

      switch (data) {
        case 'a':
          unsigned int x,y;
          std::cout << "due skudt" << '\n';
          freopen("/dev/spi_drv0","r", fp);
          fscanf(fp,"%d",&x);//Her læses ingen værdi ud,
          freopen("/dev/spi_drv0","r", fp);
          fscanf(fp,"%d",&y);//og ventes ikke på interrupt

          std::cout << "Duens position var X:" << x << " Y:" << y << '\n';
          break;
        case 'b':
          std::cout << " due detekteret " << '\n';
          break;
        case 'c':
          std::cout << "lavt vand" << '\n';
          break;
        case 'd':
          std::cout << "vand tømt" << '\n';
          break;
        case 'e':
          std::cout << "blomster vandet" << '\n';
          break;
        default:
          std::cout << "message from PSoC was misunderstood" << '\n';
          std::cout << data << std::endl;
          break;
      }
      fclose(fp);
      mut.unlock();
    }
  }

};

class main_thread : public osapi::ThreadFunctor{

public:
  main_thread(){

  }
private:
  void run(){
    FILE * fp;
    char data; //<------- Issues heropene, no way to send over an integer over 9.

    while(1){
      std::cout<<"run 1"<<std::endl;
      mut.lock();
      fp = fopen("/dev/spi_drv0","w");
      std::cout<<"run 2"<<std::endl;
      std::cout << "in main_thread" << '\n';
      std::cout<<"run 3"<<std::endl;
      std::cout<<"run 4"<<std::endl;
      std::cout<<"run 5"<<std::endl;
      std::cout << "read request from user, write an int" << '\n';
      std::cout<<"run 6"<<std::endl;
      std::cin >> data;
      std::cout<<"run 7"<<std::endl;
      std::cout << "writing " << data << " to PSoC over SPI" << '\n';
      std::cout<<"run 8"<<std::endl;
      int err = fputc((int)data, fp);
      std::cout<<"run 9"<<std::endl;
      std::cout << "data written" << '\n';
      std::cout<<"run 10"<<std::endl;
      fclose(fp);
      mut.unlock();
      std::cout<<"run done"<<std::endl;
      std::cout << "sleep startet" << '\n';
      osapi::sleep(5000);
      std::cout << "sleep ended" << '\n';
      std::cout<< err <<std::endl;
    }
  }

};

int main()
{
  try
{


  spi_req_function spi_req_f;
  //main_thread main_f;

  osapi::Thread p(&spi_req_f);
  //osapi::Thread t(&main_f);

  p.start();
  //t.start();

  p.join();
  //t.join();
}
catch (std::exception& e)
{
  std::cout<<"error found: " << e.what() << '\n';
}


  return 0;
}
