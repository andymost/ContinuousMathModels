//
// Created by Кочнев Андрей Владимирович on 25/09/2017.
//

#include "header.h"
using namespace std;

vector<double> local_b_vector(
        double h_length,
        vector<dot_type> points,
        vector<dot_type> weights,
        vector<dot_type> f_values
) {
    vector<double> result(local_matrix_size, 0);

    for (short j = 0; j < local_matrix_size; ++j) {
        for (int k = 0; k < points.size(); ++k) {
            result[j] += weights[k] * f_values[k] *
                    psi(j, h_length, points[0], points[k]);
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
