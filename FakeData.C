#include <vector>
#include <iostream>
#include <cmath>
#include "Slices.hh"
#include "DataGrabber.hh"
#include "Pattern.hh"

#include "TCanvas.h"
#include "TChain.h"
#include "TEfficiency.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TGraph.h"
#include "TLeaf.h"
#include "TMath.h"
#include "TObject.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TString.h"
#include "TSystem.h"
#include "TTimeStamp.h"
#include "TTree.h"

using namespace std;

int main(){

  vector < Slice> init_data;
  Slice dummy;
  TFile* outFile = new TFile("Results/Fake_Tests/FakeData.root","RECREATE");
  PatternRecognition Kostas(100,400);

  unsigned pulseHeight[8];
  pulseHeight[0] = 2000;
  pulseHeight[1] = 5000;
  pulseHeight[2] = 24000;
  pulseHeight[3] = 26000;
  pulseHeight[4] = 24500;
  pulseHeight[5] = 52000;
  pulseHeight[6] = 38000;
  pulseHeight[7] = 40000;

  vector <unsigned short> wave; wave.clear();
  wave.push_back(375);
  wave.push_back(385);
  wave.push_back(400);
  wave.push_back(425);
  wave.push_back(450);
  wave.push_back(470);
  wave.push_back(495);
  wave.push_back(525);

  vector <unsigned> count[3];
  bool startCycle[3];
  vector <unsigned> count400[3];
  bool startCycle400[3];
  for (unsigned i = 0; i < 3; i++){
    count[i].clear();
    count[i].push_back(0);
    startCycle[i] = false;
    count[i].clear();
    count[i].push_back(0);
    startCycle400[i] = false;
  }

  for (unsigned cycle = 0; cycle < 50; cycle++){
    for (unsigned dark_reset = 0; dark_reset < 1400; dark_reset++){
      init_data.push_back(dummy);
      init_data.back().SetInt1(10);
      init_data.back().SetInt2(10);
    }

    for (unsigned pulse = 0; pulse < 8; pulse++){
      for (unsigned pulse_counts = 0; pulse_counts < 1000; pulse_counts++){
	init_data.push_back(dummy);
	init_data.back().SetInt1(pulseHeight[pulse]);
	init_data.back().SetInt2(pulseHeight[pulse]);
      }
    
      if (pulse != 7) {
	for (unsigned dark = 0; dark < 200; dark++){
	  init_data.push_back(dummy);
	  init_data.back().SetInt1(10);
	  init_data.back().SetInt2(10);
	}
      }
    }
  }
  for (unsigned dark_reset = 0; dark_reset < 1400; dark_reset++){
    init_data.push_back(dummy);
    init_data.back().SetInt1(10);
    init_data.back().SetInt2(10);
  }

  Kostas.Stage_1(init_data);
  Kostas.Stage_2(init_data);
  Kostas.Stage_3(init_data,wave);

  
  TH1F raw_init("raw_init", "Initial Data without any problems", 541400, 0, 541400);
  for (unsigned int i = 0; i < init_data.size(); i++){
    if (init_data[i].GetWave() == 400){
      if (!startCycle400[0]){
	count400[0].back()++;
      }
      else{
	count400[0].push_back(1);
	startCycle400[0] = false;
      }
    }
    else{
      startCycle400[0] = true;
    }
    if (!init_data[i].DARK_RESET){
      if (!startCycle[0]){
	count[0].back()++;
      }
      else{
	count[0].push_back(1);
	startCycle[0] = false;
      }
    }
    else{
      startCycle[0] = true;
    }
    raw_init.Fill(i, init_data[i].GetInt1());
  }
  
  // Stage 2 of Fake Data Making

  vector < Slice > temp_data;
  temp_data = init_data;

  unsigned temp_pos = 1;
  for (;;){
    if (temp_pos*500 + 19 > temp_data.size()) break;
    temp_data.erase(temp_data.begin() + temp_pos*500 - 1, temp_data.begin() + temp_pos*500 + 19);
    temp_pos++;
  }

  TH1F raw_temp("raw_temp", "Initial Data with temperature eating data", 541400, 0, 541400);
  for (unsigned int i = 0; i < temp_data.size(); i++){
    if (temp_data[i].GetWave() == 400){
      if (!startCycle400[1]){
	count400[1].back()++;
      }
      else{
	count400[1].push_back(1);
	startCycle400[1] = false;
      }
    }
    else{
      startCycle400[1] = true;
    }
    if (!temp_data[i].DARK_RESET){
      if (!startCycle[1]){
	count[1].back()++;
      }
      else{
	count[1].push_back(1);
	startCycle[1] = false;
      }
    }
    else{
      startCycle[1] = true;
    }
    raw_temp.Fill(i, temp_data[i].GetInt1());
  }




  // Stage 3 of Fake Data Making

  vector < Slice > pres_data;
  pres_data = temp_data;

  unsigned pres_pos = 1;
  for (;;){
    if (pres_pos*6000 + 49 > pres_data.size()) break;
    pres_data.erase(pres_data.begin() + pres_pos*6000 - 1, pres_data.begin() + pres_pos*6000 + 49);
    pres_pos++;
  }

  TH1F raw_pres("raw_pres", "Final Sample with all problems", 541400, 0, 541400);
  for (unsigned int i = 0; i < pres_data.size(); i++){

    if (pres_data[i].GetWave() == 400){
      if (!startCycle400[2]){
	count400[2].back()++;
      }
      else{
	count400[2].push_back(1);
	startCycle400[2] = false;
      }
    }
    else{
      startCycle400[2] = true;
    }
    if (!pres_data[i].DARK_RESET){
      if (!startCycle[2]){
	count[2].back()++;
      }
      else{
	count[2].push_back(1);
	startCycle[2] = false;
      }
    }
    else{
      startCycle[2] = true;
    }
    raw_pres.Fill(i, pres_data[i].GetInt1());
  }


  for (unsigned int y = 0; y < 3; y++){
    cout << " ~ ~ Situation: " << y+1 << " ~ ~ " << endl << endl;
    for (unsigned int l = 0; l < count[y].size(); l++){
      cout << count[y][l] << endl;
    }
    cout << endl << endl;
  }

  for (unsigned int y = 0; y < 3; y++){
    cout << " ~ ~ Situation: " << y+1 << " ~ ~ " << endl << endl;
    for (unsigned int l = 0; l < count[y].size(); l++){
      cout << count400[y][l] << endl;
    }
    cout << endl << endl;
  }



  
  raw_init.Write();
  raw_temp.Write();
  raw_pres.Write();
  
  outFile -> Close();
  return 0;
}
