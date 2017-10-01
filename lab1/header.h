//
// Created by Кочнев Андрей Владимирович on 16/09/2017.
//

#ifndef UNITSV1_HEADER_H
#define UNITSV1_HEADER_H

#include <vector>
typedef double dot_type;
typedef std::vector<std::vector<double>> local_matrix_type, global_matrix_type;
typedef struct {
    std::vector<dot_type> h_length;   // длинна i-го КЭ
    std::vector<std::vector<dot_type>> points; // точки на КЭ
    std::vector<std::vector<double>> f_value; // значения функции
    std::vector<std::vector<double>> weights; // веса
} grid_type;

typedef struct {
    int omega_index;
    int index;
} elem_pos_type;

typedef struct {
    bool isSmaller; // разница м/у всем эл менше заданной
    double mean;    // ср. разница
    std::vector<elem_pos_type> elems; // адреса эл что больше среднего в формате:  [[omega_ind, index], ....]
} diff_type;



// расчет локальной матрицы регуляризатора бета
local_matrix_type local_beta_matrix(double h_length);
// расчет локальной матрицы a
local_matrix_type local_a_matrix(
        double h_length,
        int omega_number,
        grid_type grid
);
// сумма локальных матриц
local_matrix_type sum_local_matrix(local_matrix_type a, local_matrix_type b);
// инициализация глобальной матрицы
global_matrix_type init_global_matrix();
// добавление локальной матрицы в глобальную
void  add_local_matrix_to_global(local_matrix_type local_matrix, global_matrix_type* global_matrix, int elem_number);
// расчет глобальной матрицы
global_matrix_type calc_global_matrix(grid_type grid);
// расчет глобального вектора
std::vector<double> calc_global_vector(grid_type grid);
// расчет коэффициентов сплайна
std::vector<double> calc_spline_params(global_matrix_type global_matrix, std::vector<double> b_vector);


// lu-разложение
void lu_decomp(global_matrix_type A, global_matrix_type &L, global_matrix_type  &U);
// перемножение квадратных матриц
global_matrix_type matrix_multSQ_matrix(global_matrix_type a, global_matrix_type b);
// обратный ход
std::vector<double> backward_solution(global_matrix_type u, std::vector<double> b);
// прямой ход
std::vector<double> forward_solution(global_matrix_type l, std::vector<double> b);
// i-ая базисная Эрмитова функция
double  psi(short index, double h_length, dot_type x_left, dot_type x);
// производная i-ой базисной Эрмитовой функции в точке
double  psi_derevative(short index, double h_length, dot_type x_left, dot_type x);
// локальный вектор правой части
std::vector<double> local_b_vector(
        double h_length,
        grid_type grid,
        int omega_number
);

// разница
diff_type difference(grid_type grid, std::vector<double> q);

// обновление сетки
grid_type update_grid(grid_type grid, diff_type diff);

// добавление локального вектора в глобальный
void concat_local_vector(
        std::vector<double>* global_vector,
        std::vector<double> local_vector,
        int elem_number
);
// расчет сплайна
double spline(double x, grid_type grid, std::vector<double> q);
// расчет производной сплайна
double spline_derivatice(double x, grid_type grid, std::vector<double> q);

grid_type read_grid();

// коэффициент бета
const double beta = 0.001;
// количество элементов
const int omega_count = 2;
// размерность глобальной матрицы
const int global_matrix_size = 2 * omega_count + 2;
// отношение среднего отклонения и локального
const double diff_rel = 2;
// во сколько раз уменьшаем w_j
const double w_denominator = 2;
// количество итераций сглаживания
const int max_iteration = 10;
//epsilon окрестность для сравнения чисел
const double epsilon = 0.0000001;


// размерность локальной матрицы
const int local_matrix_size = 4;


#endif //UNITSV1_HEADER_H
