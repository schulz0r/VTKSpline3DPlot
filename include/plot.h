#pragma once

#include <unsupported/Eigen/Splines>
#include <vtkSmartPointer.h>
#include <vtkContextView.h>
#include <vtkChartXYZ.h>

typedef Eigen::Spline<double, 4, 3> CubicSpline;

enum TrajectoryStates: unsigned char {
    POSITION_X,
    POSITION_Y,
    POSITION_Z,
    SPEED_U
};

class LibPlotter final {
public:
    LibPlotter();
    void addSpline(const CubicSpline & path);
    void show() const;
private:
    vtkNew<vtkChartXYZ> chart;
    vtkNew<vtkContextView> view;
};
