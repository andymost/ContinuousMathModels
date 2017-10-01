//
// Created by Кочнев Андрей Владимирович on 25/09/2017.
//
#include "header.h"
#include <cmath>
#include <iostream>
using namespace std;


// подстановочное кси
double ksi(double h_lenght, dot_type x_left, dot_type x) {
    return (x - x_left)/h_lenght;
}

// базинсная эрмитова функция локальная 1
double psi_1(double h_length, dot_type x_left, dot_type x) {
    return 1 - 3 * pow(ksi(h_length, x_left, x),2)  + 2 * pow(ksi(h_length, x_left, x),3);
}

// базинсная эрмитова функция локальная 2 с учетом множителя
double psi_2(double h_length, dot_type x_left, dot_type x) {
    return h_length * (
            ksi(h_length, x_left, x) - 2 * pow(ksi(h_length, x_left, x),2) + pow(ksi(h_length, x_left, x),3)
    );
}

// базинсная эрмитова функция локальная 3
double psi_3(double h_length, dot_type x_left, dot_type x) {
    return 3 * pow(ksi(h_length, x_left, x),2)  - 2 * pow(ksi(h_length, x_left, x),3);
}

// базинсная эрмитова функция локальная 4 с учетом множителя
double psi_4(double h_length, dot_type x_left, dot_type x) {
    return h_length * ( -pow(ksi(h_length, x_left, x),2) + pow(ksi(h_length, x_left, x),3));
}


// базисная эрмитова локальная функция с индексом
double  psi(short index, double h_length, dot_type x_left, dot_type x) {
    switch (index) {
        case 0: return psi_1(h_length, x_left, x);
        case 1: return psi_2(h_length, x_left, x);
        case 2: return psi_3(h_length, x_left, x);
        default: return psi_4(h_length, x_left, x);
    }
}