#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

class Fileaccess {
public:
  Fileaccess();
  void reset();
  void set_mode(string);
  void set_waterlvl(int);
  void log(string);
  vector<string> getQueue();
private:
  string path;
};
