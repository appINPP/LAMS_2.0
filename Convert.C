#include <vector>
#include <string>

#include "TextToBinary.hh"

using namespace std;

/* 
   This software package works on binary data. This specific file
   converts .txt data-files to binary data-files 
*/

int main(){

  bool DontRepeat = true;

  TextToBinary converter;

  string txtFile; // Usual format of LAMS data
  string binFile; // What is needed for this software

  converter.Hex(true); // These files have hexadecimal temperature

  /* The Test_12_12_2018 format is not supported by any function anymore
  txtFile = "/Data/Test_12_12_2018/spyrosTest.txt";
  binFile = "/Data/Test_12_12_2018/spyrosTestInput";
  converter.Convert(txtFile,binFile);  // Arguments can only be strings
  */

  if (!DontRepeat){
    
    txtFile = "Data/Battery_Tests/battery_test_2.txt";
    binFile = "Data/Battery_Tests/BatteryTest2Input";
    converter.Convert_Test(txtFile,binFile);

    txtFile = "Data/Battery_Tests/Battery_test_3_green.txt";
    binFile = "Data/Battery_Tests/BatteryTest3Input";
    converter.Convert_Test(txtFile,binFile);

    txtFile = "Data/Filter_Tests/ND4_8_16_64_Source_onBatteries.txt";
    binFile = "Data/Filter_Tests/ND4_8_16_64_FilterTest";
    converter.Convert_Test(txtFile,binFile);

    txtFile = "Data/Filter_Tests/ND8_16_64_Source_onBatteries.txt";
    binFile = "Data/Filter_Tests/ND8_16_64_FilterTest";
    converter.Convert_Test(txtFile,binFile);

    txtFile = "Data/Filter_Tests/ND4_64_Source_onBatteries_DOMLab.txt";
    binFile = "Data/Filter_Tests/ND4_64_FilterTest_DOMLab";
    converter.Convert_Test(txtFile,binFile);

    txtFile = "Data/Filter_Tests/ND8_64_Source_onBatteries_DOMLab.txt";
    binFile = "Data/Filter_Tests/ND8_64_FilterTest_DOMLab";
    converter.Convert_Test(txtFile,binFile);

    txtFile = "Data/Terminal_Tests/Terminal.txt";
    binFile = "Data/Terminal_Tests/TerminalTest";
    converter.Convert_Test(txtFile,binFile);

  }

  // -- Demokritos Testing, October 2019

  if (!DontRepeat){

    txtFile = "Data/System_Tests/System_Test1_10m.txt";
    binFile = "Data/System_Tests/System_Test1_10m";
    converter.Convert(txtFile,binFile);

    txtFile = "Data/System_Tests/System_Test1_16m.txt";
    binFile = "Data/System_Tests/System_Test1_16m";
    converter.Convert(txtFile,binFile);

    txtFile = "Data/System_Tests/System_Test1_20m.txt";
    binFile = "Data/System_Tests/System_Test1_20m";
    converter.Convert(txtFile,binFile);

    txtFile = "Data/System_Tests/System_Test2_10m.txt";
    binFile = "Data/System_Tests/System_Test2_10m";
    converter.Convert(txtFile,binFile);

    txtFile = "Data/System_Tests/System_Test2_16m.txt";
    binFile = "Data/System_Tests/System_Test2_16m";
    converter.Convert(txtFile,binFile);

    txtFile = "Data/System_Tests/System_Test3_20m.txt";
    binFile = "Data/System_Tests/System_Test3_20m";
    converter.Convert(txtFile,binFile);

  }

  // -- Demokritos Testing, November 2019
  
  if (!DontRepeat){
  
    txtFile = "Data/Com_Tests/Test1_COM3.txt";
    binFile = "Data/Com_Tests/Test1_COM3";
    converter.Convert(txtFile,binFile);

    txtFile = "Data/Com_Tests/Test1_COM4.txt";
    binFile = "Data/Com_Tests/Test1_COM4";
    converter.Convert(txtFile,binFile);

    txtFile = "Data/Com_Tests/Test1_COM5.txt";
    binFile = "Data/Com_Tests/Test1_COM5";
    converter.Convert(txtFile,binFile);

    txtFile = "Data/Com_Tests/Test2_COM3_20m_alone.txt";
    binFile = "Data/Com_Tests/Test2_COM3_20m_alone";
    converter.Convert(txtFile,binFile);
  
    txtFile = "Data/Com_Tests/Test2_COM3_20m_paired.txt";
    binFile = "Data/Com_Tests/Test2_COM3_20m_paired";
    converter.Convert(txtFile,binFile);
  
    txtFile = "Data/Com_Tests/Test2_COM4_16m_paired.txt";
    binFile = "Data/Com_Tests/Test2_COM4_16m_paired";
    converter.Convert(txtFile,binFile);

    txtFile = "Data/Com_Tests/Test3_COM3_20m_paired.txt";
    binFile = "Data/Com_Tests/Test3_COM3_20m_paired";
    converter.Convert(txtFile,binFile);
  
    txtFile = "Data/Com_Tests/Test3_COM4_16m_paired.txt";
    binFile = "Data/Com_Tests/Test3_COM4_16m_paired";
    converter.Convert(txtFile,binFile);
  
    txtFile = "Data/Com_Tests/Test3_COM5_10m_paired.txt";
    binFile = "Data/Com_Tests/Test3_COM5_10m_paired";
    converter.Convert(txtFile,binFile);
  
    txtFile = "Data/Com_Tests/Test4_COM3_10m.txt";
    binFile = "Data/Com_Tests/Test4_COM3_10m";
    converter.Convert(txtFile,binFile);

    txtFile = "Data/Com_Tests/Test4_COM4_16.txt";
    binFile = "Data/Com_Tests/Test4_COM4_16";
    converter.Convert(txtFile,binFile);

    txtFile = "Data/Com_Tests/Test4_COM5_10.txt";
    binFile = "Data/Com_Tests/Test4_COM5_10";
    converter.Convert(txtFile,binFile);

    txtFile = "Data/Com_Tests/Test5_COM3.txt";
    binFile = "Data/Com_Tests/Test5_COM3";
    converter.Convert(txtFile,binFile);
  
    txtFile = "Data/Com_Tests/Test6_COM4.txt";
    binFile = "Data/Com_Tests/Test6_COM4";
    converter.Convert(txtFile,binFile);

    txtFile = "Data/Com_Tests/Test6_COM5.txt";
    binFile = "Data/Com_Tests/Test6_COM5";
    converter.Convert(txtFile,binFile);

  }

  // -- Demokritos Testing, November 2019
  
  if (!DontRepeat){

    txtFile = "Data/Com_Tests/Test7_COM3_10m.txt";
    binFile = "Data/Com_Tests/Test7_COM3_10m";
    converter.Convert(txtFile,binFile);
  
    txtFile = "Data/Com_Tests/Test7_COM4_10m_start.txt";
    binFile = "Data/Com_Tests/Test7_COM4_10m_start";
    converter.Convert(txtFile,binFile);

    txtFile = "Data/Com_Tests/Test7_COM4_10m_end.txt";
    binFile = "Data/Com_Tests/Test7_COM4_10m_end";
    converter.Convert(txtFile,binFile);
  
    txtFile = "Data/Com_Tests/Test7_COM4_10m_end2.txt";
    binFile = "Data/Com_Tests/Test7_COM4_10m_end2";
    converter.Convert(txtFile,binFile);

    txtFile = "Data/Com_Tests/Test7_COM5_10m.txt";
    binFile = "Data/Com_Tests/Test7_COM5_10m";
    converter.Convert(txtFile,binFile);
  
    txtFile = "Data/Com_Tests/Test8_COM3_20m.txt";
    binFile = "Data/Com_Tests/Test8_COM3_20m";
    converter.Convert(txtFile,binFile);
  
    txtFile = "Data/Com_Tests/Test8_COM4_16m.txt";
    binFile = "Data/Com_Tests/Test8_COM4_16m";
    converter.Convert(txtFile,binFile);
  
    txtFile = "Data/Com_Tests/Test8_COM5_10m.txt";
    binFile = "Data/Com_Tests/Test8_COM5_10m";
    converter.Convert(txtFile,binFile);
  
    txtFile = "Data/Com_Tests/Test9_COM3_10m.txt";
    binFile = "Data/Com_Tests/Test9_COM3_10m";
    converter.Convert(txtFile,binFile);
  
    txtFile = "Data/Com_Tests/Test9_COM4_10m.txt";
    binFile = "Data/Com_Tests/Test9_COM4_10m";
    converter.Convert(txtFile,binFile);
  
    txtFile = "Data/Com_Tests/Test9_COM5_10m.txt";
    binFile = "Data/Com_Tests/Test9_COM5_10m";
    converter.Convert(txtFile,binFile);
  
    txtFile = "Data/Com_Tests/Test10_COM3_10m.txt";
    binFile = "Data/Com_Tests/Test10_COM3_10m";
    converter.Convert(txtFile,binFile);
  
    txtFile = "Data/Com_Tests/Test10_COM4_10m.txt";
    binFile = "Data/Com_Tests/Test10_COM4_10m";
    converter.Convert(txtFile,binFile);
  
    txtFile = "Data/Com_Tests/Test11_COM3_10m.txt";
    binFile = "Data/Com_Tests/Test11_COM3_10m";
    converter.Convert(txtFile,binFile);
  
    txtFile = "Data/Com_Tests/Test11_COM4_10m.txt";
    binFile = "Data/Com_Tests/Test11_COM4_10m";
    converter.Convert(txtFile,binFile);
  
    txtFile = "Data/Com_Tests/Test11_COM5_10m.txt";
    binFile = "Data/Com_Tests/Test11_COM5_10m";
    converter.Convert(txtFile,binFile);

    txtFile = "Data/Com_Tests/Test12_COM3_10m.txt";
    binFile = "Data/Com_Tests/Test12_COM3_10m";
    converter.Convert(txtFile,binFile);
  
    txtFile = "Data/Com_Tests/Test12_COM4_10m.txt";
    binFile = "Data/Com_Tests/Test12_COM4_10m";
    converter.Convert(txtFile,binFile);
  
    txtFile = "Data/Com_Tests/Test12_COM5_10m.txt";
    binFile = "Data/Com_Tests/Test12_COM5_10m";
    converter.Convert(txtFile,binFile);

    txtFile = "Data/Com_Tests/Test12_COM3_15m.txt";
    binFile = "Data/Com_Tests/Test12_COM3_15m";
    converter.Convert(txtFile,binFile);
  
    txtFile = "Data/Com_Tests/Test12_COM4_15m.txt";
    binFile = "Data/Com_Tests/Test12_COM4_15m";
    converter.Convert(txtFile,binFile);
  
    txtFile = "Data/Com_Tests/Test12_COM5_15m.txt";
    binFile = "Data/Com_Tests/Test12_COM5_15m";
    converter.Convert(txtFile,binFile);

  }
    
  // Calibration Tests

  txtFile = "Data/Calibration_Tests/Com3_16_7_20.txt";
  binFile = "Data/Calibration_Tests/Com3_Calibration1";
  converter.Convert(txtFile,binFile);

  txtFile = "Data/Calibration_Tests/Com4_16_7_20.txt";
  binFile = "Data/Calibration_Tests/Com4_Calibration1";
  converter.Convert(txtFile,binFile);

  txtFile = "Data/Calibration_Tests/Com5_16_7_20.txt";
  binFile = "Data/Calibration_Tests/Com5_Calibration1";
  converter.Convert(txtFile,binFile);

  txtFile = "Data/Calibration_Tests/Com3_17_7_20.txt";
  binFile = "Data/Calibration_Tests/Com3_Calibration2";
  converter.Convert(txtFile,binFile);

  txtFile = "Data/Calibration_Tests/Com4_17_7_20.txt";
  binFile = "Data/Calibration_Tests/Com4_Calibration2";
  converter.Convert(txtFile,binFile);

  txtFile = "Data/Calibration_Tests/Com5_17_7_20.txt";
  binFile = "Data/Calibration_Tests/Com5_Calibration2";
  converter.Convert(txtFile,binFile);
  
    
  converter.Hex(false);  // Next files have decimal values

  // -- Nestor, May 2009
  
  if (!DontRepeat){
    
    txtFile = "Data/Revisit_2009/10mp11.tx1";
    binFile = "Data/Revisit_2009/Nestor_10m";
    converter.Convert_Old(txtFile,binFile);

    txtFile = "Data/Revisit_2009/15mp14.tx1";
    binFile = "Data/Revisit_2009/Nestor_15m";
    converter.Convert_Old(txtFile,binFile);

    txtFile = "Data/Revisit_2009/17mp13.tx1";
    binFile = "Data/Revisit_2009/Nestor_17m";
    converter.Convert_Old(txtFile,binFile);

    txtFile = "Data/Revisit_2009/23mp12.tx1";
    binFile = "Data/Revisit_2009/Nestor_23m";
    converter.Convert_Old(txtFile,binFile);
  
    txtFile = "Data/Revisit_2009/Nestor_10m_Cut.tx1";
    binFile = "Data/Revisit_2009/Nestor_10m_Cut";
    converter.Convert_Old(txtFile,binFile);

    txtFile = "Data/Revisit_2009/Nestor_15m_Cut.tx1";
    binFile = "Data/Revisit_2009/Nestor_15m_Cut";
    converter.Convert_Old(txtFile,binFile);

    txtFile = "Data/Revisit_2009/Nestor_17m_Cut.tx1";
    binFile = "Data/Revisit_2009/Nestor_17m_Cut";
    converter.Convert_Old(txtFile,binFile);

    txtFile = "Data/Revisit_2009/Nestor_23m_Cut.tx1";
    binFile = "Data/Revisit_2009/Nestor_23m_Cut";
    converter.Convert_Old(txtFile,binFile);

  }


  // -- Capo Passero 2, May 2009

  if (!DontRepeat){

    txtFile = "Data/Revisit_2009/10mp8.tx1";
    binFile = "Data/Revisit_2009/Capo2_10m";
    converter.Convert_Old(txtFile,binFile);

    txtFile = "Data/Revisit_2009/15mp9.tx1";
    binFile = "Data/Revisit_2009/Capo2_15m";
    converter.Convert_Old(txtFile,binFile);

    txtFile = "Data/Revisit_2009/17mp10.tx1";
    binFile = "Data/Revisit_2009/Capo2_17m";
    converter.Convert_Old(txtFile,binFile);

    txtFile = "Data/Revisit_2009/22mp7.tx1";
    binFile = "Data/Revisit_2009/Capo2_22m";
    converter.Convert_Old(txtFile,binFile);

  }

  // Same as above, but cut

  if (!DontRepeat){
  
    txtFile = "Data/Revisit_2009/Capo2_10.tx1";
    binFile = "Data/Revisit_2009/Capo2_10m_Cut";
    converter.Convert_Old(txtFile,binFile);

    txtFile = "Data/Revisit_2009/Capo2_15.tx1";
    binFile = "Data/Revisit_2009/Capo2_15m_Cut";
    converter.Convert_Old(txtFile,binFile);

    txtFile = "Data/Revisit_2009/Capo2_17.tx1";
    binFile = "Data/Revisit_2009/Capo2_17m_Cut";
    converter.Convert_Old(txtFile,binFile);
  
    txtFile = "Data/Revisit_2009/Capo2_22.tx1";
    binFile = "Data/Revisit_2009/Capo2_22m_Cut";
    converter.Convert_Old(txtFile,binFile);

  }

  // There is no difference between Capo2, Capo. Same files for different analysis
  
  if (!DontRepeat){

    txtFile = "Data/Revisit_2009/Capo_10m_Cut.txt";
    binFile = "Data/Revisit_2009/Capo_10m_Cut";
    converter.Convert_Old(txtFile,binFile);

    txtFile = "Data/Revisit_2009/Capo_15m_Cut.txt";
    binFile = "Data/Revisit_2009/Capo_15m_Cut";
    converter.Convert_Old(txtFile,binFile);

    txtFile = "Data/Revisit_2009/Capo_17m_Cut.txt";
    binFile = "Data/Revisit_2009/Capo_17m_Cut";
    converter.Convert_Old(txtFile,binFile);

    txtFile = "Data/Revisit_2009/Capo_22m_Cut.txt";
    binFile = "Data/Revisit_2009/Capo_22m_Cut";
    converter.Convert_Old(txtFile,binFile);

  }

  return 0;
}
