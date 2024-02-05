#include <iostream>
#include <string>
#include <vector>

#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"
#include "TVirtualFFT.h"


#include "DataGrabber.hh"
#include "Slices.hh"

using namespace std;

int main(){

   
  //TFile* out_file1 = new TFile("Results/Test_12_12_2018/spyrosTestOutput.root","RECREATE");
  vector <Slice> dataSlices;

  string name_of_file;
  DataGrabber readData;

  // Battery Test 2
  
  TFile* out_file2 = new TFile("Results/Battery_Tests/BatteryTest2Output.root","RECREATE");
  
  name_of_file = "Data/Battery_Tests/BatteryTest2Input"; // NAME of TEST FILE (after being converted from txt to binary)
  
  readData.Open(name_of_file);
  readData.Prepare_Test(dataSlices);
  readData.Fill_Test(dataSlices);

  // Data files not filtered for error line
  TH1F bat2_diode1("Intensity_1_bat2", "Battery Test 2 - Intensity of Photodiode 1", 10958616,1456000027,1466958643);
  TH1F bat2_diode2("Intensity_2_bat2", "Battery Test 2 - Intensity of Photodiode 2", 10958616,1456000027,1466958643);
  TH1F bat2_temperature("Temperature_bat2", "Battery Test 2 - Temperature", 10958616,1456000027,1466958643);
  
  TH1F bat2_diode1_points("Int1_bat2_points", "Battery Test 2 - Intensity of Photodiode 1", 688055, 0, 688055);
  TH1F bat2_diode2_points("Int2_bat2_points", "Battery Test 2 - Intensity of Photodiode 2", 688055, 0, 688055);
  TH1F bat2_temperature_points("Temperature_bat2_points", "Battery Test 2 - Temperature", 688055, 0, 688055);
  TH1F bat2_diodes_divide("Int1_Int2_comp_bat2", "Battery Test 2 - Intensity 1 / Intensity 2", 688055, 0, 688055);
  TH1F bat2_diode1_temp("Int1_temp_comp_bat2", "Battery Test 2 - Intensity 1 / Temperature", 688055, 0, 688055);
  TH1F bat2_diode2_temp("Int2_temp_comp_bat2", "Battery Test 2 - Intensity 2 / Temperature", 688055, 0, 688055);
  
  TH1F bat2_diode1_hist("Int1_range_bat2", "Battery Test 2 - Values Range of Intensity 1", 50000, 0, 50000);
  TH1F bat2_diode2_hist("Int2_range_bat2", "Battery Test 2 - Values Range of Intensity 2", 50000, 0, 50000);
  TH1F bat2_temperature_hist("Temp_range_bat2", "Battery Test 2 - Values Range of Temperature", 50000, 0, 50000);

  // Data filtered of their atrocious errors
  TH1F bat2_diode1_corr("Intensity_1_bat2_corr", "Battery Test 2 - Intensity of Photodiode 1", 10958616,1456000027,1466958643);
  TH1F bat2_diode2_corr("Intensity_2_bat2_corr", "Battery Test 2 - Intensity of Photodiode 2", 10958616,1456000027,1466958643);
  TH1F bat2_temperature_corr("Temperature_bat2_corr", "Battery Test 2 - Temperature", 10958616,1456000027,1466958643);
  
  TH1F bat2_diode1_points_corr("Int1_bat2_points_corr", "Battery Test 2 - Intensity of Photodiode 1", 688055, 0, 688055);
  TH1F bat2_diode2_points_corr("Int2_bat2_points_corr", "Battery Test 2 - Intensity of Photodiode 2", 688055, 0, 688055);
  TH1F bat2_temperature_points_corr("Temperature_bat2_points_corr", "Battery Test 2 - Temperature", 688055, 0, 688055);
  TH1F bat2_diodes_divide_corr("Int1_Int2_comp_bat2_corr", "Battery Test 2 - Intensity 1 / Intensity 2", 688055, 0, 688055);
  TH1F bat2_diode1_temp_corr("Int1_temp_comp_bat2_corr", "Battery Test 2 - Intensity 1 / Temperature", 688055, 0, 688055);
  TH1F bat2_diode2_temp_corr("Int2_temp_comp_bat2_corr", "Battery Test 2 - Intensity 2 / Temperature", 688055, 0, 688055);
  
  TH1F bat2_diode1_hist_corr("Int1_range_bat2_corr", "Battery Test 2 - Values Range of Intensity 1", 50000, 0, 50000);
  TH1F bat2_diode2_hist_corr("Int2_range_bat2_corr", "Battery Test 2 - Values Range of Intensity 2", 50000, 0, 50000);
  TH1F bat2_temperature_hist_corr("Temp_range_bat2_corr", "Battery Test 2 - Values Range of Temperature", 50000, 0, 50000);

  // Same as above but with stricter temperature
  TH1F bat2_diode1_points_corrT("Int1_bat2_points_corrT", "Battery Test 2 - Intensity of Photodiode 1", 688055, 0, 688055);
  TH1F bat2_diode2_points_corrT("Int2_bat2_points_corrT", "Battery Test 2 - Intensity of Photodiode 2", 688055, 0, 688055);
  TH1F bat2_temperature_points_corrT("Temperature_bat2_points_corrT", "Battery Test 2 - Temperature", 688055, 0, 688055);
  TH1F bat2_diodes_divide_corrT("Int1_Int2_comp_bat2_corrT", "Battery Test 2 - Intensity 1 / Intensity 2", 688055, 0, 688055);
  TH1F bat2_diode1_temp_corrT("Int1_temp_comp_bat2_corrT", "Battery Test 2 - Intensity 1 / Temperature", 688055, 0, 688055);
  TH1F bat2_diode2_temp_corrT("Int2_temp_comp_bat2_corrT", "Battery Test 2 - Intensity 2 / Temperature", 688055, 0, 688055);
  
  TH1F bat2_diode1_hist_corrT("Int1_range_bat2_corrT", "Battery Test 2 - Values Range of Intensity 1", 50000, 0, 50000);
  TH1F bat2_diode2_hist_corrT("Int2_range_bat2_corrT", "Battery Test 2 - Values Range of Intensity 2", 50000, 0, 50000);
  TH1F bat2_temperature_hist_corrT("Temp_range_bat2_corrT", "Battery Test 2 - Values Range of Temperature", 50000, 0, 50000);

  TH2D bat2_diode1_temp_comp("Int1_temp_bat2_2D", "Battery Test 2 - Intensity 1 vs Temperature", 10000, 40000, 50000, 100, 20, 30);
  TH2D bat2_diode2_temp_comp("Int2_temp_bat2_2D", "Battery Test 2 - Intensity 2 vs Temperature", 10000, 40000, 50000, 100, 20, 30);
  //TH2D bat2_time1_temp_comp("Int1_temp_bat2_time", "Battery Test 2 - Intensity 1 vs Time (Temperature)", 688055, 0, 688055, 10000, 50000, 60000);
  //TH2D bat2_time2_temp_comp("Int2_temp_bat2_time", "Battery Test 2 - Intensity 2 vs Time (Temperature)", 688055, 0, 688055, 10000, 50000, 60000);
  
  long long c = 0;
  for (long long i=0; i < dataSlices.size(); i++){
    
    bat2_diode1.Fill(dataSlices[i].GetTime(), dataSlices[i].GetInt1());
    bat2_diode2.Fill(dataSlices[i].GetTime(), dataSlices[i].GetInt2());
    bat2_temperature.Fill(dataSlices[i].GetTime(), dataSlices[i].GetTemper());

    bat2_diode1_points.Fill(i, dataSlices[i].GetInt1());
    bat2_diode2_points.Fill(i, dataSlices[i].GetInt2());
    bat2_temperature_points.Fill(i, dataSlices[i].GetTemper());

    bat2_diodes_divide.Fill(i, dataSlices[i].GetInt1());
    bat2_diode1_temp.Fill(i, dataSlices[i].GetInt1());
    bat2_diode2_temp.Fill(i, dataSlices[i].GetInt2());

    bat2_diode1_hist.Fill(dataSlices[i].GetInt1());
    bat2_diode2_hist.Fill(dataSlices[i].GetInt2());
    bat2_temperature_hist.Fill(dataSlices[i].GetTemper());

    if (dataSlices[i].GetInt1() < 50000 && dataSlices[i].GetInt1() > 40000){
      if (dataSlices[i].GetInt2() < 50000 && dataSlices[i].GetInt2() > 40000){
	if (dataSlices[i].GetTemper() < 30 && dataSlices[i].GetTemper() > 15){
	  bat2_diode1_corr.Fill(dataSlices[i].GetTime(), dataSlices[i].GetInt1());
	  bat2_diode2_corr.Fill(dataSlices[i].GetTime(), dataSlices[i].GetInt2());
	  bat2_temperature_corr.Fill(dataSlices[i].GetTime(), dataSlices[i].GetTemper());

	  bat2_diode1_points_corr.Fill(c, dataSlices[i].GetInt1());
	  bat2_diode2_points_corr.Fill(c, dataSlices[i].GetInt2());
	  bat2_temperature_points_corr.Fill(c, dataSlices[i].GetTemper());

	  bat2_diodes_divide_corr.Fill(c, dataSlices[i].GetInt1());
	  bat2_diode1_temp_corr.Fill(c, dataSlices[i].GetInt1());
	  bat2_diode2_temp_corr.Fill(c, dataSlices[i].GetInt2());

	  bat2_diode1_hist_corr.Fill(dataSlices[i].GetInt1());
	  bat2_diode2_hist_corr.Fill(dataSlices[i].GetInt2());
	  bat2_temperature_hist_corr.Fill(dataSlices[i].GetTemper());
	  
	  if (dataSlices[i].GetTemper() < 27.5 && dataSlices[i].GetTemper() > 26.5){
	    bat2_diode1_points_corrT.Fill(c, dataSlices[i].GetInt1());
	    bat2_diode2_points_corrT.Fill(c, dataSlices[i].GetInt2());
	    bat2_temperature_points_corrT.Fill(c, dataSlices[i].GetTemper());

	    bat2_diodes_divide_corrT.Fill(c, dataSlices[i].GetInt1());
	    bat2_diode1_temp_corrT.Fill(c, dataSlices[i].GetInt1());
	    bat2_diode2_temp_corrT.Fill(c, dataSlices[i].GetInt2());

	    bat2_diode1_hist_corrT.Fill(dataSlices[i].GetInt1());
	    bat2_diode2_hist_corrT.Fill(dataSlices[i].GetInt2());
	    bat2_temperature_hist_corrT.Fill(dataSlices[i].GetTemper());
	  }

	  bat2_diode1_temp_comp.Fill(dataSlices[i].GetInt1(), dataSlices[i].GetTemper());
	  bat2_diode2_temp_comp.Fill(dataSlices[i].GetInt2(), dataSlices[i].GetTemper());
	  //bat2_time1_temp_comp.Fill(c,dataSlices[i].GetInt1(), dataSlices[i].GetTemper());
	  //bat2_time2_temp_comp.Fill(c,dataSlices[i].GetInt2(), dataSlices[i].GetTemper());
	  
	  c += 1;
	}
      }
    }
  }
  bat2_diodes_divide.Divide(&bat2_diode2_points);
  bat2_diode1_temp.Divide(&bat2_temperature_points);
  bat2_diode2_temp.Divide(&bat2_temperature_points);
  bat2_diodes_divide_corr.Divide(&bat2_diode2_points_corr);
  bat2_diode1_temp_corr.Divide(&bat2_temperature_points_corr);
  bat2_diode2_temp_corr.Divide(&bat2_temperature_points_corr);
  cout << "Battery 2 input file size: " << readData.Size() << endl;
  cout << "But Data size: " << dataSlices.size() << endl;

  bat2_diode1.Write();
  bat2_diode2.Write();
  bat2_temperature.Write();

  bat2_diode1_points.Write();
  bat2_diode2_points.Write();
  bat2_temperature_points.Write();
  
  bat2_diodes_divide.Write();
  bat2_diode1_temp.Write();
  bat2_diode2_temp.Write();

  bat2_diode1_hist.Write();
  bat2_diode2_hist.Write();
  bat2_temperature_hist.Write();

  bat2_diode1_corr.Write();
  bat2_diode2_corr.Write();
  bat2_temperature_corr.Write();

  bat2_diode1_points_corr.Write();
  bat2_diode2_points_corr.Write();
  bat2_temperature_points_corr.Write();
  
  bat2_diodes_divide_corr.Write();
  bat2_diode1_temp_corr.Write();
  bat2_diode2_temp_corr.Write();

  bat2_diode1_hist_corr.Write();
  bat2_diode2_hist_corr.Write();
  bat2_temperature_hist_corr.Write();

  bat2_diode1_temp_comp.Write();
  bat2_diode2_temp_comp.Write();
  //bat2_time1_temp_comp.Write();
  //bat2_time2_temp_comp.Write();

  out_file2 -> Close();
  delete out_file2;

  
  // Battery Test 3
  
  TFile* out_file3 = new TFile("Results/Battery_Tests/BatteryTest3Output.root","RECREATE");
  
  name_of_file = "Data/Battery_Tests/BatteryTest3Input"; // NAME of TEST FILE (after being converted from txt to binary)
  
  readData.Open(name_of_file);
  readData.Prepare_Test(dataSlices);
  readData.Fill_Test(dataSlices);
  
  // Data files not filtered for error line
  TH1F bat3_diode1("Intensity_1_bat3", "Battery Test 3 - Intensity of Photodiode 1", 21620400,1791792026,1813412426);
  TH1F bat3_diode2("Intensity_2_bat3", "Battery Test 3 - Intensity of Photodiode 2", 21620400,1791792026,1813412426);
  TH1F bat3_temperature("Temperature_bat3", "Battery Test 3 - Temperature", 21620400,1791792026,1813412426);
  
  TH1F bat3_diode1_points("Int1_bat3_points", "Battery Test 3 - Intensity of Photodiode 1", 1363937, 0, 1363937);
  TH1F bat3_diode2_points("Int2_bat3_points", "Battery Test 3 - Intensity of Photodiode 2", 1363937, 0, 1363937);
  TH1F bat3_temperature_points("Temperature_bat3_points", "Battery Test 3 - Temperature", 1363937, 0, 1363937);
  TH1F bat3_diodes_divide("Int1_Int2_comp_bat3", "Battery Test 3 - Intensity 1 / Intensity 2", 1363937, 0, 1363937);
  TH1F bat3_diode1_temp("Int1_temp_comp_bat3", "Battery Test 3 - Intensity 1 / Temperature", 1363937, 0, 1363937);
  TH1F bat3_diode2_temp("Int2_temp_comp_bat3", "Battery Test 3 - Intensity 2 / Temperature", 1363937, 0, 1363937);
  
  TH1F bat3_diode1_hist("Int1_range_bat3", "Battery Test 3 - Values Range of Intensity 1", 60000, 0, 60000);
  TH1F bat3_diode2_hist("Int2_range_bat3", "Battery Test 3 - Values Range of Intensity 2", 60000, 0, 60000);
  TH1F bat3_temperature_hist("Temp_range_bat3", "Battery Test 3 - Values Range of Temperature", 60000, 0, 60000);

  // Data filtered of their atrocious errors
  TH1F bat3_diode1_corr("Intensity_1_bat3_corr", "Battery Test 3 - Intensity of Photodiode 1", 21620400,1791792026,1813412426);
  TH1F bat3_diode2_corr("Intensity_2_bat3_corr", "Battery Test 3 - Intensity of Photodiode 2", 21620400,1791792026,1813412426);
  TH1F bat3_temperature_corr("Temperature_bat3_corr", "Battery Test 3 - Temperature", 21620400,1791792026,1813412426);
  
  TH1F bat3_diode1_points_corr("Int1_bat3_points_corr", "Battery Test 3 - Intensity of Photodiode 1", 1363937, 0, 1363937);
  TH1F bat3_diode2_points_corr("Int2_bat3_points_corr", "Battery Test 3 - Intensity of Photodiode 2", 1363937, 0, 1363937);
  TH1F bat3_temperature_points_corr("Temperature_bat3_points_corr", "Battery Test 3 - Temperature", 1363937, 0, 1363937);
  TH1F bat3_diodes_divide_corr("Int1_Int2_comp_bat3_corr", "Battery Test 3 - Intensity 1 / Intensity 2", 1363937, 0, 1363937);
  TH1F bat3_diode1_temp_corr("Int1_temp_comp_bat3_corr", "Battery Test 3 - Intensity 1 / Temperature", 1363937, 0, 1363937);
  TH1F bat3_diode2_temp_corr("Int2_temp_comp_bat3_corr", "Battery Test 3 - Intensity 2 / Temperature", 1363937, 0, 1363937);
  
  TH1F bat3_diode1_hist_corr("Int1_range_bat3_corr", "Battery Test 3 - Values Range of Intensity 1", 60000, 0, 60000);
  TH1F bat3_diode2_hist_corr("Int2_range_bat3_corr", "Battery Test 3 - Values Range of Intensity 2", 60000, 0, 60000);
  TH1F bat3_temperature_hist_corr("Temp_range_bat3_corr", "Battery Test 3 - Values Range of Temperature", 60000, 0, 60000);

  TH2D bat3_diode1_temp_comp("Int1_temp_bat3_2D", "Battery Test 3 - Intensity 1 vs Temperature", 10000, 50000, 60000, 100, 20, 30);
  TH2D bat3_diode2_temp_comp("Int2_temp_bat3_2D", "Battery Test 3 - Intensity 2 vs Temperature", 10000, 50000, 60000, 100, 20, 30);
  //TH2D bat3_time1_temp_comp("Int1_temp_bat3_time", "Battery Test 3 - Intensity 1 vs Time (Temperature)", 1363937, 0, 1363937, 10000, 50000, 60000);
  //TH2D bat3_time2_temp_comp("Int2_temp_bat3_time", "Battery Test 3 - Intensity 2 vs Time (Temperature)", 1363937, 0, 1363937, 10000, 50000, 60000);
  
  c = 0;
  for (long long i=0; i < readData.Size()/18; i++){
    
    bat3_diode1.Fill(dataSlices[i].GetTime(), dataSlices[i].GetInt1());
    bat3_diode2.Fill(dataSlices[i].GetTime(), dataSlices[i].GetInt2());
    bat3_temperature.Fill(dataSlices[i].GetTime(), dataSlices[i].GetTemper());

    bat3_diode1_points.Fill(i, dataSlices[i].GetInt1());
    bat3_diode2_points.Fill(i, dataSlices[i].GetInt2());
    bat3_temperature_points.Fill(i, dataSlices[i].GetTemper());

    bat3_diodes_divide.Fill(i, dataSlices[i].GetInt1());
    bat3_diode1_temp.Fill(i, dataSlices[i].GetInt1());
    bat3_diode2_temp.Fill(i, dataSlices[i].GetInt2());

    bat3_diode1_hist.Fill(dataSlices[i].GetInt1());
    bat3_diode2_hist.Fill(dataSlices[i].GetInt2());
    bat3_temperature_hist.Fill(dataSlices[i].GetTemper());

    if (dataSlices[i].GetInt1() < 60000 && dataSlices[i].GetInt1() > 50000){
      if (dataSlices[i].GetInt2() < 60000 && dataSlices[i].GetInt2() > 50000){
	if (dataSlices[i].GetTemper() < 30 && dataSlices[i].GetTemper() > 15){
	  bat3_diode1_corr.Fill(dataSlices[i].GetTime(), dataSlices[i].GetInt1());
	  bat3_diode2_corr.Fill(dataSlices[i].GetTime(), dataSlices[i].GetInt2());
	  bat3_temperature_corr.Fill(dataSlices[i].GetTime(), dataSlices[i].GetTemper());

	  bat3_diode1_points_corr.Fill(c, dataSlices[i].GetInt1());
	  bat3_diode2_points_corr.Fill(c, dataSlices[i].GetInt2());
	  bat3_temperature_points_corr.Fill(c, dataSlices[i].GetTemper());

	  bat3_diodes_divide_corr.Fill(c, dataSlices[i].GetInt1());
	  bat3_diode1_temp_corr.Fill(c, dataSlices[i].GetInt1());
	  bat3_diode2_temp_corr.Fill(c, dataSlices[i].GetInt2());

	  bat3_diode1_hist_corr.Fill(dataSlices[i].GetInt1());
	  bat3_diode2_hist_corr.Fill(dataSlices[i].GetInt2());
	  bat3_temperature_hist_corr.Fill(dataSlices[i].GetTemper());

	  bat3_diode1_temp_comp.Fill(dataSlices[i].GetInt1(), dataSlices[i].GetTemper());
	  bat3_diode2_temp_comp.Fill(dataSlices[i].GetInt2(), dataSlices[i].GetTemper());
	  //bat3_time1_temp_comp.Fill(c,dataSlices[i].GetInt1(), dataSlices[i].GetTemper());
	  //bat3_time1_temp_comp.Fill(c,dataSlices[i].GetInt2(), dataSlices[i].GetTemper());
	  c += 1;
	}
      }
    }
  }
  bat3_diodes_divide.Divide(&bat3_diode2_points);
  bat3_diode1_temp.Divide(&bat3_temperature_points);
  bat3_diode2_temp.Divide(&bat3_temperature_points);
  bat3_diodes_divide_corr.Divide(&bat3_diode2_points_corr);
  bat3_diode1_temp_corr.Divide(&bat3_temperature_points_corr);
  bat3_diode2_temp_corr.Divide(&bat3_temperature_points_corr);
  cout << "Battery 3 input file size: " << readData.Size() << endl;
  cout << "But Data size: " << dataSlices.size() << endl;

  bat3_diode1.Write();
  bat3_diode2.Write();
  bat3_temperature.Write();

  bat3_diode1_points.Write();
  bat3_diode2_points.Write();
  bat3_temperature_points.Write();
  
  bat3_diodes_divide.Write();
  bat3_diode1_temp.Write();
  bat3_diode2_temp.Write();

  bat3_diode1_hist.Write();
  bat3_diode2_hist.Write();
  bat3_temperature_hist.Write();

  bat3_diode1_corr.Write();
  bat3_diode2_corr.Write();
  bat3_temperature_corr.Write();

  bat3_diode1_points_corr.Write();
  bat3_diode2_points_corr.Write();
  bat3_temperature_points_corr.Write();
  
  bat3_diodes_divide_corr.Write();
  bat3_diode1_temp_corr.Write();
  bat3_diode2_temp_corr.Write();

  bat3_diode1_hist_corr.Write();
  bat3_diode2_hist_corr.Write();
  bat3_temperature_hist_corr.Write();

  bat3_diode1_temp_comp.Write();
  bat3_diode2_temp_comp.Write();
  //bat3_time1_temp_comp.Write();
  //bat3_time2_temp_comp.Write();

  out_file3 -> Close();
  delete out_file3;



  // Terminal Test 
  
  TFile* out_file4 = new TFile("Results/Terminal_Tests/TerminalTestOutput.root","RECREATE");

  TVirtualFFT::SetTransform(0);
  TH1* fastTransform1 = NULL;
  TH1* fastTransform2 = NULL;
  
  
  name_of_file = "Data/Terminal_Tests/TerminalTest"; // NAME of TEST FILE (after being converted from txt to binary)
  
  readData.Open(name_of_file);
  readData.Prepare_Test(dataSlices);
  readData.Fill_Test(dataSlices);

  // Data files not filtered for error line
  TH1F term1_diode1("Intensity_1_term1", "Terminal Test - Intensity of Photodiode 1", 525291,0,525291);
  TH1F term1_diode2("Intensity_2_term1", "Terminal Test - Intensity of Photodiode 2", 525291,0,525291);
  TH1F term1_temperature("Temperature_term1", "Terminal Test - Temperature", 525291,0,525291);
  
  TH1F term1_diode1_points("Int1_term1_points", "Terminal Test - Intensity of Photodiode 1", 525291, 0, 525291);
  TH1F term1_diode2_points("Int2_term1_points", "Terminal Test - Intensity of Photodiode 2", 525291, 0, 525291);
  TH1F term1_temperature_points("Temperature_term1_points", "Terminal Test - Temperature", 525291, 0, 525291);
  TH1F term1_diodes_divide("Int1_Int2_comp_term1", "Terminal Test - Intensity 1 / Intensity 2", 525291, 0, 525291);
  TH1F term1_diode1_temp("Int1_temp_comp_term1", "Terminal Test - Intensity 1 / Temperature", 525291, 0, 525291);
  TH1F term1_diode2_temp("Int2_temp_comp_term1", "Terminal Test - Intensity 2 / Temperature", 525291, 0, 525291);
  
  TH1F term1_diode1_hist("Int1_range_term1", "Terminal Test - Values Range of Intensity 1", 50000, 0, 50000);
  TH1F term1_diode2_hist("Int2_range_term1", "Terminal Test - Values Range of Intensity 2", 50000, 0, 50000);
  TH1F term1_temperature_hist("Temp_range_term1", "Terminal Test - Values Range of Temperature", 50000, 0, 50000);

  // Data filtered of their atrocious errors
  TH1F term1_diode1_corr("Intensity_1_term1_corr", "Terminal Test - Intensity of Photodiode 1", 525291,0,525291);
  TH1F term1_diode2_corr("Intensity_2_term1_corr", "Terminal Test - Intensity of Photodiode 2", 525291,0,525291);
  TH1F term1_temperature_corr("Temperature_term1_corr", "Terminal Test - Temperature", 525291,0,525291);
  
  TH1F term1_diode1_points_corr("Int1_term1_points_corr", "Terminal Test - Intensity of Photodiode 1", 525291, 0, 525291);
  TH1F term1_diode2_points_corr("Int2_term1_points_corr", "Terminal Test - Intensity of Photodiode 2", 525291, 0, 525291);
  TH1F term1_temperature_points_corr("Temperature_term1_points_corr", "Terminal Test - Temperature", 525291, 0, 525291);
  TH1F term1_diodes_divide_corr("Int1_Int2_comp_term1_corr", "Terminal Test - Intensity 1 / Intensity 2", 525291, 0, 525291);
  TH1F term1_diode1_temp_corr("Int1_temp_comp_term1_corr", "Terminal Test - Intensity 1 / Temperature", 525291, 0, 525291);
  TH1F term1_diode2_temp_corr("Int2_temp_comp_term1_corr", "Terminal Test - Intensity 2 / Temperature", 525291, 0, 525291);
  
  TH1F term1_diode1_hist_corr("Int1_range_term1_corr", "Terminal Test - Values Range of Intensity 1", 50000, 0, 50000);
  TH1F term1_diode2_hist_corr("Int2_range_term1_corr", "Terminal Test - Values Range of Intensity 2", 50000, 0, 50000);
  TH1F term1_temperature_hist_corr("Temp_range_term1_corr", "Terminal Test - Values Range of Temperature", 50000, 0, 50000);

  // Same as above but with stricter temperature
  TH1F term1_diode1_points_corrT("Int1_term1_points_corrT", "Terminal Test - Intensity of Photodiode 1", 525291, 0, 525291);
  TH1F term1_diode2_points_corrT("Int2_term1_points_corrT", "Terminal Test - Intensity of Photodiode 2", 525291, 0, 525291);
  TH1F term1_temperature_points_corrT("Temperature_term1_points_corrT", "Terminal Test - Temperature", 525291, 0, 525291);
  TH1F term1_diodes_divide_corrT("Int1_Int2_comp_term1_corrT", "Terminal Test - Intensity 1 / Intensity 2", 525291, 0, 525291);
  TH1F term1_diode1_temp_corrT("Int1_temp_comp_term1_corrT", "Terminal Test - Intensity 1 / Temperature", 525291, 0, 525291);
  TH1F term1_diode2_temp_corrT("Int2_temp_comp_term1_corrT", "Terminal Test - Intensity 2 / Temperature", 525291, 0, 525291);
																
  TH1F term1_diode1_hist_corrT("Int1_range_term1_corrT", "Terminal Test- Values Range of Intensity 1", 50000, 0, 50000);
  TH1F term1_diode2_hist_corrT("Int2_range_term1_corrT", "Terminal Test - Values Range of Intensity 2", 50000, 0, 50000);
  TH1F term1_temperature_hist_corrT("Temp_range_term1_corrT", "Terminal Test - Values Range of Temperature", 50000, 0, 50000);

  TH2D term1_diode1_temp_comp("Int1_temp_term1_2D", "Terminal Test - Intensity 1 vs Temperature", 10000, 40000, 50000, 100, 20, 30);
  TH2D term1_diode2_temp_comp("Int2_temp_term1_2D", "Terminal Test - Intensity 2 vs Temperature", 10000, 40000, 50000, 100, 20, 30);
  //TH2D term1_time1_temp_comp("Int1_temp_bat2_time", "Terminal Test - Intensity 1 vs Time (Temperature)", 688055, 0, 688055, 10000, 50000, 60000);
  //TH2D term1_time2_temp_comp("Int2_temp_bat2_time", "Terminal Test - Intensity 2 vs Time (Temperature)", 688055, 0, 688055, 10000, 50000, 60000);
  
  c = 0;
  for (long long i=0; i < readData.Size()/18; i++){
    
    term1_diode1.Fill(dataSlices[i].GetTime(), dataSlices[i].GetInt1());
    term1_diode2.Fill(dataSlices[i].GetTime(), dataSlices[i].GetInt2());
    term1_temperature.Fill(dataSlices[i].GetTime(), dataSlices[i].GetTemper());

    term1_diode1_points.Fill(i, dataSlices[i].GetInt1());
    term1_diode2_points.Fill(i, dataSlices[i].GetInt2());
    term1_temperature_points.Fill(i, dataSlices[i].GetTemper());

    term1_diodes_divide.Fill(i, dataSlices[i].GetInt1());
    term1_diode1_temp.Fill(i, dataSlices[i].GetInt1());
    term1_diode2_temp.Fill(i, dataSlices[i].GetInt2());

    term1_diode1_hist.Fill(dataSlices[i].GetInt1());
    term1_diode2_hist.Fill(dataSlices[i].GetInt2());
    term1_temperature_hist.Fill(dataSlices[i].GetTemper());

    if (dataSlices[i].GetInt1() < 50000 && dataSlices[i].GetInt1() > 40000){
      if (dataSlices[i].GetInt2() < 50000 && dataSlices[i].GetInt2() > 40000){
	if (dataSlices[i].GetTemper() < 30 && dataSlices[i].GetTemper() > 15){
	  term1_diode1_corr.Fill(dataSlices[i].GetTime(), dataSlices[i].GetInt1());
	  term1_diode2_corr.Fill(dataSlices[i].GetTime(), dataSlices[i].GetInt2());
	  term1_temperature_corr.Fill(dataSlices[i].GetTime(), dataSlices[i].GetTemper());

	  term1_diode1_points_corr.Fill(c, dataSlices[i].GetInt1());
	  term1_diode2_points_corr.Fill(c, dataSlices[i].GetInt2());
	  term1_temperature_points_corr.Fill(c, dataSlices[i].GetTemper());

	  term1_diodes_divide_corr.Fill(c, dataSlices[i].GetInt1());
	  term1_diode1_temp_corr.Fill(c, dataSlices[i].GetInt1());
	  term1_diode2_temp_corr.Fill(c, dataSlices[i].GetInt2());

	  term1_diode1_hist_corr.Fill(dataSlices[i].GetInt1());
	  term1_diode2_hist_corr.Fill(dataSlices[i].GetInt2());
	  term1_temperature_hist_corr.Fill(dataSlices[i].GetTemper());
	  
	  if (dataSlices[i].GetTemper() < 27.5 && dataSlices[i].GetTemper() > 26.5){
	    term1_diode1_points_corrT.Fill(c, dataSlices[i].GetInt1());
	    term1_diode2_points_corrT.Fill(c, dataSlices[i].GetInt2());
	    term1_temperature_points_corrT.Fill(c, dataSlices[i].GetTemper());

	    term1_diodes_divide_corrT.Fill(c, dataSlices[i].GetInt1());
	    term1_diode1_temp_corrT.Fill(c, dataSlices[i].GetInt1());
	    term1_diode2_temp_corrT.Fill(c, dataSlices[i].GetInt2());

	    term1_diode1_hist_corrT.Fill(dataSlices[i].GetInt1());
	    term1_diode2_hist_corrT.Fill(dataSlices[i].GetInt2());
	    term1_temperature_hist_corrT.Fill(dataSlices[i].GetTemper());
	  }

	  term1_diode1_temp_comp.Fill(dataSlices[i].GetInt1(), dataSlices[i].GetTemper());
	  term1_diode2_temp_comp.Fill(dataSlices[i].GetInt2(), dataSlices[i].GetTemper());
	  //term1_time1_temp_comp.Fill(c,dataSlices[i].GetInt1(), dataSlices[i].GetTemper());
	  //term1_time2_temp_comp.Fill(c,dataSlices[i].GetInt2(), dataSlices[i].GetTemper());
	  
	  c += 1;
	}
      }
    }
  }
  term1_diodes_divide.Divide(&term1_diode2_points);
  term1_diode1_temp.Divide(&term1_temperature_points);
  term1_diode2_temp.Divide(&term1_temperature_points);
  term1_diodes_divide_corr.Divide(&term1_diode2_points_corr);
  term1_diode1_temp_corr.Divide(&term1_temperature_points_corr);
  term1_diode2_temp_corr.Divide(&term1_temperature_points_corr);
  cout << "Terminal input file size: " << readData.Size() << endl;
  cout << "But Data size: " << dataSlices.size() << endl;

  fastTransform1 = term1_diode1_hist_corr.FFT(fastTransform1, "MAG");
  fastTransform2 = term1_diode2_hist_corr.FFT(fastTransform2, "MAG");

  fastTransform1 -> Write();
  fastTransform2 -> Write();
  
  term1_diode1.Write();
  term1_diode2.Write();
  term1_temperature.Write();

  term1_diode1_points.Write();
  term1_diode2_points.Write();
  term1_temperature_points.Write();
  
  term1_diodes_divide.Write();
  term1_diode1_temp.Write();
  term1_diode2_temp.Write();

  term1_diode1_hist.Write();
  term1_diode2_hist.Write();
  term1_temperature_hist.Write();

  term1_diode1_corr.Write();
  term1_diode2_corr.Write();
  term1_temperature_corr.Write();

  term1_diode1_points_corr.Write();
  term1_diode2_points_corr.Write();
  term1_temperature_points_corr.Write();
  
  term1_diodes_divide_corr.Write();
  term1_diode1_temp_corr.Write();
  term1_diode2_temp_corr.Write();

  term1_diode1_hist_corr.Write();
  term1_diode2_hist_corr.Write();
  term1_temperature_hist_corr.Write();

  term1_diode1_temp_comp.Write();
  term1_diode2_temp_comp.Write();
  //term1_time1_temp_comp.Write();
  //term1_time2_temp_comp.Write();

  out_file4 -> Close();
  delete out_file4;

  
  return 0;
}
