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

// System Tests
int main(){

  // TxT files for writing
  ofstream test_txt_abs_exc[6];
  ofstream test_txt_abs_inc[6];
  ofstream test_txt_rel_exc[6];

  test_txt_abs_exc[0].open("Results/System_Tests/test1_10m_abs_exc.txt", ios::out);
  test_txt_abs_exc[1].open("Results/System_Tests/test1_16m_abs_exc.txt", ios::out);
  test_txt_abs_exc[2].open("Results/System_Tests/test1_20m_abs_exc.txt", ios::out);
  test_txt_abs_exc[3].open("Results/System_Tests/test2_10m_abs_exc.txt", ios::out);
  test_txt_abs_exc[4].open("Results/System_Tests/test2_16m_abs_exc.txt", ios::out);
  test_txt_abs_exc[5].open("Results/System_Tests/test3_20m_abs_exc.txt", ios::out);

  test_txt_abs_inc[0].open("Results/System_Tests/test1_10m_abs_inc.txt", ios::out);
  test_txt_abs_inc[1].open("Results/System_Tests/test1_16m_abs_inc.txt", ios::out);
  test_txt_abs_inc[2].open("Results/System_Tests/test1_20m_abs_inc.txt", ios::out);
  test_txt_abs_inc[3].open("Results/System_Tests/test2_10m_abs_inc.txt", ios::out);
  test_txt_abs_inc[4].open("Results/System_Tests/test2_16m_abs_inc.txt", ios::out);
  test_txt_abs_inc[5].open("Results/System_Tests/test3_20m_abs_inc.txt", ios::out);

  test_txt_rel_exc[0].open("Results/System_Tests/test1_10m_rel_exc.txt", ios::out);
  test_txt_rel_exc[1].open("Results/System_Tests/test1_16m_rel_exc.txt", ios::out);
  test_txt_rel_exc[2].open("Results/System_Tests/test1_20m_rel_exc.txt", ios::out);
  test_txt_rel_exc[3].open("Results/System_Tests/test2_10m_rel_exc.txt", ios::out);
  test_txt_rel_exc[4].open("Results/System_Tests/test2_16m_rel_exc.txt", ios::out);
  test_txt_rel_exc[5].open("Results/System_Tests/test3_20m_rel_exc.txt", ios::out);

  vector <unsigned> abs_inc[6][8];
  vector <unsigned> abs_exc[6][8];
  vector <unsigned> rel_exc[6][8];
  bool start_abs_inc[6][8];
  bool start_abs_exc[6][8];
  bool start_rel_exc[6][8];
  unsigned count_abs_inc[6][8];
  unsigned count_abs_exc[6][8];
  unsigned count_rel_exc[6][8];

  for (unsigned i = 0; i < 6; i++){
    for (unsigned k = 0; k < 8; k++){
      
      abs_inc[i][k].clear();
      abs_inc[i][k].push_back(0);
      count_abs_inc[i][k] = 0;
      start_abs_inc[i][k] = false;

      abs_exc[i][k].clear();
      abs_exc[i][k].push_back(0);
      count_abs_exc[i][k] = 0;
      start_abs_exc[i][k] = false;

      rel_exc[i][k].clear();
      rel_exc[i][k].push_back(0);
      count_rel_exc[i][k] = 0;
      start_rel_exc[i][k] = false;
    }
  }
  
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
  vector < string > file;
  DataGrabber readData;
  PatternRecognition Kostas(100,400);
  
  file.clear();
  file.push_back(static_cast<string>("Data/System_Tests/System_Test1_10m"));
  file.push_back(static_cast<string>("Data/System_Tests/System_Test1_16m"));
  file.push_back(static_cast<string>("Data/System_Tests/System_Test1_20m"));
  file.push_back(static_cast<string>("Data/System_Tests/System_Test2_10m"));
  file.push_back(static_cast<string>("Data/System_Tests/System_Test2_16m"));
  file.push_back(static_cast<string>("Data/System_Tests/System_Test3_20m"));


  // Loop for all files
  for (unsigned selectFile = 0; selectFile < file.size(); selectFile++){
    
    readData.Open(file[selectFile]);
    readData.Prepare(data);
    readData.Fill(data);

    Kostas.Stage_1(data);
    Kostas.Stage_2(data);
    Kostas.Stage_3(data,wave);

    // Get the distribution of Intensities
    for (unsigned long i=0; i < data.size(); i++){
      // Data fall into waves
      if (data[i].GetWave() == 375){
	  
	if (i % 100 == 0){
	  start_abs_exc[selectFile][0] = true;
	  if (count_abs_inc[selectFile][0] > 0){
	    abs_inc[selectFile][0].back() ++;
	    count_abs_inc[selectFile][0] = 0;
	  }
	}
	start_abs_inc[selectFile][0] = true;
	start_rel_exc[selectFile][0] = true;

	if (start_abs_exc[selectFile][0]){
	  count_abs_exc[selectFile][0] ++;
	}
	  
	count_abs_inc[selectFile][0] ++;
	count_rel_exc[selectFile][0] ++;

	if (count_abs_exc[selectFile][0] == 100){
	  abs_exc[selectFile][0].back() ++;
	  count_abs_exc[selectFile][0] = 0;
	}

	if (count_rel_exc[selectFile][0] == 100){
	  rel_exc[selectFile][0].back() ++;
	  count_rel_exc[selectFile][0] = 0;
	}
	  
      }
      else if (data[i].GetWave() == 385){

	if (i % 100 == 0){
	  start_abs_exc[selectFile][1] = true;
	  if (count_abs_inc[selectFile][1] > 0){
	    abs_inc[selectFile][1].back() ++;
	    count_abs_inc[selectFile][1] = 0;
	  }
	}
	start_abs_inc[selectFile][1] = true;
	start_rel_exc[selectFile][1] = true;

	if (start_abs_exc[selectFile][1]){
	  count_abs_exc[selectFile][1] ++;
	}
	  
	count_abs_inc[selectFile][1] ++;
	count_rel_exc[selectFile][1] ++;

	if (count_abs_exc[selectFile][1] == 100){
	  abs_exc[selectFile][1].back() ++;
	  count_abs_exc[selectFile][1] = 0;
	}

	if (count_rel_exc[selectFile][1] == 100){
	  rel_exc[selectFile][1].back() ++;
	  count_rel_exc[selectFile][1] = 0;
	}
	  
      }
      else if (data[i].GetWave() == 400){

	if (i % 100 == 0){
	  start_abs_exc[selectFile][2] = true;
	  if (count_abs_inc[selectFile][2] > 0){
	    abs_inc[selectFile][2].back() ++;
	    count_abs_inc[selectFile][2] = 0;
	  }
	}
	start_abs_inc[selectFile][2] = true;
	start_rel_exc[selectFile][2] = true;

	if (start_abs_exc[selectFile][2]){
	  count_abs_exc[selectFile][2] ++;
	}
	  
	count_abs_inc[selectFile][2] ++;
	count_rel_exc[selectFile][2] ++;

	if (count_abs_exc[selectFile][2] == 100){
	  abs_exc[selectFile][2].back() ++;
	  count_abs_exc[selectFile][2] = 0;
	}

	if (count_rel_exc[selectFile][2] == 100){
	  rel_exc[selectFile][2].back() ++;
	  count_rel_exc[selectFile][2] = 0;
	}
	  
      }
      else if (data[i].GetWave() == 425){

	if (i % 100 == 0){
	  start_abs_exc[selectFile][3] = true;
	  if (count_abs_inc[selectFile][3] > 0){
	    abs_inc[selectFile][3].back() ++;
	    count_abs_inc[selectFile][3] = 0;
	  }
	}
	start_abs_inc[selectFile][3] = true;
	start_rel_exc[selectFile][3] = true;

	if (start_abs_exc[selectFile][3]){
	  count_abs_exc[selectFile][3] ++;
	}
	  
	count_abs_inc[selectFile][3] ++;
	count_rel_exc[selectFile][3] ++;

	if (count_abs_exc[selectFile][3] == 100){
	  abs_exc[selectFile][3].back() ++;
	  count_abs_exc[selectFile][3] = 0;
	}

	if (count_rel_exc[selectFile][3] == 100){
	  rel_exc[selectFile][3].back() ++;
	  count_rel_exc[selectFile][3] = 0;
	}
	  
      }
      else if (data[i].GetWave() == 450){

	if (i % 100 == 0){
	  start_abs_exc[selectFile][4] = true;
	  if (count_abs_inc[selectFile][4] > 0){
	    abs_inc[selectFile][4].back() ++;
	    count_abs_inc[selectFile][4] = 0;
	  }
	}
	start_abs_inc[selectFile][4] = true;
	start_rel_exc[selectFile][4] = true;

	if (start_abs_exc[selectFile][4]){
	  count_abs_exc[selectFile][4] ++;
	}
	  
	count_abs_inc[selectFile][4] ++;
	count_rel_exc[selectFile][4] ++;

	if (count_abs_exc[selectFile][4] == 100){
	  abs_exc[selectFile][4].back() ++;
	  count_abs_exc[selectFile][4] = 0;
	}

	if (count_rel_exc[selectFile][4] == 100){
	  rel_exc[selectFile][4].back() ++;
	  count_rel_exc[selectFile][4] = 0;
	}
	  
      }
      else if (data[i].GetWave() == 470){

	if (i % 100 == 0){
	  start_abs_exc[selectFile][5] = true;
	  if (count_abs_inc[selectFile][5] > 0){
	    abs_inc[selectFile][5].back() ++;
	    count_abs_inc[selectFile][5] = 0;
	  }
	}
	start_abs_inc[selectFile][5] = true;
	start_rel_exc[selectFile][5] = true;

	if (start_abs_exc[selectFile][5]){
	  count_abs_exc[selectFile][5] ++;
	}
	  
	count_abs_inc[selectFile][5] ++;
	count_rel_exc[selectFile][5] ++;

	if (count_abs_exc[selectFile][5] == 100){
	  abs_exc[selectFile][5].back() ++;
	  count_abs_exc[selectFile][5] = 0;
	}

	if (count_rel_exc[selectFile][5] == 100){
	  rel_exc[selectFile][5].back() ++;
	  count_rel_exc[selectFile][5] = 0;
	}
	  
      }
      else if (data[i].GetWave() == 495){

	if (i % 100 == 0){
	  start_abs_exc[selectFile][6] = true;
	  if (count_abs_inc[selectFile][6] > 0){
	    abs_inc[selectFile][6].back() ++;
	    count_abs_inc[selectFile][6] = 0;
	  }
	}
	start_abs_inc[selectFile][6] = true;
	start_rel_exc[selectFile][6] = true;

	if (start_abs_exc[selectFile][6]){
	  count_abs_exc[selectFile][6] ++;
	}
	  
	count_abs_inc[selectFile][6] ++;
	count_rel_exc[selectFile][6] ++;

	if (count_abs_exc[selectFile][6] == 100){
	  abs_exc[selectFile][6].back() ++;
	  count_abs_exc[selectFile][6] = 0;
	}

	if (count_rel_exc[selectFile][6] == 100){
	  rel_exc[selectFile][6].back() ++;
	  count_rel_exc[selectFile][6] = 0;
	}
	  
      }
      else if (data[i].GetWave() == 525){

	if (i % 100 == 0){
	  start_abs_exc[selectFile][7] = true;
	  if (count_abs_inc[selectFile][7] > 0){
	    abs_inc[selectFile][7].back() ++;
	    count_abs_inc[selectFile][7] = 0;
	  }
	}
	start_abs_inc[selectFile][7] = true;
	start_rel_exc[selectFile][7] = true;

	if (start_abs_exc[selectFile][7]){
	  count_abs_exc[selectFile][7] ++;
	}
	  
	count_abs_inc[selectFile][7] ++;
	count_rel_exc[selectFile][7] ++;

	if (count_abs_exc[selectFile][7] == 100){
	  abs_exc[selectFile][7].back() ++;
	  count_abs_exc[selectFile][7] = 0;
	}

	if (count_rel_exc[selectFile][7] == 100){
	  rel_exc[selectFile][7].back() ++;
	  count_rel_exc[selectFile][7] = 0;
	}
	  
      }
      else{
	for (unsigned pulseCount = 0; pulseCount < 8; pulseCount++){
	  if (count_abs_inc[selectFile][pulseCount] > 0){
	    abs_inc[selectFile][pulseCount].back() ++;
	    count_abs_inc[selectFile][pulseCount] = 0;
	  }

	  count_abs_exc[selectFile][pulseCount] = 0;
	  count_rel_exc[selectFile][pulseCount] = 0;

	  if (start_abs_exc[selectFile][pulseCount]){
	    abs_exc[selectFile][pulseCount].push_back(0);
	  }
	  if (start_abs_inc[selectFile][pulseCount]){
	    abs_inc[selectFile][pulseCount].push_back(0);
	  }
	  if (start_rel_exc[selectFile][pulseCount]){
	    rel_exc[selectFile][pulseCount].push_back(0);
	  }

	  start_abs_exc[selectFile][pulseCount] = false;
	  start_abs_inc[selectFile][pulseCount] = false;
	  start_rel_exc[selectFile][pulseCount] = false;

	  
	}
      }
    }
  }

  
  for (unsigned fileN = 0; fileN < file.size(); fileN++){
    cout << "File: " << fileN << endl;
    for (unsigned length = 0; length < abs_exc[fileN][7].size(); length++){
      for (unsigned pulseN = 0; pulseN < 8; pulseN++){
	cout << abs_exc[fileN][pulseN][length] << "\t";
	test_txt_abs_exc[fileN] << abs_exc[fileN][pulseN][length] << "\t";
      }
      cout << endl;
      test_txt_abs_exc[fileN] << endl;
    }
    cout << endl;
    test_txt_abs_exc[fileN].close();
  }

  for (unsigned fileN = 0; fileN < file.size(); fileN++){
    for (unsigned length = 0; length < abs_inc[fileN][7].size(); length++){
      for (unsigned pulseN = 0; pulseN < 8; pulseN++){
	test_txt_abs_inc[fileN] << abs_inc[fileN][pulseN][length] << "\t";
      }
      test_txt_abs_inc[fileN] << endl;
    }
    test_txt_abs_inc[fileN].close();
  }

  for (unsigned fileN = 0; fileN < file.size(); fileN++){
    for (unsigned length = 0; length < rel_exc[fileN][7].size(); length++){
      for (unsigned pulseN = 0; pulseN < 8; pulseN++){
	test_txt_rel_exc[fileN] << rel_exc[fileN][pulseN][length] << "\t";
      }
      test_txt_rel_exc[fileN] << endl;
    }
    test_txt_rel_exc[fileN].close();
  }
  
  return 0;
}
