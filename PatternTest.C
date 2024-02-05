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

  double slope1 = 0, slope2 = 0;
  double bestSlope1 = 0, bestSlope2 = 0;
  vector < Slice > data;
  string file;
  DataGrabber readData;
  vector <unsigned short> wave; wave.clear();
  wave.push_back(375);
  wave.push_back(385);
  wave.push_back(400);
  wave.push_back(425);
  wave.push_back(450);
  wave.push_back(470);
  wave.push_back(495);
  wave.push_back(525);

  // Count Cycles
  vector <unsigned> count[6];

  for (unsigned i = 0; i < 6; i++){
    count[i].clear();
    count[i].push_back(0);
  }
  
  TFile* outFile = new TFile("Results/Slopes/PatternTesting.root","RECREATE");
  
  file = "Data/Filter_Tests/ND4_64_FilterTest_DOMLab";
  readData.Open(file);
  readData.Prepare_Test(data);
  readData.Fill_Test(data);
  TH1F low_1_f3("low_1_f3","Intensity 1 LOWs [4-64]",221000,0,221000);
  TH1F low_2_f3("low_2_f3","Intensity 2 LOWs [4-64]",221000,0,221000);
  TH1F mid_1_f3("mid_1_f3","Intensity 1 MIDs [4-64]",221000,0,221000);
  TH1F mid_2_f3("mid_2_f3","Intensity 2 MIDs [4-64]",221000,0,221000);
  TH1F high_1_f3("high_1_f3","Intensity 1 HIGHs [4-64]",221000,0,221000);
  TH1F high_2_f3("high_2_f3","Intensity 2 HIGHs [4-64]",221000,0,221000);
  TH1F else_1_f3("else_1_f3","Intensity 1 ELSEs [4-64]",221000,0,221000);
  TH1F else_2_f3("else_2_f3","Intensity 2 ELSEs [4-64]",221000,0,221000);
  TH1F abn_1_f3("abn_1_f3","Intensity 1 ABNORMALs [4-64]",221000,0,221000);
  TH1F abn_2_f3("abn_2_f3","Intensity 2 ABNORMALs [4-64]",221000,0,221000);
  TH1F jump_1_f3("jump_1_f3","Intensity 1 JUMPIEs [4-64]",221000,0,221000);
  TH1F jump_2_f3("jump_2_f3","Intensity 2 JUMPIEs [4-64]",221000,0,221000);

  TH1F slope_1_f3("slope_1_f3","Photodiode 1 Best Slopes (3-points)[4-64]",221000,0,221000);
  TH1F slope_2_f3("slope_2_f3","Photodiode 2 Best Slopes (3-points)[4-64]",221000,0,221000);
  TH1F std_1_f3("std_1_f3","Photodiode 1 STDs (3-points)[4-64]",221000,0,221000);
  TH1F std_2_f3("std_2_f3","Photodiode 2 STDs (3-points)[4-64]",221000,0,221000);
  TH1F jumper_1_f3("jumper_1_f3","PH 1 Jumpers by Slopes [4-64]",221000,0,221000);
  TH1F jumper_2_f3("jumper_2_f3","PH 2 Jumpers by Slopes [4-64]",221000,0,221000);

  TH1F stability_1_f3("stability_1_f3","Stability [4-64]",221000,0,221000);
  TH1F stability_2_f3("stability_2_f3","Stability [4-64]",221000,0,221000);

  TH1F dark_1_f3("dark_1_f3","Intensity 1 DARKs [4-64]",221000,0,221000);
  TH1F dark_2_f3("dark_2_f3","Intensity 2 DARKs [4-64]",221000,0,221000);
  TH1F darkr_1_f3("darkr_1_f3","Intensity 1 DARKs [4-64]",221000,0,221000);
  TH1F darkr_2_f3("darkr_2_f3","Intensity 2 DARKs [4-64]",221000,0,221000);
  TH1F stem_1_f3("stem_1_f3","Intensity 1 STEMs [4-64]",221000,0,221000);
  TH1F stem_2_f3("stem_2_f3","Intensity 2 STEMs [4-64]",221000,0,221000);
  TH1F pulse_1_f3("pulse_1_f3","Intensity 1 PULSEs [4-64]",221000,0,221000);
  TH1F pulse_2_f3("pulse_2_f3","Intensity 2 PULSEs [4-64]",221000,0,221000);
  TH1F error_1_f3("error_1_f3","Intensity 1 ERRORs [4-64]",221000,0,221000);
  TH1F error_2_f3("error_2_f3","Intensity 2 ERRORs [4-64]",221000,0,221000);
  TH1F else2_1_f3("else2_1_f3","Intensity 1 ELSEs [4-64]",221000,0,221000);
  TH1F else2_2_f3("else2_2_f3","Intensity 2 ELSEs [4-64]",221000,0,221000);

  TH1F stable1_f3("stable1_f3","Stability of Data point [4-64]",221000,0,221000);
  TH1F stable2_f3("stable2_f3","Stability of Data point [4-64]",221000,0,221000);
  TH1F unstable1_f3("unstable1_f3","Unstability of Data point [4-64]",221000,0,221000);
  TH1F unstable2_f3("unstable2_f3","Unstability of Data point [4-64]",221000,0,221000);
  TH1F jumping1_f3("jumping1_f3","Jumping of Data point [4-64]",221000,0,221000);
  TH1F jumping2_f3("jumping2_f3","Jumping of Data point [4-64]",221000,0,221000);

  TH1F wave0_f3("wave0_f3","First Wavelength Data [4-64]",221000,0,221000);
  TH1F wave1_f3("wave1_f3","Second Wavelength Data [4-64]",221000,0,221000);
  TH1F wave2_f3("wave2_f3","Third Wavelength Data [4-64]",221000,0,221000);
  TH1F wave3_f3("wave3_f3","Fourth Wavelength Data [4-64]",221000,0,221000);
  TH1F wave4_f3("wave4_f3","Fifth Wavelength Data [4-64]",221000,0,221000);
  TH1F wave5_f3("wave5_f3","Sixth Wavelength Data [4-64]",221000,0,221000);
  TH1F wave6_f3("wave6_f3","Seventh Wavelength Data [4-64]",221000,0,221000);
  TH1F wave7_f3("wave7_f3","Eighth Wavelength Data [4-64]",221000,0,221000);
  

  PatternRecognition Kostas;
  Kostas.Stage_1(data);
  Kostas.Stage_2(data);
  Kostas.Stage_3(data,wave);
  
  for (unsigned long i = 0; i < data.size(); i++){
    if (data[i].ZERO_HIGH){
      high_1_f3.Fill(i,data[i].GetInt1());
      high_2_f3.Fill(i,data[i].GetInt2());
    }
    else if (data[i].ZERO_LOW){
      low_1_f3.Fill(i,data[i].GetInt1());
      low_2_f3.Fill(i,data[i].GetInt2());
    }
    else if (data[i].ZERO_STEM){
      mid_1_f3.Fill(i,data[i].GetInt1());
      mid_2_f3.Fill(i,data[i].GetInt2());
    }
    else if (data[i].ZERO_ABNORMAL){
      abn_1_f3.Fill(i,data[i].GetInt1());
      abn_2_f3.Fill(i,data[i].GetInt2());
    }
    else {
      else_1_f3.Fill(i,data[i].GetInt1());
      else_2_f3.Fill(i,data[i].GetInt2());
    }

    

    if (data[i].DARK_RESET){
      darkr_1_f3.Fill(i,6000);
      darkr_2_f3.Fill(i,6000);
    }
    else if (data[i].DARK){
      dark_1_f3.Fill(i,4000);
      dark_2_f3.Fill(i,4000);
    }
    else if (data[i].PULSE){
      pulse_1_f3.Fill(i,data[i].GetInt1());
      pulse_2_f3.Fill(i,data[i].GetInt2());
    }
    else if (data[i].STEM){
      stem_1_f3.Fill(i,data[i].GetInt1());
      stem_2_f3.Fill(i,data[i].GetInt2());
    }
    else if (data[i].ERROR){
      error_1_f3.Fill(i,data[i].GetInt1());
      error_2_f3.Fill(i,data[i].GetInt2());
    }
    else {
      else2_1_f3.Fill(i,data[i].GetInt1());
      else2_2_f3.Fill(i,data[i].GetInt2());
    }

    if (data[i].GetWave() == 375 && data[i].PULSE) wave0_f3.Fill(i,data[i].GetInt1());
    else if (data[i].GetWave() == 385 && data[i].PULSE) wave1_f3.Fill(i,data[i].GetInt1());
    else if (data[i].GetWave() == 400 && data[i].PULSE) wave2_f3.Fill(i,data[i].GetInt1());
    else if (data[i].GetWave() == 425 && data[i].PULSE) wave3_f3.Fill(i,data[i].GetInt1());
    else if (data[i].GetWave() == 450 && data[i].PULSE) wave4_f3.Fill(i,data[i].GetInt1());
    else if (data[i].GetWave() == 470 && data[i].PULSE) wave5_f3.Fill(i,data[i].GetInt1());
    else if (data[i].GetWave() == 495 && data[i].PULSE) wave6_f3.Fill(i,data[i].GetInt1());
    else if (data[i].GetWave() == 525 && data[i].PULSE) wave7_f3.Fill(i,data[i].GetInt1());
    
    
    if (data[i].IS_STABLE){
      stable1_f3.Fill(i,data[i].GetInt1());
      stable2_f3.Fill(i,data[i].GetInt2());
    }
    else{
      unstable1_f3.Fill(i,data[i].GetInt1());
      unstable2_f3.Fill(i,data[i].GetInt2());
    }

    if (data[i].JUMPER){
      jumping1_f3.Fill(i,data[i].GetInt1());
      jumping2_f3.Fill(i,data[i].GetInt2());
    }

    
    slope_1_f3.Fill(i,data[i].slope1);
    slope_2_f3.Fill(i,data[i].slope2);

    std_1_f3.Fill(i,data[i].std1);
    std_2_f3.Fill(i,data[i].std2);

    if (abs(data[i].slope1) < 150){
      stability_1_f3.Fill(i,data[i].GetInt1());
    }
    if (abs(data[i].slope2) < 150){
      stability_2_f3.Fill(i,data[i].GetInt2());
    }
    
    if (i > 0){
      slope1 = data[i].GetInt1() - data[i-1].GetInt1();
      slope2 = data[i].GetInt2() - data[i-1].GetInt2();
    }
    else {
      slope1 = 0;
      slope2 = 0;
    }

    if (abs((slope1 - bestSlope1) / bestSlope1) > 0.9){
      jumper_1_f3.Fill(i,data[i].GetInt1());
    }
    if (abs((slope2 - bestSlope2) / bestSlope2) > 0.9){
      jumper_2_f3.Fill(i,data[i].GetInt2());
    }

  }
    
  for (unsigned int y = 0; y < 6; y++){
    cout << " ~ ~ Vector: " << y << " ~ ~ " << endl << endl;
    for (unsigned int l = 0; l < count[y].size(); l++){
      cout << count[y][l] << endl;
    }
    cout << endl << endl;
  }

  low_1_f3.Write();
  low_2_f3.Write();
  mid_1_f3.Write();
  mid_2_f3.Write();
  high_1_f3.Write();
  high_2_f3.Write();
  else_1_f3.Write();
  else_2_f3.Write();
  abn_1_f3.Write();
  abn_2_f3.Write();
  jump_1_f3.Write();
  jump_2_f3.Write();
  slope_1_f3.Write();
  slope_2_f3.Write();
  std_1_f3.Write();
  std_2_f3.Write();
  stability_1_f3.Write();
  stability_2_f3.Write();
  jumper_1_f3.Write();
  jumper_2_f3.Write();

  dark_1_f3.Write();
  dark_2_f3.Write();
  darkr_1_f3.Write();
  darkr_2_f3.Write();
  stem_1_f3.Write();
  stem_2_f3.Write();
  pulse_1_f3.Write();
  pulse_2_f3.Write();
  error_1_f3.Write();
  error_2_f3.Write();
  else2_1_f3.Write();
  else2_2_f3.Write();

  stable1_f3.Write();
  stable2_f3.Write();
  unstable1_f3.Write();
  unstable2_f3.Write();
  jumping1_f3.Write();
  jumping2_f3.Write();

  wave0_f3.Write();
  wave1_f3.Write();
  wave2_f3.Write();
  wave3_f3.Write();
  wave4_f3.Write();
  wave5_f3.Write();
  wave6_f3.Write();
  wave7_f3.Write();

  unsigned long long dump_counter;
  file = "Data/Revisit_2009/Capo2_15m";
  readData.Open(file);
  readData.Prepare_Old(data);
  readData.Fill_Old(data, dump_counter);
  TH1F low_1_c15("low_1_c15","Intensity 1 LOWs Capo2 - 15m",101000,0,101000);
  TH1F low_2_c15("low_2_c15","Intensity 2 LOWs Capo2 - 15m",101000,0,101000);
  TH1F mid_1_c15("mid_1_c15","Intensity 1 MIDs Capo2 - 15m",101000,0,101000);
  TH1F mid_2_c15("mid_2_c15","Intensity 2 MIDs Capo2 - 15m",101000,0,101000);
  TH1F high_1_c15("high_1_c15","Intensity 1 HIGHs Capo2 - 15m",101000,0,101000);
  TH1F high_2_c15("high_2_c15","Intensity 2 HIGHs Capo2 - 15m",101000,0,101000);
  TH1F else_1_c15("else_1_c15","Intensity 1 ELSEs Capo2 - 15m",101000,0,101000);
  TH1F else_2_c15("else_2_c15","Intensity 2 ELSEs Capo2 - 15m",101000,0,101000);
  TH1F abn_1_c15("abn_1_c15","Intensity 1 ABNORMALs Capo2 - 15m",101000,0,101000);
  TH1F abn_2_c15("abn_2_c15","Intensity 2 ABNORMALs Capo2 - 15m",101000,0,101000);
  TH1F jump_1_c15("jump_1_c15","Intensity 1 JUMPIEs Capo2 - 15m",101000,0,101000);
  TH1F jump_2_c15("jump_2_c15","Intensity 2 JUMPIEs Capo2 - 15m",101000,0,101000);

  TH1F slope_1_c15("slope_1_c15","Photodiode 1 Best Slopes (3-points) Capo2 - 15m",101000,0,101000);
  TH1F slope_2_c15("slope_2_c15","Photodiode 2 Best Slopes (3-points) Capo2 - 15m",101000,0,101000);
  TH1F std_1_c15("std_1_c15","Photodiode 1 STDs (3-points) Capo2 - 15m",101000,0,101000);
  TH1F std_2_c15("std_2_c15","Photodiode 2 STDs (3-points) Capo2 - 15m",101000,0,101000);
  TH1F jumper_1_c15("jumper_1_c15","PH 1 Jumpers by Slopes Capo2 - 15m",101000,0,101000);
  TH1F jumper_2_c15("jumper_2_c15","PH 2 Jumpers by Slopes Capo2 - 15m",101000,0,101000);

  TH1F stability_1_c15("stability_1_c15","Stability Capo2 - 15m",101000,0,101000);
  TH1F stability_2_c15("stability_2_c15","Stability Capo2 - 15m",101000,0,101000);

  TH1F dark_1_c15("dark_1_c15","Intensity 1 DARKs Capo2 - 15m",101000,0,101000);
  TH1F dark_2_c15("dark_2_c15","Intensity 2 DARKs Capo2 - 15m",101000,0,101000);
  TH1F darkr_1_c15("darkr_1_c15","Intensity 1 DARKs Capo2 - 15m",101000,0,101000);
  TH1F darkr_2_c15("darkr_2_c15","Intensity 2 DARKs Capo2 - 15m",101000,0,101000);
  TH1F stem_1_c15("stem_1_c15","Intensity 1 STEMs Capo2 - 15m",101000,0,101000);
  TH1F stem_2_c15("stem_2_c15","Intensity 2 STEMs Capo2 - 15m",101000,0,101000);
  TH1F pulse_1_c15("pulse_1_c15","Intensity 1 PULSEs Capo2 - 15m",101000,0,101000);
  TH1F pulse_2_c15("pulse_2_c15","Intensity 2 PULSEs Capo2 - 15m",101000,0,101000);
  TH1F error_1_c15("error_1_c15","Intensity 1 ERRORs Capo2 - 15m",101000,0,101000);
  TH1F error_2_c15("error_2_c15","Intensity 2 ERRORs Capo2 - 15m",101000,0,101000);
  TH1F else2_1_c15("else2_1_c15","Intensity 1 ELSEs Capo2 - 15m",101000,0,101000);
  TH1F else2_2_c15("else2_2_c15","Intensity 2 ELSEs Capo2 - 15m",101000,0,101000);

  TH1F stable1_c15("stable1_c15","Stability of Data point Capo2 - 15m",101000,0,101000);
  TH1F stable2_c15("stable2_c15","Stability of Data point Capo2 - 15m",101000,0,101000);
  TH1F unstable1_c15("unstable1_c15","Unstability of Data point Capo2 - 15m",101000,0,101000);
  TH1F unstable2_c15("unstable2_c15","Unstability of Data point Capo2 - 15m",101000,0,101000);
  TH1F jumping1_c15("jumping1_c15","Jumping of Data point Capo2 - 15m",101000,0,101000);
  TH1F jumping2_c15("jumping2_c15","Jumping of Data point Capo2 - 15m",101000,0,101000);

  TH1F wave0_c15("wave0_c15","First Wavelength Data Capo2 - 15m",101000,0,101000);
  TH1F wave1_c15("wave1_c15","Second Wavelength Data Capo2 - 15m",101000,0,101000);
  TH1F wave2_c15("wave2_c15","Third Wavelength Data Capo2 - 15m",101000,0,101000);
  TH1F wave3_c15("wave3_c15","Fourth Wavelength Data Capo2 - 15m",101000,0,101000);
  TH1F wave4_c15("wave4_c15","Fifth Wavelength Data Capo2 - 15m",101000,0,101000);
  TH1F wave5_c15("wave5_c15","Sixth Wavelength Data Capo2 - 15m",101000,0,101000);
  TH1F wave6_c15("wave6_c15","Seventh Wavelength Data Capo2 - 15m",101000,0,101000);
  TH1F wave7_c15("wave7_c15","Eighth Wavelength Data Capo2 - 15m",101000,0,101000);

  slope1 = 0;
  slope2 = 0;
  bestSlope1 = 0;
  bestSlope2 = 0;
  Kostas.Stage_1(data);
  Kostas.Stage_2(data);
  Kostas.Stage_3(data,wave);
  
  for (unsigned long i = 68000; i < 168000; i++){
    if (data[i].ZERO_HIGH){
      high_1_c15.Fill(i-68000,data[i].GetInt1());
      high_2_c15.Fill(i-68000,data[i].GetInt2());
    }
    else if (data[i].ZERO_LOW){
      low_1_c15.Fill(i-68000,data[i].GetInt1());
      low_2_c15.Fill(i-68000,data[i].GetInt2());
    }
    else if (data[i].ZERO_STEM){
      mid_1_c15.Fill(i-68000,data[i].GetInt1());
      mid_2_c15.Fill(i-68000,data[i].GetInt2());
    }
    else if (data[i].ZERO_ABNORMAL){
      abn_1_c15.Fill(i-68000,data[i].GetInt1());
      abn_2_c15.Fill(i-68000,data[i].GetInt2());
    }
    else{
      else_1_c15.Fill(i-68000,data[i].GetInt1());
      else_2_c15.Fill(i-68000,data[i].GetInt2());
    }

    
    if (data[i].DARK_RESET){
      darkr_1_c15.Fill(i-68000,6000);
      darkr_2_c15.Fill(i-68000,6000);
    }
    else if (data[i].DARK){
      dark_1_c15.Fill(i-68000,4000);
      dark_2_c15.Fill(i-68000,4000);
    }
    else if (data[i].PULSE){
      pulse_1_c15.Fill(i-68000,data[i].GetInt1());
      pulse_2_c15.Fill(i-68000,data[i].GetInt2());
    }
    else if (data[i].STEM){
      stem_1_c15.Fill(i-68000,data[i].GetInt1());
      stem_2_c15.Fill(i-68000,data[i].GetInt2());
    }
    else if (data[i].ERROR){
      error_1_c15.Fill(i-68000,data[i].GetInt1());
      error_2_c15.Fill(i-68000,data[i].GetInt2());
    }
    else{
      else2_1_c15.Fill(i-68000,data[i].GetInt1());
      else2_2_c15.Fill(i-68000,data[i].GetInt2());
    }

    if (data[i].GetWave() == 375 && data[i].PULSE) wave0_c15.Fill(i-68000,data[i].GetInt1());
    else if (data[i].GetWave() == 385 && data[i].PULSE) wave1_c15.Fill(i-68000,data[i].GetInt1());
    else if (data[i].GetWave() == 400 && data[i].PULSE) wave2_c15.Fill(i-68000,data[i].GetInt1());
    else if (data[i].GetWave() == 425 && data[i].PULSE) wave3_c15.Fill(i-68000,data[i].GetInt1());
    else if (data[i].GetWave() == 450 && data[i].PULSE) wave4_c15.Fill(i-68000,data[i].GetInt1());
    else if (data[i].GetWave() == 470 && data[i].PULSE) wave5_c15.Fill(i-68000,data[i].GetInt1());
    else if (data[i].GetWave() == 495 && data[i].PULSE) wave6_c15.Fill(i-68000,data[i].GetInt1());
    else if (data[i].GetWave() == 525 && data[i].PULSE) wave7_c15.Fill(i-68000,data[i].GetInt1());


    if (data[i].IS_STABLE){
      stable1_c15.Fill(i-68000,data[i].GetInt1());
      stable2_c15.Fill(i-68000,data[i].GetInt2());
    }
    else{
      unstable1_c15.Fill(i-68000,data[i].GetInt1());
      unstable2_c15.Fill(i-68000,data[i].GetInt2());
    }
    if (data[i].JUMPER){
      jumping1_c15.Fill(i-68000,data[i].GetInt1());
      jumping2_c15.Fill(i-68000,data[i].GetInt2());
    }
    
    
    slope_1_c15.Fill(i-68000,data[i].slope1);
    slope_2_c15.Fill(i-68000,data[i].slope2);

    std_1_c15.Fill(i-68000,data[i].std1);
    std_2_c15.Fill(i-68000,data[i].std2);

    if (abs(data[i].slope1) < 150){
      stability_1_c15.Fill(i-68000,data[i].GetInt1());
    }
    if (abs(data[i].slope2) < 150){
      stability_2_c15.Fill(i-68000,data[i].GetInt2());
    }
    
    if (i > 0){
      slope1 = data[i].GetInt1() - data[i-1].GetInt1();
      slope2 = data[i].GetInt2() - data[i-1].GetInt2();
    }
    else {
      slope1 = 0;
      slope2 = 0;
    }

    if (abs((slope1 - bestSlope1) / bestSlope1) > 0.9){
      jumper_1_c15.Fill(i-68000,data[i].GetInt1());
    }
    if (abs((slope2 - bestSlope2) / bestSlope2) > 0.9){
      jumper_2_c15.Fill(i-68000,data[i].GetInt2());
    }
  }
    
    

  low_1_c15.Write();
  low_2_c15.Write();
  high_1_c15.Write();
  high_2_c15.Write();
  mid_1_c15.Write();
  mid_2_c15.Write();
  else_1_c15.Write();
  else_2_c15.Write();
  abn_1_c15.Write();
  abn_2_c15.Write();
  jump_1_c15.Write();
  jump_2_c15.Write();
  slope_1_c15.Write();
  slope_2_c15.Write();
  std_1_c15.Write();
  std_2_c15.Write();
  stability_1_c15.Write();
  stability_2_c15.Write();
  jumper_1_c15.Write();
  jumper_2_c15.Write();

  dark_1_c15.Write();
  dark_2_c15.Write();
  darkr_1_c15.Write();
  darkr_2_c15.Write();
  stem_1_c15.Write();
  stem_2_c15.Write();
  pulse_1_c15.Write();
  pulse_2_c15.Write();
  else2_1_c15.Write();
  else2_2_c15.Write();
  error_1_c15.Write();
  error_2_c15.Write();

  stable1_c15.Write();
  stable2_c15.Write();
  unstable1_c15.Write();
  unstable2_c15.Write();
  jumping1_c15.Write();
  jumping2_c15.Write();

  wave0_c15.Write();
  wave1_c15.Write();
  wave2_c15.Write();
  wave3_c15.Write();
  wave4_c15.Write();
  wave5_c15.Write();
  wave6_c15.Write();
  wave7_c15.Write();

  file = "Data/Revisit_2009/Nestor_17m";
  readData.Open(file);
  readData.Prepare_Old(data);
  readData.Fill_Old(data, dump_counter);
  
  TH1F low_1_n17("low_1_n17","Intensity 1 LOWs Nestor - 17m",90000,0,90000);
  TH1F low_2_n17("low_2_n17","Intensity 2 LOWs Nestor - 17m",90000,0,90000);
  TH1F mid_1_n17("mid_1_n17","Intensity 1 MIDs Nestor - 17m",90000,0,90000);
  TH1F mid_2_n17("mid_2_n17","Intensity 2 MIDs Nestor - 17m",90000,0,90000);
  TH1F high_1_n17("high_1_n17","Intensity 1 HIGHs Nestor - 17m",90000,0,90000);
  TH1F high_2_n17("high_2_n17","Intensity 2 HIGHs Nestor - 17m",90000,0,90000);
  TH1F else_1_n17("else_1_n17","Intensity 1 ELSEs Nestor - 17m",90000,0,90000);
  TH1F else_2_n17("else_2_n17","Intensity 2 ELSEs Nestor - 17m",90000,0,90000);
  TH1F abn_1_n17("abn_1_n17","Intensity 1 ABNORMALs Nestor - 17m",90000,0,90000);
  TH1F abn_2_n17("abn_2_n17","Intensity 2 ABNORMALs Nestor - 17m",90000,0,90000);
  TH1F jump_1_n17("jump_1_n17","Intensity 1 JUMPIEs Nestor - 17m",90000,0,90000);
  TH1F jump_2_n17("jump_2_n17","Intensity 2 JUMPIEs Nestor - 17m",90000,0,90000);

  TH1F slope_1_n17("slope_1_n17","Photodiode 1 Best Slopes (3-points) Nestor - 17m",90000,0,90000);
  TH1F slope_2_n17("slope_2_n17","Photodiode 2 Best Slopes (3-points) Nestor - 17m",90000,0,90000);
  TH1F std_1_n17("std_1_n17","Photodiode 1 STDs (3-points) Nestor - 17m",90000,0,90000);
  TH1F std_2_n17("std_2_n17","Photodiode 2 STDs (3-points) Nestor - 17m",90000,0,90000);
  TH1F jumper_1_n17("jumper_1_n17","PH 1 Jumpers by Slopes Nestor - 17m",90000,0,90000);
  TH1F jumper_2_n17("jumper_2_n17","PH 2 Jumpers by Slopes Nestor - 17m",90000,0,90000);

  TH1F stability_1_n17("stability_1_n17","Stability Nestor - 17m",90000,0,90000);
  TH1F stability_2_n17("stability_2_n17","Stability Nestor - 17m",90000,0,90000);

  TH1F dark_1_n17("dark_1_n17","Intensity 1 DARKs Nestor - 17m",90000,0,90000);
  TH1F dark_2_n17("dark_2_n17","Intensity 2 DARKs Nestor - 17m",90000,0,90000);
  TH1F darkr_1_n17("darkr_1_n17","Intensity 1 DARKs Nestor - 17m",90000,0,90000);
  TH1F darkr_2_n17("darkr_2_n17","Intensity 2 DARKs Nestor - 17m",90000,0,90000);
  TH1F stem_1_n17("stem_1_n17","Intensity 1 STEMs Nestor - 17m",90000,0,90000);
  TH1F stem_2_n17("stem_2_n17","Intensity 2 STEMs Nestor - 17m",90000,0,90000);
  TH1F pulse_1_n17("pulse_1_n17","Intensity 1 PULSEs Nestor - 17m",90000,0,90000);
  TH1F pulse_2_n17("pulse_2_n17","Intensity 2 PULSEs Nestor - 17m",90000,0,90000);
  TH1F error_1_n17("error_1_n17","Intensity 1 ERRORs Nestor - 17m",90000,0,90000);
  TH1F error_2_n17("error_2_n17","Intensity 2 ERRORs Nestor - 17m",90000,0,90000);
  TH1F else2_1_n17("else2_1_n17","Intensity 1 ELSEs Nestor - 17m",90000,0,90000);
  TH1F else2_2_n17("else2_2_n17","Intensity 2 ELSEs Nestor - 17m",90000,0,90000);

  TH1F stable1_n17("stable1_n17","Stability of Data point Nestor - 17m",90000,0,90000);
  TH1F stable2_n17("stable2_n17","Stability of Data point Nestor - 17m",90000,0,90000);
  TH1F unstable1_n17("unstable1_n17","Unstability of Data point Nestor - 17m",90000,0,90000);
  TH1F unstable2_n17("unstable2_n17","Unstability of Data point Nestor - 17m",90000,0,90000);
  TH1F jumping1_n17("jumping1_n17","Jumping of Data point Nestor - 17m",90000,0,90000);
  TH1F jumping2_n17("jumping2_n17","Jumping of Data point Nestor - 17m",90000,0,90000);

  TH1F wave0_n17("wave0_n17","First Wavelength Data Nestor - 17m",90000,0,90000);
  TH1F wave1_n17("wave1_n17","Second Wavelength Data Nestor - 17m",90000,0,90000);
  TH1F wave2_n17("wave2_n17","Third Wavelength Data Nestor - 17m",90000,0,90000);
  TH1F wave3_n17("wave3_n17","Fourth Wavelength Data Nestor - 17m",90000,0,90000);
  TH1F wave4_n17("wave4_n17","Fifth Wavelength Data Nestor - 17m",90000,0,90000);
  TH1F wave5_n17("wave5_n17","Sixth Wavelength Data Nestor - 17m",90000,0,90000);
  TH1F wave6_n17("wave6_n17","Seventh Wavelength Data Nestor - 17m",90000,0,90000);
  TH1F wave7_n17("wave7_n17","Eighth Wavelength Data Nestor - 17m",90000,0,90000);
  
  slope1 = 0;
  slope2 = 0;
  bestSlope1 = 0;
  bestSlope2 = 0;
  Kostas.Stage_1(data);
  Kostas.Stage_2(data);
  Kostas.Stage_3(data,wave);
  
  for (unsigned long i = 55000; i < 145000; i++){
    if (data[i].ZERO_HIGH){
      high_1_n17.Fill(i-55000,data[i].GetInt1());
      high_2_n17.Fill(i-55000,data[i].GetInt2());
    }
    else if (data[i].ZERO_LOW){
      low_1_n17.Fill(i-55000,data[i].GetInt1());
      low_2_n17.Fill(i-55000,data[i].GetInt2());
    }
    else if (data[i].ZERO_STEM){
      mid_1_n17.Fill(i-55000,data[i].GetInt1());
      mid_2_n17.Fill(i-55000,data[i].GetInt2());
    }
    else if (data[i].ZERO_ABNORMAL){
      abn_1_n17.Fill(i-55000,data[i].GetInt1());
      abn_2_n17.Fill(i-55000,data[i].GetInt2());
    }
    else{
      else_1_n17.Fill(i-55000,data[i].GetInt1());
      else_2_n17.Fill(i-55000,data[i].GetInt2());
    }

    
    if (data[i].DARK_RESET){
      darkr_1_n17.Fill(i-55000,6000);
      darkr_2_n17.Fill(i-55000,6000);
    }
    else if (data[i].DARK){
      dark_1_n17.Fill(i-55000,4000);
      dark_2_n17.Fill(i-55000,4000);
    }
    else if (data[i].PULSE){
      pulse_1_n17.Fill(i-55000,data[i].GetInt1());
      pulse_2_n17.Fill(i-55000,data[i].GetInt2());
    }
    else if (data[i].STEM){
      stem_1_n17.Fill(i-55000,data[i].GetInt1());
      stem_2_n17.Fill(i-55000,data[i].GetInt2());
    }
    else if (data[i].ERROR){
      error_1_n17.Fill(i-55000,data[i].GetInt1());
      error_2_n17.Fill(i-55000,data[i].GetInt2());
    }
    else{
      else2_1_n17.Fill(i-55000,data[i].GetInt1());
      else2_2_n17.Fill(i-55000,data[i].GetInt2());
    }

    if (data[i].GetWave() == 375 && data[i].PULSE) wave0_n17.Fill(i-55000,data[i].GetInt1());
    else if (data[i].GetWave() == 385 && data[i].PULSE) wave1_n17.Fill(i-55000,data[i].GetInt1());
    else if (data[i].GetWave() == 400 && data[i].PULSE) wave2_n17.Fill(i-55000,data[i].GetInt1());
    else if (data[i].GetWave() == 425 && data[i].PULSE) wave3_n17.Fill(i-55000,data[i].GetInt1());
    else if (data[i].GetWave() == 450 && data[i].PULSE) wave4_n17.Fill(i-55000,data[i].GetInt1());
    else if (data[i].GetWave() == 470 && data[i].PULSE) wave5_n17.Fill(i-55000,data[i].GetInt1());
    else if (data[i].GetWave() == 495 && data[i].PULSE) wave6_n17.Fill(i-55000,data[i].GetInt1());
    else if (data[i].GetWave() == 525 && data[i].PULSE) wave7_n17.Fill(i-55000,data[i].GetInt1());


    if (data[i].IS_STABLE){
      stable1_n17.Fill(i-55000,data[i].GetInt1());
      stable2_n17.Fill(i-55000,data[i].GetInt2());
    }
    else{
      unstable1_n17.Fill(i-55000,data[i].GetInt1());
      unstable2_n17.Fill(i-55000,data[i].GetInt2());
    }
    if (data[i].JUMPER){
      jumping1_n17.Fill(i-55000,data[i].GetInt1());
      jumping2_n17.Fill(i-55000,data[i].GetInt2());
    }
    
    
    slope_1_n17.Fill(i-55000,data[i].slope1);
    slope_2_n17.Fill(i-55000,data[i].slope2);

    std_1_n17.Fill(i-55000,data[i].std1);
    std_2_n17.Fill(i-55000,data[i].std2);

    if (abs(data[i].slope1) < 150){
      stability_1_n17.Fill(i-55000,data[i].GetInt1());
    }
    if (abs(data[i].slope2) < 150){
      stability_2_n17.Fill(i-55000,data[i].GetInt2());
    }
    
    if (i > 0){
      slope1 = data[i].GetInt1() - data[i-1].GetInt1();
      slope2 = data[i].GetInt2() - data[i-1].GetInt2();
    }
    else {
      slope1 = 0;
      slope2 = 0;
    }

    if (abs((slope1 - bestSlope1) / bestSlope1) > 0.9){
      jumper_1_n17.Fill(i-55000,data[i].GetInt1());
    }
    if (abs((slope2 - bestSlope2) / bestSlope2) > 0.9){
      jumper_2_n17.Fill(i-55000,data[i].GetInt2());
    }
  }
    
    

  low_1_n17.Write();
  low_2_n17.Write();
  high_1_n17.Write();
  high_2_n17.Write();
  mid_1_n17.Write();
  mid_2_n17.Write();
  else_1_n17.Write();
  else_2_n17.Write();
  abn_1_n17.Write();
  abn_2_n17.Write();
  jump_1_n17.Write();
  jump_2_n17.Write();
  slope_1_n17.Write();
  slope_2_n17.Write();
  std_1_n17.Write();
  std_2_n17.Write();
  stability_1_n17.Write();
  stability_2_n17.Write();
  jumper_1_n17.Write();
  jumper_2_n17.Write();

  dark_1_n17.Write();
  dark_2_n17.Write();
  darkr_1_n17.Write();
  darkr_2_n17.Write();
  stem_1_n17.Write();
  stem_2_n17.Write();
  pulse_1_n17.Write();
  pulse_2_n17.Write();
  else2_1_n17.Write();
  else2_2_n17.Write();
  error_1_n17.Write();
  error_2_n17.Write();

  stable1_n17.Write();
  stable2_n17.Write();
  unstable1_n17.Write();
  unstable2_n17.Write();
  jumping1_n17.Write();
  jumping2_n17.Write();

  wave0_n17.Write();
  wave1_n17.Write();
  wave2_n17.Write();
  wave3_n17.Write();
  wave4_n17.Write();
  wave5_n17.Write();
  wave6_n17.Write();
  wave7_n17.Write();
  
  outFile -> Close();
  delete outFile;
  return 0;
}
