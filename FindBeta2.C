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

// System Tests
int main(){
  // Distance Parameters
  const double R1 = 10; // 1st Distance
  const double R2 = 16; // 2nd Distance
  const double R3 = 20; // 3rd Distance

  const double err_R1 = 0.05;
  const double err_R2 = 0.05;
  const double err_R3 = 0.05;

  // Histograms
  TH1F raw1_ph1_10m("raw1_ph1_10m", "Raw Data Test 1 - Photodiode 1 - 10m", 566738, 0, 566738);
  TH1F raw1_ph2_10m("raw1_ph2_10m", "Raw Data Test 1 - Photodiode 2 - 10m", 566738, 0, 566738);
  TH1F raw1_ph1_16m("raw1_ph1_16m", "Raw Data Test 1 - Photodiode 1 - 16m", 643136, 0, 643136);
  TH1F raw1_ph2_16m("raw1_ph2_16m", "Raw Data Test 1 - Photodiode 2 - 16m", 643136, 0, 643136);
  TH1F raw1_ph1_20m("raw1_ph1_20m", "Raw Data Test 1 - Photodiode 1 - 20m", 743123, 0, 743123);
  TH1F raw1_ph2_20m("raw1_ph2_20m", "Raw Data Test 1 - Photodiode 2 - 20m", 743123, 0, 743123);

  TH1F raw2_ph1_10m("raw2_ph1_10m", "Raw Data Test 2 - Photodiode 1 - 10m", 736372, 0, 736372);
  TH1F raw2_ph2_10m("raw2_ph2_10m", "Raw Data Test 2 - Photodiode 2 - 10m", 736372, 0, 736372);
  TH1F raw2_ph1_16m("raw2_ph1_16m", "Raw Data Test 2 - Photodiode 1 - 16m", 745246, 0, 745246);
  TH1F raw2_ph2_16m("raw2_ph2_16m", "Raw Data Test 2 - Photodiode 2 - 16m", 745246, 0, 745246);
  TH1F raw3_ph1_20m("raw3_ph1_20m", "Raw Data Test 3 - Photodiode 1 - 20m", 743123, 0, 743123);
  TH1F raw3_ph2_20m("raw3_ph2_20m", "Raw Data Test 3 - Photodiode 2 - 20m", 743123, 0, 743123);

  TH1F stg1_ph1_10m("stg1_ph1_10m", "Stage 2 Data Test 1 - Photodiode 1 - 10m", 566738, 0, 566738);
  TH1F stg1_ph2_10m("stg1_ph2_10m", "Stage 2 Data Test 1 - Photodiode 2 - 10m", 566738, 0, 566738);
  TH1F stg1_ph1_16m("stg1_ph1_16m", "Stage 2 Data Test 1 - Photodiode 1 - 16m", 643136, 0, 643136);
  TH1F stg1_ph2_16m("stg1_ph2_16m", "Stage 2 Data Test 1 - Photodiode 2 - 16m", 643136, 0, 643136);
  TH1F stg1_ph1_20m("stg1_ph1_20m", "Stage 2 Data Test 1 - Photodiode 1 - 20m", 743123, 0, 743123);
  TH1F stg1_ph2_20m("stg1_ph2_20m", "Stage 2 Data Test 1 - Photodiode 2 - 20m", 743123, 0, 743123);

  TH1F stg2_ph1_10m("stg2_ph1_10m", "Stage 2 Data Test 2 - Photodiode 1 - 10m", 736372, 0, 736372);
  TH1F stg2_ph2_10m("stg2_ph2_10m", "Stage 2 Data Test 2 - Photodiode 2 - 10m", 736372, 0, 736372);
  TH1F stg2_ph1_16m("stg2_ph1_16m", "Stage 2 Data Test 2 - Photodiode 1 - 16m", 745246, 0, 745246);
  TH1F stg2_ph2_16m("stg2_ph2_16m", "Stage 2 Data Test 2 - Photodiode 2 - 16m", 745246, 0, 745246);
  TH1F stg3_ph1_20m("stg3_ph1_20m", "Stage 2 Data Test 3 - Photodiode 1 - 20m", 743123, 0, 743123);
  TH1F stg3_ph2_20m("stg3_ph2_20m", "Stage 2 Data Test 3 - Photodiode 2 - 20m", 743123, 0, 743123);


  TH1F dis1_pulse0("dis1_pulse0", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis1_pulse1("dis1_pulse1", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis1_pulse2("dis1_pulse2", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis1_pulse3("dis1_pulse3", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis1_pulse4("dis1_pulse4", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis1_pulse5("dis1_pulse5", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis1_pulse6("dis1_pulse6", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis1_pulse7("dis1_pulse7", "Intensity Distribution", 16384, 0, 65535);

  TH1F dis2_pulse0("dis2_pulse0", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis2_pulse1("dis2_pulse1", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis2_pulse2("dis2_pulse2", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis2_pulse3("dis2_pulse3", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis2_pulse4("dis2_pulse4", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis2_pulse5("dis2_pulse5", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis2_pulse6("dis2_pulse6", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis2_pulse7("dis2_pulse7", "Intensity Distribution", 16384, 0, 65535);

  TH1F dis3_pulse0("dis3_pulse0", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis3_pulse1("dis3_pulse1", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis3_pulse2("dis3_pulse2", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis3_pulse3("dis3_pulse3", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis3_pulse4("dis3_pulse4", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis3_pulse5("dis3_pulse5", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis3_pulse6("dis3_pulse6", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis3_pulse7("dis3_pulse7", "Intensity Distribution", 16384, 0, 65535);

  TH1F dis4_pulse0("dis4_pulse0", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis4_pulse1("dis4_pulse1", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis4_pulse2("dis4_pulse2", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis4_pulse3("dis4_pulse3", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis4_pulse4("dis4_pulse4", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis4_pulse5("dis4_pulse5", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis4_pulse6("dis4_pulse6", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis4_pulse7("dis4_pulse7", "Intensity Distribution", 16384, 0, 65535);

  TH1F dis5_pulse0("dis5_pulse0", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis5_pulse1("dis5_pulse1", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis5_pulse2("dis5_pulse2", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis5_pulse3("dis5_pulse3", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis5_pulse4("dis5_pulse4", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis5_pulse5("dis5_pulse5", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis5_pulse6("dis5_pulse6", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis5_pulse7("dis5_pulse7", "Intensity Distribution", 16384, 0, 65535);

  TH1F dis6_pulse0("dis6_pulse0", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis6_pulse1("dis6_pulse1", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis6_pulse2("dis6_pulse2", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis6_pulse3("dis6_pulse3", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis6_pulse4("dis6_pulse4", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis6_pulse5("dis6_pulse5", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis6_pulse6("dis6_pulse6", "Intensity Distribution", 16384, 0, 65535);
  TH1F dis6_pulse7("dis6_pulse7", "Intensity Distribution", 16384, 0, 65535);

  // Intensities
  double Int[6][8];
  double err_Int[6][8];

  // Count Cycles
  vector <unsigned> count[6];
  bool startCycle[6];

  vector <unsigned> count400[6];
  bool startCycle400[6];

  for (unsigned i = 0; i < 6; i++){
    count[i].clear();
    count[i].push_back(0);
    startCycle[i] = false;
    count400[i].clear();
    count400[i].push_back(0);
    startCycle400[i] = false;
    for (unsigned k = 0; k < 8; k++){
      Int[i][k] = 0;
      err_Int[i][k] = 0;
    }
  }
  
  // Beta
  double beta[8] = {0};
  double err_beta[8] = {0};

  // Distribution of intensity values
  vector < vector < unsigned > > distrib; distrib.clear(); distrib.resize(8);

  // Wavelengths
  vector <unsigned short> wave; wave.clear();
  wave.push_back(375);
  wave.push_back(385);
  wave.push_back(400);
  wave.push_back(425);
  wave.push_back(450);
  wave.push_back(470);
  wave.push_back(495);
  wave.push_back(525);
  
  // Basic Structures
  vector < Slice > data; 
  string file;
  DataGrabber readData;
  PatternRecognition Kostas(100,400);
  TFile* outFile = new TFile("Results/System_Tests/BetaTesting2.root","RECREATE");


  // Loop for all files
  for (unsigned selectFile = 0; selectFile < 6; selectFile++){
    if (selectFile == 0){
      file = "Data/System_Tests/System_Test1_10m";
    }
    else if (selectFile == 1){
      file = "Data/System_Tests/System_Test1_16m";
    }
    else if (selectFile == 2){
      file = "Data/System_Tests/System_Test1_20m";
    }
    else if (selectFile == 3){
      file = "Data/System_Tests/System_Test2_10m";
    }
    else if (selectFile == 4){
      file = "Data/System_Tests/System_Test2_16m";
    }
    else {
      file = "Data/System_Tests/System_Test3_20m";
    }
    readData.Open(file);
    readData.Prepare(data);
    readData.Fill(data);

    Kostas.Stage_1(data);
    Kostas.Stage_2(data);
    Kostas.Stage_3(data,wave);

    for (unsigned i = 0; i < 8; i++){
      distrib[i].clear();
    }

    // Get the distribution of Intensities
    for (unsigned long i=0; i < data.size(); i++){
      // Data Visualization
      if (selectFile == 0){
	raw1_ph1_10m.Fill(i, data[i].GetInt1());
	raw1_ph2_10m.Fill(i, data[i].GetInt2());
      }
      else if (selectFile == 1){
        raw1_ph1_16m.Fill(i, data[i].GetInt1());
	raw1_ph2_16m.Fill(i, data[i].GetInt2());
      }
      else if (selectFile == 2){
        raw1_ph1_20m.Fill(i, data[i].GetInt1());
	raw1_ph2_20m.Fill(i, data[i].GetInt2());
      }
      else if (selectFile == 3){
        raw2_ph1_10m.Fill(i, data[i].GetInt1());
	raw2_ph2_10m.Fill(i, data[i].GetInt2());
      }
      else if (selectFile == 4){
	raw2_ph1_16m.Fill(i, data[i].GetInt1());
	raw2_ph2_16m.Fill(i, data[i].GetInt2());
      }
      else {
	raw3_ph1_20m.Fill(i, data[i].GetInt1());
	raw3_ph2_20m.Fill(i, data[i].GetInt2());
      }
      if (!data[i].DARK_RESET){
	if (!startCycle[selectFile]){
	  count[selectFile].back()++;
	}
	else{
	  count[selectFile].push_back(1);
	  startCycle[selectFile] = false;
	}
      }
      else{
	startCycle[selectFile] = true;
      }

      if (data[i].GetWave() == 400){
	if (!startCycle400[selectFile]){
	  count400[selectFile].back()++;
	}
	else{
	  count400[selectFile].push_back(1);
	  startCycle400[selectFile] = false;
	}
      }
      else{
	startCycle400[selectFile] = true;
      }
      if (data[i].GetWave() != 0 && data[i].PULSE){
	// Data Visualization
	if (selectFile == 0){
	  stg1_ph1_10m.Fill(i, data[i].GetInt1());
	  stg1_ph2_10m.Fill(i, data[i].GetInt2());
	}
	else if (selectFile == 1){
	  stg1_ph1_16m.Fill(i, data[i].GetInt1());
	  stg1_ph2_16m.Fill(i, data[i].GetInt2());
	}
	else if (selectFile == 2){
	  stg1_ph1_20m.Fill(i, data[i].GetInt1());
	  stg1_ph2_20m.Fill(i, data[i].GetInt2());
	}
	else if (selectFile == 3){
	  stg2_ph1_10m.Fill(i, data[i].GetInt1());
	  stg2_ph2_10m.Fill(i, data[i].GetInt2());
	}
	else if (selectFile == 4){
	  stg2_ph1_16m.Fill(i, data[i].GetInt1());
	  stg2_ph2_16m.Fill(i, data[i].GetInt2());
	}
	else {
	  stg3_ph1_20m.Fill(i, data[i].GetInt1());
	  stg3_ph2_20m.Fill(i, data[i].GetInt2());
	}

	// Data fall into waves
	if (data[i].GetWave() == 375){
	  distrib[0].push_back(data[i].GetInt1());
	  distrib[0].push_back(data[i].GetInt2());
	  if (selectFile == 0) {
	    dis1_pulse0.Fill(data[i].GetInt1());
	    dis1_pulse0.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 1){
	    dis2_pulse0.Fill(data[i].GetInt1());
	    dis2_pulse0.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 2){
	    dis3_pulse0.Fill(data[i].GetInt1());
	    dis3_pulse0.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 3){
	    dis4_pulse0.Fill(data[i].GetInt1());
	    dis4_pulse0.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 4){
	    dis5_pulse0.Fill(data[i].GetInt1());
	    dis5_pulse0.Fill(data[i].GetInt2());
	  }
	  else{
	    dis6_pulse0.Fill(data[i].GetInt1());
	    dis6_pulse0.Fill(data[i].GetInt2());
	  }
	}
	else if (data[i].GetWave() == 385){
	  distrib[1].push_back(data[i].GetInt1());
	  distrib[1].push_back(data[i].GetInt2());
	  if (selectFile == 0) {
	    dis1_pulse1.Fill(data[i].GetInt1());
	    dis1_pulse1.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 1){
	    dis2_pulse1.Fill(data[i].GetInt1());
	    dis2_pulse1.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 2){
	    dis3_pulse1.Fill(data[i].GetInt1());
	    dis3_pulse1.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 3){
	    dis4_pulse1.Fill(data[i].GetInt1());
	    dis4_pulse1.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 4){
	    dis5_pulse1.Fill(data[i].GetInt1());
	    dis5_pulse1.Fill(data[i].GetInt2());
	  }
	  else{
	    dis6_pulse1.Fill(data[i].GetInt1());
	    dis6_pulse1.Fill(data[i].GetInt2());
	  }
	}
	else if (data[i].GetWave() == 400){
	  distrib[2].push_back(data[i].GetInt1());
	  distrib[2].push_back(data[i].GetInt2());
	  if (selectFile == 0) {
	    dis1_pulse2.Fill(data[i].GetInt1());
	    dis1_pulse2.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 1){
	    dis2_pulse2.Fill(data[i].GetInt1());
	    dis2_pulse2.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 2){
	    dis3_pulse2.Fill(data[i].GetInt1());
	    dis3_pulse2.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 3){
	    dis4_pulse2.Fill(data[i].GetInt1());
	    dis4_pulse2.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 4){
	    dis5_pulse2.Fill(data[i].GetInt1());
	    dis5_pulse2.Fill(data[i].GetInt2());
	  }
	  else{
	    dis6_pulse2.Fill(data[i].GetInt1());
	    dis6_pulse2.Fill(data[i].GetInt2());
	  }
	}
	else if (data[i].GetWave() == 425){
	  distrib[3].push_back(data[i].GetInt1());
	  distrib[3].push_back(data[i].GetInt2());
	  if (selectFile == 0) {
	    dis1_pulse3.Fill(data[i].GetInt1());
	    dis1_pulse3.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 1){
	    dis2_pulse3.Fill(data[i].GetInt1());
	    dis2_pulse3.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 2){
	    dis3_pulse3.Fill(data[i].GetInt1());
	    dis3_pulse3.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 3){
	    dis4_pulse3.Fill(data[i].GetInt1());
	    dis4_pulse3.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 4){
	    dis5_pulse3.Fill(data[i].GetInt1());
	    dis5_pulse3.Fill(data[i].GetInt2());
	  }
	  else{
	    dis6_pulse3.Fill(data[i].GetInt1());
	    dis6_pulse3.Fill(data[i].GetInt2());
	  }
	}
	else if (data[i].GetWave() == 450){
	  distrib[4].push_back(data[i].GetInt1());
	  distrib[4].push_back(data[i].GetInt2());
	  if (selectFile == 0) {
	    dis1_pulse4.Fill(data[i].GetInt1());
	    dis1_pulse4.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 1){
	    dis2_pulse4.Fill(data[i].GetInt1());
	    dis2_pulse4.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 2){
	    dis3_pulse4.Fill(data[i].GetInt1());
	    dis3_pulse4.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 3){
	    dis4_pulse4.Fill(data[i].GetInt1());
	    dis4_pulse4.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 4){
	    dis5_pulse4.Fill(data[i].GetInt1());
	    dis5_pulse4.Fill(data[i].GetInt2());
	  }
	  else{
	    dis6_pulse4.Fill(data[i].GetInt1());
	    dis6_pulse4.Fill(data[i].GetInt2());
	  }
	}
	else if (data[i].GetWave() == 470){
	  distrib[5].push_back(data[i].GetInt1());
	  distrib[5].push_back(data[i].GetInt2());
	  if (selectFile == 0) {
	    dis1_pulse5.Fill(data[i].GetInt1());
	    dis1_pulse5.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 1){
	    dis2_pulse5.Fill(data[i].GetInt1());
	    dis2_pulse5.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 2){
	    dis3_pulse5.Fill(data[i].GetInt1());
	    dis3_pulse5.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 3){
	    dis4_pulse5.Fill(data[i].GetInt1());
	    dis4_pulse5.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 4){
	    dis5_pulse5.Fill(data[i].GetInt1());
	    dis5_pulse5.Fill(data[i].GetInt2());
	  }
	  else{
	    dis6_pulse5.Fill(data[i].GetInt1());
	    dis6_pulse5.Fill(data[i].GetInt2());
	  }
	}
	else if (data[i].GetWave() == 495){
	  distrib[6].push_back(data[i].GetInt1());
	  distrib[6].push_back(data[i].GetInt2());
	  if (selectFile == 0) {
	    dis1_pulse6.Fill(data[i].GetInt1());
	    dis1_pulse6.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 1){
	    dis2_pulse6.Fill(data[i].GetInt1());
	    dis2_pulse6.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 2){
	    dis3_pulse6.Fill(data[i].GetInt1());
	    dis3_pulse6.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 3){
	    dis4_pulse6.Fill(data[i].GetInt1());
	    dis4_pulse6.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 4){
	    dis5_pulse6.Fill(data[i].GetInt1());
	    dis5_pulse6.Fill(data[i].GetInt2());
	  }
	  else{
	    dis6_pulse6.Fill(data[i].GetInt1());
	    dis6_pulse6.Fill(data[i].GetInt2());
	  }
	}
	else if (data[i].GetWave() == 525){
	  distrib[7].push_back(data[i].GetInt1());
	  distrib[7].push_back(data[i].GetInt2());
	  if (selectFile == 0) {
	    dis1_pulse7.Fill(data[i].GetInt1());
	    dis1_pulse7.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 1){
	    dis2_pulse7.Fill(data[i].GetInt1());
	    dis2_pulse7.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 2){
	    dis3_pulse7.Fill(data[i].GetInt1());
	    dis3_pulse7.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 3){
	    dis4_pulse7.Fill(data[i].GetInt1());
	    dis4_pulse7.Fill(data[i].GetInt2());
	  }
	  else if (selectFile == 4){
	    dis5_pulse7.Fill(data[i].GetInt1());
	    dis5_pulse7.Fill(data[i].GetInt2());
	  }
	  else{
	    dis6_pulse7.Fill(data[i].GetInt1());
	    dis6_pulse7.Fill(data[i].GetInt2());
	  }
	}
      }
    }

    // Mean Intensity
    for (unsigned k = 0; k < 8; k++){
      for (unsigned i = 0; i < distrib[k].size(); i++){
	Int[selectFile][k] += distrib[k][i];
      }
      Int[selectFile][k] = Int[selectFile][k] / distrib[k].size();
    }

    // Find the STD or Error of Intensity
    for (unsigned k = 0; k < 8; k++){
      for (unsigned i = 0; i < distrib[k].size(); i++){
	err_Int[selectFile][k] = err_Int[selectFile][k] + pow(distrib[k][i] - Int[selectFile][k],2);
      }
      err_Int[selectFile][k] = err_Int[selectFile][k] / distrib.size();
      err_Int[selectFile][k] = sqrt(err_Int[selectFile][k]);
    }
  }


  cout << " ~ ~ ~ TEST 1 ~ ~ ~ " << endl << endl;
  cout << "Rs = " << R1 << " and Rl = " << R2 << endl;
  for (unsigned k = 0; k < 8; k++){
    beta[k] = log(Int[0][k] / Int[1][k]) + 2 * log(R1 / R2);
    beta[k] = beta[k] / (R2 - R1);
    cout << "For k: " << k << ", transmission length is: " << -1/beta[k] << endl;
    cout << "Beta is: " << beta[k] << endl;
  }
  cout << endl;

  cout << "Rs = " << R2 << " and Rl = " << R3 << endl;
  for (unsigned k = 0; k < 8; k++){
    beta[k] = log(Int[1][k] / Int[2][k]) + 2 * log(R2 / R3);
    beta[k] = beta[k] / (R3 - R2);
    cout << "For k: " << k << ", transmission length is: " << -1/beta[k] << endl;
    cout << "Beta is: " << beta[k] << endl;
  }
  cout << endl;

  cout << "Rs = " << R1 << " and Rl = " << R3 << endl;
  for (unsigned k = 0; k < 8; k++){
    beta[k] = log(Int[0][k] / Int[2][k]) + 2 * log(R1 / R3);
    beta[k] = beta[k] / (R3 - R1);
    cout << "For k: " << k << ", transmission length is: " << -1/beta[k] << endl;
    cout << "Beta is: " << beta[k] << endl;
  }
  cout << endl;


  cout << " ~ ~ ~ TEST 2 ~ ~ ~ " << endl << endl;
  cout << "Rs = " << R1 << " and Rl = " << R2 << endl;
  for (unsigned k = 0; k < 8; k++){
    beta[k] = log(Int[3][k] / Int[4][k]) + 2 * log(R1 / R2);
    beta[k] = beta[k] / (R2 - R1);
    cout << "For k: " << k << ", transmission length is: " << -1/beta[k] << endl;
    cout << "Beta is: " << beta[k] << endl;
  }
  cout << endl;

  cout << "Rs = " << R2 << " and Rl = " << R3 << endl;
  for (unsigned k = 0; k < 8; k++){
    beta[k] = log(Int[4][k] / Int[5][k]) + 2 * log(R2 / R3);
    beta[k] = beta[k] / (R3 - R2);
    cout << "For k: " << k << ", transmission length is: " << -1/beta[k] << endl;
    cout << "Beta is: " << beta[k] << endl;
  }
  cout << endl;

  cout << "Rs = " << R1 << " and Rl = " << R3 << endl;
  for (unsigned k = 0; k < 8; k++){
    beta[k] = log(Int[3][k] / Int[5][k]) + 2 * log(R1 / R3);
    beta[k] = beta[k] / (R3 - R1);
    cout << "For k: " << k << ", transmission length is: " << -1/beta[k] << endl;
    cout << "Beta is: " << beta[k] << endl;
  }
  cout << endl;

  for (unsigned int y = 0; y < 6; y++){
    cout << " ~ ~ File: " << y+1 << " ~ ~ " << endl << endl;
    for (unsigned int l = 0; l < count[y].size(); l++){
      cout << count[y][l] << endl;
    }
    cout << endl << endl;
  }

  for (unsigned int y = 0; y < 6; y++){
    cout << " ~ ~ Special 3rd Pulse, File: " << y+1 << " ~ ~ " << endl << endl;
    for (unsigned int l = 0; l < count400[y].size(); l++){
      cout << count400[y][l] << endl;
    }
    cout << endl << endl;
  }


  raw1_ph1_10m.Write();
  raw1_ph2_10m.Write();
  raw1_ph1_16m.Write();
  raw1_ph2_16m.Write();
  raw1_ph1_20m.Write();
  raw1_ph2_20m.Write();

  raw2_ph1_10m.Write();
  raw2_ph2_10m.Write();
  raw2_ph1_16m.Write();
  raw2_ph2_16m.Write();
  raw3_ph1_20m.Write();
  raw3_ph2_20m.Write();

  stg1_ph1_10m.Write();
  stg1_ph2_10m.Write();
  stg1_ph1_16m.Write();
  stg1_ph2_16m.Write();
  stg1_ph1_20m.Write();
  stg1_ph2_20m.Write();

  stg2_ph1_10m.Write();
  stg2_ph2_10m.Write();
  stg2_ph1_16m.Write();
  stg2_ph2_16m.Write();
  stg3_ph1_20m.Write();
  stg3_ph2_20m.Write();

  dis1_pulse0.Write();
  dis1_pulse1.Write();
  dis1_pulse2.Write();
  dis1_pulse3.Write();
  dis1_pulse4.Write();
  dis1_pulse5.Write();
  dis1_pulse6.Write();
  dis1_pulse7.Write();

  dis2_pulse0.Write();
  dis2_pulse1.Write();
  dis2_pulse2.Write();
  dis2_pulse3.Write();
  dis2_pulse4.Write();
  dis2_pulse5.Write();
  dis2_pulse6.Write();
  dis2_pulse7.Write();

  dis3_pulse0.Write();
  dis3_pulse1.Write();
  dis3_pulse2.Write();
  dis3_pulse3.Write();
  dis3_pulse4.Write();
  dis3_pulse5.Write();
  dis3_pulse6.Write();
  dis3_pulse7.Write();

  dis4_pulse0.Write();
  dis4_pulse1.Write();
  dis4_pulse2.Write();
  dis4_pulse3.Write();
  dis4_pulse4.Write();
  dis4_pulse5.Write();
  dis4_pulse6.Write();
  dis4_pulse7.Write();

  dis5_pulse0.Write();
  dis5_pulse1.Write();
  dis5_pulse2.Write();
  dis5_pulse3.Write();
  dis5_pulse4.Write();
  dis5_pulse5.Write();
  dis5_pulse6.Write();
  dis5_pulse7.Write();

  dis6_pulse0.Write();
  dis6_pulse1.Write();
  dis6_pulse2.Write();
  dis6_pulse3.Write();
  dis6_pulse4.Write();
  dis6_pulse5.Write();
  dis6_pulse6.Write();
  dis6_pulse7.Write();

  outFile -> Close();

  cout << endl << "Wrote file 'Results/System_Tests/BetaTesting2.root'" << endl;
  
  return 0;
}
