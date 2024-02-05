#ifndef TextToBinary_hh
#define TextToBinary_hh

#include <iostream>
#include <fstream>
#include <string>

/*
  The purpose of this class is to convert the .txt data files to binary files.
  This is beneficial for the reason that binary files are an unformated way of
  storing data compared .txt files and alas more stable. Also it's less complex
  to convert to binary and handle that type of file, instead of handling .txt
  which could lead to errors (whitespaces, newlines) while the code is running.
*/

class TextToBinary{
private:
  std::ifstream txtFile;
  std::ofstream binFile;
  unsigned short intensity1, intensity2;
  unsigned short temperature, pressure;
  unsigned long long counter;
  double time;

  bool disableHex; // Some files will not be in hexadecimal
  bool inputFlag; // True if the .txt was not opened.
  bool outputFlag; // True if the binary was not opened.
  
  unsigned long long number_of_lines; // Keeps count of lines when using "Convert" function.
  
public:
  TextToBinary(){
    disableHex = false;
    inputFlag = false;
    outputFlag = false;
  }
  ~TextToBinary(){}

  
  void Convert(std::string input_file, std::string output_file){ // Standard way for the experiment conversions
    Reset();
    txtFile.open(input_file.c_str(), std::ios::in);
    binFile.open(output_file.c_str(), std::ios::out | std::ios::binary);

    if (txtFile.is_open()){
      inputFlag = false;
      if (binFile.is_open()){
	outputFlag = false;
	do{ // This loop reads every line of the .txt and saves it in the binary file.
	  if (!disableHex) {
	    txtFile >> std::hex >> intensity1;
	    txtFile >> std::hex >> intensity2;
	    txtFile >> std::hex >> temperature;
	    txtFile >> std::hex >> pressure;
	  }
	  else {
	    txtFile >> std::dec >> intensity1;
	    txtFile >> std::dec >> intensity2;
	    txtFile >> std::dec >> temperature;
	    txtFile >> std::dec >> pressure;
	  }
	  if (txtFile.fail()){
	    if (txtFile.eof()){
	      break;
	    }
	    else{
	      continue;
	    }
	  }
	  number_of_lines++;
	  binFile.write(reinterpret_cast <char*> (&intensity1),2);
	  binFile.write(reinterpret_cast <char*> (&intensity2),2);
	  binFile.write(reinterpret_cast <char*> (&temperature),2);
	  binFile.write(reinterpret_cast <char*> (&pressure),2);
	}while (static_cast <long long int> (txtFile.tellg()) != -1);
      }
      else{ // Binary file did not open.
	outputFlag = true;
      }
    }
    else if(binFile.is_open()){ // .txt file did not open.
      inputFlag = true;
    }
    else{ // Both files did not open.
      inputFlag = true;
      outputFlag = true;
    }
    txtFile.close();
    binFile.close();
    return;
  }

  void Convert_Test(std::string input_file, std::string output_file){ // Spyros Tests
    Reset();
    txtFile.open(input_file.c_str(), std::ios::in);
    binFile.open(output_file.c_str(), std::ios::out | std::ios::binary);

    if (txtFile.is_open()){
      inputFlag = false;
      if (binFile.is_open()){
	outputFlag = false;
	do{
	  txtFile >> std::hex >> intensity1;
	  txtFile >> std::hex >> intensity2;
	  txtFile >> std::hex >> temperature;
	  txtFile >> std::dec >> time;
	  if (txtFile.fail()){
	    if (txtFile.eof()){
	      break;
	    }
	    else{
	      continue;
	    }
	  }
	  number_of_lines += 4;
	  binFile.write(reinterpret_cast <char*> (&intensity1),2);
	  binFile.write(reinterpret_cast <char*> (&intensity2),2);
	  binFile.write(reinterpret_cast <char*> (&temperature),2);
	  binFile.write(reinterpret_cast <char*> (&time),8);
	}while (static_cast <long long int> (txtFile.tellg()) != -1);
      }
      else{ // Binary file did not open.
	outputFlag = true;
      }
    }
    else if(binFile.is_open()){ // .txt file did not open.
      inputFlag = true;
    }
    else{ // Both files did not open.
      inputFlag = true;
      outputFlag = true;
    }
    txtFile.close();
    binFile.close();
    return;
  }



  void Convert_Old(std::string input_file, std::string output_file){
    Reset();
    txtFile.open(input_file.c_str(), std::ios::in);
    binFile.open(output_file.c_str(), std::ios::out | std::ios::binary);

    if (txtFile.is_open()){
      inputFlag = false;
      if (binFile.is_open()){
	outputFlag = false;
	do{
	  txtFile >> std::dec >> counter;
	  txtFile >> std::dec >> intensity1;
	  txtFile >> std::dec >> intensity2;
	  if (txtFile.fail()){
	    if (txtFile.eof()){
	      break;
	    }
	    else{
	      continue;
	    }
	  }
	  number_of_lines += 4;
	  binFile.write(reinterpret_cast <char*> (&counter),8);
	  binFile.write(reinterpret_cast <char*> (&intensity1),2);
	  binFile.write(reinterpret_cast <char*> (&intensity2),2);
	}while (static_cast <long long int> (txtFile.tellg()) != -1);
      }
      else{ // Binary file did not open.
	outputFlag = true;
      }
    }
    else if(binFile.is_open()){ // .txt file did not open.
      inputFlag = true;
    }
    else{ // Both files did not open.
      inputFlag = true;
      outputFlag = true;
    }
    txtFile.close();
    binFile.close();
    return;
  }
  


  void Hex(bool const input){
    if (input) {
      disableHex = false;
      return;
    }
    else {
      disableHex = true;
      return;
    }
  }
  
  
  void Reset(){
    if (txtFile.is_open()) txtFile.close();
    if (binFile.is_open()) binFile.close();
    inputFlag = false;
    outputFlag = false;
    number_of_lines = 0;
    return;
  }

  
  unsigned long long int GetLines(){
    return number_of_lines;
  }
  bool InputErr(){
    return inputFlag;
  }
  bool OutputErr(){
    return outputFlag;
  }
};


#endif
