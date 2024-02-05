#ifndef Slices_hh
#define Slices_hh

#include <vector>


/*
  Each line in a txt data file is considered a slice. Based on the
  sampling rate, it will also have a unique time. If sampling rate
  is 100Hz, then slices should have a time difference of 0.01 seconds.

  Edit: Sampling rate for LAMS will not be constant. The memory card needs
  an undefined amount of time to save the data
*/


class Slice{
private:
  unsigned short intensity1, intensity2;
  double temperature, pressure, time, distance;
  short wavelength, cycle;
  
public:
  Slice(){ 
    intensity1 = 0;
    intensity2 = 0;
    pressure = 0;
    temperature = 0;

    Clear();
  }
  ~Slice(){}

  void Clear(){
    time = -1;
    distance = -1;

    Clear_Stage1();
  }

  void Clear_Stage1(){
    Clear_Stage2();
    
    ZERO_LOW = false;
    ZERO_HIGH = false;
    ZERO_STEM = false;
    ZERO_ABNORMAL = false;
    JUMPER = false;
    IS_STABLE = false;
    PH_DISAGREE = false;
    
    slope1 = 1000000;
    std1 = 1000000;
    slope2 = 1000000;
    std2 = 1000000;
    
    STAGE_1_PASS = false;
  }

  void Clear_Stage2(){
    Clear_Stage3();
    
    PULSE = false;
    DARK = false;
    DARK_RESET = false;
    STEM = false;
    ERROR = false;

    STAGE_2_PASS = false;
  }

  void Clear_Stage3(){
    EXTRA = false;
    EXP_CYCLE = false;
    IS_CYCLE = false;
    
    cycle = -1;
    wavelength = -1;
    
    STAGE_3_PASS = false;
  }

  
  // Parameters needed for Pattern Recognition:
  // Stage 1
  bool STAGE_1_PASS;
  bool ZERO_LOW, ZERO_HIGH, ZERO_ABNORMAL, ZERO_STEM;
  bool JUMPER, IS_STABLE, PH_DISAGREE;
  double slope1, std1, slope2, std2;
  // Stage 2
  bool STAGE_2_PASS;
  bool PULSE, DARK, DARK_RESET, STEM, ERROR;
  // Stage 3
  bool STAGE_3_PASS;
  bool EXTRA, EXP_CYCLE, IS_CYCLE;;

  
  void SetInt1(unsigned short num) {intensity1 = num;}
  void SetInt2(unsigned short num) {intensity2 = num;}
  void SetPress(double num) {pressure = num;}
  void SetTemper(double num) {temperature = num;}
  void SetTime(double num) {time = num;}
  void SetWave(short num) {wavelength = num;}
  void SetCycle(short num) {cycle = num;}
  void SetDistance(double num) {distance = num;}

  unsigned short GetInt1() {return intensity1;}
  unsigned short GetInt2() {return intensity2;}
  double GetPress() {return pressure;}
  double GetTemper() {return temperature;}
  double GetTime() {return time;}
  short GetWave() {return wavelength;}
  short GetCycle() {return cycle;}
  double GetDistance() {return distance;}
  
};



// This function will sort a vector of slices by time and also will return true if sorting was needed
bool SliceSort(std::vector <Slice> &vectorOfSlices){
  Slice temporary;
  bool sortingFinished;
  bool sortingHappened = false;
  for (unsigned long long i = 0; i < vectorOfSlices.size() - 1; i++){
    sortingFinished = true;
    for (unsigned long long k = i; k < vectorOfSlices.size() - 1; k++){
      if (vectorOfSlices[i].GetTime() > vectorOfSlices[i+1].GetTime()){
	temporary = vectorOfSlices[i];
	vectorOfSlices[i+1] = vectorOfSlices[i];
	vectorOfSlices[i] = temporary;
	sortingFinished = false;
	sortingHappened = true;
      }
    }
    // If sortingFinished was not changed to false, then no more sorting is needed
    if (sortingFinished) return sortingHappened;
  }
  return sortingHappened;
}

#endif
