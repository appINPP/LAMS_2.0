#ifndef DataGrabber_hh
#define DataGrabber_hh

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Slices.hh" //0-Level header


/*
  The purpose of this file is to draw the data from the txt files
*/


class DataGrabber{
private:
  unsigned short intensity1, intensity2;
  unsigned short temperByte1, temperByte2, pressure;
  double temperature, time;
  unsigned long long counter;

  unsigned long long fileSize; //This is used with c++ tellg() function, hence the type <long long int>
  std::string associatedName;
  std::ifstream binaryFile;
  
public:
  DataGrabber(){
    associatedName = "";
    fileSize = 0;
  }
  ~DataGrabber(){
    binaryFile.close();
  }
  
  bool Open(std::string fileName);

  bool Prepare(std::vector < Slice> &data);
  bool Prepare_Test(std::vector < Slice> &data);
  bool Prepare_Old(std::vector < Slice> &data);
  
  bool Fill(std::vector < Slice> &data);
  bool Fill_Test(std::vector < Slice> &data);
  bool Fill_Old(std::vector < Slice> &data, unsigned long long &counter);

  unsigned long long Size() {return fileSize;}


};



bool DataGrabber::Open(std::string fileName){
  long bytePosition = 0;
  if (associatedName != fileName){
    binaryFile.close();
    binaryFile.open(fileName.c_str(), std::ios::binary | std::ios::ate);
    if (binaryFile.is_open()){
      associatedName = fileName;
      bytePosition = binaryFile.tellg();
      if (bytePosition >= 0){
	fileSize = bytePosition;
      }
      binaryFile.seekg(0);
      return true;
    }
    else return false;
  }
  else{
    if (binaryFile.is_open()) return true;
    else return false;
  }
}


bool DataGrabber::Prepare(std::vector < Slice> &data) {
  if (fileSize != 0){
    data.clear();
    data.resize(fileSize/8);
    return true;
  }
  return false;
}

bool DataGrabber::Prepare_Test(std::vector < Slice > &data) {
  if (fileSize != 0){
    data.clear();
    data.resize(fileSize/14);
    return true;
  }
  return false;
}

bool DataGrabber::Prepare_Old(std::vector < Slice > &data) {
  if (fileSize != 0){
    data.clear();
    data.resize(fileSize/12);
    return true;
  }
  return false;
}


bool DataGrabber::Fill(std::vector < Slice > &data){
  if (data.size() == fileSize / 8){
    for (unsigned long line = 0; line < data.size(); line++){
      binaryFile.seekg(8 * line);
      pressure = 0;
      temperByte1 = 0;
      temperByte2 = 0;
      binaryFile.read(reinterpret_cast<char*>(&intensity1), 2);
      binaryFile.read(reinterpret_cast<char*>(&intensity2), 2);
      binaryFile.read(reinterpret_cast<char*>(&temperByte2), 1); //LIFO
      binaryFile.read(reinterpret_cast<char*>(&temperByte1), 1);
      binaryFile.read(reinterpret_cast<char*>(&pressure), 2);
      data[line].SetInt1(intensity1);
      data[line].SetInt2(intensity2);
      temperature = temperByte1*16. + temperByte2/16.;
      data[line].SetTemper(temperature);
      data[line].SetPress(pressure);
    }
    return true;
  }
  return false;
}



bool DataGrabber::Fill_Test(std::vector < Slice > &data){
  if (data.size() == fileSize / 14){
    for (unsigned long line = 0; line < data.size(); line++){
      binaryFile.seekg(14 * line);
      temperByte1 = 0;
      temperByte2 = 0;
      binaryFile.read(reinterpret_cast<char*>(&intensity1), 2);
      binaryFile.read(reinterpret_cast<char*>(&intensity2), 2);
      binaryFile.read(reinterpret_cast<char*>(&temperByte2), 1); //LIFO
      binaryFile.read(reinterpret_cast<char*>(&temperByte1), 1);
      binaryFile.read(reinterpret_cast<char*>(&time), 8);
      data[line].SetInt1(intensity1);
      data[line].SetInt2(intensity2);
      temperature = temperByte1*16. + temperByte2/16.;
      data[line].SetTemper(temperature);
      data[line].SetTime(time);
    }
    return true;
  }
  return false;
}



bool DataGrabber::Fill_Old(std::vector < Slice > &data, unsigned long long &counter){
  if (data.size() == fileSize / 12){
    for (unsigned long line = 0; line < data.size(); line++){
      binaryFile.seekg(12 * line);
      binaryFile.read(reinterpret_cast<char*>(&counter), 8);
      binaryFile.read(reinterpret_cast<char*>(&intensity1), 2);
      binaryFile.read(reinterpret_cast<char*>(&intensity2), 2);
      data[line].SetInt1(intensity1);
      data[line].SetInt2(intensity2);
    }
    return true;
  }
  return false;
}



#endif
