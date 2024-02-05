#include <iostream>
#include <string>
#include <vector>

#include "TFile.h"
#include "TGraph.h"
#include "TH1.h"
#include "TH2.h"

#include "DataGrabber.hh"
#include "Slices.hh"

using namespace std;

int main(){
  
  vector <Slice> dataSlices;
  string fileName;
  DataGrabber readData;
  double offset;
  double ratio;
  unsigned long c = 0;
  unsigned long l = 0;

  // ND4 - ND8 - ND16 - ND64  ~~~  Filters Test 1
  TFile* outFile_1 = new TFile("Results/Filter_Tests/FilterTest1.root","RECREATE");
  dataSlices.clear();
  
  fileName = "Data/Filter_Tests/ND4_8_16_64_FilterTest"; // NAME of TEST FILE (after being converted from txt to binary)
  readData.Open(fileName);
  readData.Prepare_Test(dataSlices);
  readData.Fill_Test(dataSlices);

  TGraph int1_tf1;
  int1_tf1.SetName("intensity1_time_f1");
  int1_tf1.SetTitle("Intensity (time) of Photodiode 1 [4-8-16-64];Time;Intensity Value");
  int1_tf1.SetLineColor(4);

  TGraph int2_tf1;
  int2_tf1.SetName("intensity2_time_f1");
  int2_tf1.SetTitle("Intensity (time) of Photodiode 2 [4-8-16-64];Time;Intensity Value");
  int2_tf1.SetLineColor(2);

  TGraph temp_tf1;
  temp_tf1.SetName("temperature_time_f1");
  temp_tf1.SetTitle("Temperature (time) of Photodiodes [4-8-16-64];Time;Temperature (Celcius)");

  TGraph int1_otf1;
  int1_otf1.SetName("intensity1_offset_time_f1");
  int1_otf1.SetTitle("Intensity (offset time) of Photodiode 1 [4-8-16-64];Offset Time;Intensity Value");
  int1_otf1.SetLineColor(4);

  TGraph int2_otf1;
  int2_otf1.SetName("intensity2_offset_time_f1");
  int2_otf1.SetTitle("Intensity (offset time) of Photodiode 2 [4-8-16-64];Offset Time;Intensity Value");
  int2_otf1.SetLineColor(2);

  TGraph temp_otf1;
  temp_otf1.SetName("temperature_offset_time_f1");
  temp_otf1.SetTitle("Temperature (offset time) of Photodiodes [4-8-16-64];Offset Time;Temperature (Celcius)");

  TGraph int1_pf1;
  int1_pf1.SetName("intensity1_point_f1");
  int1_pf1.SetTitle("Intensity of Photodiode 1 (Fixed Points) [4-8-16-64];Point;Intensity Value");
  int1_pf1.SetLineColor(4);

  TGraph int2_pf1;
  int2_pf1.SetName("intensity2_point_f1");
  int2_pf1.SetTitle("Intensity of Photodiode 2 (Fixed Points) [4-8-16-64];Point;Intensity Value");
  int2_pf1.SetLineColor(2);

  TGraph temp_pf1;
  temp_pf1.SetName("temperature_point_f1");
  temp_pf1.SetTitle("Temperature of Photodiodes (Fixed Points) [4-8-16-64];Point;Temperature (Celcius)");

  TGraph per_f1;
  per_f1.SetName("percent_f1");
  per_f1.SetTitle("Photodiode 1 Intensity divided by Photodiode 2 [4-8-16-64];Offset Time;Percent");

  c = 0;
  l = 0;
  offset = 273522505;

  for (unsigned long i=0; i < dataSlices.size(); i++){
    int1_tf1.SetPoint(i,dataSlices[i].GetTime(),dataSlices[i].GetInt1());
    int2_tf1.SetPoint(i,dataSlices[i].GetTime(),dataSlices[i].GetInt2());
    temp_tf1.SetPoint(i,dataSlices[i].GetTime(),dataSlices[i].GetTemper());

    int1_pf1.SetPoint(i,i,dataSlices[i].GetInt1());
    int2_pf1.SetPoint(i,i,dataSlices[i].GetInt2());
    temp_pf1.SetPoint(i,i,dataSlices[i].GetTemper());

    if (dataSlices[i].GetTime() >= offset){
      int1_otf1.SetPoint(c,dataSlices[i].GetTime() - offset,dataSlices[i].GetInt1());
      int2_otf1.SetPoint(c,dataSlices[i].GetTime() - offset,dataSlices[i].GetInt2());
      temp_otf1.SetPoint(c,dataSlices[i].GetTime() - offset,dataSlices[i].GetTemper());
      ratio = 100. * dataSlices[i].GetInt1() / dataSlices[i].GetInt2();
      if (ratio > 0.0025 && ratio < 400){
	per_f1.SetPoint(l,dataSlices[i].GetTime() - offset,ratio);
	l++;
      }
      c += 1;
    }
  }

  int1_tf1.Write();
  int2_tf1.Write();
  temp_tf1.Write();

  int1_otf1.Write();
  int2_otf1.Write();
  temp_otf1.Write();

  int1_pf1.Write();
  int2_pf1.Write();
  temp_pf1.Write();

  per_f1.Write();

  outFile_1 -> Close();
  delete outFile_1;

  // ND8 - ND16 - ND64  ~~~  Filters Test 2
  TFile* outFile_2 = new TFile("Results/Filter_Tests/FilterTest2.root","RECREATE");

  dataSlices.clear();
  fileName = "Data/Filter_Tests/ND8_16_64_FilterTest"; // NAME of TEST FILE (after being converted from txt to binary)
  readData.Open(fileName);
  readData.Prepare_Test(dataSlices);
  readData.Fill_Test(dataSlices);

  TGraph int1_tf2;
  int1_tf2.SetName("intensity1_time_f2");
  int1_tf2.SetTitle("Intensity (time) of Photodiode 1 [8-16-64];Time;Intensity Value");
  int1_tf2.SetLineColor(7);

  TGraph int2_tf2;
  int2_tf2.SetName("intensity2_time_f2");
  int2_tf2.SetTitle("Intensity (time) of Photodiode 2 [8-16-64];Time;Intensity Value");
  int2_tf2.SetLineColor(6);

  TGraph temp_tf2;
  temp_tf2.SetName("temperature_time_f2");
  temp_tf2.SetTitle("Temperature (time) of Photodiodes [8-16-64];Time;Temperature (Celcius)");

  TGraph int1_otf2;
  int1_otf2.SetName("intensity1_offset_time_f2");
  int1_otf2.SetTitle("Intensity(time) of Photodiode 1 [8-16-64];Offset Time;Intensity Value");
  int1_otf2.SetLineColor(7);

  TGraph int2_otf2;
  int2_otf2.SetName("intensity2_offset_time_f2");
  int2_otf2.SetTitle("Intensity(time) of Photodiode 2 [8-16-64];Offset Time;Intensity Value");
  int2_otf2.SetLineColor(6);

  TGraph temp_otf2;
  temp_otf2.SetName("temperature_offset_time_f2");
  temp_otf2.SetTitle("Temperature (offset time) of Photodiodes [8-16-64];Offset Time;Temperature (Celcius)");

  TGraph int1_pf2;
  int1_pf2.SetName("intensity1_point_f2");
  int1_pf2.SetTitle("Intensity of Photodiode 1 (Fixed Points) [8-16-64];Point;Intensity Value");
  int1_pf2.SetLineColor(7);

  TGraph int2_pf2;
  int2_pf2.SetName("intensity2_point_f2");
  int2_pf2.SetTitle("Intensity of Photodiode 2 (Fixed Points) [8-16-64];Point;Intensity Value");
  int2_pf2.SetLineColor(6);

  TGraph temp_pf2;
  temp_pf2.SetName("temperature_point_f2");
  temp_pf2.SetTitle("Temperature of Photodiodes (Fixed Points) [8-16-64];Point;Temperature (Celcius)");

  TGraph per_f2;
  per_f2.SetName("percent_f2");
  per_f2.SetTitle("Photodiode 1 Intensity divided by Photodiode 2 [8-16-64];Offset Time;Percent");

  c = 0;
  l = 0;
  offset = 263485087;
  for (unsigned long i=0; i < dataSlices.size(); i++){

    int1_tf2.SetPoint(i,dataSlices[i].GetTime(),dataSlices[i].GetInt1());
    int2_tf2.SetPoint(i,dataSlices[i].GetTime(),dataSlices[i].GetInt2());
    temp_tf2.SetPoint(i,dataSlices[i].GetTime(),dataSlices[i].GetTemper());

    int1_pf2.SetPoint(i,i,dataSlices[i].GetInt1());
    int2_pf2.SetPoint(i,i,dataSlices[i].GetInt2());
    temp_pf2.SetPoint(i,i,dataSlices[i].GetTemper());

    if (dataSlices[i].GetTime() >= offset){
      int1_otf2.SetPoint(c,dataSlices[i].GetTime() - offset,dataSlices[i].GetInt1());
      int2_otf2.SetPoint(c,dataSlices[i].GetTime() - offset,dataSlices[i].GetInt2());
      temp_otf2.SetPoint(c,dataSlices[i].GetTime() - offset,dataSlices[i].GetTemper());
      ratio = 100. * dataSlices[i].GetInt1() / dataSlices[i].GetInt2();
      if (ratio > 0.0025 && ratio < 400){
	per_f2.SetPoint(l,dataSlices[i].GetTime() - offset,ratio);
	l++;
      }
      c++;
    }
  }

  int1_tf2.Write();
  int2_tf2.Write();
  temp_tf2.Write();

  int1_otf2.Write();
  int2_otf2.Write();
  temp_otf2.Write();

  int1_pf2.Write();
  int2_pf2.Write();
  temp_pf2.Write();

  per_f2.Write();
  
  outFile_2 -> Close();
  delete outFile_2;


  // ND4 - ND64  ~~~  Filters Test 3
  TFile* outFile_3 = new TFile("Results/Filter_Tests/FilterTest3.root","RECREATE");

  dataSlices.clear();
  fileName = "Data/Filter_Tests/ND4_64_FilterTest_DOMLab"; // NAME of TEST FILE (after being converted from txt to binary)
  readData.Open(fileName);
  readData.Prepare_Test(dataSlices);
  readData.Fill_Test(dataSlices);

  TGraph int1_tf3;
  int1_tf3.SetName("intensity1_time_f3");
  int1_tf3.SetTitle("Intensity (time) of Photodiode 1 [4-64];Time;Intensity Value");
  int1_tf3.SetLineColor(7);

  TGraph int2_tf3;
  int2_tf3.SetName("intensity2_time_f3");
  int2_tf3.SetTitle("Intensity (time) of Photodiode 2 [4-64];Time;Intensity Value");
  int2_tf3.SetLineColor(6);

  TGraph temp_tf3;
  temp_tf3.SetName("temperature_time_f3");
  temp_tf3.SetTitle("Temperature (time) of Photodiodes [4-64];Time;Temperature (Celcius)");

  TGraph int1_otf3;
  int1_otf3.SetName("intensity1_offset_time_f3");
  int1_otf3.SetTitle("Intensity(time) of Photodiode 1 [4-64];Offset Time;Intensity Value");
  int1_otf3.SetLineColor(7);

  TGraph int2_otf3;
  int2_otf3.SetName("intensity2_offset_time_f3");
  int2_otf3.SetTitle("Intensity(time) of Photodiode 2 [4-64];Offset Time;Intensity Value");
  int2_otf3.SetLineColor(6);

  TGraph temp_otf3;
  temp_otf3.SetName("temperature_offset_time_f3");
  temp_otf3.SetTitle("Temperature (offset time) of Photodiodes [4-64];Offset Time;Temperature (Celcius)");

  TGraph int1_pf3;
  int1_pf3.SetName("intensity1_point_f3");
  int1_pf3.SetTitle("Intensity of Photodiode 1 (Fixed Points) [4-64];Point;Intensity Value");
  int1_pf3.SetLineColor(7);

  TGraph int2_pf3;
  int2_pf3.SetName("intensity2_point_f3");
  int2_pf3.SetTitle("Intensity of Photodiode 2 (Fixed Points) [4-64];Point;Intensity Value");
  int2_pf3.SetLineColor(6);

  TGraph temp_pf3;
  temp_pf3.SetName("temperature_point_f3");
  temp_pf3.SetTitle("Temperature of Photodiodes (Fixed Points) [4-64];Point;Temperature (Celcius)");

  TGraph per_f3;
  per_f3.SetName("percent_f3");
  per_f3.SetTitle("Photodiode 1 Intensity divided by Photodiode 2 [4-64];Offset Time;Percent");


  c = 0;
  l = 0;
  offset = 0;
  for (unsigned long i=0; i < dataSlices.size(); i++){

    int1_tf3.SetPoint(i,dataSlices[i].GetTime(),dataSlices[i].GetInt1());
    int2_tf3.SetPoint(i,dataSlices[i].GetTime(),dataSlices[i].GetInt2());
    temp_tf3.SetPoint(i,dataSlices[i].GetTime(),dataSlices[i].GetTemper());

    int1_pf3.SetPoint(i,i,dataSlices[i].GetInt1());
    int2_pf3.SetPoint(i,i,dataSlices[i].GetInt2());
    temp_pf3.SetPoint(i,i,dataSlices[i].GetTemper());

    if (dataSlices[i].GetTime() >= offset){
      int1_otf3.SetPoint(c,dataSlices[i].GetTime() - offset,dataSlices[i].GetInt1());
      int2_otf3.SetPoint(c,dataSlices[i].GetTime() - offset,dataSlices[i].GetInt2());
      temp_otf3.SetPoint(c,dataSlices[i].GetTime() - offset,dataSlices[i].GetTemper());
      ratio = 100. * dataSlices[i].GetInt1() / dataSlices[i].GetInt2();
      if (ratio > 0.0025 && ratio < 400){
	per_f3.SetPoint(l,dataSlices[i].GetTime() - offset,ratio);
	l++;
      }
      c++;
    }
  }

  int1_tf3.Write();
  int2_tf3.Write();
  temp_tf3.Write();

  int1_otf3.Write();
  int2_otf3.Write();
  temp_otf3.Write();

  int1_pf3.Write();
  int2_pf3.Write();
  temp_pf3.Write();

  per_f3.Write();
  
  outFile_3 -> Close();
  delete outFile_3;

  // ND8 - ND64  ~~~  Filters Test 4
  TFile* outFile_4 = new TFile("Results/Filter_Tests/FilterTest4.root","RECREATE");

  dataSlices.clear();
  fileName = "Data/Filter_Tests/ND8_64_FilterTest_DOMLab"; // NAME of TEST FILE (after being converted from txt to binary)
  readData.Open(fileName);
  readData.Prepare_Test(dataSlices);
  readData.Fill_Test(dataSlices);

  TGraph int1_tf4;
  int1_tf4.SetName("intensity1_time_f4");
  int1_tf4.SetTitle("Intensity (time) of Photodiode 1 [8-64];Time;Intensity Value");
  int1_tf4.SetLineColor(7);

  TGraph int2_tf4;
  int2_tf4.SetName("intensity2_time_f4");
  int2_tf4.SetTitle("Intensity (time) of Photodiode 2 [8-64];Time;Intensity Value");
  int2_tf4.SetLineColor(6);

  TGraph temp_tf4;
  temp_tf4.SetName("temperature_time_f4");
  temp_tf4.SetTitle("Temperature (time) of Photodiodes [8-64];Time;Temperature (Celcius)");

  TGraph int1_otf4;
  int1_otf4.SetName("intensity1_offset_time_f4");
  int1_otf4.SetTitle("Intensity(time) of Photodiode 1 [8-64];Offset Time;Intensity Value");
  int1_otf4.SetLineColor(7);

  TGraph int2_otf4;
  int2_otf4.SetName("intensity2_offset_time_f4");
  int2_otf4.SetTitle("Intensity(time) of Photodiode 2 [8-64];Offset Time;Intensity Value");
  int2_otf4.SetLineColor(6);

  TGraph temp_otf4;
  temp_otf4.SetName("temperature_offset_time_f4");
  temp_otf4.SetTitle("Temperature (offset time) of Photodiodes [8-64];Offset Time;Temperature (Celcius)");

  TGraph int1_pf4;
  int1_pf4.SetName("intensity1_point_f4");
  int1_pf4.SetTitle("Intensity of Photodiode 1 (Fixed Points) [8-64];Point;Intensity Value");
  int1_pf4.SetLineColor(7);

  TGraph int2_pf4;
  int2_pf4.SetName("intensity2_point_f4");
  int2_pf4.SetTitle("Intensity of Photodiode 2 (Fixed Points) [8-64];Point;Intensity Value");
  int2_pf4.SetLineColor(6);

  TGraph temp_pf4;
  temp_pf4.SetName("temperature_point_f4");
  temp_pf4.SetTitle("Temperature of Photodiodes (Fixed Points) [8-64];Point;Temperature (Celcius)");

  TGraph per_f4;
  per_f4.SetName("percent_f4");
  per_f4.SetTitle("Photodiode 1 Intensity divided by Photodiode 2 [8-64];Offset Time;Percent");

  c = 0;
  l = 0;
  offset = 0;
  for (unsigned long i=0; i < dataSlices.size(); i++){

    int1_tf4.SetPoint(i,dataSlices[i].GetTime(),dataSlices[i].GetInt1());
    int2_tf4.SetPoint(i,dataSlices[i].GetTime(),dataSlices[i].GetInt2());
    temp_tf4.SetPoint(i,dataSlices[i].GetTime(),dataSlices[i].GetTemper());

    int1_pf4.SetPoint(i,i,dataSlices[i].GetInt1());
    int2_pf4.SetPoint(i,i,dataSlices[i].GetInt2());
    temp_pf4.SetPoint(i,i,dataSlices[i].GetTemper());

    if (dataSlices[i].GetTime() >= offset){
      int1_otf4.SetPoint(c,dataSlices[i].GetTime() - offset,dataSlices[i].GetInt1());
      int2_otf4.SetPoint(c,dataSlices[i].GetTime() - offset,dataSlices[i].GetInt2());
      temp_otf4.SetPoint(c,dataSlices[i].GetTime() - offset,dataSlices[i].GetTemper());
      ratio = 100. * dataSlices[i].GetInt1() / dataSlices[i].GetInt2();
      if (ratio > 0.0025 && ratio < 400){
	per_f4.SetPoint(l,dataSlices[i].GetTime() - offset,ratio);
	l++;
      }
      c++;
    }
  }

  int1_tf4.Write();
  int2_tf4.Write();
  temp_tf4.Write();

  int1_otf4.Write();
  int2_otf4.Write();
  temp_otf4.Write();

  int1_pf4.Write();
  int2_pf4.Write();
  temp_pf4.Write();

  per_f4.Write();
  
  outFile_4 -> Close();
  delete outFile_4;
  
  return 0;
}
