#include <stdio.h>
#include <iostream>

#include <osapi/Thread.hpp>
#include <osapi/ThreadFunctor.hpp>
#include <osapi/Utility.hpp>
#include <osapi/Mutex.hpp>

osapi::Mutex mut;

FILE * SPI_driver;

class spi_req_function : public osapi::ThreadFunctor{

public:
  spi_req_function(){}

private:
  void run(){

    while(1){

      std::cout << "in spi_req_function" << '\n';
      uint8_t data;
      uint8_t * dataptr = &data;
      int err;

      mut.lock();
      SPI_driver = fopen("/dev/spi_drv0","r");
      err = fread(dataptr,1,1, SPI_driver);
      //data = fgetc(SPI_driver);
      switch (data) {
        case 1:
          uint8_t x,y;
          std::cout << "due skudt" << '\n';
          err = fread(&x,1,1, SPI_driver);
          err = fread(&y,1,1, SPI_driver);
          std::cout << "Duens position var X:" << x << " Y:" << y << '\n';
          break;
        case 2:
          std::cout << " due detekteret " << '\n';
          break;
        case 3:
          std::cout << "lavt vand" << '\n';
          break;
        case 4:
          std::cout << "vand tømt" << '\n';
          break;
        case 5:
          std::cout << "blomster vandet" << '\n';
          break;
        default:
          std::cout << "message from PSoC was misunderstood" << '\n';
          std::cout << data << std::endl;
          break;
      }
      std::cout << err << std::endl;
      fclose(SPI_driver);
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
    uint8_t data;
    uint8_t * dataptr = &data;
    while(1){
      std::cout<<"run 1"<<std::endl;
      mut.lock();
      SPI_driver = fopen("/dev/spi_drv0","a");
      std::cout<<"run 2"<<std::endl;
      std::cout << "in main_thread" << '\n';
      std::cout<<"run 3"<<std::endl;
      std::cout<<"run 4"<<std::endl;
      std::cout<<"run 5"<<std::endl;
      std::cout << "read request from user, write an int" << '\n';
      std::cout<<"run 6"<<std::endl;                                 //error occures at line 79, when trying to use input stream and inserting data
      std::cin >> data;
      std::cout<<"run 7"<<std::endl;
      std::cout << "writing " << data << " to PSoC over SPI" << '\n';
      std::cout<<"run 8"<<std::endl;
      int err = fwrite(dataptr,1,1,SPI_driver);
      std::cout<<"run 9"<<std::endl;
      std::cout << "data written" << '\n';
      std::cout<<"run 10"<<std::endl;
      fclose(SPI_driver);
      mut.unlock();
      std::cout<<"run done"<<std::endl;
      std::cout<< err <<std::endl;
    }
  }

};

int main()
{
  try
{

  spi_req_function spi_req_f;
  main_thread main_f;

  osapi::Thread p(&spi_req_f);
  osapi::Thread t(&main_f);

  p.start();
  t.start();

  p.join();
  t.join();
}
catch (std::exception& e)
{
  std::cout<<"error found: " << e.what() << '\n';
}


  return 0;
}
