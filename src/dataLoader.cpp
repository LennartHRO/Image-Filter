#include <vector>
#include <opencv2/opencv.hpp>
#include <iostream>

#include "dataLoader.h"


cv::Mat read_image_file(int argc, char **argv)
{
    // Check if the image file path is provided
    if (argc != 2)
    {
        std::cerr << "Error: Unable to load image" << std::endl;
    }
    cv::Mat image;
    image = cv::imread(argv[1], cv::IMREAD_COLOR);
    if (!image.data)
    {
        std::cerr << "Error: No image data" << std::endl;
    }

    return image;
}


std::vector<std::vector<std::vector<int>>> convertMatToMatrix(const cv::Mat &image)
{
    std::vector<std::vector<std::vector<int>>> matrix;

    // Check if the input matrix is empty
    if (image.empty())
    {
        std::cerr << "Error: Input matrix is empty" << std::endl;
        return matrix;
    }

    // Convert the input image matrix to a 3D vector
    for (int i = 0; i < image.rows; ++i)
    {
        std::vector<std::vector<int>> row;
        for (int j = 0; j < image.cols; ++j)
        {
            // Access the pixel values for each channel and store them in a vector
            cv::Vec3b color = image.at<cv::Vec3b>(i, j);
            std::vector<int> pixelValues = {static_cast<int>(color[0]), static_cast<int>(color[1]), static_cast<int>(color[2])};
            // Add the vector to the row
            row.push_back(pixelValues);
        }
        // Add the row to the matrix
        matrix.push_back(row);
    }

    return matrix;
}


cv::Mat convertMatrixToMat(const std::vector<std::vector<std::vector<int>>> &matrix)
{
    // Check if the input matrix is empty
    if (matrix.empty() || matrix[0].empty() || matrix[0][0].empty())
    {
        std::cerr << "Error: Input matrix is empty" << std::endl;
        return cv::Mat();
    }

    // Create a cv::Mat with the same size as the matrix
    cv::Mat image(matrix.size(), matrix[0].size(), CV_8UC3);

    // Copy the values from the matrix to the cv::Mat
    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix[0].size(); ++j)
        {
            cv::Vec3b &color = image.at<cv::Vec3b>(i, j);
            color[0] = static_cast<uchar>(matrix[i][j][0]); // Blue
            color[1] = static_cast<uchar>(matrix[i][j][1]); // Green
            color[2] = static_cast<uchar>(matrix[i][j][2]); // Red
        }
    }

    return image;
}


void write_img(std::vector<std::vector<std::vector<int>>> &matrix, std::string saveimage)
{
    cv::Mat new_image = convertMatrixToMat(matrix);
    cv::imwrite(saveimage, new_image);
    cv::waitKey();
}