#include "funcs.h"

std::complex<double> impedance_for_resistance(double res, double freq) {
  //circuit with resistance only
  //Z=R
  std::complex<double> res_imp( res, 0.0);
  return res_imp;
}

std::complex<double> impedance_for_inductance(double ind, double freq) {
  double w = 2.0*PI*freq;
  //circuit with inductance only
  //Z=jwl, z=imp_ind
  std::complex<double> imp_ind(0.0, w*ind);
  return imp_ind;
}

std::complex<double> impedance_for_capacitance(double cap, double freq) {
  double w = 2.0*PI*freq;
  //circuit with capacitance only 
  //Z=-j/wc 
  std::complex<double> imp_cap(0.0, -1.0/(w*cap));
  return imp_cap;
}

std::complex<double> impedance_for_resistance_inductance(double res,double ind, double freq){
  double w = 2.0*PI*freq;
  //circuit with inductance and resistance
  std::complex<double> imp_res_ind(res, (w*ind));
  return imp_res_ind;
}

std::complex<double> impedance_for_resistance_capacitance(double res,double cap, double freq){
  double w = 2.0*PI*freq;
  //circuit with capacitance and resistance
  std::complex<double> imp_res_cap(res, -1.0/(w*cap));
  return imp_res_cap;
}

std::complex<double> impedance_for_inductance_capacitance(double ind, double cap, double freq){
  double w = 2.0*PI*freq;
  //circuit with capacitance and inductance
  std::complex<double> imp_ind_cap(0.0, (-1.0/(w*cap)+(w*ind)));
  return imp_ind_cap;
}

std::complex<double> impedance_for_RLC_circuit(double res, double cap, double ind, double freq) {
  double w = 2.0*PI*freq;
  std::complex<double> Zc( 0.0, -1.0 / (((w) * cap )));
  std::complex<double> Zr(res, 0.0);
  std::complex<double> Zl(0.0, w * ind);
  std::complex<double> Zt(0.0,0.0);
  Zt = Zc + Zr + Zl;
  return Zt;
}

double getRes(){
  double num;
  std::cout << "Please enter your resistance (ohms): ";
  while (!(std::cin >> num) || !(num > 0) ) {
    std::cout << "Please enter a valid resistance (ohms): ";
    std::cin.clear(); //"ignores" error flag
    std::cin.ignore(100, '\n'); //first number is amount of input stream to ignore
  }
  //std::cout << "Your number is " << num << std::endl;
  return num;
}

bool isMin() {
  char response = ' ';
  std::cout << "Is the resistance a required minimum?\n";
  do {
    std::cin.clear();
    std::cin.ignore(100, '\n');
    std::cout << "[y/n] >";
    std::cin >> response;
  }
  while (!std::cin.fail() && std::tolower(response) !='y' && std::tolower(response) !='n');

  if (response == 'y') {
    return true;
  }
  else {
    return false;
  }
}

//Obtains value to be compared against available resistor values
double compVal(double res) {
  int pwr = floor(log10(res));
  float comp = (res / pow(10, pwr));

  return comp;
}

float closest(std::vector<float> npv, float val, bool min) {
  float diff = 0;
  float diff2 = 0;
  for (int i = 0; i < npv.size() - 1; i++) {
    diff = npv[i] - val;
    diff2 = npv[i+1] - val;
    if (diff <= 0 && diff2 > 0) {
      if (min == true) {
        return npv[i+1];
      }
      else if (std::abs(diff) > std::abs(diff2)) {
        return npv[i+1];
      }
      else if (std::abs(diff) < std::abs(diff2)) {
        return npv[i];
      }
      else {
        return npv[i+1];
      }
    }
  }
  std::cout << "An unexpected error occurred\n";
  std::cout << "Exiting...";
  return 0;
}

float calcRes(float val, float res) {
  int pwr = floor(log10(res));
  float resistor = val * pow(10, pwr);
  return resistor;
}