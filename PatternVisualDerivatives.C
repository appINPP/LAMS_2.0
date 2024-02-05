#include <vector>
#include <iostream>
#include <cmath>
#include "Slices.hh"
#include "DataGrabber.hh"

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

double slope(double f1, double f2){
  return f2 - f1;
}

double der(double f1, double f2, double step){
  return (f2 - f1) / step;
}

double test_err(unsigned long &i, vector <Slice> &data, int ph){
  double a, b, c, d, e;
  double mean;
  double error;
  if (ph == 1){
    c = data[i].GetInt1();
  
    if (i > 1){
      a = data[i-2].GetInt1();
      b = data[i-1].GetInt1();
    }
    else if (i > 0){
      a = data[i-1].GetInt1();
      b = a;
    }
    else if (i > -1){
      a = data[i].GetInt1();
      b = a;
    }

    if (i < data.size() - 2){
      e = data[i+2].GetInt1();
      d = data[i+1].GetInt1();
    }
    else if(i < data.size() - 1){
      e = data[i+1].GetInt1();
      d = e;
    }
    else if(i < data.size()){
      e = data[i].GetInt1();
      d = e;
    }
  }
  else if (ph == 2){
    c = data[i].GetInt2();
  
    if (i > 1){
      a = data[i-2].GetInt2();
      b = data[i-1].GetInt2();
    }
    else if (i > 0){
      a = data[i-1].GetInt2();
      b = a;
    }
    else if (i > -1){
      a = data[i].GetInt2();
      b = a;
    }

    if (i < data.size() - 2){
      e = data[i+2].GetInt2();
      d = data[i+1].GetInt2();
    }
    else if(i < data.size() - 1){
      e = data[i+1].GetInt2();
      d = e;
    }
    else if(i < data.size()){
      e = data[i].GetInt2();
      d = e;
    }
  }
  else return -1;
  mean = (a + b + c + d + e)/5;
  error = sqrt(0.2*(pow(a-mean,2) + pow(b-mean,2) + pow(c-mean,2)
		    + pow(d-mean,2) + pow(e-mean,2)));
  return error;
}

int main(){
  vector <Slice> dataSlices;
  string fileName;
  DataGrabber readData;
  int c;
  TFile* outFile1 = new TFile("Results/Slopes/TestingSlopes.root","RECREATE");

  //Battery Test 2
  fileName = "Data/Battery_Tests/BatteryTest2Input";
  readData.Open(fileName);
  readData.Prepare_Test(dataSlices);
  readData.Fill_Test(dataSlices);
  
  TGraph int1_bat2;
  int1_bat2.SetName("int1_bat2");
  int1_bat2.SetTitle("Intensity 1 Slopes (Test 2);Point;Int1 Differences");
  TGraph int2_bat2;
  int2_bat2.SetName("int2_bat2");
  int2_bat2.SetTitle("Intensity 2 Slopes (Test 2);Point;Int2 Differences");
  TGraph temp_bat2;
  temp_bat2.SetName("temp_bat2");
  temp_bat2.SetTitle("Temperature Slopes (Test 2);Point;Temp Differences");

  TGraph err1_bat2;
  err1_bat2.SetName("err1_bat2");
  err1_bat2.SetTitle("PH 1 5-points errors (Test 2);Point;Error");
  TGraph err2_bat2;
  err2_bat2.SetName("err2_bat2");
  err2_bat2.SetTitle("PH 2 5-points errors (Test 2);Point;Error");


  c = 0;
  for (unsigned long i=0; i < dataSlices.size() - 1; i++){
    if (dataSlices[i].GetTemper() < 30 && dataSlices[i].GetTemper() > 15){
      int1_bat2.SetPoint(c,i,slope(dataSlices[i].GetInt1(),dataSlices[i+1].GetInt1()));
      int2_bat2.SetPoint(c,i,slope(dataSlices[i].GetInt2(),dataSlices[i+1].GetInt2()));
      temp_bat2.SetPoint(c,i,slope(dataSlices[i].GetTemper(),dataSlices[i+1].GetTemper()));

      err1_bat2.SetPoint(c,i,test_err(i,dataSlices,1));
      err2_bat2.SetPoint(c,i,test_err(i,dataSlices,2));
      c += 1;
    }
  }
  int1_bat2.Write();
  int2_bat2.Write();
  temp_bat2.Write();

  //Battery Test 3
  fileName = "Data/Battery_Tests/BatteryTest3Input";
  readData.Open(fileName);
  readData.Prepare_Test(dataSlices);
  readData.Fill_Test(dataSlices);
  
  TGraph int1_bat3;
  int1_bat3.SetName("int1_bat3");
  int1_bat3.SetTitle("Intensity 1 Slopes (Test 3);Point;Int1 Differences");
  TGraph int2_bat3;
  int2_bat3.SetName("int2_bat3");
  int2_bat3.SetTitle("Intensity 2 Slopes (Test 3);Point;Int2 Differences");
  TGraph temp_bat3;
  temp_bat3.SetName("temp_bat3");
  temp_bat3.SetTitle("Temperature Slopes (Test 3);Point;Temp Differences");

  TGraph err1_bat3;
  err1_bat3.SetName("err1_bat3");
  err1_bat3.SetTitle("PH 1 5-points errors (Test 3);Point;Error");
  TGraph err2_bat3;
  err2_bat3.SetName("err2_bat3");
  err2_bat3.SetTitle("PH 2 5-points errors (Test 3);Point;Error");


  c = 0;
  for (unsigned long i=0; i < dataSlices.size() - 1; i++){
    if (dataSlices[i].GetTemper() < 30 && dataSlices[i].GetTemper() > 15){
      int1_bat3.SetPoint(c,i,slope(dataSlices[i].GetInt1(),dataSlices[i+1].GetInt1()));
      int2_bat3.SetPoint(c,i,slope(dataSlices[i].GetInt2(),dataSlices[i+1].GetInt2()));
      temp_bat3.SetPoint(c,i,slope(dataSlices[i].GetTemper(),dataSlices[i+1].GetTemper()));

      err1_bat3.SetPoint(c,i,test_err(i,dataSlices,1));
      err2_bat3.SetPoint(c,i,test_err(i,dataSlices,2));
      c += 1;
    }
  }
  int1_bat3.Write();
  int2_bat3.Write();
  temp_bat3.Write();

  //Terminal Test 1
  fileName = "Data/Terminal_Tests/TerminalTest";
  readData.Open(fileName);
  readData.Prepare_Test(dataSlices);
  readData.Fill_Test(dataSlices);
  
  TGraph int1_term1;
  int1_term1.SetName("int1_term1");
  int1_term1.SetTitle("Intensity 1 Slopes (Terminal Test);Point;Int1 Differences");
  TGraph int2_term1;
  int2_term1.SetName("int2_term1");
  int2_term1.SetTitle("Intensity 2 Slopes (Terminal Test);Point;Int2 Differences");
  TGraph temp_term1;
  temp_term1.SetName("temp_term1");
  temp_term1.SetTitle("Temperature Slopes (Terminal Test);Point;Temp Differences");

  TGraph err1_term1;
  err1_term1.SetName("err1_term1");
  err1_term1.SetTitle("PH 1 5-points errors (Terminal Test);Point;Error");
  TGraph err2_term1;
  err2_term1.SetName("err2_term1");
  err2_term1.SetTitle("PH 2 5-points errors (Terminal Test);Point;Error");


  c = 0;
  for (unsigned long i=0; i < dataSlices.size() - 1; i++){
    if (dataSlices[i].GetTemper() < 30 && dataSlices[i].GetTemper() > 15){
      int1_term1.SetPoint(i,i,slope(dataSlices[i].GetInt1(),dataSlices[i+1].GetInt1()));
      int2_term1.SetPoint(i,i,slope(dataSlices[i].GetInt2(),dataSlices[i+1].GetInt2()));
      temp_term1.SetPoint(i,i,slope(dataSlices[i].GetTemper(),dataSlices[i+1].GetTemper()));

      err1_term1.SetPoint(c,i,test_err(i,dataSlices,1));
      err2_term1.SetPoint(c,i,test_err(i,dataSlices,2));
      c += 1;
    }
  }
  int1_term1.Write();
  int2_term1.Write();
  temp_term1.Write();

  outFile1 -> Close();
  delete outFile1;

  
  //Filter 1 - More Filters - More Distance
  TFile* outFile2 = new TFile("Results/Slopes/FilterSlopes.root","RECREATE");
  double step = 0;
  
  fileName = "Data/Filter_Tests/ND4_8_16_64_FilterTest";
  readData.Open(fileName);
  readData.Prepare_Test(dataSlices);
  readData.Fill_Test(dataSlices);
  
  TGraph int1_sf1;
  int1_sf1.SetName("int1_sf1");
  int1_sf1.SetTitle("Intensity 1 Slopes [4-8-16-64];Point;Intensity Value");
  int1_sf1.SetLineColor(4);

  TGraph int2_sf1;
  int2_sf1.SetName("int2_sf1");
  int2_sf1.SetTitle("Intensity 2 Slopes [4-8-16-64];Point;Intensity Value");
  int2_sf1.SetLineColor(2);

  TGraph temp_sf1;
  temp_sf1.SetName("temp_sf1");
  temp_sf1.SetTitle("Temperature Slopes [4-8-16-64];Point;Temperature (Celcius)");

  TGraph int1_df1;
  int1_df1.SetName("int1_df1");
  int1_df1.SetTitle("Intensity 1 1st Derivatives [4-8-16-64];Point;Intensity Value");
  int1_df1.SetLineColor(4);

  TGraph int2_df1;
  int2_df1.SetName("int2_df1");
  int2_df1.SetTitle("Intensity 2 1st Derivatives [4-8-16-64];Point;Intensity Value");
  int2_df1.SetLineColor(2);

  TGraph temp_df1;
  temp_df1.SetName("temp_df1");
  temp_df1.SetTitle("Temperature 1st Derivatives [4-8-16-64];Point;Temperature (Celcius)");

  TGraph err1_f1;
  err1_f1.SetName("err1_f1");
  err1_f1.SetTitle("PH 1 5-points errors (Filter 1);Point;Error");
  
  TGraph err2_f1;
  err2_f1.SetName("err2_f1");
  err2_f1.SetTitle("PH 2 5-points errors (Filter 1);Point;Error");


  for (unsigned long i=0; i < dataSlices.size() - 1; i++){
    int1_sf1.SetPoint(i,i,slope(dataSlices[i].GetInt1(),dataSlices[i+1].GetInt1()));
    int2_sf1.SetPoint(i,i,slope(dataSlices[i].GetInt2(),dataSlices[i+1].GetInt2()));
    temp_sf1.SetPoint(i,i,slope(dataSlices[i].GetTemper(),dataSlices[i+1].GetTemper()));

    step = dataSlices[i+1].GetTime() - dataSlices[i].GetTime();
    int1_df1.SetPoint(i,i,der(dataSlices[i].GetInt1(),dataSlices[i+1].GetInt1(),step));
    int2_df1.SetPoint(i,i,der(dataSlices[i].GetInt2(),dataSlices[i+1].GetInt2(),step));
    temp_df1.SetPoint(i,i,der(dataSlices[i].GetTemper(),dataSlices[i+1].GetTemper(),step));

    err1_f1.SetPoint(i,i,test_err(i,dataSlices,1));
    err2_f1.SetPoint(i,i,test_err(i,dataSlices,2));
  }

  int1_sf1.Write();
  int2_sf1.Write();
  temp_sf1.Write();

  int1_df1.Write();
  int2_df1.Write();
  temp_df1.Write();

  err1_f1.Write();
  err2_f1.Write();

  //Filter 2 - Less Filters - Less Distance
  fileName = "Data/Filter_Tests/ND4_8_16_64_FilterTest";
  readData.Open(fileName);
  readData.Prepare_Test(dataSlices);
  readData.Fill_Test(dataSlices);
  
  TGraph int1_sf2;
  int1_sf2.SetName("int1_sf2");
  int1_sf2.SetTitle("Intensity 1 Slopes [8-16-64];Point;Intensity Value");
  int1_sf2.SetLineColor(7);

  TGraph int2_sf2;
  int2_sf2.SetName("int2_sf2");
  int2_sf2.SetTitle("Intensity 2 Slopes [8-16-64];Point;Intensity Value");
  int2_sf2.SetLineColor(6);

  TGraph temp_sf2;
  temp_sf2.SetName("temp_sf2");
  temp_sf2.SetTitle("Temperature Slopes [8-16-64];Point;Temperature (Celcius)");

  TGraph int1_df2;
  int1_df2.SetName("int1_df2");
  int1_df2.SetTitle("Intensity 1 1st Derivatives [8-16-64];Point;Intensity Value");
  int1_df2.SetLineColor(7);

  TGraph int2_df2;
  int2_df2.SetName("int2_df2");
  int2_df2.SetTitle("Intensity 2 1st Derivatives [8-16-64];Point;Intensity Value");
  int2_df2.SetLineColor(6);

  TGraph temp_df2;
  temp_df2.SetName("temp_df2");
  temp_df2.SetTitle("Temperature 1st Derivatives [8-16-64];Point;Temperature (Celcius)");
  
  TGraph err1_f2;
  err1_f2.SetName("err1_f2");
  err1_f2.SetTitle("PH 1 5-points errors (Filter 2);Point;Error");
  
  TGraph err2_f2;
  err2_f2.SetName("err2_f2");
  err2_f2.SetTitle("PH 2 5-points errors (Filter 2);Point;Error");


  for (unsigned long i=0; i < dataSlices.size() - 1; i++){
    int1_sf2.SetPoint(i,i,slope(dataSlices[i].GetInt1(),dataSlices[i+1].GetInt1()));
    int2_sf2.SetPoint(i,i,slope(dataSlices[i].GetInt2(),dataSlices[i+1].GetInt2()));
    temp_sf2.SetPoint(i,i,slope(dataSlices[i].GetTemper(),dataSlices[i+1].GetTemper()));

    step = dataSlices[i+1].GetTime() - dataSlices[i].GetTime();
    int1_df2.SetPoint(i,i,der(dataSlices[i].GetInt1(),dataSlices[i+1].GetInt1(),step));
    int2_df2.SetPoint(i,i,der(dataSlices[i].GetInt2(),dataSlices[i+1].GetInt2(),step));
    temp_df2.SetPoint(i,i,der(dataSlices[i].GetTemper(),dataSlices[i+1].GetTemper(),step));

    err1_f2.SetPoint(i,i,test_err(i,dataSlices,1));
    err2_f2.SetPoint(i,i,test_err(i,dataSlices,2));
  }

  int1_sf2.Write();
  int2_sf2.Write();
  temp_sf2.Write();

  int1_df2.Write();
  int2_df2.Write();
  temp_df2.Write();

  err1_f2.Write();
  err2_f2.Write();


  //Filter 3
  fileName = "Data/Filter_Tests/ND4_64_FilterTest_DOMLab";
  readData.Open(fileName);
  readData.Prepare_Test(dataSlices);
  readData.Fill_Test(dataSlices);
  
  TGraph int1_sf3;
  int1_sf3.SetName("int1_sf3");
  int1_sf3.SetTitle("Intensity 1 Slopes [4-64];Point;Intensity Value");
  int1_sf3.SetLineColor(4);
  
  TGraph int2_sf3;
  int2_sf3.SetName("int2_sf3");
  int2_sf3.SetTitle("Intensity 2 Slopes [4-64];Point;Intensity Value");
  int2_sf3.SetLineColor(2);

  TGraph temp_sf3;
  temp_sf3.SetName("temp_sf3");
  temp_sf3.SetTitle("Temperature Slopes [4-64];Point;Temperature (Celcius)");

  TGraph int1_df3;
  int1_df3.SetName("int1_df3");
  int1_df3.SetTitle("Intensity 1 1st Derivatives [4-64];Point;Intensity Value");
  int1_df3.SetLineColor(4);

  TGraph int2_df3;
  int2_df3.SetName("int2_df3");
  int2_df3.SetTitle("Intensity 2 1st Derivatives [4-64];Point;Intensity Value");
  int2_df3.SetLineColor(2);

  TGraph temp_df3;
  temp_df3.SetName("temp_df3");
  temp_df3.SetTitle("Temperature 1st Derivatives [4-64];Point;Temperature (Celcius)");

  TGraph err1_f3;
  err1_f3.SetName("err1_f3");
  err1_f3.SetTitle("PH 1 5-points errors (Filter 3);Point;Error");
  
  TGraph err2_f3;
  err2_f3.SetName("err2_f3");
  err2_f3.SetTitle("PH 2 5-points errors (Filter 3);Point;Error");


  for (unsigned long i=0; i < dataSlices.size() - 1; i++){
    int1_sf3.SetPoint(i,i,slope(dataSlices[i].GetInt1(),dataSlices[i+1].GetInt1()));
    int2_sf3.SetPoint(i,i,slope(dataSlices[i].GetInt2(),dataSlices[i+1].GetInt2()));
    temp_sf3.SetPoint(i,i,slope(dataSlices[i].GetTemper(),dataSlices[i+1].GetTemper()));

    step = dataSlices[i+1].GetTime() - dataSlices[i].GetTime();
    int1_df3.SetPoint(i,i,der(dataSlices[i].GetInt1(),dataSlices[i+1].GetInt1(),step));
    int2_df3.SetPoint(i,i,der(dataSlices[i].GetInt2(),dataSlices[i+1].GetInt2(),step));
    temp_df3.SetPoint(i,i,der(dataSlices[i].GetTemper(),dataSlices[i+1].GetTemper(),step));

    err1_f3.SetPoint(i,i,test_err(i,dataSlices,1));
    err2_f3.SetPoint(i,i,test_err(i,dataSlices,2));
  }

  int1_sf3.Write();
  int2_sf3.Write();
  temp_sf3.Write();

  int1_df3.Write();
  int2_df3.Write();
  temp_df3.Write();

  err1_f3.Write();
  err2_f3.Write();

  //Filter 4
  fileName = "Data/Filter_Tests/ND8_64_FilterTest_DOMLab";
  readData.Open(fileName);
  readData.Prepare_Test(dataSlices);
  readData.Fill_Test(dataSlices);
  
  TGraph int1_sf4;
  int1_sf4.SetName("int1_sf4");
  int1_sf4.SetTitle("Intensity 1 Slopes [8-64];Point;Intensity Value");
  int1_sf4.SetLineColor(7);

  TGraph int2_sf4;
  int2_sf4.SetName("int2_sf4");
  int2_sf4.SetTitle("Intensity 2 Slopes [8-64];Point;Intensity Value");
  int2_sf4.SetLineColor(6);

  TGraph temp_sf4;
  temp_sf4.SetName("temp_sf4");
  temp_sf4.SetTitle("Temperature Slopes [8-64];Point;Temperature (Celcius)");

  TGraph int1_df4;
  int1_df4.SetName("int1_df4");
  int1_df4.SetTitle("Intensity 1 1st Derivatives [8-64];Point;Intensity Value");
  int1_df4.SetLineColor(7);

  TGraph int2_df4;
  int2_df4.SetName("int2_df4");
  int2_df4.SetTitle("Intensity 2 1st Derivatives [8-64];Point;Intensity Value");
  int2_df4.SetLineColor(6);

  TGraph temp_df4;
  temp_df4.SetName("temp_df4");
  temp_df4.SetTitle("Temperature 1st Derivatives [8-64];Point;Temperature (Celcius)");

  TGraph err1_f4;
  err1_f4.SetName("err1_f4");
  err1_f4.SetTitle("PH 1 5-points errors (Filter 4);Point;Error");
  
  TGraph err2_f4;
  err2_f4.SetName("err2_f4");
  err2_f4.SetTitle("PH 2 5-points errors (Filter 4);Point;Error");


  for (unsigned long i=0; i < dataSlices.size() - 1; i++){
    int1_sf4.SetPoint(i,i,slope(dataSlices[i].GetInt1(),dataSlices[i+1].GetInt1()));
    int2_sf4.SetPoint(i,i,slope(dataSlices[i].GetInt2(),dataSlices[i+1].GetInt2()));
    temp_sf4.SetPoint(i,i,slope(dataSlices[i].GetTemper(),dataSlices[i+1].GetTemper()));

    step = dataSlices[i+1].GetTime() - dataSlices[i].GetTime();
    int1_df4.SetPoint(i,i,der(dataSlices[i].GetInt1(),dataSlices[i+1].GetInt1(),step));
    int2_df4.SetPoint(i,i,der(dataSlices[i].GetInt2(),dataSlices[i+1].GetInt2(),step));
    temp_df4.SetPoint(i,i,der(dataSlices[i].GetTemper(),dataSlices[i+1].GetTemper(),step));

    err1_f4.SetPoint(i,i,test_err(i,dataSlices,1));
    err2_f4.SetPoint(i,i,test_err(i,dataSlices,2));
  }

  int1_sf4.Write();
  int2_sf4.Write();
  temp_sf4.Write();

  int1_df4.Write();
  int2_df4.Write();
  temp_df4.Write();

  err1_f4.Write();
  err2_f4.Write();


  outFile2 -> Close();
  delete outFile2;
  
  return 0;
}
