//
// Created by Кочнев Андрей Владимирович on 16/09/2017.
//

#include "header.h"
#include <cmath>

local_matrix_type local_beta_matrix(double h_length) {
    // инициализация
    local_matrix_type result;
    std::vector<double> tmp(local_matrix_size, 0);
    for (int i = 0; i < local_matrix_size; ++i) {
        result.push_back(tmp);
    }

    result[0][0] = (beta * 60/pow(h_length,3));
    result[0][1] = (beta * 30/pow(h_length,2));
    result[0][2] = (beta * (-60)/pow(h_length,3));
    result[0][3] = (beta * 30/pow(h_length,2));
    result[1][0] = (beta * 30/pow(h_length,2));
    result[1][1] = (beta * 16/h_length);
    result[1][2] = (beta * (-30)/pow(h_length,2));
    result[1][3] = (beta * 14/h_length);
    result[2][0] = (beta * (-60)/pow(h_length,3));
    result[2][1] = (beta * (-30)/pow(h_length,2));
    result[2][2] = (beta * 60/pow(h_length,3));
    result[2][3] = (beta * (-30)/pow(h_length,2));
    result[3][0] = (beta * 30/pow(h_length,2));
    result[3][1] = (beta * 14/h_length);
    result[3][2] = (beta * (-30)/pow(h_length,2));
    result[3][3] = (beta * 16/h_length);

    return  result;
}

// локальная матрица для КЭ
local_matrix_type local_a_matrix(
        double h_length,
        std::vector<dot_type> points,
        std::vector<dot_type> weights
) {
    // инициализация, заполним сразу нулями, так проще будет
    local_matrix_type result;
    std::vector<double> tmp(local_matrix_size, 0);
    for (int i = 0; i < local_matrix_size; ++i) {
        result.push_back(tmp);
    }

    for (short i = 0; i < local_matrix_size; ++i) {
        for (short j = 0; j < local_matrix_size; ++j) {
            for (int k = 0; k < points.size(); ++k) {

                double psi_i = psi(i, h_length, points[0], points[k]);
                double psi_j = psi(j, h_length, points[0], points[k]);

                double a_ij_for_k = weights[k] * psi_i * psi_j;
                result[i][j] += a_ij_for_k;

            }
        }
    }

    return  result;
}

// сумма локальный матриц
local_matrix_type sum_local_matrix(local_matrix_type a, local_matrix_type b) {
    local_matrix_type result;
    std::vector<double> tmp_vector;
    // выделяем память
    for (int i = 0; i < local_matrix_size; ++i) {
        result.push_back(tmp_vector);
    }

    for (int i = 0; i < local_matrix_size; ++i) {
        for (int j = 0; j < local_matrix_size; ++j) {
            result[i].push_back(a[i][j] + b[i][j]);
        }
    }

    return result;
}