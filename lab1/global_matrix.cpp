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