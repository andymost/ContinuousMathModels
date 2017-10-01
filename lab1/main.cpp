#include "header.h"
#include <iostream>

using namespace std;

int main( int argc, const char *argv[] ) {
    grid_type grid;

    grid = read_grid();

    const int max_iteration = 3;
    const double max_difference = 0.1;

    vector<double> b_vector = calc_global_vector(grid);
    global_matrix_type global_matrix = calc_global_matrix(grid);
    vector<double> q = calc_spline_params(global_matrix, b_vector);
    double diff = difference(grid, q);


    for (int j = 0; j < max_iteration && diff > max_difference ; ++j) {
        grid = update_grid(grid, diff, q);
        b_vector = calc_global_vector(grid);
        global_matrix = calc_global_matrix(grid);
        q = calc_spline_params(global_matrix, b_vector);
        diff = difference(grid, q);
    }

    cout<<"DIFF: "<<diff<<endl;

    cout<<"Q vector: "<<endl;
    for (int i = 0; i < global_matrix_size; ++i) {
        cout<<q[i]<<"  ";
    }
    cout<<endl;

    double x = grid.points[0][0];
    double x_end = grid.points[grid.points.size() - 1][grid.points[grid.points.size() - 1].size() -1];
    double step = 0.1;

    while(x <= x_end){
        cout<<"X: "<<x<<"  P(x): "<<spline(x,grid,q)<<endl;
        x += step;
    }


    return 0 ;
}
