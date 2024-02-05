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

// Nestor And Capo Passero Analysis


int main(){
  
  // Distances of Source-Emitter, error is commmon for all distances
  //double R[4] = {10,15,17,22};
  double R[4] = {10,15.10,17.17,22.27};
  double R_err = 0.5;

  // Intensities of every pulse in every distance  
  double I_avg[8][4][2];
  double I_err[8][4][2];
  long nI[8][4][2]; // number of intensity points counted in, before doing the average intensity
  
  for (unsigned int i = 0; i < 8; i++){
    for (unsigned int k = 0; k < 4; k++){
      for (unsigned int v = 0; v < 2; v++){
	I_avg[i][k][v] = 0;
	I_err[i][k][v] = 0.01;
	nI[i][k][v] = 0;
      }
    }
  }

  // Create Histograms
  vector < vector < vector <TH1F* > > > pulse;
  string ref_name;
  string hist_title;
  unsigned bin = 200000;
  float bottom_range = 0;
  float top_range = 200000;
  string deployment_site[2];
  deployment_site[0] = "Nestor - Pulse: ";
  deployment_site[1] = "Capo Passero - Pulse: ";
  pulse.resize(8);
  for (unsigned i = 0; i < 8; i++){
    pulse[i].resize(4);
    for (unsigned k = 0; k < 4; k++){
      for (unsigned v = 0; v < 2; v++){
	ref_name = static_cast<string>("pulse") + NumToString(i+1) + static_cast<string>("_site") + NumToString(v) + static_cast<string>("_") + NumToString(R[k]) + static_cast<string>("m");
	hist_title = deployment_site[v] + NumToString(i+1) + static_cast<string>(" - ") + NumToString(R[k]) + static_cast<string>("m");
	pulse[i][k].push_back( MakeHist(ref_name, hist_title, bin, bottom_range, top_range));
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
  unsigned long long dummy;
  DataGrabber readData;
  PatternRecognition Pattern;
  TFile* outFile = new TFile("Results/Complete/CompleteOld.root","RECREATE");

  // Loop for all files
  for (unsigned site = 0; site < 2; site++){
    for (unsigned selectFile = 0; selectFile < 4; selectFile++){
      file = "Data/Revisit_2009/";
      if (selectFile == 0){
	Pattern = PatternRecognition(10000,60000);
	if (site == 0){
	  file = file + static_cast<string>("Nestor_10m_Cut");
	}
	else{
	  file = file + static_cast<string>("Capo_10m_Cut");
	}
      }
      else if (selectFile == 1){
	Pattern = PatternRecognition(4000,60000);
	if (site == 0){
	  file = file + static_cast<string>("Nestor_15m_Cut");
	}
	else{
	  file = file + static_cast<string>("Capo_15m_Cut");
	}
      }
      else if (selectFile == 2){
	Pattern = PatternRecognition(2000,60000);
	if (site == 0){
	  file = file + static_cast<string>("Nestor_17m_Cut");
	}
	else{
	  file = file + static_cast<string>("Capo_17m_Cut");
	}
      }
      else {
	Pattern = PatternRecognition(1000,60000);
	if (site == 0){
	  file = file + static_cast<string>("Nestor_23m_Cut");
	}
	else{
	  file = file + static_cast<string>("Capo_22m_Cut");
	}
      }
      dummy = 0;
      //cout << "selectfile: " << selectFile << " | site: " << site << endl;
      data.clear();
      readData.Open(file);
      readData.Prepare_Old(data);
      readData.Fill_Old(data,dummy);

      //cout << "Data Size: " << data.size() << endl;
      for (unsigned long i = 0; i < data.size(); i++){
	data[i].SetInt2(data[i].GetInt1());
      }
      
      Pattern.Stage_1(data);
      Pattern.Stage_2(data);
      Pattern.Stage_3_1(data,wave);

      for (unsigned long long i = 0; i < data.size(); i++){
	if (data[i].PULSE && data[i].IS_CYCLE && data[i].GetWave() > -1){
	  //cout << "[" << data[i].GetWave() << "," << selectFile << "," << site << "]";
	  pulse[data[i].GetWave()][selectFile][site] -> Fill(i,data[i].GetInt1());
	  I_avg[data[i].GetWave()][selectFile][site] += data[i].GetInt1();
	  nI[static_cast<unsigned>(data[i].GetWave())][selectFile][site]++;
	}
      }

    }
  }

  for (unsigned int v = 0; v < 2; v++){
    for (unsigned int i = 0; i < 8; i++){
      for (unsigned int k = 0; k < 4; k++){
	I_avg[i][k][v] = I_avg[i][k][v]/nI[i][k][v];
	pulse[i][k][v] -> Write();
      }
    }
  }

  double b;
  for (unsigned v = 0; v < 2; v++){
    for (unsigned i = 0; i < 8; i++){
      for (unsigned k = 0; k < 3; k++){
	for (unsigned g = k+1; g < 4; g++){
	  cout << "[Pulse: " << i+1 << " |Rs, Rl = " << R[k] << ", " << R[g] << " |Site: " << v+1 << "]" << endl;
	  b = beta(I_avg[i][k][v], I_avg[i][g][v], R[k], R[g]);
	  cout << "  Beta =  " << b << endl << "    Transmission Length =  " << 1/b << endl;
	  //cout << I_avg[i][k][v] << ", " << I_avg[i][g][v] << ", " <<  R[k] << ", " <<  R[g] << ", " << nI[i][k][v] << ", " << nI[i][g][v] << endl;
	}
      }
      cout << endl;
    }
  }

  cout << "" << R[0] << "m\t" << R[1] << "m\t" << R[2] << "m\t" << R[3] << "m" << endl;
  for (unsigned v = 0; v < 2; v++){
    for (unsigned i = 0; i < 8; i++){
      for (unsigned k = 0; k < 4; k++){
	cout << I_avg[i][k][v] << "\t";
      }
      cout << endl;
    }
  }
  outFile -> Close();

  return 0;
}
