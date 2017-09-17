//
// Created by Кочнев Андрей Владимирович on 24/09/2017.
//

#include "header.h"
#include <algorithm>

void lu_decomp(global_matrix_type a, global_matrix_type &l, global_matrix_type &u)
{
    int i = 0, j = 0, k = 0;
    for (i = 0; i < global_matrix_size; i++)
    {
        for (j = 0; j < global_matrix_size; j++)
        {
            if (j < i)
                l[j][i] = 0;
            else
            {
                l[j][i] = a[j][i];
                for (k = 0; k < i; k++)
                {
                    l[j][i] = l[j][i] - l[j][k] * u[k][i];
                }
            }
        }
        for (j = 0; j < global_matrix_size; j++)
        {
            if (j < i)
                u[i][j] = 0;
            else if (j == i)
                u[i][j] = 1;
            else
            {
                u[i][j] = a[i][j] / l[i][i];
                for (k = 0; k < i; k++)
                {
                    u[i][j] = u[i][j] - ((l[i][k] * u[k][j]) / l[i][i]);
                }
            }
        }
    }
}

std::vector<double> backward_solution(global_matrix_type u, std::vector<double> b) {
    unsigned long size = b.size();
    std::vector<double> result(b.size(), 0);
    double sum;
    for (int i = size - 1; i >= 0; --i) {
        for (int j = size - 1; j > i; --j) {
            sum += result[j] * u[i][j];
        }
        result[i] = (b[i] - sum)/u[i][i];
        sum = 0;
    }

    return result;
}

std::vector<double> forward_solution(global_matrix_type l, std::vector<double> b) {
    unsigned long size = b.size();
    std::vector<double> result;
    double sum = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < i; ++j) {
            sum += result[j] * l[i][j];
        }
        result.push_back((b[i] - sum)/l[i][i]);
        sum = 0;
    }
    return result;
}