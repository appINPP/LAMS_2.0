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
  vector <string> file;
  vector <string> file2;
  DataGrabber readData;
  PatternRecognition Kostas(100,60000);

  file.clear();
  file.push_back(static_cast<string>("Data/System_Tests/System_Test1_10m"));
  file.push_back(static_cast<string>("Data/System_Tests/System_Test1_16m"));
  file.push_back(static_cast<string>("Data/System_Tests/System_Test1_20m"));
  file.push_back(static_cast<string>("Data/System_Tests/System_Test2_10m"));
  file.push_back(static_cast<string>("Data/System_Tests/System_Test2_16m"));
  file.push_back(static_cast<string>("Data/System_Tests/System_Test3_20m"));

  file2.clear();
  file2.push_back(static_cast<string>("Data/Com_Tests/Test1_COM3"));
  file2.push_back(static_cast<string>("Data/Com_Tests/Test1_COM4"));
  file2.push_back(static_cast<string>("Data/Com_Tests/Test1_COM5"));
  file2.push_back(static_cast<string>("Data/Com_Tests/Test2_COM3_20m_alone"));
  file2.push_back(static_cast<string>("Data/Com_Tests/Test2_COM3_20m_paired"));
  file2.push_back(static_cast<string>("Data/Com_Tests/Test2_COM4_16m_paired"));
  file2.push_back(static_cast<string>("Data/Com_Tests/Test3_COM3_20m_paired"));
  file2.push_back(static_cast<string>("Data/Com_Tests/Test3_COM4_16m_paired"));
  file2.push_back(static_cast<string>("Data/Com_Tests/Test3_COM5_10m_paired"));
  file2.push_back(static_cast<string>("Data/Com_Tests/Test4_COM3_10m"));
  file2.push_back(static_cast<string>("Data/Com_Tests/Test4_COM4_16"));
  file2.push_back(static_cast<string>("Data/Com_Tests/Test4_COM5_10"));
  file2.push_back(static_cast<string>("Data/Com_Tests/Test5_COM3"));
  file2.push_back(static_cast<string>("Data/Com_Tests/Test6_COM4"));
  file2.push_back(static_cast<string>("Data/Com_Tests/Test6_COM5"));

  for (unsigned f = 0; f < file2.size(); f++){
    //if (f == 1) break;
    readData.Open(file2[f]);
    readData.Prepare(data);
    readData.Fill(data);

    string output = "cout";
    string option = "";
  
    cout << endl << "AT FILE: " << file2[f] << endl;
    Kostas.Set_PH_Tolerance(0.2);
    Kostas.Stage_1(data);
    //Kostas.Stage_1_Report(data,output,option);
    Kostas.Stage_2(data);
    //Kostas.Stage_2_Report(data,output,option);
    Kostas.Stage_3(data,wave);
    //Kostas.Stage_3_Report(data,output,option);

    cout << endl << endl << endl;
  }

  
  
  return 0;
}
