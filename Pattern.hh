#ifndef Pattern_hh
#define Pattern_hh

#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <iostream>
#include "Slices.hh"
#include "Tools.hh"

class PatternRecognition{
private:
  unsigned darkCurrent;  // Below this value: natural darkness
  unsigned saturationLight;  // Above this value: natural light
  float ph_disagreement_tolerance;  // If equal to: 0 (0%)-> Zero Tolerance, 1 (100%)-> Full Tolerance
public:

  
  PatternRecognition(){
    darkCurrent = 1000;
    saturationLight = 60000;
    Set_PH_Tolerance(0.2);
  }


  PatternRecognition(unsigned user_darkCurrent, unsigned user_saturationLight){
    darkCurrent = user_darkCurrent;
    saturationLight = user_saturationLight;
    Set_PH_Tolerance(0.2);
  }


  ~PatternRecognition(){}

  
  void Clear(std::vector <Slice> &data);
  void Set_PH_Tolerance(float tolerance);
  
  double bestSlope(std::vector<Slice> &data, unsigned long start_point, unsigned long end_point, unsigned short choose_ph);
  double std(std::vector<Slice> &data, unsigned long start_point, unsigned long end_point, unsigned short choose_ph);
  
  void Stage_1 (std::vector <Slice> &data);
  void Stage_2 (std::vector <Slice> &data);
  void Stage_3 (std::vector <Slice> &data, std::vector <unsigned short> &wave);
  void Stage_3_1 (std::vector <Slice> &data, std::vector <unsigned short> &wave);
  void RemoveCycle(std::vector <Slice> &data, unsigned cycle);
};




void PatternRecognition::Clear(std::vector <Slice> &data){
  for (unsigned long long i = 0; i < data.size(); i++){
    data[i].Clear();
  }
}



void PatternRecognition::Set_PH_Tolerance(float tolerance){
  ph_disagreement_tolerance = tolerance;
}


  
double PatternRecognition::bestSlope(std::vector<Slice> &data, unsigned long start_point, unsigned long end_point, unsigned short choose_ph){
  double xMean = 0, yMean = 0, sumTop = 0, sumBot = 0;
  if (choose_ph == 1){
    for (unsigned long i = start_point; i <= end_point; i++){
      xMean += i;
      yMean += data[i].GetInt1();
    }
    xMean = xMean / (end_point - start_point +1);
    yMean = yMean / (end_point - start_point +1);
    for (unsigned long i = start_point; i <= end_point; i++){
      sumTop += (i - xMean)*(data[i].GetInt1() - yMean);
      sumBot += (i - xMean)*(i - xMean);
    }
    return sumTop / sumBot;
  }
  else if (choose_ph == 2){
    for (unsigned long i = start_point; i <= end_point; i++){
      xMean += i;
      yMean += data[i].GetInt2();
    }
    xMean = xMean / (end_point - start_point +1);
    yMean = yMean / (end_point - start_point +1);
    for (unsigned long i = start_point; i <= end_point; i++){
      sumTop += (i - xMean)*(data[i].GetInt2() - yMean);
      sumBot += (i - xMean)*(i - xMean);
    }
    return sumTop / sumBot;
  }
  else{
    return 1000000;
  } 
}


  
double PatternRecognition::std(std::vector<Slice> &data, unsigned long start_point, unsigned long end_point, unsigned short choose_ph){
  double result = 0;
  double mean = 0;
  if (end_point <= start_point){
    return 500000; // We don't want this to happen ever.
  }
    
  if (choose_ph == 1){
    for (unsigned long i = start_point; i <= end_point; i++){
      mean += data[i].GetInt1();
    }
    mean /= (end_point - start_point + 1);
    for (unsigned long i = start_point; i <= end_point; i++){
      result += pow(data[i].GetInt1() - mean,2);
    }
  }
  if (choose_ph == 2){
    for (unsigned long i = start_point; i <= end_point; i++){
      mean += data[i].GetInt2();
    }
    mean /= (end_point - start_point + 1);
    for (unsigned long i = start_point; i <= end_point; i++){
      result += pow(data[i].GetInt2() - mean,2);
    }
  }
  result /= (end_point - start_point);
  return sqrt(result);
}




//+ + + + + STAGES RECOGNITION + + + + +//

  
//+++++++++++++++ Stage 1 +++++++++++++++//
void PatternRecognition::Stage_1 (std::vector <Slice> &data){
  double mean1 = 0, mean2 = 0;
  unsigned long range = 0;

  // Stage 1 should always be provided with clean data
  Clear(data);
  
  // First scan: Find data below darkCurrent, or one of photodiodes below darkCurrent
  for (unsigned long i = 0; i < data.size(); i++){
    data[i].ZERO_LOW = data[i].GetInt1() <= darkCurrent && data[i].GetInt2() <= darkCurrent;
    data[i].ZERO_ABNORMAL = !data[i].ZERO_LOW && (data[i].GetInt1() <= darkCurrent || data[i].GetInt2() <= darkCurrent);
    data[i].ZERO_ABNORMAL = data[i].GetInt1() > saturationLight || data[i].GetInt2() > saturationLight;
      
    if (data[i].GetInt1() > data[i].GetInt2()){
      data[i].PH_DISAGREE = (data[i].GetInt1() - data[i].GetInt2()) > data[i].GetInt1() * ph_disagreement_tolerance;
    }
    else if (data[i].GetInt1() < data[i].GetInt2()){
      data[i].PH_DISAGREE = (data[i].GetInt2() - data[i].GetInt1()) > data[i].GetInt2() * ph_disagreement_tolerance;
    }
  }

    
  // Second scan: Quickly splits data into STEM-like and PULSE-like
  for (unsigned long i = 0; i < data.size(); i++){
    if (!data[i].ZERO_LOW && !data[i].ZERO_ABNORMAL){
      mean1 += data[i].GetInt1();
      mean2 += data[i].GetInt2();
      range++;
    }
    else{
      if (range > 0){
	mean1 *= 0.9 / range;
	mean2 *= 0.9 / range;
	for (unsigned long c = i - range; c < i; c++){
	  data[c].ZERO_HIGH = data[c].GetInt1() >= mean1 && data[c].GetInt2() >= mean2;
	  data[c].ZERO_STEM = !data[c].ZERO_LOW && !data[c].ZERO_ABNORMAL && !data[c].ZERO_HIGH;	    
	}
	mean1 = 0;
	mean2 = 0;
	range = 0;
      }
    }
    if (i == data.size() - 1 && range > 0){
      mean1 *= 0.9 / range;
      mean2 *= 0.9 / range;
      for (unsigned long c = i - range; c <= i; c++){
	data[c].ZERO_HIGH = data[c].GetInt1() >= mean1 && data[c].GetInt2() >= mean2;
	data[c].ZERO_STEM = !data[c].ZERO_LOW && !data[c].ZERO_ABNORMAL && !data[c].ZERO_HIGH;	    
      }
      mean1 = 0;
      mean2 = 0;
      range = 0;
    }
  }
    

  // Search for the slopes and STDs of 3 points, and apply to middle    
  data[0].slope1 = bestSlope(data,0,1,1);
  data[0].std1 = std(data,0,1,1);
    
  data[0].slope2 = bestSlope(data,0,1,2);
  data[0].std2 = std(data,0,1,2);

  data[0].IS_STABLE = true;
  
  data[data.size()-1].slope1 = bestSlope(data,data.size()-2,data.size()-1,1);
  data[data.size()-1].std1 = std(data,data.size()-2,data.size()-1,1);

  data[data.size()-1].slope2 = bestSlope(data,data.size()-2,data.size()-1,2);
  data[data.size()-1].std2 = std(data,data.size()-2,data.size()-1,2);

  data[data.size()-1].IS_STABLE = true;

  for (unsigned long i = 1; i < data.size()-1; i++){
      
    data[i].slope1 = bestSlope(data,i-1,i+1,1);
    data[i].std1 = std(data,i-1,i+1,1);
    
    data[i].slope2 = bestSlope(data,i-1,i+1,2);
    data[i].std2 = std(data,i-1,i+1,2);

    data[i].IS_STABLE = data[i].std1 < 400 && data[i].std2 < 400;
    data[i-1].JUMPER = data[i+1].IS_STABLE && !data[i].IS_STABLE;
    data[i+1].JUMPER = data[i-1].IS_STABLE && !data[i].IS_STABLE;
  }

  for (unsigned long i = 0; i < data.size(); i++){

  }
}


  
  
//+++++++++++++++ Stage 2 +++++++++++++++// 
void PatternRecognition::Stage_2 (std::vector <Slice> &data){
  for (unsigned long i = 0; i < data.size(); i++){
    //data[i].PULSE = data[i].ZERO_HIGH && data[i].IS_STABLE && (data[i].GetInt1() > darkAlmost && data[i].GetInt2() > darkAlmost);
    data[i].PULSE = data[i].ZERO_HIGH && data[i].IS_STABLE;
    data[i].STEM = data[i].ZERO_STEM;
    data[i].DARK = data[i].ZERO_LOW && data[i].IS_STABLE;
    data[i].ERROR = data[i].ZERO_ABNORMAL || ((data[i].ZERO_LOW || data[i].ZERO_HIGH) && !data[i].IS_STABLE);
  }
  unsigned range = 0;
  double averageRange = 0;
  unsigned nRanges = 0;
  for (unsigned long i = 0; i < data.size(); i++){
    if (data[i].DARK){  // Inside dark area.
      range++;
    }
    else if (range > 0){  // Just left dark area.
      averageRange += range;
      nRanges++;
      range = 0;	
    }
    else{  // Outside of any dark area 
      continue;
    }
  }
  if (nRanges == 0) nRanges ++;
  averageRange *= 3. / nRanges; // Multiply by 3 to be sure.

  // Same process as above, but to set DARK_RESET = true where needed
  for (unsigned long i = 0; i < data.size(); i++){
    if (data[i].DARK){
      range++;
    }
    else if (range > 0){
      if (range > averageRange){
	for (unsigned long c = i - range; c < i; c++){
	  data[c].DARK_RESET = true;
	  data[c].DARK = false;
	}
      }
      range = 0;
    }
    else{ 
      continue;
    }
  }
}




//+++++++++++++++ Stage 3 +++++++++++++++//
void PatternRecognition::Stage_3 (std::vector <Slice> &data, std::vector <unsigned short> &wave){
  unsigned range = 0;
  unsigned range2 = 0;
  unsigned nRanges = 0;
  std::vector <unsigned long> start; start.clear();
  std::vector <unsigned> areaSize; areaSize.clear();

  std::vector <unsigned long> startReset; startReset.clear();
  unsigned notReset = 0;
  for (unsigned long i = 0; i < data.size(); i++){
    if (!data[i].DARK_RESET){
      notReset++;
    }
    else{
      if (notReset > 0){
	startReset.push_back(i);
	notReset = 0;
      }
    }
  }
  if (startReset.size() == 0) return;
  for (unsigned i = 0; i < startReset.size() - 1; i++){
    for (unsigned v = startReset[i]; v < startReset[i+1]; v++){
      data[v].EXP_CYCLE = true;
      data[v].SetCycle(i);
    }
  }
  
  
  for (unsigned long i = 0; i < data.size(); i++){
    if (!data[i].DARK_RESET){
      range++;
      if (!data[i].DARK){
	if (range2 == 0){
	  start.push_back(i);
	}
	range2++;
      }
      else if (range2 > 0){
	nRanges++;
	areaSize.push_back(range2);
	range2 = 0;
      }
    }
    else if (range > 0){
      nRanges++;
      areaSize.push_back(range2);
      range2 = 0;
      if (nRanges == 8){
	for (unsigned k = 0; k < 8; k++){
	  for (unsigned long v = start[k]; v < start[k] + areaSize[k]; v++){
	    data[v].SetWave(wave[k]);
	    data[v].IS_CYCLE = true;
	  }
	}
      }
      else if (nRanges > 8){
	unsigned smallest = 0;
	for (;;){
	  for (unsigned k = 0; k < nRanges; k++){
	    if (k == 0) smallest = 0;
	    else{
	      if (areaSize[k] < smallest){
		smallest = k;
	      }
	    }
	  }
	  for (unsigned long v = start[smallest]; v < start[smallest] + areaSize[smallest]; v++){
	    data[v].EXTRA = true;
	  }
	  areaSize.erase(areaSize.begin()+smallest);
	  start.erase(start.begin()+smallest);
	  nRanges--;
	  if (nRanges == 8) break;
	}
	for (unsigned k = 0; k < 8; k++){
	  for (unsigned long v = start[k]; v < start[k] + areaSize[k]; v++){
	    data[v].SetWave(wave[k]);
	    data[v].IS_CYCLE = true;
	  }
	}
      }
      nRanges = 0;
      start.clear();
      areaSize.clear();
      range = 0;
      range2 = 0;
    }
    else{ 
      continue;
    }
  }
  for (unsigned i = 0; i < startReset.size() -1; i++){
    bool confirm = false;
    for (unsigned v = startReset[i]; v < startReset[i+1]; v++){
      if (data[v].IS_CYCLE){
	confirm = true;
	break;
      }
    }
    if (confirm){
      for (unsigned v = startReset[i]; v < startReset[i+1]; v++){
	data[v].IS_CYCLE = true;
      }
    }
  }
}




//+++++++++++++++ Stage 3.1 +++++++++++++++//
void PatternRecognition::Stage_3_1 (std::vector <Slice> &data, std::vector <unsigned short> &wave){
  std::vector <unsigned long> resetStart;
  std::vector <unsigned long> darkStart;
  std::vector <unsigned > resetArea;
  std::vector <unsigned > darkArea;
  unsigned long area = 0;
  unsigned cycle = 0;

  unsigned medianSize = 0;
  std::vector <unsigned> cycleSize;

  cycleSize.clear();
  resetStart.clear();
  resetArea.clear();
  
  // Find all DARK_RESET areas
  for (unsigned long i = 0; i < data.size(); i++){
    if (data[i].DARK_RESET){
      area++;
    }
    else if (!data[i].ERROR){
      if (area > 0){
	resetStart.push_back(i-area);
	resetArea.push_back(area);
	area = 0;
      }
    }
    else{
      if (area > 0){
	area++;
      }
    }
  }

  // High priority condition, keep this high or *SEGMENTATION FAULT* will show up
  if (resetStart.size() < 2) return;
  
  // Find the median Reset Area, it's needed to exclude too big or too small cycles
  for (unsigned i = 0; i < resetStart.size() - 1; i++){
    cycleSize.push_back(resetStart[i+1] - resetStart[i]);
  } 
  std::sort(cycleSize.begin(), cycleSize.end());
  medianSize = cycleSize[cycleSize.size()/2];

  // Start working for the dark areas
  for (unsigned long i = 0; i < resetStart.size() - 1; i++){
    area = 0;
    darkStart.clear();
    darkArea.clear();
    
    for (unsigned long v = resetStart[i] + resetArea[i]; v < resetStart[i+1]; v++){
      if (data[v].DARK){
	area++;
      }
      else if (!data[v].ERROR){
	if (area > 0){
	  darkStart.push_back(v-area);
	  darkArea.push_back(area);
	  area = 0;
	}
      }
      else{
	if (area > 0){
	  area++;
	}
      }
    }
    
    // Too small cycles are marked as EXPECTED CYCLES
    if (darkStart.size() < 7 || resetStart[i+1] - resetStart[i] < 0.8 * medianSize){
      for (unsigned long k = resetStart[i] + resetArea[i]; k < resetStart[i+1]; k++){
	data[k].EXP_CYCLE = true;
      }
    }
    else {
      // Check if resetArea size is too big (~ +1 more pulse or more). If yes, mark as EXPECTED CYCLE 
      if (resetStart[i+1] - resetStart[i] > 1.1 * medianSize){
	for (unsigned long k = resetStart[i] + resetArea[i]; k < resetStart[i+1]; k++){
	  data[k].EXP_CYCLE = true;
	}
	continue;
      }
      
      // In case of extra dark areas
      while (darkArea.size() > 7){
	unsigned smallestArea = darkArea[0];
	unsigned pointToSmallest = 0;
	for (unsigned v = 1; v < darkArea.size(); v++){
	  if (smallestArea > darkArea[v]){
	    smallestArea = darkArea[v];
	    pointToSmallest = v;
	  }
	}
	darkStart.erase(darkStart.begin() + pointToSmallest);
	darkArea.erase(darkArea.begin() + pointToSmallest);
      }
      
      // There will be no extra dark areas from now on
      for (unsigned long k = 0; k < 8; k++){
	if (k == 0){
	  for (unsigned long v = resetStart[i] + resetArea[i]; v < darkStart[k]; v++){
	    if (data[v].PULSE || data[v].STEM){
	      data[v].SetWave(wave[k]);
	    }
	  }
	}
	else if (k == 7){
	  for (unsigned long v = darkStart[k-1]; v < resetStart[i+1]; v++){
	    if (data[v].PULSE || data[v].STEM){
	      data[v].SetWave(wave[k]);
	    }
	  }
	}
	else{
	  for (unsigned long v = darkStart[k-1]; v < darkStart[k]; v++){
	    if (data[v].PULSE || data[v].STEM){
	      data[v].SetWave(wave[k]);
	    }
	  }
	}
      }

      // Mark Data with 8 Pulses as Cycles
      for (unsigned long v = resetStart[i]; v < resetStart[i+1]; v++){
	data[v].IS_CYCLE = true;
	data[v].SetCycle(cycle);
      }
      cycle++;
    }
  }
}


void PatternRecognition::RemoveCycle(std::vector <Slice> &data, unsigned cycle){
  bool found = false;
  for (unsigned long long i = 0; i < data.size(); i++){
    if (data[i].GetCycle() == cycle){
      found = true;
      data[i].SetCycle(-1);
      data[i].IS_CYCLE = false;
      data[i].EXP_CYCLE = true;
    }
    if (found){
      if (data[i].IS_CYCLE){
	data[i].SetCycle(data[i].GetCycle()-1);
      }
    }
  }
}

#endif
