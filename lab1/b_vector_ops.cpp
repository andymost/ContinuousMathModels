//
// Created by Кочнев Андрей Владимирович on 25/09/2017.
//

#include "header.h"
using namespace std;

vector<double> local_b_vector(
        double h_length,
        grid_type grid,
        int omega_number
) {
    vector<double> result(local_matrix_size, 0);
    vector<double> points = grid.points[omega_number];
    vector<double> weights = grid.weights[omega_number];
    vector<double> f_values = grid.f_value[omega_number];

    double x_p = omega_number == 0 ?
                 points[0] :
                 grid.points[omega_number - 1][grid.points[omega_number - 1].size() - 1];

    for (short j = 0; j < local_matrix_size; ++j) {
        for (int k = 0; k < points.size(); ++k) {
            result[j] += weights[k] * f_values[k] *
                    psi(j, h_length, x_p, points[k]);
        }
    }

    return result;
}

void concat_local_vector(vector<double>* global_vector, vector<double> local_vector, int elem_number) {
    int offset = elem_number * 2;
    for (int i = 0; i < local_matrix_size; ++i) {
        (*global_vector)[offset * elem_number+i] += local_vector[i];
    }
}
