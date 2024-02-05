#include <vector>
#include <iostream>
#include <cmath>
#include "Slices.hh"
#include "DataGrabber.hh"
#include "Pattern.hh"
#include "LamsMath.hh"
#include "Tools.hh"

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
  
  // Distances of Source-Emitter, error is commmon for all distances
  //double R[4] = {10,15,20};
  double R[3] = {10,15,20};
  double R_err = 0.5;

  // Intensities of every pulse in every distance  
  double I_avg[8][3];
  double I_err[8][3];
  long nI[8][3]; // number of intensity points counted in, before doing the average intensity
  
  for (unsigned int i = 0; i < 8; i++){
    for (unsigned int k = 0; k < 3; k++){
      I_avg[i][k] = 0;
      I_err[i][k] = 0.01;
      nI[i][k] = 0;
    }
  }

  // Create Histograms
  vector < vector <TH1F* > > pulse;
  vector <TH1F* > expected;
  string ref_name;
  string hist_title;
  unsigned bin;
  float bottom_range = 0;
  float top_range;
  pulse.resize(8);
  for (unsigned i = 0; i < 8; i++){
    for (unsigned k = 0; k < 3; k++){
      if (k == 0){
	bin = 870000;
	top_range = bin;
      }
      else if (k == 1){
	bin = 620000;
	top_range = bin;
      }
      else{
	bin = 410000;
	top_range = bin;
      }
      ref_name = static_cast<string>("pulse") + NumToString(i+1) + static_cast<string>("_") + NumToString(R[k]) + static_cast<string>("m");
      hist_title = "Pulse: " + NumToString(i+1) + static_cast<string>(" - ") + NumToString(R[k]) + static_cast<string>("m");
      pulse[i].push_back( MakeHist(ref_name, hist_title, bin, bottom_range, top_range));

      if (i == 0){
	ref_name = static_cast<string>("expected_") + NumToString(R[k]) + static_cast<string>("m");
	hist_title = "Expected Cycles" + static_cast<string>(" - ") + NumToString(R[k]) + static_cast<string>("m");
	expected.push_back( MakeHist(ref_name, hist_title, bin, bottom_range, top_range));
      }
    }
  }
  
  // Wavelengths
  vector <unsigned short> wave;
  for (unsigned i = 0; i < 8; i++){
    wave.push_back(i);
  }
  
  // Basic Structures
  vector < Slice > data;
  string file;
  DataGrabber readData;
  PatternRecognition Pattern;
  TFile* outFile = new TFile("Results/Complete/CompleteNew.root","RECREATE");

  // Loop for all files
  for (unsigned selectFile = 0; selectFile < 3; selectFile++){
    if (selectFile == 0){
      Pattern = PatternRecognition(1000,60000);
      file = static_cast<string>("Data/Com_Tests/Test12_COM3_10m");
    }
    else if (selectFile == 1){
      Pattern = PatternRecognition(400,60000);
      file = static_cast<string>("Data/Com_Tests/Test12_COM3_15m");
    }
    else {
      Pattern = PatternRecognition(130,60000);
      file = static_cast<string>("Data/Com_Tests/Test8_COM3_20m");
    }
    data.clear();
    readData.Open(file);
    readData.Prepare(data);
    readData.Fill(data);
  
    Pattern.Stage_1(data);
    Pattern.Stage_2(data); 
    Pattern.Stage_3_1(data,wave);

    for (unsigned long long i = 0; i < data.size(); i++){
      if (selectFile == 2 && i >= 410000) continue;
      if (data[i].PULSE && data[i].IS_CYCLE && data[i].GetWave() > -1){
	pulse[data[i].GetWave()][selectFile] -> Fill(i,data[i].GetInt1());
	I_avg[data[i].GetWave()][selectFile] += data[i].GetInt1();
	nI[static_cast<unsigned>(data[i].GetWave())][selectFile]++;
      }
      else if (data[i].EXP_CYCLE){
        expected[selectFile] -> Fill(i,data[i].GetInt1());
      }
    }
  }
  

  for (unsigned int i = 0; i < 8; i++){
    for (unsigned int k = 0; k < 3; k++){
      I_avg[i][k] = I_avg[i][k]/nI[i][k];
      pulse[i][k] -> Write();
    }
  }

  for (unsigned int k = 0; k < 3; k++){
    expected[k] -> Write();
  }

  double b;
  for (unsigned i = 0; i < 8; i++){
    for (unsigned k = 0; k < 2; k++){
      for (unsigned g = k+1; g < 3; g++){
	cout << "[Pulse: " << i+1 << " |Rs, Rl = " << R[k] << ", " << R[g] <<  "]" << endl;
	b = beta(I_avg[i][k], I_avg[i][g], R[k], R[g]);
	cout << "  Beta =  " << b << endl << "    Transmission Length =  " << 1/b << endl;
      }
    }
    cout << endl;
  }

  cout << "" << R[0] << "m\t" << R[1] << "m\t" << R[2] << "m" << endl;
  for (unsigned i = 0; i < 8; i++){
    for (unsigned k = 0; k < 3; k++){
      cout << I_avg[i][k] << "\t";
    }
    cout << endl;
  }
  outFile -> Close();

  return 0;
}
