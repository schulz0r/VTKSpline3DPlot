//
//  plot.cpp
//  LowLevelPlanner_plot
//
//  Created by Philipp Waxweiler on 12.10.20.
//

#include "plot.h"
#include <vtkParametricSpline.h>
#include <vtkLineSource.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolygon.h>
#include <vtkParametricFunctionSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkContextScene.h>
#include <vtkPlotLine3D.h>
#include <vtkTable.h>

LibPlotter::LibPlotter() {
    // configure chart
    chart->SetGeometry(vtkRectf(10, 10, 800, 600));
    chart->SetXAxisLabel("x [m]");
    chart->SetYAxisLabel("y [m]");
    chart->SetZAxisLabel("z [m]");
    chart->SetEnsureOuterEdgeAxisLabelling(true);
    chart->SetFitToScene(true);
    chart->SetDecorateAxes(true);
    chart->SetClippingPlanesEnabled(false);
    
    // configure window
    view->GetRenderWindow()->SetSize(800, 600);
    view->GetRenderWindow()->SetWindowName("Trajectories");
    
    // basic setup
    view->GetScene()->AddItem(chart);
    view->GetRenderer()->SetBackground(1, 1, 1); // white background
}

void LibPlotter::addSpline(const CubicSpline & path) {
    vtkNew<vtkParametricSpline> spline;
    vtkNew<vtkParametricFunctionSource> functionSource;
    vtkNew<vtkPolyDataMapper> mapper;
    vtkNew<vtkActor> actor;
    
    spline->SetNumberOfPoints(path.ctrls().cols());
    for(unsigned idx = 0; idx < path.ctrls().cols(); idx++) {
        spline->SetPoint(path.knots()[idx],
                         path.ctrls().col(idx)[POSITION_X],
                         path.ctrls().col(idx)[POSITION_Y],
                         path.ctrls().col(idx)[POSITION_Z]);
    }
    spline->Modified();
    
    
    functionSource->SetParametricFunction(spline);
    functionSource->Update();

    // Setup actor and mapper
    mapper->SetInputConnection(functionSource->GetOutputPort());
    
    actor->SetMapper(mapper);
    actor->GetProperty()->SetLineWidth(2.0);
    actor->GetProperty()->SetColor(1.0, 0, 0);
    chart->GetScene()->GetRenderer()->AddActor(actor);
}

void LibPlotter::show() const {
    view->GetInteractor()->Initialize();
    view->GetInteractor()->Start();
}
