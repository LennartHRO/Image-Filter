#include "dataLoader.cpp"
#include <vector>
#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char **argv)
{
    // Read image file
    cv::Mat image = read_image_file(argc, argv);

    // Convert the image to a matrix
    std::vector<std::vector<std::vector<int>>> matrix = convertMatToMatrix(image);

    // Access RGB values in the matrix (example):
    std::vector<int> rgbValues = matrix[100][100];
    std::cout << "RGB values at (100, 100): "
              << "R=" << rgbValues[0] << " G=" << rgbValues[1] << " B=" << rgbValues[2] << std::endl;

    // Convert the matrix back to an image
    image = convertMatrixToMat(matrix);

    // Display image
    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Display Image", image);
    cv::waitKey(0);
    return 0;
}