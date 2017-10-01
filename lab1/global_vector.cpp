//
// Created by Кочнев Андрей Владимирович on 01/10/2017.
//

#include "header.h"
using namespace std;

vector<double> calc_global_vector(grid_type grid){
    vector<double> result(global_matrix_size, 0);
    for (int i = 0; i < omega_count; ++i) {
        vector<double> b_local = local_b_vector(grid.h_length[i], grid, i);
        concat_local_vector(&result, b_local, i);
    }

    return result;
}