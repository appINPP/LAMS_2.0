#ifndef Tools_hh
#define Tools_hh

#include <string>
#include <vector>
#include <sstream>
#include <ctime>
#include <cstring>

#include "TH1.h"
#include "TH2.h"

/* - - - - - - - - - - - Contents - - - - - - - - - - -

   Overloaded NumToString function to accomodate various
   parameter types and sizes. You can add your own types
   by copying the function and changing the input
   parameter. 

   Stopwatch class which is used to measure the time
   passed between 2 points in the code. There are 3
   functions in it: Start(int), Stop(int) and Show(int).
   Within a single Stopwatch object you can label 
   different watches, with the <int> parameter input.
*/

std::string NumToString(int number){
  std::ostringstream convert;
  convert << number;
  return convert.str();
}

std::string NumToString(unsigned int number){
  std::ostringstream convert;
  convert << number;
  return convert.str();
}

std::string NumToString(unsigned long int number){
  std::ostringstream convert;
  convert << number;
  return convert.str();
}

std::string NumToString(float number){
  std::ostringstream convert;
  convert << number;
  return convert.str();
}

std::string NumToString(double number){
  std::ostringstream convert;
  convert << number;
  return convert.str();
}

TH1F *MakeHist(std::string ref_name, std::string hist_title, unsigned bin, float bottom_range, float top_range){
  char* temp1 = new char[ref_name.size()+1];
  std::copy(ref_name.begin(),ref_name.end(),temp1);
  temp1[ref_name.size()] = '\0';
  char* temp2 = new char[hist_title.size()+1];
  std::copy(hist_title.begin(),hist_title.end(),temp2);
  temp2[hist_title.size()] = '\0';
  TH1F *hist = new TH1F(temp1,temp2,bin,bottom_range,top_range);
  delete temp1;
  delete temp2;
  return hist;
}


class Stopwatch{
private:
  std::vector <std::clock_t> starting_time;
  std::vector <std::clock_t> stopping_time;
  std::vector <int> index;
  std::string message;
  unsigned long int time;
  unsigned long int temp;
  
public:
  Stopwatch(){}
  ~Stopwatch(){}
  
  void Start(int number_of_watch){
    for (unsigned long long i = 0; i < index.size(); i++){
      if (number_of_watch == index[i]){
	starting_time[i] = clock();
	return;
      }
    }
    index.push_back(number_of_watch);
    starting_time.push_back(clock());
    stopping_time.push_back(clock());
    return;
  }

  void Stop(int number_of_watch){
    for (unsigned long long int i = 0; i < index.size(); i++){
      if (number_of_watch == index[i]){
	stopping_time[i] = clock();
	return;
      }
    }
    return; // This will happen if Start function was not used before a Stop function.
  }
  
  std::string Show(int number_of_watch){
    for (unsigned long long int i = 0; i < index.size(); i++){
      if (number_of_watch == index[i]){
	time = static_cast <unsigned long int> (nearbyint((stopping_time[i] - starting_time[i]) * 1000.0 / static_cast<double>(CLOCKS_PER_SEC)));
	temp = time / 60000;
	message = static_cast <std::string> (NumToString(temp) + " minutes, ");
	temp = time/1000 - (time/60000)*60;
	message += static_cast <std::string> (NumToString(temp) + " seconds, ");
	temp = time-(time/1000)*1000;
	message += static_cast <std::string> (NumToString(temp) + " milliseconds. \n");
	return message;
      }
    }
    message = "There is no watch";
    return message;
  }
};



#endif
