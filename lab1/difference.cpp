//
// Created by Кочнев Андрей Владимирович on 01/10/2017.
//
#include "header.h"
#include <cmath>
#include <iostream>

using namespace std;

struct local_buffer_type{
    int omega_i;
    int index;
    double diff;
};


/*
 * Суть:
 * Считаем среднее отклонение, попутно складывая точки с отклонением в структуру(чтоб второй раз не пересчитывать).
 * После того как сосчитали, если отклонение в точке больше среднего в n раз перекладываем в структуру разницы, меняем флаг
 *
 * */
diff_type difference(grid_type grid, vector<double> q){
    diff_type diff;

    // [[omega_index, index, item_diff], ...]
    vector<local_buffer_type> buffer;

    // инициализация
    diff.isSmaller = true;
    diff.mean = 0;

    double item_diff = 0;
    int dot_count = 0;

    // подсчет среднего и запись об элементах
    for (int i = 0; i < grid.points.size(); ++i) {
        for (int j = 0; j < grid.points[i].size() - 1; ++j) {
            item_diff = abs(grid.f_value[i][j] - spline(grid.points[i][j], grid, q));

            local_buffer_type local_buffer{
                    .diff = item_diff,
                    .omega_i = i,
                    .index = j
            };
            buffer.push_back(local_buffer);

            diff.mean += item_diff;
            ++dot_count;
        }
    }

    diff.mean = diff.mean/dot_count;

    // перекладываем большую разницу в diff
    for (auto buffer_item:buffer) {
        if(buffer_item.diff / diff_rel> diff.mean) {
            diff.isSmaller = false;
            elem_pos_type elem_pos {
                    .omega_index = buffer_item.omega_i,
                    .index = buffer_item.index
            };

            diff.elems.push_back(elem_pos);
        }
    }

    return diff;
}

