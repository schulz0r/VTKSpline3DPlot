//
//  plot.cpp
//  LowLevelPlanner_plot
//
//  Created by Philipp Waxweiler on 12.10.20.
//

#include "plot.h"
#include <math.h>

int main() {
    LibPlotter plotter;
    Eigen::Matrix<double, 4, 5, Eigen::ColMajor> points = Eigen::Matrix<double, 4, 5, Eigen::ColMajor>::Zero();

    for(unsigned i = 0; i < 5; i++){
        points.col(i)[POSITION_X] = std::cos(i * M_PI_4);
        points.col(i)[POSITION_Y] = std::sin(i * M_PI_4);
        points.col(i)[POSITION_Z] = i;
        points.col(i)[SPEED_U] = double(i) * 2; // this will be considered later
    }
    
    CubicSpline trajectory = Eigen::SplineFitting<CubicSpline>::Interpolate(points, 3);
    
    plotter.addSpline(trajectory);
    plotter.show();
    
    return 0;
}
