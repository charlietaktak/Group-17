#include <iostream>
#include <regex>
#include <complex>
#include "funcs.h"
#include <cmath>
#include <fstream>

void main_menu();
int get_user_input();
void select_menu_item(int input);
void print_main_menu();
void go_back_to_main_menu();
bool is_integer(std::string num);
void menu_item_1();
void menu_item_2();
void menu_item_3();
std::string yorn;
std::string yns;
float t;
float r;
float c;
float bp;
float ts;
float rt; 

//https://elec2645.github.io/103/menus.html

int main(int argc, char const *argv[]) {
  main_menu();
  return 0;
}

void main_menu() {
  print_main_menu();
  int input = get_user_input();
  select_menu_item(input);
}

int get_user_input() {
  int input;
  std::string input_string;
  bool valid_input = false;
  int menu_items = 6;

  do {
    std::cout << "\nSelect item: ";
    std::cin >> input_string;
    valid_input = is_integer(input_string);
    // if input is not an integer, print an error message
    if (valid_input == false) {
      std::cout << "Enter an integer!\n";
    } else {  // if it is an int, check whether in range
      input = std::stoi(input_string);  // convert to int
      if (input >= 1 && input <= menu_items) {
        valid_input = true;
      } else {
        std::cout << "Invalid menu item!\n";
        valid_input = false;
      }
    }
  } while (valid_input == false);

  return input;
}

void select_menu_item(int input) {
  switch (input) {
    case 1:
      menu_item_1();
      break;
    case 2:
      menu_item_2();
      break;
    case 3:
      menu_item_3();
      break;
    default:
      exit(1);
      break;
  }
}

void print_main_menu() {
  std::cout << "\n----------- Main menu -----------\n";
  std::cout << "|\t\t\t\t\t\t\t\t|\n";
  std::cout << "|\t1. Impedance\t\t\t\t|\n";
  std::cout << "|\t2. I2C\t\t\t\t\t\t|\n";
  std::cout << "|\t3. Resistor NPV Calculator\t|\n";
  std::cout << "|\t4. Exit\t\t\t\t\t\t|\n";
  std::cout << "|\t\t\t\t\t\t\t\t|\n";
  std::cout << "---------------------------------\n";
}

void go_back_to_main() {
  std::string input;
  do {
    std::cout << "\nEnter 'b' or 'B' to go back to main menu: ";
    std::cin >> input;
  } while (input != "b" && input != "B");
  main_menu();
}

bool is_integer(std::string num) {
  return std::regex_match(num, std::regex("[+-]?[0-9]+"));
}

void menu_item_1() {
  std::cout << "\n>> Impedance Calculator\n";
  std::cout << "\nEnter Value for Resistance(ohms):\n";
  //taking in values
  double res;
  std::cin >> res;
  std::cout << "\nEnter Value for Inductance(H):\n";
  double ind;
  std::cin >> ind;
  std::cout << "\nEnter Value for Capacitance(F):\n";
  double cap;
  std::cin >> cap;
  std::cout << "\nEnter Value for Frequency(Hz):\n";
  double freq;
  std::cin >> freq;
  if(res != 0 and ind == 0 and cap == 0){

    std::complex<double> res_imp = impedance_for_resistance(res,freq);
    std::cout << "The impedance of the circuit with only resistance is " << res_imp.real() << " + j" << res_imp.imag() << " ohms" << std::endl;
    std::cout << "The magnitude of the impedance of the circuit with only resistance is " << res_imp.real() << " ohms" << std::endl;
  }
  else if(res == 0 and ind != 0 and cap == 0){

    std::complex<double> ind_imp = impedance_for_inductance(ind,freq);
    std::cout << "The impedance of the circuit with only inductance is " << ind_imp.real() << " + j" <<ind_imp.imag() << " ohms" << std::endl;
    std::cout << "The magnitude of the impedance of the circuit with only inductance is " << ind_imp.imag() << " ohms" << std::endl;
  }

  else if(res == 0 and ind == 0 and cap != 0 and freq != 0){
    //resistance and inductance = 0, frequency must not = 0
     std::complex<double> cap_imp = impedance_for_capacitance(cap,freq);
    std::cout << "The impedance of the circuit with only capacitance is " << cap_imp.real() << " + j" << cap_imp.imag() << " ohms" << std::endl;
    std::cout << "The magnitude of the impedance of the circuit with only capacitance is " << -cap_imp.imag() << " ohms" << std::endl;
  }

  else if(res != 0 and ind != 0 and cap == 0){
    //capacitance = 0, so frequency can = 0 (does not cause errors when calculated)
    std::complex<double> res_ind_imp = impedance_for_resistance_inductance(res,ind,freq);
    std::cout << "The impedance of the circuit with resistance and inductance is " << res_ind_imp.real() << " + j" << res_ind_imp.imag() << " ohms" << std::endl;
    std::cout << "The magnitude of the impedance of the circuit with resistance and inductance is " << std::abs(res_ind_imp) << " ohms" << std::endl;
  }
  else if(res != 0 and ind == 0 and cap != 0 and freq != 0){
    //impedance withour inductance, frequency not = 0
     std::complex<double> res_cap_imp = impedance_for_resistance_capacitance(res,cap,freq);
    std::cout << "The impedance of the circuit with resistance and capacitance is " << res_cap_imp.real() << " + j" << res_cap_imp.imag() << " ohms" << std::endl;
    //magnitude caluculation
    std::cout << "The magnitude of the impedance of the circuit with resistance and capacitance is " << std::abs(res_cap_imp) << " ohms" << std::endl;
  }
  else if(res ==0 and ind != 0 and cap != 0 and freq != 0){
    //inductance and capactiance, freq not = 0
    std::complex<double> imp_ind_cap = impedance_for_inductance_capacitance(ind,cap,freq);
    std::cout << "The impedance of a circuit with inductance and capacitance is " << imp_ind_cap.real() << " + j" << imp_ind_cap.imag() << " ohms" << std::endl;
    //magnitude caluculation
    std::cout << "The magnitude of the impedance of the circuit with inductance and capacitance is " << std::abs(imp_ind_cap) << " ohms" << std::endl;
  }
  else if(res != 0 and ind != 0 and cap != 0 and freq != 0){
    //all 3 components, frequency not = 0
    std::complex<double> imp = impedance_for_RLC_circuit(res, cap, ind,freq);
    std::cout << "The impedance of a circuit with resistance, inductance and capacitance is " << imp.real() << " + j" << imp.imag() << " ohms" << std::endl;
    //magnitude caluculation
    std::cout << "The magnitude of the impedance of the circuit with resistance, inductance and capacitance is " << std::abs(imp) << " ohms" << std::endl;
  }
  else{
    //when frequency = 0, imp = res
    std::cout << "If all 3 components are equal to 0, there is no imaginary part to the impedance as there is no way to calculate 1/0. If your frequency is equal to 0, then the impedance of your circuit is " << res << " ohms" << std::endl;
  }
  go_back_to_main();
}
void menu_item_2() {
  std::cout << "\n-----I2C Calculator------\n";
  std::cout << "|\t\t\t\t\t\t|\n";
  std::cout << "|\t1. Capacitance\t\t|\n";
  std::cout << "|\t2. Pull-up resistor\t|\n";
  std::cout << "|\t3. Rise time\t\t|\n";
  std::cout << "|\t4. Bit period\t\t|\n";
  std::cout << "|\t5. Transfer speed\t|\n";
  std::cout << "|\t6. Exit\t\t\t\t|\n";
  std::cout << "|\t\t\t\t\t\t|\n";
  std::cout << "-------------------------\n";

  int input = get_user_input();
  ////////////////////////////////////////////////////
  if(input == 1) {
    std::cout << "\n>> Capacitance calculator\n";
    std::cout << "Do you know the maximum rise time? (y/n): ";
    std::cin >> yorn;

    if (yorn == "y") {
      std::cout << "Enter the rise time (µs): ";
      std::cin >> t;
      std::cout << "Enter the pull-up resistor value: ";
      std::cin >> r;
      std::cout << "Capacitance = " << t/(1.2*r) << "F.\n";
    }
    else if(yorn == "n") {
      std::cout << "\nUse I2C function 3 to calculate rise time!";
    }
    else {
      std::cout << "Enter y or n\n";
      menu_item_2();
    }
  }
  /////////////////////////////////////////////////////
    else if(input == 2) {
      std::cout << "\n>> Pull-up Resistor Calculator\n";
      std::cout << "Do you know the maximum rise time? (y/n): ";
      std::cin >> yorn;

      if(yorn == "y") {
        std::cout << "Enter the rise time (µs): ";
        std::cin >> t;
        std::cout << "Enter the capacitance: ";
        std::cin >> c;
        std::cout << "Resistance = " << t/(1.2*c) << "ohms.\n";
      }
      else if(yorn == "n") {
        std::cout << "\nUse I2C function 3 to calculate rise time!";
      }
      else {
        std::cout << "Enter y or n\n";
        menu_item_2();
      }
    }
  ////////////////////////////////////////////////////////////
    else if(input == 3) {
      std::cout << "\n>> Rise Time Calculator\n";
      std::cout << "Do you know the bit period? (y/n): ";
      std::cin >> yorn;

      if(yorn == "y") {
        std::cout << "Enter the bit period (µs): ";
        std::cin >> bp;
        std::cout << "Rise time < " << 0.1*bp << "µs\n";
      }
      else if(yorn == "n") {
        std::cout << "Do you know the transfer speed? (y/n): ";
        std::cin >> yns;
        if(yns == "y") {
          std::cout << "Enter the transfer speed (kbit/s): ";
          std::cin >> ts;
          std::cout << "Rise time < " << 0.1*(1/ts) << "µs\n";
        }
      if(yns == "n") {
        std::cout << "Enter the capacitance (F): ";
        std::cin >> c;
        std::cout << "Enter the pull-up resistor value (ohms): ";
        std::cin >> r;
        std::cout << "Rise time = " << 1.2*c*r << "µs\n";
      }
      else {
        std::cout << "Please enter y or n\n";
        menu_item_2();
      }
    }
    else {
      std::cout << "Please enter y or n\n";
      menu_item_2();
    }
  }
  /////////////////////////////////////////////////////////
    else if(input == 4) {
      std::cout << "\n>> Bit Period calculator\n";
      std::cout << "Do you know the transfer speed? (y/n): ";
      std::cin >> yorn;

      if(yorn == "y") {
        std::cout << "Enter the transfer speed (kbit/s): ";
        std::cin >> ts;
        std::cout << "Bit period = " << 1/ts << "µs\n";
      }
      else if(yorn == "n") {
        std::cout << "Enter the rise time (µs): ";
        std::cin >> rt;
        std::cout << "Bit period = " << rt/0.1 << "µs\n";
      }
      else {
        std::cout << "Enter y or n\n";
        menu_item_2();
      }
    }
  /////////////////////////////////////////////////////////////
    else if(input == 5) {
      std::cout << "\n>> Transfer Speed Calculator\n";
      std::cout << "Do you know the bit period? (y/n): ";
      std::cin >> yorn;

      if(yorn == "y") {
        std::cout << "Enter the bit period (µs): ";
        std::cin >> bp;
        std::cout << "Transfer speed = " << 1/bp << "kbit/s.\n";
      }
      else if(yorn == "n") {
        std::cout << "Use I2C function 4 to calculate bit period!\n";
      }
      else {
        std::cout << "Enter y or n\n";
        menu_item_2();
      }

    }
  //////////////////////////////////////////////////////////////
    else if(input == 6) {
      go_back_to_main();
    }
  /////////////////////////////////////////////////////////////
    else {
      std::cout << "Invalid menu item!";
      menu_item_2();
    }

  go_back_to_main();
}
void menu_item_3() {
  const std::string tolerances[6] = {"0.5%", "1%", "2%", "5%", "10%", "20%"};
  const std::string series[6] = {"192", "96", "48", "24", "12", "6"};
  double tolerance;

  std::cout << "*********NPV Calculator*********\n";
  double R = getRes(); //get resistance
  double RC = compVal(R); //gets value to compare against available resistors

  //Display available tolerance levels
  std::cout << "Available tolerance levels: " << std::endl;
  for (int i = 0; i < std::size(tolerances); i++) {
    if (i == (std::size(tolerances)-1)) {
      std::cout << tolerances[i] << "\n";
    }
    else {
      std::cout << tolerances[i] << ", ";
    }
  }

  //Asking user for their desired level of tolerance
  std::cout << "Please enter your tolerance: ";
  bool valid = false;
  int E;
  std::string input;

  while (valid == false) {
    std::cin >> input;
    for (int i = 0; i < std::size(tolerances); i++) {
      if (input == tolerances[i]) {
        //std::cout << tolerances[i];
        valid = true;
        E = i;
      }
    }
    if (valid == false) {
      std::cout << "Please enter a specified value: ";
    }
  }
  
  std::cout << "Selecting from E" << series[E] << std::endl;
  
  bool min = isMin(); //Asking if the resistance is a required minimum
  if (min == true) {
    std::cout << "Selecting next highest resistor\n";
  }

  std::ifstream file; //open npv.csv
  file.open("npv.csv");

  std::vector<float> vals;

  while(file.good()) {
    std::string line;
    std::getline(file,line,',');
    if (line == series[E]) {
      for(int i=0; i < std::stoi(series[E]); i++ ){
        std::getline(file,line, ',');
        vals.push_back(std::stof(line));
      }
    }
  }
  file.close(); //close npv.csv

  float v = closest(vals, RC, min);
  std::cout << "\nYour resistor to use is: " << calcRes(v, R) << "ohms";

  go_back_to_main();
}