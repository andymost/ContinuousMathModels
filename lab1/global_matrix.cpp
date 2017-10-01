//
// Created by Кочнев Андрей Владимирович on 17/09/2017.
//

#include "header.h"

global_matrix_type init_global_matrix(){
    global_matrix_type result;
    for (int i = 0; i < global_matrix_size; ++i) {
        std::vector<double> tmp_vector;
        result.push_back(tmp_vector);
        for (int j = 0; j < global_matrix_size; ++j) {
            result[i].push_back(0);
        }
    }

    return result;
}

void  add_local_matrix_to_global(local_matrix_type local_matrix, global_matrix_type* global_matrix, int elem_number) {
    int offset = elem_number * 2;
    for (int i = 0; i < local_matrix_size; ++i) {
        for (int j = 0; j < local_matrix_size; ++j) {
            (*global_matrix)[offset * elem_number+i][offset * elem_number+j] += local_matrix[i][j];
        }
    }
}

global_matrix_type calc_global_matrix(grid_type grid) {
    // Расчет локальных матриц и векторов + добавление в глобальную
    global_matrix_type global_matrix = init_global_matrix();
    for (int i = 0; i < omega_count; ++i) {
        local_matrix_type beta_matrix = local_beta_matrix(grid.h_length[i]);
        local_matrix_type a_matrix = local_a_matrix(grid.h_length[i], i, grid);
        local_matrix_type local_matrix = sum_local_matrix(a_matrix, beta_matrix);

        add_local_matrix_to_global(local_matrix, &global_matrix, i);
    }

    return global_matrix;
}