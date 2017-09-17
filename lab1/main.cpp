#include "header.h"

using namespace std;

int main( int argc, const char *argv[] ) {
    grid_type grid;

    grid = read_grid();
    vector<double> b_vector(global_matrix_size, 0);
    global_matrix_type global_matrix = init_global_matrix();

    // Расчет локальных матриц и векторов + добавление в глобальную
    for (int i = 0; i < omega_count; ++i) {
        local_matrix_type beta_matrix = local_beta_matrix(grid.h_length[i]);
        local_matrix_type a_matrix = local_a_matrix(grid.h_length[i], grid.points[i], grid.weights[i]);
        local_matrix_type local_matrix = sum_local_matrix(a_matrix, beta_matrix);
        vector<double> b_local = local_b_vector(grid.h_length[i], grid.points[i], grid.weights[i], grid.f_value[i]);

        concat_local_vector(&b_vector, b_local, i);
        add_local_matrix_to_global(local_matrix, &global_matrix, i);
    }

    // Разложение глобальной матрицы
    global_matrix_type l_matrix = init_global_matrix();
    global_matrix_type u_matrix = init_global_matrix();

    lu_decomp(global_matrix, l_matrix, u_matrix);

    vector<double> x_1 = forward_solution(l_matrix, b_vector);
    vector<double> res = backward_solution(u_matrix, x_1);

    return 0 ;
}
