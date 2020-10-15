cmake_minimum_required (VERSION 3.10)
project(Plot3DSpline LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

# dependencies
find_package(Eigen3 REQUIRED NO_MODULE)
find_package(VTK 9 REQUIRED
    COMPONENTS
        ChartsCore
        CommonCore
        CommonComputationalGeometry
        CommonDataModel
        RenderingCore
        RenderingOpenGL2
        RenderingContext2D
        RenderingFreeType
        RenderingContextOpenGL2
        ViewsContext2D
        FiltersSources
        InteractionStyle
)

# executable
file(GLOB SRC "src/*.cpp")
file(GLOB HEADERS "include/*.h")

add_executable(${PROJECT_NAME} ${SRC} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_link_libraries(${PROJECT_NAME} Eigen3::Eigen ${VTK_LIBRARIES})

vtk_module_autoinit(
	TARGETS ${PROJECT_NAME}
        MODULES ${VTK_LIBRARIES}
)
