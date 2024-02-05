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
  const double R2 = 15; // 2nd Distance
  const double R3 = 17; // 3rd Distance
  const double R4 = 22; // 4th Distance

  const double err_R1 = 0.05;
  const double err_R2 = 0.05;
  const double err_R3 = 0.05;
  const double err_R4 = 0.05;

  unsigned long long dummy;
  // Histograms
  TH1F pulse0_10m("pulse0_10m", "Pulse Plots", 200000, 0, 200000);
  TH1F pulse0_15m("pulse0_15m", "Pulse Plots", 200000, 0, 200000);
  TH1F pulse0_17m("pulse0_17m", "Pulse Plots", 200000, 0, 200000);
  TH1F pulse0_22m("pulse0_22m", "Pulse Plots", 200000, 0, 200000);

  TH1F pulse1_10m("pulse1_10m", "Pulse Plots", 200000, 0, 200000);
  TH1F pulse1_15m("pulse1_15m", "Pulse Plots", 200000, 0, 200000);
  TH1F pulse1_17m("pulse1_17m", "Pulse Plots", 200000, 0, 200000);
  TH1F pulse1_22m("pulse1_22m", "Pulse Plots", 200000, 0, 200000);

  TH1F pulse2_10m("pulse2_10m", "Pulse Plots", 200000, 0, 200000);
  TH1F pulse2_15m("pulse2_15m", "Pulse Plots", 200000, 0, 200000);
  TH1F pulse2_17m("pulse2_17m", "Pulse Plots", 200000, 0, 200000);
  TH1F pulse2_22m("pulse2_22m", "Pulse Plots", 200000, 0, 200000);

  TH1F pulse3_10m("pulse3_10m", "Pulse Plots", 200000, 0, 200000);
  TH1F pulse3_15m("pulse3_15m", "Pulse Plots", 200000, 0, 200000);
  TH1F pulse3_17m("pulse3_17m", "Pulse Plots", 200000, 0, 200000);
  TH1F pulse3_22m("pulse3_22m", "Pulse Plots", 200000, 0, 200000);

  TH1F pulse4_10m("pulse4_10m", "Pulse Plots", 200000, 0, 200000);
  TH1F pulse4_15m("pulse4_15m", "Pulse Plots", 200000, 0, 200000);
  TH1F pulse4_17m("pulse4_17m", "Pulse Plots", 200000, 0, 200000);
  TH1F pulse4_22m("pulse4_22m", "Pulse Plots", 200000, 0, 200000);

  TH1F pulse5_10m("pulse5_10m", "Pulse Plots", 200000, 0, 200000);
  TH1F pulse5_15m("pulse5_15m", "Pulse Plots", 200000, 0, 200000);
  TH1F pulse5_17m("pulse5_17m", "Pulse Plots", 200000, 0, 200000);
  TH1F pulse5_22m("pulse5_22m", "Pulse Plots", 200000, 0, 200000);

  TH1F pulse6_10m("pulse6_10m", "Pulse Plots", 200000, 0, 200000);
  TH1F pulse6_15m("pulse6_15m", "Pulse Plots", 200000, 0, 200000);
  TH1F pulse6_17m("pulse6_17m", "Pulse Plots", 200000, 0, 200000);
  TH1F pulse6_22m("pulse6_22m", "Pulse Plots", 200000, 0, 200000);

  TH1F pulse7_10m("pulse7_10m", "Pulse Plots", 200000, 0, 200000);
  TH1F pulse7_15m("pulse7_15m", "Pulse Plots", 200000, 0, 200000);
  TH1F pulse7_17m("pulse7_17m", "Pulse Plots", 200000, 0, 200000);
  TH1F pulse7_22m("pulse7_22m", "Pulse Plots", 200000, 0, 200000);

  TH1F pulse_no_10m("pulse_no_10m", "Pulse Plots", 200000, 0, 200000);
  TH1F pulse_no_15m("pulse_no_15m", "Pulse Plots", 200000, 0, 200000);
  TH1F pulse_no_17m("pulse_no_17m", "Pulse Plots", 200000, 0, 200000);
  TH1F pulse_no_22m("pulse_no_22m", "Pulse Plots", 200000, 0, 200000);

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

  // Intensities
  double Int[4][8];
  double err_Int[4][8];

  // Count Cycles
  vector <unsigned long long> count[4];
  bool startCycle[4];

  for (unsigned i = 0; i < 4; i++){
    count[i].clear();
    count[i].push_back(0);
    startCycle[i] = false;
    for (unsigned k = 0; k < 8; k++){
      Int[i][k] = 0;
      err_Int[i][k] = 0;
    }
  }
  
  // Beta
  double beta[8] = {0};
  double err_beta[8] = {0};

  // Distribution of intensity values
  vector < unsigned > distrib[8];

  for (unsigned i = 0; i < 8; i++){
    distrib[i].clear();
  }

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
  PatternRecognition Kostas(1000,4000);
  TFile* outFile = new TFile("Results/Revisit_2009/Beta2009_2.root","RECREATE");


  // Loop for all files
  for (unsigned selectFile = 0; selectFile < 4; selectFile++){
    if (selectFile == 0){
      file = "Data/Revisit_2009/Nestor_10m_Cut";
    }
    else if (selectFile == 1){
      file = "Data/Revisit_2009/Nestor_15m_Cut";
    }
    else if (selectFile == 2){
      file = "Data/Revisit_2009/Nestor_17m_Cut";
    }
    else {
      file = "Data/Revisit_2009/Nestor_23m_Cut";
    }
    readData.Open(file);
    readData.Prepare_Old(data);
    readData.Fill_Old(data,dummy);

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
      }
      else if (selectFile == 1){
      }
      else if (selectFile == 2){
      }
      else {
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
      if (data[i].PULSE){
	if (data[i].GetWave() == 375){
	  distrib[0].push_back(data[i].GetInt1());
	  distrib[0].push_back(data[i].GetInt2());
	  if (selectFile == 0) pulse0_10m.Fill(i,data[i].GetInt1());
	  else if (selectFile == 1) pulse0_15m.Fill(i,data[i].GetInt1());
	  else if (selectFile == 2) pulse0_17m.Fill(i,data[i].GetInt1());
	  else pulse0_22m.Fill(i,data[i].GetInt1());
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
	  else {
	    dis4_pulse0.Fill(data[i].GetInt1());
	    dis4_pulse0.Fill(data[i].GetInt2());
	  }
	}
	else if (data[i].GetWave() == 385){
	  distrib[1].push_back(data[i].GetInt1());
	  distrib[1].push_back(data[i].GetInt2());
	  if (selectFile == 0) pulse1_10m.Fill(i,data[i].GetInt1());
	  else if (selectFile == 1) pulse1_15m.Fill(i,data[i].GetInt1());
	  else if (selectFile == 2) pulse1_17m.Fill(i,data[i].GetInt1());
	  else pulse1_22m.Fill(i,data[i].GetInt1());
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
	  else {
	    dis4_pulse1.Fill(data[i].GetInt1());
	    dis4_pulse1.Fill(data[i].GetInt2());
	  }
	}
	else if (data[i].GetWave() == 400){
	  distrib[2].push_back(data[i].GetInt1());
	  distrib[2].push_back(data[i].GetInt2());
	  if (selectFile == 0) pulse2_10m.Fill(i,data[i].GetInt1());
	  else if (selectFile == 1) pulse2_15m.Fill(i,data[i].GetInt1());
	  else if (selectFile == 2) pulse2_17m.Fill(i,data[i].GetInt1());
	  else pulse2_22m.Fill(i,data[i].GetInt1());
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
	  else {
	    dis4_pulse2.Fill(data[i].GetInt1());
	    dis4_pulse2.Fill(data[i].GetInt2());
	  }
	}
	else if (data[i].GetWave() == 425){
	  distrib[3].push_back(data[i].GetInt1());
	  distrib[3].push_back(data[i].GetInt2());
	  if (selectFile == 0) pulse3_10m.Fill(i,data[i].GetInt1());
	  else if (selectFile == 1) pulse3_15m.Fill(i,data[i].GetInt1());
	  else if (selectFile == 2) pulse3_17m.Fill(i,data[i].GetInt1());
	  else pulse3_22m.Fill(i,data[i].GetInt1());
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
	  else {
	    dis4_pulse3.Fill(data[i].GetInt1());
	    dis4_pulse3.Fill(data[i].GetInt2());
	  }
	}
	else if (data[i].GetWave() == 450){
	  distrib[4].push_back(data[i].GetInt1());
	  distrib[4].push_back(data[i].GetInt2());
	  if (selectFile == 0) pulse4_10m.Fill(i,data[i].GetInt1());
	  else if (selectFile == 1) pulse4_15m.Fill(i,data[i].GetInt1());
	  else if (selectFile == 2) pulse4_17m.Fill(i,data[i].GetInt1());
	  else pulse4_22m.Fill(i,data[i].GetInt1());
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
	  else {
	    dis4_pulse4.Fill(data[i].GetInt1());
	    dis4_pulse4.Fill(data[i].GetInt2());
	  }
	}
	else if (data[i].GetWave() == 470){
	  distrib[5].push_back(data[i].GetInt1());
	  distrib[5].push_back(data[i].GetInt2());
	  if (selectFile == 0) pulse5_10m.Fill(i,data[i].GetInt1());
	  else if (selectFile == 1) pulse5_15m.Fill(i,data[i].GetInt1());
	  else if (selectFile == 2) pulse5_17m.Fill(i,data[i].GetInt1());
	  else pulse5_22m.Fill(i,data[i].GetInt1());
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
	  else {
	    dis4_pulse5.Fill(data[i].GetInt1());
	    dis4_pulse5.Fill(data[i].GetInt2());
	  }
	}
	else if (data[i].GetWave() == 495){
	  distrib[6].push_back(data[i].GetInt1());
	  distrib[6].push_back(data[i].GetInt2());
	  if (selectFile == 0) pulse6_10m.Fill(i,data[i].GetInt1());
	  else if (selectFile == 1) pulse6_15m.Fill(i,data[i].GetInt1());
	  else if (selectFile == 2) pulse6_17m.Fill(i,data[i].GetInt1());
	  else pulse6_22m.Fill(i,data[i].GetInt1());
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
	  else {
	    dis4_pulse6.Fill(data[i].GetInt1());
	    dis4_pulse6.Fill(data[i].GetInt2());
	  }
	}
	else if (data[i].GetWave() == 525){
	  distrib[7].push_back(data[i].GetInt1());
	  distrib[7].push_back(data[i].GetInt2());
	  if (selectFile == 0) pulse7_10m.Fill(i,data[i].GetInt1());
	  else if (selectFile == 1) pulse7_15m.Fill(i,data[i].GetInt1());
	  else if (selectFile == 2) pulse7_17m.Fill(i,data[i].GetInt1());
	  else pulse7_22m.Fill(i,data[i].GetInt1());
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
	  else {
	    dis4_pulse7.Fill(data[i].GetInt1());
	    dis4_pulse7.Fill(data[i].GetInt2());
	  }
	}
      }
      if (data[i].GetWave() == 0){
	if (selectFile == 0) pulse_no_10m.Fill(i,data[i].GetInt1());
	else if (selectFile == 1) pulse_no_15m.Fill(i,data[i].GetInt1());
	else if (selectFile == 2) pulse_no_17m.Fill(i,data[i].GetInt1());
	else pulse_no_22m.Fill(i,data[i].GetInt1());
      }
    }

    // Mean Intensity
    for (unsigned k = 0; k < 8; k++){
      for (unsigned i = 0; i < distrib[k].size(); i++){
	Int[selectFile][k] += distrib[k][i];
      }
      if (distrib[k].size() > 0){
	Int[selectFile][k] = Int[selectFile][k] / distrib[k].size();
      }
      else{
	Int[selectFile][k] = 1;
      }
    }

    // Find the STD or Error of Intensity
    for (unsigned k = 0; k < 8; k++){
      for (unsigned i = 0; i < distrib[k].size(); i++){
	err_Int[selectFile][k] = err_Int[selectFile][k] + pow(distrib[k][i] - Int[selectFile][k],2);
      }
      err_Int[selectFile][k] = err_Int[selectFile][k] / distrib[k].size();
      err_Int[selectFile][k] = sqrt(err_Int[selectFile][k]);
    }
  }


  cout << " ~ ~ ~ TEST 1 ~ ~ ~ " << endl << endl;
  cout << "Rs = " << R1 << " and Rl = " << R2 << endl;
  for (unsigned k = 0; k < 8; k++){
    cout << "Pulse = " << k << ": Int-Short = " << Int[0][k] << " and Int-Long = " << Int[1][k] << endl;
    beta[k] = log(Int[0][k] / Int[1][k]) + 2 * log(R1 / R2);
    beta[k] = beta[k] / (R2 - R1);
    cout << "For k: " << k << ", transmission length is: " << 1/beta[k] << endl;
    cout << "Beta is: " << beta[k] << endl;
  }
  cout << endl;

  cout << "Rs = " << R2 << " and Rl = " << R3 << endl;
  for (unsigned k = 0; k < 8; k++){
    cout << "Pulse = " << k << ": Int-Short = " << Int[1][k] << " and Int-Long = " << Int[2][k] << endl;
    beta[k] = log(Int[1][k] / Int[2][k]) + 2 * log(R2 / R3);
    beta[k] = beta[k] / (R3 - R2);
    cout << "For k: " << k << ", transmission length is: " << 1/beta[k] << endl;
    cout << "Beta is: " << beta[k] << endl;
  }
  cout << endl;

  cout << "Rs = " << R3 << " and Rl = " << R4 << endl;
  for (unsigned k = 0; k < 8; k++){
    cout << "Pulse = " << k << ": Int-Short = " << Int[2][k] << " and Int-Long = " << Int[3][k] << endl;
    beta[k] = log(Int[2][k] / Int[3][k]) + 2 * log(R3 / R4);
    beta[k] = beta[k] / (R4 - R3);
    cout << "For k: " << k << ", transmission length is: " << 1/beta[k] << endl;
    cout << "Beta is: " << beta[k] << endl;
  }
  cout << endl;

  cout << "Rs = " << R1 << " and Rl = " << R3 << endl;
  for (unsigned k = 0; k < 8; k++){
    cout << "Pulse = " << k << ": Int-Short = " << Int[0][k] << " and Int-Long = " << Int[2][k] << endl;
    beta[k] = log(Int[0][k] / Int[2][k]) + 2 * log(R1 / R3);
    beta[k] = beta[k] / (R3 - R1);
    cout << "For k: " << k << ", transmission length is: " << 1/beta[k] << endl;
    cout << "Beta is: " << beta[k] << endl;
  }
  cout << endl;

  cout << "Rs = " << R1 << " and Rl = " << R4 << endl;
  for (unsigned k = 0; k < 8; k++){
    cout << "Pulse = " << k << ": Int-Short = " << Int[0][k] << " and Int-Long = " << Int[3][k] << endl;
    beta[k] = log(Int[0][k] / Int[3][k]) + 2 * log(R1 / R4);
    beta[k] = beta[k] / (R4 - R1);
    cout << "For k: " << k << ", transmission length is: " << 1/beta[k] << endl;
    cout << "Beta is: " << beta[k] << endl;
  }
  cout << endl;

  cout << "Rs = " << R2 << " and Rl = " << R4 << endl;
  for (unsigned k = 0; k < 8; k++){
    cout << "Pulse = " << k << ": Int-Short = " << Int[1][k] << " and Int-Long = " << Int[3][k] << endl;
    beta[k] = log(Int[1][k] / Int[3][k]) + 2 * log(R2 / R4);
    beta[k] = beta[k] / (R4 - R2);
    cout << "For k: " << k << ", transmission length is: " << 1/beta[k] << endl;
    cout << "Beta is: " << beta[k] << endl;
  }
  cout << endl;


  
  /*
  for (unsigned int y = 0; y < 4; y++){
    cout << " ~ ~ File: " << y+1 << " ~ ~ " << endl << endl;
    for (unsigned int l = 0; l < count[y].size(); l++){
      cout << count[y][l] << endl;
    }
    cout << endl << endl;
  }
  */

  pulse0_10m.Write();
  pulse0_15m.Write();
  pulse0_17m.Write();
  pulse0_22m.Write();
  
  pulse1_10m.Write();
  pulse1_15m.Write();
  pulse1_17m.Write();
  pulse1_22m.Write();
  
  pulse2_10m.Write();
  pulse2_15m.Write();
  pulse2_17m.Write();
  pulse2_22m.Write();

  pulse3_10m.Write();
  pulse3_15m.Write();
  pulse3_17m.Write();
  pulse3_22m.Write();

  pulse4_10m.Write();
  pulse4_15m.Write();
  pulse4_17m.Write();
  pulse4_22m.Write();

  pulse5_10m.Write();
  pulse5_15m.Write();
  pulse5_17m.Write();
  pulse5_22m.Write();
  
  pulse6_10m.Write();
  pulse6_15m.Write();
  pulse6_17m.Write();
  pulse6_22m.Write();

  pulse7_10m.Write();
  pulse7_15m.Write();
  pulse7_17m.Write();
  pulse7_22m.Write();

  pulse_no_10m.Write();
  pulse_no_15m.Write();
  pulse_no_17m.Write();
  pulse_no_22m.Write();
  
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
  
  outFile -> Close();
  
  return 0;
}
