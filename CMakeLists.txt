cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(BundleAdjustment)

########################
# Third parties
########################

find_package(OpenCV REQUIRED core imgproc imgcodecs highgui cudafilters cudaimgproc features2d xfeatures2d videoio)
find_package(Boost REQUIRED COMPONENTS filesystem)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(Ceres REQUIRED)

########################
# Build
########################
add_library(DataLoader src/DataLoader.cpp)
target_include_directories(DataLoader 
    PUBLIC ${Boost_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS} ${CERES_INCLUDE_DIRS})
target_link_libraries(DataLoader Eigen3::Eigen Boost::filesystem ${OpenCV_LIBS} ${CERES_LIBRARIES})

# Runner
add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME}
    PUBLIC include)
target_link_libraries(${PROJECT_NAME} DataLoader)