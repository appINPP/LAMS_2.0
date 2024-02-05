#include <iostream>
#include <string>
#include <vector>

#include "TFile.h"
#include "TH1.h"

#include "DataGrabber.hh"
#include "Slices.hh"
#include "Tools.hh"

using namespace std;

int main(){
  
  TFile* out_file = new TFile("Results/Revisit_2009/NestorOutput.root","RECREATE");
  vector <Slice> nestorData;
  unsigned long long counter;
  
  TH1F N_photodiode1_10m("N_Intensity1_10m", "2009 - Intensity of Photodiode 1 at 10 meters", 3000000,0,3000000);
  TH1F N_photodiode2_10m("N_Intensity2_10m", "2009 - Intensity of Photodiode 2 at 10 meters", 3000000,0,3000000);
  
  TH1F N_photodiode1_15m("N_Intensity1_15m", "2009 - Intensity of Photodiode 1 at 15 meters", 3000000,0,3000000);
  TH1F N_photodiode2_15m("N_Intensity2_15m", "2009 - Intensity of Photodiode 2 at 15 meters", 3000000,0,3000000);
  
  TH1F N_photodiode1_17m("N_Intensity1_17m", "2009 - Intensity of Photodiode 1 at 17 meters", 3000000,0,3000000);
  TH1F N_photodiode2_17m("N_Intensity2_17m", "2009 - Intensity of Photodiode 2 at 17 meters", 3000000,0,3000000);
  
  TH1F N_photodiode1_23m("N_Intensity1_23m", "2009 - Intensity of Photodiode 1 at 23 meters", 3000000,0,3000000);
  TH1F N_photodiode2_23m("N_Intensity2_23m", "2009 - Intensity of Photodiode 2 at 23 meters", 3000000,0,3000000);

  TH1F N_sample1_10m("N_sample1_10m", "2009 - Intensity of Photodiode 1 at 10 meters", 100000,0,100000);
  TH1F N_sample2_10m("N_sample2_10m", "2009 - Intensity of Photodiode 2 at 10 meters", 100000,0,100000);
  
  TH1F N_sample1_15m("N_sample1_15m", "2009 - Intensity of Photodiode 1 at 15 meters", 100000,0,100000);
  TH1F N_sample2_15m("N_sample2_15m", "2009 - Intensity of Photodiode 2 at 15 meters", 100000,0,100000);
  
  TH1F N_sample1_17m("N_sample1_17m", "2009 - Intensity of Photodiode 1 at 17 meters", 100000,0,100000);
  TH1F N_sample2_17m("N_sample2_17m", "2009 - Intensity of Photodiode 2 at 17 meters", 100000,0,100000);
  
  TH1F N_sample1_23m("N_sample1_23m", "2009 - Intensity of Photodiode 1 at 23 meters", 100000,0,100000);
  TH1F N_sample2_23m("N_sample2_23m", "2009 - Intensity of Photodiode 2 at 23 meters", 100000,0,100000);

  TH1F C2_photodiode1_10m("C2_Intensity1_10m", "2009 - Intensity of Photodiode 1 at 10 meters", 2500000,0,2500000);
  TH1F C2_photodiode2_10m("C2_Intensity2_10m", "2009 - Intensity of Photodiode 2 at 10 meters", 2500000,0,2500000);
  
  TH1F C2_photodiode1_15m("C2_Intensity1_15m", "2009 - Intensity of Photodiode 1 at 15 meters", 2500000,0,2500000);
  TH1F C2_photodiode2_15m("C2_Intensity2_15m", "2009 - Intensity of Photodiode 2 at 15 meters", 2500000,0,2500000);
  
  TH1F C2_photodiode1_17m("C2_Intensity1_17m", "2009 - Intensity of Photodiode 1 at 17 meters", 2500000,0,2500000);
  TH1F C2_photodiode2_17m("C2_Intensity2_17m", "2009 - Intensity of Photodiode 2 at 17 meters", 2500000,0,2500000);
  
  TH1F C2_photodiode1_22m("C2_Intensity1_22m", "2009 - Intensity of Photodiode 1 at 22 meters", 2500000,0,2500000);
  TH1F C2_photodiode2_22m("C2_Intensity2_22m", "2009 - Intensity of Photodiode 2 at 22 meters", 2500000,0,2500000);

  TH1F C2_sample1_10m("C2_sample1_10m", "2009 - Intensity of Photodiode 1 at 10 meters", 100000,0,100000);
  TH1F C2_sample2_10m("C2_sample2_10m", "2009 - Intensity of Photodiode 2 at 10 meters", 100000,0,100000);
  
  TH1F C2_sample1_15m("C2_sample1_15m", "2009 - Intensity of Photodiode 1 at 15 meters", 100000,0,100000);
  TH1F C2_sample2_15m("C2_sample2_15m", "2009 - Intensity of Photodiode 2 at 15 meters", 100000,0,100000);
  
  TH1F C2_sample1_17m("C2_sample1_17m", "2009 - Intensity of Photodiode 1 at 17 meters", 100000,0,100000);
  TH1F C2_sample2_17m("C2_sample2_17m", "2009 - Intensity of Photodiode 2 at 17 meters", 100000,0,100000);
  
  TH1F C2_sample1_22m("C2_sample1_23m", "2009 - Intensity of Photodiode 1 at 22 meters", 100000,0,100000);
  TH1F C2_sample2_22m("C2_sample2_23m", "2009 - Intensity of Photodiode 2 at 22 meters", 100000,0,100000);
  
  Stopwatch clock;
  clock.Start(0);
  DataGrabber readData;
  vector <string> files;
  files.push_back("Data/Revisit_2009/Nestor_10m");
  files.push_back("Data/Revisit_2009/Nestor_15m");
  files.push_back("Data/Revisit_2009/Nestor_17m");
  files.push_back("Data/Revisit_2009/Nestor_23m");

  files.push_back("Data/Revisit_2009/Capo2_10m");
  files.push_back("Data/Revisit_2009/Capo2_15m");
  files.push_back("Data/Revisit_2009/Capo2_17m");
  files.push_back("Data/Revisit_2009/Capo2_22m");

  for (unsigned int i = 0; i < files.size(); i++){
    clock.Stop(0);
    cout << "Now at file: " << files[i] << " at time: " << clock.Show(0) << endl;
    readData.Open(files[i]);
    readData.Prepare_Old(nestorData);
    readData.Fill_Old(nestorData, counter);

    for (unsigned int time=0; time < nestorData.size(); time++){
      
      switch(i){
      case 0:{
	N_photodiode1_10m.Fill(time, nestorData[time].GetInt1());
	N_photodiode2_10m.Fill(time, nestorData[time].GetInt2());
	if (time >= 60000 && time < 160000){
	  N_sample1_10m.Fill(time - 60000, nestorData[time].GetInt1());
	  N_sample2_10m.Fill(time - 60000, nestorData[time].GetInt2());
	}
	break;
      }
      case 1:{
	N_photodiode1_15m.Fill(time, nestorData[time].GetInt1());
	N_photodiode2_15m.Fill(time, nestorData[time].GetInt2());
	if (time >= 60000 && time < 160000){
	  N_sample1_15m.Fill(time - 60000, nestorData[time].GetInt1());
	  N_sample2_15m.Fill(time - 60000, nestorData[time].GetInt2());
	}
	break;
      }
      case 2:{
	N_photodiode1_17m.Fill(time, nestorData[time].GetInt1());
	N_photodiode2_17m.Fill(time, nestorData[time].GetInt2());
	if (time >= 60000 && time < 160000){
	  N_sample1_17m.Fill(time - 60000, nestorData[time].GetInt1());
	  N_sample2_17m.Fill(time - 60000, nestorData[time].GetInt2());
	}
	break;
      }
      case 3:{
	N_photodiode1_23m.Fill(time, nestorData[time].GetInt1());
	N_photodiode2_23m.Fill(time, nestorData[time].GetInt2());
	if (time >= 60000 && time < 160000){
	  N_sample1_23m.Fill(time - 60000, nestorData[time].GetInt1());
	  N_sample2_23m.Fill(time - 60000, nestorData[time].GetInt2());
	}
	break;
      }
      case 4:{
	C2_photodiode1_10m.Fill(time, nestorData[time].GetInt1());
	C2_photodiode2_10m.Fill(time, nestorData[time].GetInt2());
	if (time >= 60000 && time < 160000){
	  C2_sample1_10m.Fill(time - 60000, nestorData[time].GetInt1());
	  C2_sample2_10m.Fill(time - 60000, nestorData[time].GetInt2());
	}
	break;
      }
      case 5:{
	C2_photodiode1_15m.Fill(time, nestorData[time].GetInt1());
	C2_photodiode2_15m.Fill(time, nestorData[time].GetInt2());
	if (time >= 60000 && time < 160000){
	  C2_sample1_15m.Fill(time - 60000, nestorData[time].GetInt1());
	  C2_sample2_15m.Fill(time - 60000, nestorData[time].GetInt2());
	}
	break;
      }
      case 6:{
	C2_photodiode1_17m.Fill(time, nestorData[time].GetInt1());
	C2_photodiode2_17m.Fill(time, nestorData[time].GetInt2());
	if (time >= 60000 && time < 160000){
	  C2_sample1_17m.Fill(time - 60000, nestorData[time].GetInt1());
	  C2_sample2_17m.Fill(time - 60000, nestorData[time].GetInt2());
	}
	break;
      }
      case 7:{
	C2_photodiode1_22m.Fill(time, nestorData[time].GetInt1());
	C2_photodiode2_22m.Fill(time, nestorData[time].GetInt2());
	if (time >= 60000 && time < 160000){
	  C2_sample1_22m.Fill(time - 60000, nestorData[time].GetInt1());
	  C2_sample2_22m.Fill(time - 60000, nestorData[time].GetInt2());
	}
	break;
      }
      }
    }
  }

  N_photodiode1_10m.Write();
  N_photodiode2_10m.Write();
  N_photodiode1_15m.Write();
  N_photodiode2_15m.Write();
  N_photodiode1_17m.Write();
  N_photodiode2_17m.Write();
  N_photodiode1_23m.Write();
  N_photodiode2_23m.Write();

  N_sample1_10m.Write();
  N_sample2_10m.Write();
  N_sample1_15m.Write();
  N_sample2_15m.Write();
  N_sample1_17m.Write();
  N_sample2_17m.Write();
  N_sample1_23m.Write();
  N_sample2_23m.Write();

  C2_photodiode1_10m.Write();
  C2_photodiode2_10m.Write();
  C2_photodiode1_15m.Write();
  C2_photodiode2_15m.Write();
  C2_photodiode1_17m.Write();
  C2_photodiode2_17m.Write();
  C2_photodiode1_22m.Write();
  C2_photodiode2_22m.Write();

  C2_sample1_10m.Write();
  C2_sample2_10m.Write();
  C2_sample1_15m.Write();
  C2_sample2_15m.Write();
  C2_sample1_17m.Write();
  C2_sample2_17m.Write();
  C2_sample1_22m.Write();
  C2_sample2_22m.Write();

  out_file -> Close();
  delete out_file;

  clock.Stop(0);
  cout << "Program ends at time: " << clock.Show(0) << endl;
  return 0;
}
