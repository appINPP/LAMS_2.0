#ifndef LamsMath_hh
#define LamsMath_hh

#include <cmath>


double beta(double &Is, double &Il, double &Rs, double &Rl){
  return (log(Il / Is) + 2 * log(Rl / Rs)) / (Rs - Rl);
}

//double beta_err(double Is, souble Il, double Rs, double Rl, double Is_err, double Il_err, double Rs_err, double Rl_err){
//  double term1 = 0, term2 = 0, term3 = 0, term4 = 0;


#endif
