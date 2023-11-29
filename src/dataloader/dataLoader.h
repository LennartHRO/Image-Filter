#include <vector>
#include <opencv2/opencv.hpp>


cv::Mat read_image_file(int argc, char **argv);


std::vector<std::vector<std::vector<int>>> convertMatToMatrix(const cv::Mat &image);


cv::Mat convertMatrixToMat(const std::vector<std::vector<std::vector<int>>> &matrix);