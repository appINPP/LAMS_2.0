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

int main(){

  std::string referenceName;
  std::vector <TH1F*> raw_ph1_10m;
  std::vector <TH1F*> raw_ph2_10m;

  raw_ph1_10m.resize(6);
  raw_ph2_10m.resize(6);

  for (unsigned i = 0; i < 6; i++){
    referenceName = static_cast<std::string>("raw_ph1_10m_") + ((i<3) ? "test1_com" : "test2_com") + NumToString(i%3+3);
    raw_ph1_10m[i] = new TH1F(referenceName.c_str(), "Calibration Test", 1400000, 0, 1400000);
    referenceName = static_cast<std::string>("raw_ph2_10m_") + ((i<3) ? "test1_com" : "test2_com") + NumToString(i%3+3);
    raw_ph2_10m[i] = new TH1F(referenceName.c_str(), "Calibration Test", 1400000, 0, 1400000);
  }

  std::vector <std::string> filename;
  filename.push_back("Data/Calibration_Tests/Com3_Calibration1");
  filename.push_back("Data/Calibration_Tests/Com4_Calibration1");
  filename.push_back("Data/Calibration_Tests/Com5_Calibration1");
  filename.push_back("Data/Calibration_Tests/Com3_Calibration2");
  filename.push_back("Data/Calibration_Tests/Com4_Calibration2");
  filename.push_back("Data/Calibration_Tests/Com5_Calibration2");

  std::vector <unsigned short> wave;
  for (unsigned i = 0; i < 8; i++){
    wave.push_back(i);
  }

  
  TFile* outFile = new TFile("Results/Calibration_Tests/Calibration.root","RECREATE");
  for (unsigned selectFile = 0; selectFile < filename.size(); selectFile++){
    
    // Basic Structures
    std::vector < Slice > data;
    DataGrabber readData;
    PatternRecognition Pattern;

    data.clear();
    readData.Open(filename[selectFile]);
    readData.Prepare(data);
    readData.Fill(data);
  
    Pattern.Stage_1(data);
    Pattern.Stage_2(data); 
    Pattern.Stage_3_1(data,wave);

    for (unsigned long i = 0; i < data.size(); i++){
      raw_ph1_10m[selectFile] -> Fill(i,data[i].GetInt1());
      raw_ph2_10m[selectFile] -> Fill(i,data[i].GetInt2());
    }

    raw_ph1_10m[selectFile] -> Write();
    raw_ph2_10m[selectFile] -> Write();
  }
  outFile -> Close();
  return 0;
}
