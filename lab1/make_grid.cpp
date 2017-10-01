//
// Created by Кочнев Андрей Владимирович on 16/09/2017.
//

#include "header.h"
#include <fstream>
#include <cmath>

using namespace std;

// grid_model - задача из учебника
// linear_clean     f(x) = 2.5 + x
// linear_noized    linear_clean(x) + rnornm(mean=1, sd=0.2)
// cubic_clean      f(x) = 3 + 2x + 0.5x**3
// cubic_noized     cubic_noized(x) + rnornm(mean=1, sd=0.2)
// sin_clean        f(x) = 2*sin(Pi * x)
// sin_noized       sin_clean + rnornm(mean=1, sd=0.2)

/*
 * ГСЧ для шума значений

rnormF <- function(f_vals){
   f_vals + rnorm(n=length(f_vals), sd=0.2)
}
 * */

grid_type read_grid() {
    grid_type grid;
    fstream grid_file ("../resources/exp_errored.txt", ios_base::in);
    vector<double> tmp_vec;

    double h, len, x_val, f_val, w_val;

    for (int i = 0; i < omega_count; ++i) {
        grid_file>>len;
        grid_file>>h;
        grid.h_length.push_back(h);

        grid.f_value.push_back(tmp_vec);
        grid.points.push_back(tmp_vec);
        grid.weights.push_back(tmp_vec);
        for (int j = 0; j < len; ++j) {
            grid_file>>w_val;
            grid_file>>x_val;
            grid_file>>f_val;

            grid.points[i].push_back(x_val);
            grid.f_value[i].push_back(f_val);
            grid.weights[i].push_back(w_val);
        }

    }


    return grid;
}

grid_type update_grid(grid_type grid, diff_type diff) {
    for(auto elem:diff.elems) {
        grid.weights[elem.omega_index][elem.index] = grid.weights[elem.omega_index][elem.index]/w_denominator;
    }

    return grid;
}