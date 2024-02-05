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

// Spyros Filter Tests
int main(){
  // Distance Parameters (constant for specific filters)
  const double R1 = 13.30; // ND 4,64
  const double R2 = 20.93; // ND 8,64
  const double R3 = 85.51; // ND 8,16,64
  const double R4 = 153.02; // ND 4,8,16,64

  const double err_R1 = 0.06;
  const double err_R2 = 0.09;
  const double err_R3 = 0.39;
  const double err_R4 = 0.77;

  // Intensities
  double I1[8] = {0};
  double I2[8] = {0};
  double I3[8] = {0};
  double I4[8] = {0};

  double err_I1[8] = {0};
  double err_I2[8] = {0};
  double err_I3[8] = {0};
  double err_I4[8] = {0};

  // Beta
  double beta[8] = {0};
  double err_beta[8] = {0};

  // Count Cycles
  vector <unsigned> count[4];
  bool startCycle[4];

  for (unsigned i = 0; i < 4; i++){
    count[i].clear();
    count[i].push_back(0);
    startCycle[i] = false;
  }

  // Distribution of intensity values
  vector < vector < unsigned > > distrib; distrib.clear(); distrib.resize(8);

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
  string file;
  DataGrabber readData;
  PatternRecognition Kostas;
  //TFile* outFile = new TFile("Results/Filter_Tests/BetaTesting.root","RECREATE");


  // Loop for all files
  for (unsigned selectFile = 0; selectFile < 4; selectFile++){
    if (selectFile == 0){
      file = "Data/Filter_Tests/ND4_64_FilterTest_DOMLab";
    }
    else if (selectFile == 1){
      file = "Data/Filter_Tests/ND8_64_FilterTest_DOMLab";
    }
    else if (selectFile == 2){
      file = "Data/Filter_Tests/ND8_16_64_FilterTest";
    }
    else{
      file = "Data/Filter_Tests/ND4_8_16_64_FilterTest";
    }
    
    readData.Open(file);
    readData.Prepare(data);
    readData.Fill(data);

    Kostas.Stage_1(data);
    Kostas.Stage_2(data);
    Kostas.Stage_3(data,wave);

    for (unsigned i = 0; i < 8; i++){
      distrib[i].clear();
    }

    // Get the distribution of Intensities
    for (unsigned long i=0; i < data.size(); i++){
      if (!data[i].DARK_RESET){
	if (!startCycle[selectFile]){
	  count[selectFile].back()++;
	}
	else{
	  count[selectFile].push_back(1);
	  startCycle[selectFile] = false;
	}
      }
      else{
	startCycle[selectFile] = true;
      }
      if (data[i].PULSE){
	if (data[i].GetWave() == 375){
	  distrib[0].push_back(data[i].GetInt1());
	  distrib[0].push_back(data[i].GetInt2());
	}
	else if (data[i].GetWave() == 385){
	  distrib[1].push_back(data[i].GetInt1());
	  distrib[1].push_back(data[i].GetInt2());
	}
	else if (data[i].GetWave() == 400){
	  distrib[2].push_back(data[i].GetInt1());
	  distrib[2].push_back(data[i].GetInt2());
	}
	else if (data[i].GetWave() == 425){
	  distrib[3].push_back(data[i].GetInt1());
	  distrib[3].push_back(data[i].GetInt2());
	}
	else if (data[i].GetWave() == 450){
	  distrib[4].push_back(data[i].GetInt1());
	  distrib[4].push_back(data[i].GetInt2());
	}
	else if (data[i].GetWave() == 470){
	  distrib[5].push_back(data[i].GetInt1());
	  distrib[5].push_back(data[i].GetInt2());
	}
	else if (data[i].GetWave() == 495){
	  distrib[6].push_back(data[i].GetInt1());
	  distrib[6].push_back(data[i].GetInt2());
	}
	else if (data[i].GetWave() == 525){
	  distrib[7].push_back(data[i].GetInt1());
	  distrib[7].push_back(data[i].GetInt2());
	}
      }
    }

    // Mean Intensity
    for (unsigned k = 0; k < 8; k++){
      for (unsigned i = 0; i < distrib[k].size(); i++){
	if (selectFile == 0){
	  I1[k] = I1[k] + distrib[k][i];
	}
	else if (selectFile == 1){
	  I2[k] = I2[k] + distrib[k][i];
	}
	else if (selectFile == 2){
	  I3[k] = I3[k] + distrib[k][i];
	}
	else{
	  I4[k] = I4[k] + distrib[k][i];
	}
      }
      if (selectFile == 0){
	I1[k] = I1[k] / distrib[k].size();
      }
      else if (selectFile == 1){
	I2[k] = I2[k] / distrib[k].size();
      }
      else if (selectFile == 2){
	I3[k] = I3[k] / distrib[k].size();
      }
      else{
	I4[k] = I4[k] / distrib[k].size();
      }
    }

    // Find the STD or Error of Intensity
    for (unsigned k = 0; k < 8; k++){
      for (unsigned i = 0; i < distrib[k].size(); i++){
	if (selectFile == 0){
	  err_I1[k] = err_I1[k] + pow(distrib[k][i] - I1[k],2);
	}
	else if (selectFile == 1){
	  err_I2[k] = err_I2[k] + pow(distrib[k][i] - I2[k],2);
	}
	else if (selectFile == 2){
	  err_I3[k] = err_I3[k] + pow(distrib[k][i] - I3[k],2);
	}
	else{
	  err_I4[k] = err_I4[k] + pow(distrib[k][i] - I4[k],2);
	}
      }
      if (selectFile == 0){
	err_I1[k] = err_I1[k] / distrib.size();
	err_I1[k] = sqrt(err_I1[k]);
      }
      else if (selectFile == 1){
	err_I2[k] = err_I2[k] / distrib.size();
	err_I2[k] = sqrt(err_I2[k]);
      }
      else if (selectFile == 2){
	err_I3[k] = err_I3[k] / distrib.size();
	err_I3[k] = sqrt(err_I3[k]);
      }
      else{
	err_I4[k] = err_I4[k] / distrib.size();
	err_I4[k] = sqrt(err_I4[k]);
      }
    }
  }

  cout << "Rs = " << R1 << " and Rl = " << R2 << endl;
  for (unsigned k = 0; k < 8; k++){
    beta[k] = log(I1[k] / I2[k]) + 2 * log(R1 / R2);
    beta[k] = beta[k] / (R2 - R1);
    cout << "For k: " << k << ", transmission length is: " << -1/beta[k] << endl;
    cout << "Beta is: " << beta[k] << endl;
  }
  cout << endl;

  cout << "Rs = " << R2 << " and Rl = " << R3 << endl;
  for (unsigned k = 0; k < 8; k++){
    beta[k] = log(I2[k] / I3[k]) + 2 * log(R2 / R3);
    beta[k] = beta[k] / (R3 - R2);
    cout << "For k: " << k << ", transmission length is: " << -1/beta[k] << endl;
    cout << "Beta is: " << beta[k] << endl;
  }
  cout << endl;

  cout << "Rs = " << R3 << " and Rl = " << R4 << endl;
  for (unsigned k = 0; k < 8; k++){
    beta[k] = log(I3[k] / I4[k]) + 2 * log(R3 / R4);
    beta[k] = beta[k] / (R4 - R3);
    cout << "For k: " << k << ", transmission length is: " << -1/beta[k] << endl;
    cout << "Beta is: " << beta[k] << endl;
  }
  cout << endl;

  cout << "Rs = " << R1 << " and Rl = " << R3 << endl;
  for (unsigned k = 0; k < 8; k++){
    beta[k] = log(I1[k] / I3[k]) + 2 * log(R1 / R3);
    beta[k] = beta[k] / (R3 - R1);
    cout << "For k: " << k << ", transmission length is: " << -1/beta[k] << endl;
    cout << "Beta is: " << beta[k] << endl;
  }
  cout << endl;

  cout << "Rs = " << R2 << " and Rl = " << R4 << endl;
  for (unsigned k = 0; k < 8; k++){
    beta[k] = log(I2[k] / I4[k]) + 2 * log(R2 / R4);
    beta[k] = beta[k] / (R4 - R2);
    cout << "For k: " << k << ", transmission length is: " << -1/beta[k] << endl;
    cout << "Beta is: " << beta[k] << endl;
  }
  cout << endl;

  cout << "Rs = " << R1 << " and Rl = " << R4 << endl;
  for (unsigned k = 0; k < 8; k++){
    beta[k] = log(I1[k] / I4[k]) + 2 * log(R1 / R4);
    beta[k] = beta[k] / (R4 - R1);
    cout << "For k: " << k << ", transmission length is: " << -1/beta[k] << endl;
    cout << "Beta is: " << beta[k] << endl;
  }
  cout << endl;

  for (unsigned int y = 0; y < 4; y++){
    cout << " ~ ~ Vector: " << y << " ~ ~ " << endl << endl;
    for (unsigned int l = 0; l < count[y].size(); l++){
      cout << count[y][l] << endl;
    }
    cout << endl << endl;
  }
  
  return 0;
}
