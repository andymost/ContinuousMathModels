//
// Created by Кочнев Андрей Владимирович on 16/09/2017.
//

#include "header.h"
#include <fstream>

using namespace std;

grid_type read_grid() {
    grid_type grid;
    fstream grid_file ("../resources/grid.txt", ios_base::in);
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
