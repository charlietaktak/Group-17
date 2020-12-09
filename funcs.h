#ifndef FUNCS_H
#define FUNCS_H

#include <iostream>
#include <complex>
#include <string>
#include <vector>

#define PI 3.14159265358979323846

std::complex<double> impedance_for_resistance(double res, double freq);

std::complex<double> impedance_for_inductance(double ind, double freq);

std::complex<double> impedance_for_capacitance(double cap, double freq);

std::complex<double> impedance_for_resistance_inductance(double res, double ind, double freq);

std::complex<double> impedance_for_resistance_capacitance(double res, double cap, double freq);

std::complex<double> impedance_for_inductance_capacitance(double ind, double cap, double freq);

std::complex<double> impedance_for_RLC_circuit(double res, double cap, double ind, double freq);

double getRes();

bool isMin();

double compVal(double res);

float closest(std::vector<float> npv, float val, bool min);

float calcRes(float val, float res);

#endif