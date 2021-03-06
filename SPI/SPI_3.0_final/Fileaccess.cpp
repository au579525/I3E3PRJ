#include "Fileaccess.hpp"

Fileaccess::Fileaccess(){
    ifstream pathsettings;

    pathsettings.open("path.txt");
    //check if file is open
    if(pathsettings.is_open()){
      string line;
      getline(pathsettings,path);
    }
    //if file doesnt open use standard path
    else{
      ofstream pathsettings;
      pathsettings.open("path.txt", ios::trunc);
      pathsettings << "/opt/pigeon/";
      path = "/opt/pigeon/";
    }
    reset();
}

void Fileaccess::reset(){
  ofstream mode;
  ofstream log;
  ofstream queue;
  ofstream waterLevel;
  mode.open(path + "systemmode", ios::trunc);
  mode << "normal";
  log.open(path + "log", ios::trunc);
  queue.open(path + "queue", ios::trunc);
  waterLevel.open(path + "waterlevel", ios::trunc);
  waterLevel << "1";
}

void Fileaccess::set_waterlvl(int lvl){
    ofstream file;
    file.open(path + "waterlevel", ios::trunc);
    if(lvl == 0){
      set_mode("standby");
      log("Waterlevel too low!");
    }
    if(file.is_open()){
      file << lvl;
    }
}

void Fileaccess::set_mode(string mode){
     ofstream file;
     file.open(path + "systemmode", ios::trunc);
     if(file.is_open()){
       file << mode;
     }
     log("Systemmode changed to: " + mode);
}

void Fileaccess::log(string message){
      ofstream file;
      file.open(path + "log", ios::app);
      char timestring[1000];
      time_t t = time(NULL);
      struct tm * p = localtime(&t);
      strftime(timestring, 1000, "%D, %R", p);
      if(file.is_open()){
        file << timestring << ": " << message << endl;
      }
}

vector<string> Fileaccess::getQueue(){
    vector<string> queue;
    ifstream file;
    file.open(path + "queue");
    for(string line; getline(file, line);){
      queue.push_back(line);
    }
    file.close();
    ofstream filedl;
    filedl.open(path + "queue", ios::trunc);
    filedl.close();
    return queue;
}
