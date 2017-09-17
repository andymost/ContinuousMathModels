//
// Created by Кочнев Андрей Владимирович on 24/09/2017.
//
#include "header.h"
using namespace std;

double vector_mult_vector(vector<double> a, vector<double> b) {
    double result = 0;
    for (int i = 0; i < a.size(); ++i) {
        result += a[i]*b[i];
    }

    return result;
}

global_matrix_type matrix_multSQ_matrix(global_matrix_type a, global_matrix_type b) {
    global_matrix_type result;
    int size = a.size();
    vector<double> tmp(size, 0);
    for (int k = 0; k < size; ++k) {
        result.push_back(tmp);
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            vector<double> b_row;
            for (int k = 0; k < size; ++k) {
                b_row.push_back(b[k][j]);
            }
            result[i][j] = vector_mult_vector(a[i], b_row);
        }
    }

    return result;
}