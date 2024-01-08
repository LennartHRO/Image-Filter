#include <vector>
#include <opencv2/opencv.hpp>
#include "image.h"

class DataLoader
{
private:
    Image convertMatToImage(const cv::Mat &image);

public:
    Image loadImage(int argc, char **argv);
};

/*
--------- OLD DATALOADER FUNCTION: ---------
// Function to read an image file and return a cv::Mat image
// Input: argc and argv from main()
// Output: cv::Mat image
cv::Mat read_image_file(int argc, char **argv);

// Function to convert cv::Mat to a 3D vector (matrix) for color images
// Input: cv::Mat image
// Output: Tensor: Rows x Cols x Channels (RGB)
std::vector<std::vector<std::vector<int>>> convertMatToMatrix(const cv::Mat &image);

// Function to convert a Tensor to a image
// Input: Tensor: Rows x Cols x Channels (RGB)
// Output: cv::M
cv::Mat convertMatrixToMat(const std::vector<std::vector<std::vector<int>>> &matrix);

// Function to write an image to a file
// Input: Tensor: Rows x Cols x Channels (RGB)
// Output: -
void write_img(std::vector<std::vector<std::vector<int>>> &matrix, std::string saveimage);
*/