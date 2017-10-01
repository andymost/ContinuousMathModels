//
// Created by Кочнев Андрей Владимирович on 01/10/2017.
//
#include "header.h"

using namespace std;

double spline(double x, grid_type grid, vector<double> q) {
    short omega_number;
    bool finded = false;
    double result = 0;

    // определяем КЭ
    for(short i = 0; i < grid.points.size() && !finded; i++){
        // ожидаем что элементы в сетке упорядочены
        double start = i == 0 ?
            grid.points[0][0] : grid.points[i - 1][grid.points[i - 1].size() - 1];
        double end = grid.points[i][grid.points[i].size() - 1];
        if(x > start && x < end){
            finded = true;
            omega_number = i;
        }
    }

    double x_left = omega_number == 0 ?
                    grid.points[omega_number][0] :
                    grid.points[omega_number - 1][grid.points[omega_number - 1].size() - 1];

    double h = grid.points[omega_number][grid.points[omega_number].size() - 1] - x_left;
    for (short j = 0; j < local_matrix_size; ++j) {
        double value = psi(j, h, x_left, x) ;
        result += value * q[j + omega_number * 2];
    }

    return result;
}

double spline_derivatice(double x, grid_type grid, vector<double> q) {
    short omega_number;
    bool finded = false;
    double result = 0;

    // определяем КЭ
    for(short i = 0; i < grid.points.size() && !finded; i++){
        // ожидаем что элементы в сетке упорядочены
        double start = i == 0 ?
                       grid.points[0][0] : grid.points[i - 1][grid.points[i - 1].size() - 1];
        double end = grid.points[i][grid.points[i].size() - 1];
        if(x + epsilon > start && x - epsilon < end){
            finded = true;
            omega_number = i;
        }
    }

    double x_left = omega_number == 0 ?
                    grid.points[omega_number][0] :
                    grid.points[omega_number - 1][grid.points[omega_number - 1].size() - 1];

    double h = grid.h_length[omega_number];
    for (short j = 0; j < local_matrix_size; ++j) {
        double value = psi_derevative(j, h, x_left, x) ;
        result += value * q[j + omega_number * 2];
    }

    return result;
}


vector<double> calc_spline_params(global_matrix_type global_matrix, vector<double> b_vector){
    global_matrix_type l_matrix = init_global_matrix();
    global_matrix_type u_matrix = init_global_matrix();

    lu_decomp(global_matrix, l_matrix, u_matrix);

    vector<double> x_1 = forward_solution(l_matrix, b_vector);
    return backward_solution(u_matrix, x_1);
}