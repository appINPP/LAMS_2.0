#ifndef Report_hh
#define Report_hh

#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include "Slices.hh"
#include "Tools.hh"

class Report{
  std::string write_to;

  std::vector <std::vector <float> > int1;
  std::vector <std::vector <float> > int2;

  // CycleAnalysis
  std::vector <unsigned> cycleSize;
  std::vector <unsigned> expPos;
  std::vector <unsigned long long> cycleStart;
  std::vector <unsigned long long> expStart;

public:
  Report(){}
  ~Report(){}
  
  void OpAnalysis(std::vector <Slice> &data);
  
  void IntensityAnalysis(std::vector <Slice> &data, std::vector <unsigned short> &wave);
  void IntensityShow();
  std::vector <std::vector <float> > GetInt1() {return int1;}
  std::vector <std::vector <float> > GetInt2() {return int2;}
  
  void CycleAnalysis(std::vector <Slice> &data);
  void CycleShow();
  unsigned CyclesTotal() {return cycleStart.size();}
  unsigned ExpTotal() {return expStart.size();}
  unsigned GetCycleSize(unsigned num) {return cycleSize[num];}
  unsigned GetCycleStart(unsigned num) {return cycleStart[num];}

  
  void Stage_1_Report(std::vector <Slice> &data, std::string &output, std::string &option);
  void Stage_2_Report(std::vector <Slice> &data, std::string &output, std::string &option);
  void Stage_3_Report(std::vector <Slice> &data, std::string &output, std::string &option);
};

void Report::IntensityAnalysis(std::vector <Slice> &data, std::vector <unsigned short> &wave){
  if (data.size() == 0) return;
  int cycle_num[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
  std::vector <std::vector <unsigned> > count;
  unsigned short v = 0;
  int1.clear();
  int1.resize(8);
  int2.clear();
  int2.resize(8);
  count.clear();
  count.resize(8);

  for (unsigned long long i = 0; i < data.size(); i++){
    if (data[i].IS_CYCLE && data[i].PULSE){
      if (data[i].GetWave() == wave[0]) v = 0;
      else if (data[i].GetWave() == wave[1]) v = 1;
      else if (data[i].GetWave() == wave[2]) v = 2;
      else if (data[i].GetWave() == wave[3]) v = 3;
      else if (data[i].GetWave() == wave[4]) v = 4;
      else if (data[i].GetWave() == wave[5]) v = 5;
      else if (data[i].GetWave() == wave[6]) v = 6;
      else if (data[i].GetWave() == wave[7]) v = 7;
      else std::cout << "SHIT" << std::endl;
      
      if (v > -1 && v < 8){
	if (data[i].GetCycle() > cycle_num[v]){
	  cycle_num[v] = data[i].GetCycle();
	  int1[v].push_back(data[i].GetInt1());
	  int2[v].push_back(data[i].GetInt2());
	  count[v].push_back(1);
	}
	else{
	  int1[v].back() = int1[v].back() + data[i].GetInt1();
	  int2[v].back() = int2[v].back() + data[i].GetInt2();
	  count[v].back()++;
	}
      }
    }
  }

  for (unsigned k = 0; k < 8; k++){
    for (unsigned j = 0; j < int1[k].size(); j++){
      int1[k][j] = int1[k][j] / count[k][j];  
      int2[k][j] = int2[k][j] / count[k][j];
    }
  }

  
}


void Report::IntensityShow(){
  std::cout << "Intensity 1" << std::endl;
  for (unsigned i = 0; i < int1[0].size(); i++){
    std::cout << "[" << i << "]";
    for (unsigned v = 0; v < 8; v++){
      if (int1[v].size() > i){
	std::cout << "\t" << int1[v][i];
      }
      else{
	std::cout << "\t";
      }
    }
    std::cout << std::endl;
  }

  
  std::cout << "Intensity 2" << std::endl;
  for (unsigned i = 0; i < int2[0].size(); i++){
    std::cout << "[" << i << "]";
    for (unsigned v = 0; v < 8; v++){
      if (int2[v].size() > i){
	std::cout << "\t" << int2[v][i];
      }
      else{
	std::cout << "\t";
      }
    }
    std::cout << std::endl;
  }
}


void Report::CycleAnalysis(std::vector <Slice> &data){
  int cycle_num = -1;
  bool found_expected = false;
  cycleSize.clear();
  cycleStart.clear();
  expPos.clear();
  expStart.clear();

  for (unsigned long long i = 0; i < data.size(); i++){
    if (data[i].GetCycle() > cycle_num){
      found_expected = false;
      cycle_num = data[i].GetCycle();
      cycleSize.push_back(1);
      cycleStart.push_back(i);
    }
    else if(data[i].IS_CYCLE){
      cycleSize.back()++;
    }

    if (data[i].EXP_CYCLE && !found_expected){
      found_expected = true;
      expStart.push_back(i);
      expPos.push_back(cycleStart.size());
    }
  }
}

void Report::CycleShow(){
  unsigned v = 0;
  
  for (unsigned i = 0; i < cycleStart.size(); i++){
    std::cout << "[" << i << "]:\t" << cycleSize[i] << "\t -> at position: " << cycleStart[i] << std::endl;
    if (expPos.size() > v){
      if (expPos[v] == i+1){
	std::cout << "_" << i << "_:\t" << "Expected Cycle at:  " << expStart[v] << std::endl;
	v++;
      }
    }
  }
}


void Report::OpAnalysis(std::vector <Slice> &data){
  std::string message;
  
  unsigned short overlap1;
  unsigned long count1[4] = {0,0,0,0};  // ZERO_LOW, ZERO_HIGH, ZERO_STEM, ZERO_ABNORMAL
  unsigned long range1[4] = {0,0,0,0};
  unsigned area1[4] = {0,0,0,0};
  
  unsigned short overlap2;
  unsigned long count2[5] = {0,0,0,0,0};  // DARK_RESET, DARK, PULSE, STEM, ERROR
  unsigned long range2[5] = {0,0,0,0,0};
  unsigned area2[5] = {0,0,0,0,0};
  
  std::vector <std::string> stage1_overlap;
  std::vector <std::string> stage2_overlap;
  
  std::vector <std::string> stage1_missing;
  std::vector <std::string> stage2_missing;

  stage1_overlap.clear();
  stage2_overlap.clear();
  
  stage1_missing.clear();
  stage2_missing.clear();

  stage1_overlap.push_back(static_cast <std::string> ("~~> STAGE 1 OVERLAPING ISSUES ["));
  stage2_overlap.push_back(static_cast <std::string> ("~~> STAGE 2 OVERLAPING ISSUES ["));
  
  stage1_missing.push_back(static_cast <std::string> ("~~> STAGE 1 MISSING ISSUES ["));
  stage2_missing.push_back(static_cast <std::string> ("~~> STAGE 2 MISSING ISSUES ["));

  for (unsigned long i = 0; i < data.size(); i++){
    overlap1 = 0;
    overlap2 = 0;
    message = "";

    // ZERO_LOW
    if (data[i].ZERO_LOW){
      count1[0]++;
      range1[0]++;
      overlap1++;
      message += "1";
      if (range1[1] > 0){
	area1[1]++;
	range1[1] = 0;
      }
      else if (range1[2] > 0){
	area1[2]++;
	range1[2] = 0;
      }
      else if (range1[3] > 0){
	area1[3]++;
	range1[3] = 0;
      }
    }
    else{
      message += "0";
    }

    // ZERO_HIGH
    if (data[i].ZERO_HIGH){
      count1[1]++;
      range1[1]++;
      overlap1++;
      message += "1";
      if (range1[0] > 0){
	area1[0]++;
	range1[0] = 0;
      }
      else if (range1[2] > 0){
	area1[2]++;
	range1[2] = 0;
      }
      else if (range1[3] > 0){
	area1[3]++;
	range1[3] = 0;
      }
    }
    else{
      message += "0";
    }

    // ZERO_STEM
    if (data[i].ZERO_STEM){
      count1[2]++;
      range1[2]++;
      overlap1++;
      message += "1";
      if (range1[0] > 0){
	area1[0]++;
	range1[0] = 0;
      }
      else if (range1[1] > 0){
	area1[1]++;
	range1[1] = 0;
      }
      else if (range1[3] > 0){
	area1[3]++;
	range1[3] = 0;
      }
    }
    else{
      message += "0";
    }

    // ZERO_ABNORMAL
    if (data[i].ZERO_ABNORMAL){
      count1[3]++;
      range1[3]++;
      overlap1++;
      message += "1";
      if (range1[0] > 0){
	area1[0]++;
	range1[0] = 0;
      }
      else if (range1[1] > 0){
	area1[1]++;
	range1[1] = 0;
      }
      else if (range1[2] > 0){
	area1[2]++;
	range1[2] = 0;
      }
    }
    else{
      message += "0";
    }
    
  }
  
}



  
//+++++++++ STAGE 1 REPORT +++++++++//
void Report::Stage_1_Report(std::vector <Slice> &data, std::string &output, std::string &option){

  float ph_disagreement_tolerance = 0.2;
  std::string message;
  std::string zero;
  float overall_stability = 0;
  unsigned short overlap;

  unsigned long countZ[4] = {0,0,0,0};  // LOW, HIGH, STEM, ABNORMAL
  unsigned long countStable[2] = {0,0};  // LOW, HIGH
  unsigned long countDisagree[4] = {0,0,0,0};  // PH Disagreement for LOW, HIGH, LOW but STABLE, HIGH but STABLE

  std::vector <std::string> zero_overlap;
  std::vector <std::string> zero_missing;
  std::vector <std::string> ph_disagreement;
    
  zero_overlap.clear();
  zero_missing.clear();
  ph_disagreement.clear();
    
  message = "~~> OVERLAPING ISSUES [";
  zero_overlap.push_back(message);
  message = "~~> MISSING ISSUES [";
  zero_missing.push_back(message);
  message = "~~> PHOTODIODES DISAGREEMENTS (TOLERANCE: " + NumToString(100*ph_disagreement_tolerance) + "%) [";
  ph_disagreement.push_back(message);
    
  for (unsigned long i = 0; i < data.size(); i++){
    overlap = 0;
    zero = "";
    
    if (data[i].ZERO_LOW){
      countZ[0]++;
      if (data[i].PH_DISAGREE) countDisagree[0]++;
      if (data[i].IS_STABLE) {
	countStable[0]++;
	if (data[i].PH_DISAGREE) countDisagree[2]++;
      }
      overlap++;
      zero = zero + "1";
    }
    else zero = zero + "0";
    if (data[i].ZERO_HIGH){
      countZ[1]++;
      if (data[i].PH_DISAGREE) countDisagree[1]++;
      if (data[i].IS_STABLE) {
	countStable[1]++;
	if (data[i].PH_DISAGREE) countDisagree[3]++;
      }
      overlap++;
      zero = zero + "1";
    }
    else zero = zero + "0";
    if (data[i].ZERO_STEM){
      countZ[2]++;
      overlap++;
      zero = zero + "1";
    }
    else zero = zero + "0";
    if (data[i].ZERO_ABNORMAL){
      countZ[3]++;
      overlap++;
      zero = zero + "1";
    }
    else zero = zero + "0";
    
    
    if (overlap == 0){
      message = "[" + NumToString(i) + "]\t";
      zero_missing.push_back(message);
    }
    else if (overlap > 1){
      message = "[" + NumToString(i) + "]:[" + zero + "]\t";
      zero_overlap.push_back(message);
    }

    if (data[i].PH_DISAGREE){
      message = "[" + NumToString(i) + "]\t";
      ph_disagreement.push_back(message);
    }

    if (data[i].IS_STABLE) overall_stability++;
  }

  zero_overlap[0] = zero_overlap[0] + NumToString(zero_overlap.size() - 1) + "/" + NumToString(data.size())
    + "]: " + NumToString(100.0*(zero_overlap.size() - 1)/data.size()) + "%\n";
  zero_missing[0] = zero_missing[0] + NumToString(zero_missing.size() - 1) + "/" + NumToString(data.size())
    + "]: " + NumToString(100.0*(zero_missing.size() - 1)/data.size()) + "%\n"; 
  ph_disagreement[0] = ph_disagreement[0] + NumToString(ph_disagreement.size() - 1) + "/" + NumToString(data.size())
    + "]: " +NumToString(100.0*(ph_disagreement.size() - 1)/data.size()) + "%\n";
    
  
  if (output == "cout" || output == "COUT"){
    std::cout << "______________________________________________________" << std::endl;
    std::cout << "+ + + + + + + + + + STAGE 1 REPORT + + + + + + + + + +" << std::endl << std::endl;
    for (unsigned long v = 0; v < zero_overlap.size(); v++){
      std::cout << zero_overlap[v];
      if (option != "full" || option != "FULL") break;
      if (v % 8 == 0 && v != 0) std::cout << std::endl;
    }
    std::cout << std::endl;
    for (unsigned long v = 0; v < zero_missing.size(); v++){
      std::cout << zero_missing[v];
      if (option != "full" || option != "FULL") break;
      if (v % 8 == 0 && v != 0) std::cout << std::endl;
    }
    std::cout << std::endl << ph_disagreement[0];

    message = "~~> OVERALL STABILITY OF DATA [" + NumToString(overall_stability) + "/" + NumToString(data.size())
      + "]: " + NumToString(100*overall_stability/data.size()) + "%\n";
    std::cout << std::endl << message;
    
    message = "~~> RESULTING VALUES FOR NEXT STAGE:\n\n";
    message += " * ZERO_LOW [" + NumToString(countZ[0]) + "/" + NumToString(data.size()) + "]: "
      + NumToString(100.0*countZ[0]/data.size()) + "%\n";
    message += "  > PH DISAGREE [" + NumToString(countDisagree[0]) + "/" + NumToString(countZ[0]) + "]: "
      + NumToString(100.0*countDisagree[0]/countZ[0]) + "%\n";
    message += "  > STABLE [" + NumToString(countStable[0]) + "/" + NumToString(countZ[0]) + "]: "
      + NumToString(100.0*countStable[0]/countZ[0]) + "%\n";
    message += "   > PH DISAGREE [" + NumToString(countDisagree[2]) + "/" + NumToString(countStable[0]) + "]: "
      + NumToString(100.0*countDisagree[2]/countStable[0]) + "%\n\n";
    
    message += " * ZERO_HIGH [" + NumToString(countZ[1]) + "/" + NumToString(data.size()) + "]: "
      + NumToString(100.0*countZ[1]/data.size()) + "%\n";
    message += "  > PH DISAGREE [" + NumToString(countDisagree[1]) + "/" + NumToString(countZ[1]) + "]: "
      + NumToString(100.0*countDisagree[1]/countZ[1]) + "%\n";
    message += "  > STABLE [" + NumToString(countStable[1]) + "/" + NumToString(countZ[1]) + "]: "
      + NumToString(100.0*countStable[1]/countZ[1]) + "%\n";
    message += "   > PH DISAGREE [" + NumToString(countDisagree[3]) + "/" + NumToString(countStable[1]) + "]: "
      + NumToString(100.0*countDisagree[3]/countStable[1]) + "%\n\n";
    
    message += " * ZERO_STEM [" + NumToString(countZ[2]) + "/" + NumToString(data.size()) + "]: "
      + NumToString(100.0*countZ[2]/data.size()) + "%\n\n";
    
    message += " * ZERO_ABNORMAL [" + NumToString(countZ[3]) + "/" + NumToString(data.size()) + "]: "
      + NumToString(100.0*countZ[3]/data.size()) + "%";
    
    std::cout << std::endl << message << std::endl;
    std::cout << "______________________________________________________" << std::endl;

  }
}



//+++++++++ STAGE 2 REPORT +++++++++//
void Report::Stage_2_Report(std::vector <Slice> &data, std::string &output, std::string &option){
  std::string message;
  std::string type;
  unsigned short overlap;
  unsigned long count[5] = {0,0,0,0,0};  // DARK_RESET, DARK, PULSE, STEM, ERROR
  unsigned long range[5] = {0,0,0,0,0};
  unsigned area[5] = {0,0,0,0,0};

  std::vector <std::string> type_overlap;
  std::vector <std::string> type_missing;
    
  type_overlap.clear();
  type_missing.clear();
    
  message = "~~> OVERLAPING ISSUES [";
  type_overlap.push_back(message);
  message = "~~> MISSING ISSUES [";
  type_missing.push_back(message);
    
  for (unsigned long i = 0; i < data.size(); i++){
    overlap = 0;
    type = "";
    if (data[i].DARK_RESET){
      count[0]++;
      range[0]++;
      if (range[1] > 0){
	area[1]++;
	range[1] = 0;
      }
      if (range[2] > 0){
	area[2]++;
	range[2] = 0;
      }
      if (range[3] > 0){
	area[3]++;
	range[3] = 0;
      }
      if (range[4] > 0){
	area[4]++;
	range[4] = 0;
      }
      
      overlap++;
      type = type + "1";
    }
    else type = type + "0";
    if (data[i].DARK){
      count[1]++;
      range[1]++;
      if (range[0] > 0){
	area[0]++;
	range[0] = 0;
      }
      if (range[2] > 0){
	area[2]++;
	range[2] = 0;
      }
      if (range[3] > 0){
	area[3]++;
	range[3] = 0;
      }
      if (range[4] > 0){
	area[4]++;
	range[4] = 0;
      }
      overlap++;
      type = type + "1";
    }
    else type = type + "0";
    if (data[i].PULSE){
      count[2]++;
      range[2]++;
      if (range[0] > 0){
	area[0]++;
	range[0] = 0;
      }
      if (range[1] > 0){
	area[1]++;
	range[1] = 0;
      }
      if (range[3] > 0){
	area[3]++;
	range[3] = 0;
      }
      if (range[4] > 0){
	area[4]++;
	range[4] = 0;
      }
      overlap++;
      type = type + "1";
    }
    else type = type + "0";
    if (data[i].STEM){
      count[3]++;
      range[3]++;
      if (range[0] > 0){
	area[0]++;
	range[0] = 0;
      }
      if (range[1] > 0){
	area[1]++;
	range[1] = 0;
      }
      if (range[2] > 0){
	area[2]++;
	range[2] = 0;
      }
      if (range[4] > 0){
	area[4]++;
	range[4] = 0;
      }
      overlap++;
      type = type + "1";
    }
    else type = type + "0";
    if (data[i].ERROR){
      count[4]++;
      range[4]++;
      if (range[0] > 0){
	area[0]++;
	range[0] = 0;
      }
      if (range[1] > 0){
	area[1]++;
	range[1] = 0;
      }
      if (range[2] > 0){
	area[2]++;
	range[2] = 0;
      }
      if (range[3] > 0){
	area[3]++;
	range[3] = 0;
      }
      overlap++;
      type = type + "1";
    }
    else type = type + "0";

    if (overlap == 0){
      message = "[" + NumToString(i) + "]\t";
      type_missing.push_back(message);
    }
    else if (overlap > 1){
      message = "[" + NumToString(i) + "]:[" + type + "]\t";
      type_overlap.push_back(message);
    }

  }

  type_overlap[0] = type_overlap[0] + NumToString(type_overlap.size() - 1) + "/" + NumToString(data.size())
    + "]: " + NumToString(100.0*(type_overlap.size() - 1)/data.size()) + "%\n";
  type_missing[0] = type_missing[0] + NumToString(type_missing.size() - 1) + "/" + NumToString(data.size())
    + "]: " + NumToString(100.0*(type_missing.size() - 1)/data.size()) + "%\n";
  
  if (output == "cout" || output == "COUT"){
    std::cout << "______________________________________________________" << std::endl;
    std::cout << "+ + + + + + + + + + STAGE 2 REPORT + + + + + + + + + +" << std::endl << std::endl;
    for (unsigned long v = 0; v < type_overlap.size(); v++){
      std::cout << type_overlap[v];
      if (option != "full") break;
      if (v % 6 == 0 && v != 0) std::cout << std::endl;
    }
    std::cout << std::endl;
    for (unsigned long v = 0; v < type_missing.size(); v++){
      std::cout << type_missing[v];
      if (option != "full") break;
      if (v % 8 == 0 && v != 0) std::cout << std::endl;
    }

    message = "~~> RESULTING VALUES FOR NEXT STAGE:\n\n";
    message += " * DARK_RESET [" + NumToString(count[0]) + "/" + NumToString(data.size()) + "]: "
      + NumToString(100.0*count[0]/data.size()) + "%\n";
    message += "  > AREAS: " + NumToString(area[0]) + "\n\n";

    message += " * DARK [" + NumToString(count[1]) + "/" + NumToString(data.size()) + "]: "
      + NumToString(100.0*count[1]/data.size()) + "%\n";
    message += "  > AREAS: " + NumToString(area[1]) + "\n\n";
    
    message += " * PULSE [" + NumToString(count[2]) + "/" + NumToString(data.size()) + "]: "
      + NumToString(100.0*count[2]/data.size()) + "%\n";
    message += "  > AREAS: " + NumToString(area[2]) + "\n\n";
    
    message += " * STEM [" + NumToString(count[3]) + "/" + NumToString(data.size()) + "]: "
      + NumToString(100.0*count[3]/data.size()) + "%\n";
    message += "  > AREAS: " + NumToString(area[3]) + "\n\n";
    
    message += " * ERROR [" + NumToString(count[4]) + "/" + NumToString(data.size()) + "]: "
      + NumToString(100.0*count[4]/data.size()) + "%\n";
    message += "  > AREAS: " + NumToString(area[4]);

    std::cout << std::endl << message << std::endl;

    std::cout << "______________________________________________________" << std::endl;
  }
}


//+++++++++ STAGE 3 REPORT +++++++++//
void Report::Stage_3_Report(std::vector <Slice> &data, std::string &output, std::string &option){
  
}

#endif
