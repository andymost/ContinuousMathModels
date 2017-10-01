//
// Created by Кочнев Андрей Владимирович on 01/10/2017.
//
#include "header.h"
#include <cmath>

using namespace std;

double difference(grid_type grid, vector<double> q){
    double shared_result = 0;
    int dot_count = 0;

    for (int i = 0; i < grid.points.size(); ++i) {
        for (int j = 0; j < grid.points[i].size(); ++j) {
            shared_result += abs(grid.f_value[i][j] - spline(grid.points[i][j], grid, q));
            ++dot_count;
        }
    }

    return shared_result/dot_count;
}

