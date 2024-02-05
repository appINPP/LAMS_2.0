#include <vector>
#include <iostream>
#include <cmath>
#include "Slices.hh"
#include "DataGrabber.hh"
#include "Pattern.hh"
#include "Report.hh"
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
  Stopwatch chronos;
  
  vector <vector <float> > int1_4;
  vector <vector <float> > int2_4;
  vector <vector <float> > int1_5;
  vector <vector <float> > int2_5;

  vector <vector <float> > int14_24;
  vector <vector <float> > int14_15;
  vector <vector <float> > int14_25;
  vector <vector <float> > int24_15;
  vector <vector <float> > int24_25;
  vector <vector <float> > int15_25;
  
  int1_4.clear();
  int2_4.clear();
  int1_5.clear();
  int2_5.clear();

  int14_24.clear();
  int14_15.clear();
  int14_25.clear();
  int24_15.clear();
  int24_25.clear();
  int15_25.clear();

  int14_24.resize(8);
  int14_15.resize(8);
  int14_25.resize(8);
  int24_15.resize(8);
  int24_25.resize(8);
  int15_25.resize(8);

  

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

  vector <string> file;
  vector <string> fname;
  file.clear();
  fname.clear();
  
  file.push_back(static_cast<string>("Data/Com_Tests/Test1_COM3"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test1_COM4"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test1_COM5"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test2_COM3_20m_alone"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test2_COM3_20m_paired"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test2_COM4_16m_paired"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test3_COM3_20m_paired"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test3_COM4_16m_paired"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test3_COM5_10m_paired"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test4_COM3_10m"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test4_COM4_16"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test4_COM5_10"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test5_COM3"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test6_COM4"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test6_COM5"));
  
  file.push_back(static_cast<string>("Data/Com_Tests/Test7_COM3_10m"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test7_COM4_10m_start"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test7_COM4_10m_end"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test7_COM4_10m_end2"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test7_COM5_10m"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test8_COM3_20m"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test8_COM4_16m"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test8_COM5_10m"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test9_COM3_10m"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test9_COM4_10m"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test9_COM5_10m"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test10_COM3_10m"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test10_COM4_10m"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test11_COM3_10m"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test11_COM4_10m"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test11_COM5_10m"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test12_COM3_10m"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test12_COM4_10m"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test12_COM5_10m"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test12_COM3_15m"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test12_COM4_15m"));
  file.push_back(static_cast<string>("Data/Com_Tests/Test12_COM5_15m"));
  
  fname.push_back(static_cast<string>("test1_com3")); //0
  fname.push_back(static_cast<string>("test1_com4"));
  fname.push_back(static_cast<string>("test1_com5"));
  fname.push_back(static_cast<string>("test2_com3_20m_alone"));
  fname.push_back(static_cast<string>("test2_com3_20m_paired"));
  fname.push_back(static_cast<string>("test2_com4_16m_paired")); //5
  fname.push_back(static_cast<string>("test3_com3_20m_paired"));
  fname.push_back(static_cast<string>("test3_com4_16m_paired"));
  fname.push_back(static_cast<string>("test3_com5_10m_paired"));
  fname.push_back(static_cast<string>("test4_com3_10m"));
  fname.push_back(static_cast<string>("test4_com4_16m")); //10
  fname.push_back(static_cast<string>("test4_com5_10m"));
  fname.push_back(static_cast<string>("test5_com3"));
  fname.push_back(static_cast<string>("test6_com4"));
  fname.push_back(static_cast<string>("test6_com5"));
  
  fname.push_back(static_cast<string>("test7_com3_10m")); //15
  fname.push_back(static_cast<string>("test7_com4_10m_start"));
  fname.push_back(static_cast<string>("test7_com4_10m_end"));
  fname.push_back(static_cast<string>("test7_com4_10m_end2"));
  fname.push_back(static_cast<string>("test7_com5_10m"));
  fname.push_back(static_cast<string>("test8_com3_20m")); //20
  fname.push_back(static_cast<string>("test8_com4_16m"));
  fname.push_back(static_cast<string>("test8_com5_10m"));
  fname.push_back(static_cast<string>("test9_com3_10m"));
  fname.push_back(static_cast<string>("test9_com4_10m"));
  fname.push_back(static_cast<string>("test9_com5_10m")); //25
  fname.push_back(static_cast<string>("test10_com3_10m"));
  fname.push_back(static_cast<string>("test10_com4_10m"));
  fname.push_back(static_cast<string>("test11_com3_10m"));
  fname.push_back(static_cast<string>("test11_com4_10m"));
  fname.push_back(static_cast<string>("test11_com5_10m")); //30

  fname.push_back(static_cast<string>("test12_com3_10m"));
  fname.push_back(static_cast<string>("test12_com4_10m"));
  fname.push_back(static_cast<string>("test12_com5_10m"));
  fname.push_back(static_cast<string>("test12_com3_15m"));
  fname.push_back(static_cast<string>("test12_com4_15m")); //35
  fname.push_back(static_cast<string>("test12_com5_15m"));

  TFile* outFile = new TFile("Results/Com_Tests/ComTesting.root","RECREATE");
  DataGrabber readData;
  Report Klark;
  Report COM3;
  Report COM4;
  Report COM5;
  PatternRecognition Kostas(100,60000);
  vector <Slice> data;
  vector <TH1F*> ph1_raw;
  vector <TH1F*> ph2_raw;
  vector <TH1F*> ph1_valid;
  vector <TH1F*> ph2_valid;
  string ref_name;
  string title_name;
  
  for (unsigned i = 0; i < file.size(); i++){
    chronos.Start(1);

    readData.Open(file[i]);
    readData.Prepare(data);
    readData.Fill(data);
      
    title_name = "Raw Data";
    ref_name = fname[i] + static_cast<string>("_ph1_raw");
    ph1_raw.push_back(MakeHist(ref_name,title_name,data.size(),0,data.size()));
    ref_name = fname[i] + static_cast<string>("_ph2_raw");
    ph2_raw.push_back(MakeHist(ref_name,title_name,data.size(),0,data.size()));

    title_name = "Validated Cycles Data";
    ref_name = fname[i] + static_cast<string>("_ph1_valid");
    ph1_valid.push_back(MakeHist(ref_name,title_name,data.size(),0,data.size()));
    ref_name = fname[i] + static_cast<string>("_ph2_valid");
    ph2_valid.push_back(MakeHist(ref_name,title_name,data.size(),0,data.size()));

    ph1_raw[i] -> SetXTitle("Time");
    ph2_raw[i] -> SetXTitle("Time");
    ph1_valid[i] -> SetXTitle("Time");
    ph2_valid[i] -> SetXTitle("Time");

    ph1_raw[i] -> SetYTitle("Intensity Counts");
    ph2_raw[i] -> SetYTitle("Intensity Counts");
    ph1_valid[i] -> SetYTitle("Intensity Counts");
    ph2_valid[i] -> SetYTitle("Intensity Counts");

    if (i == 23){
      PatternRecognition Kostas2(200,60000);
      Kostas = Kostas2;
    }
    
    Kostas.Stage_1(data);
    Kostas.Stage_2(data);
    Kostas.Stage_3_1(data,wave);
    if (i == 29){
      Kostas.RemoveCycle(data,472);
    }
      
    if (i == 29){
      COM4.IntensityAnalysis(data,wave);
      //COM4.IntensityShow();
      int1_4 = COM4.GetInt1();
      int2_4 = COM4.GetInt2();
    }

    if (i == 30){
      //COM5.IntensityAnalysis(data,wave);
      //COM5.IntensityShow();
      int1_5 = COM5.GetInt1();
      int2_5 = COM5.GetInt2();
    }

    if (i == 31 || i == 34){
      //COM3.IntensityAnalysis(data,wave);
      //COM3.IntensityShow();
      COM3.CycleAnalysis(data);
      COM3.CycleShow();
    }
    
    if (i == 32 || i == 35){
      //COM4.IntensityAnalysis(data,wave);
      //COM4.IntensityShow();
      COM4.CycleAnalysis(data);
      COM4.CycleShow();
    }
    
    if (i == 33 || i == 36){
      //COM5.IntensityAnalysis(data,wave);
      //COM5.IntensityShow();
      COM5.CycleAnalysis(data);
      COM5.CycleShow();
    }

    for (unsigned v = 0; v < data.size(); v++){
      ph1_raw[i] -> Fill(v,data[v].GetInt1());
      ph2_raw[i] -> Fill(v,data[v].GetInt2());
      if (data[v].IS_CYCLE){
	ph1_valid[i] -> Fill(v,data[v].GetInt1());
	ph2_valid[i] -> Fill(v,data[v].GetInt2());
      }
    }

    ph1_raw[i] -> Write();
    ph2_raw[i] -> Write();
    ph1_valid[i] -> Write();
    ph2_valid[i] -> Write();

    
    delete ph1_raw[i];
    delete ph2_raw[i];
    delete ph1_valid[i];
    delete ph2_valid[i];
    chronos.Stop(1);
    cout << "Time of [" << i << "] <" << fname[i] << ">: " << chronos.Show(1);
  }

  
  outFile -> Close();
  cout << endl << "Wrote file 'Results/Com_Tests/ComTesting.root'" << endl;
  TFile* outFile2 = new TFile("Results/Com_Tests/ComInt.root","RECREATE");

  cout << "Debug: 1" << endl;
  vector <vector <TH1F*> > compare;
  compare.clear();
  compare.resize(8);
  vector <string> category;
  vector <string> refCat;
  category.clear();
  refCat.clear();
  cout << "Debug: 2" << endl;
  
  category.push_back(static_cast<string>("Int1 of Com4 VS Int2 of Com4"));
  category.push_back(static_cast<string>("Int1 of Com4 VS Int1 of Com5"));
  category.push_back(static_cast<string>("Int1 of Com4 VS Int2 of Com5"));
  category.push_back(static_cast<string>("Int2 of Com4 VS Int1 of Com5"));
  category.push_back(static_cast<string>("Int2 of Com4 VS Int2 of Com5"));
  category.push_back(static_cast<string>("Int1 of Com5 VS Int2 of Com5"));
		     
  refCat.push_back(static_cast<string>("int_14_24"));
  refCat.push_back(static_cast<string>("int_14_15"));
  refCat.push_back(static_cast<string>("int_14_25"));
  refCat.push_back(static_cast<string>("int_24_15"));
  refCat.push_back(static_cast<string>("int_24_25"));
  refCat.push_back(static_cast<string>("int_15_25"));

  cout << "Debug: 3" << endl;
  for (unsigned v = 0; v < 8; v++){
    title_name = " - Pulse " + NumToString(v);
    ref_name = "_" + NumToString(v);

    cout << "Debug: 4" << endl;
    for (unsigned i = 0; i < 6; i++){
      compare[v].push_back(MakeHist(refCat[i]+ref_name,category[i] + title_name,210,-0.005,0.1));
    }
    //for (unsigned i = 0; i < int1_4[v].size() - 3; i++){      
    for (unsigned i = 0; i < 481; i++){
      if (int1_4[v][i] > int2_4[v][i]) int14_24[v].push_back((int1_4[v][i] - int2_4[v][i])/int1_4[v][i]);
      else int14_24[v].push_back((int2_4[v][i] - int1_4[v][i])/int2_4[v][i]);
      compare[v][0] -> Fill(int14_24[v].back());

      if (int1_4[v][i] > int1_5[v][i+3]) int14_15[v].push_back((int1_4[v][i] - int1_5[v][i+3])/int1_4[v][i]);
      else int14_15[v].push_back((int1_5[v][i+3] - int1_4[v][i])/int1_5[v][i+3]);
      compare[v][1] -> Fill(int14_15[v].back());

      if (int1_4[v][i] > int2_5[v][i+3]) int14_25[v].push_back((int1_4[v][i] - int2_5[v][i+3])/int1_4[v][i]);
      else int14_25[v].push_back((int2_5[v][i+3] - int1_4[v][i])/int2_5[v][i+3]);
      compare[v][2] -> Fill(int14_25[v].back());

      if (int2_4[v][i] > int1_5[v][i+3]) int24_15[v].push_back((int2_4[v][i] - int1_5[v][i+3])/int2_4[v][i]);
      else int24_15[v].push_back((int1_5[v][i+3] - int2_4[v][i])/int1_5[v][i+3]);
      compare[v][3] -> Fill(int24_15[v].back());

      if (int2_4[v][i] > int2_5[v][i+3]) int24_25[v].push_back((int2_4[v][i] - int2_5[v][i+3])/int2_4[v][i]);
      else int24_25[v].push_back((int2_5[v][i+3] - int2_5[v][i])/int2_5[v][i+3]);
      compare[v][4] -> Fill(int24_25[v].back());

      if (int1_5[v][i] > int2_5[v][i]) int15_25[v].push_back((int1_5[v][i] - int2_5[v][i])/int1_5[v][i]);
      else int15_25[v].push_back((int2_5[v][i] - int1_5[v][i])/int2_5[v][i]);
      compare[v][5] -> Fill(int15_25[v].back());
      
    }

    cout << "Debug: 5" << endl;
    for (unsigned i = 0; i < 6; i++){
      compare[v][i] -> Write();
      delete compare[v][i];
    }
  }

  cout << "Debug: 6" << endl;
  cout << endl << "Wrote file 'Results/Com_Tests/ComInt.root'" << endl;
  outFile2 -> Close();
}
