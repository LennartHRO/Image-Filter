#include "dataLoader.cpp"
#include <vector>
#include <opencv2/opencv.hpp>
#include <iostream>

void change_brightness(std::vector<std::vector<std::vector<int>>> &matrix, int brightness)
{
    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix[0].size(); ++j)
        {
            for (int k = 0; k < matrix[0][0].size(); ++k)
            {
                matrix[i][j][k] += brightness;
                if (matrix[i][j][k] > 255)
                {
                    matrix[i][j][k] = 255;
                }
                else if (matrix[i][j][k] < 0)
                {
                    matrix[i][j][k] = 0;
                }
            }
        }
    }
}

void invert_image(std::vector<std::vector<std::vector<int>>> &matrix)
{
    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix[0].size(); ++j)
        {
            for (int k = 0; k < matrix[0][0].size(); ++k)
            {
                matrix[i][j][k] = 255 - matrix[i][j][k];
            }
        }
    }
}

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

    // Change the brightness of the image
    invert_image(matrix);

    // Convert the matrix back to an image
    image = convertMatrixToMat(matrix);

    // Display image
    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Display Image", image);
    cv::waitKey(0);
    return 0;
}