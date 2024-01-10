#include "image.h"
#include <vector>
#include <opencv2/opencv.hpp>

Image::Image(std::vector<std::vector<std::vector<int>>> imageData) : _imageData(imageData)
{
}

cv::Mat Image::convertImageDataToMat() const
{
    // Check if the input matrix is empty
    if (_imageData.empty() || _imageData[0].empty() || _imageData[0][0].empty())
    {
        std::cerr << "Error: Input matrix is empty" << std::endl;
        return cv::Mat();
    }

    // Create a cv::Mat with the same size as the matrix
    cv::Mat image(_imageData.size(), _imageData[0].size(), CV_8UC3);

    // Copy the values from the matrix to the cv::Mat
    for (int i = 0; i < _imageData.size(); ++i)
    {
        for (int j = 0; j < _imageData[0].size(); ++j)
        {
            cv::Vec3b &color = image.at<cv::Vec3b>(i, j);
            color[0] = static_cast<uchar>(_imageData[i][j][0]); // Blue
            color[1] = static_cast<uchar>(_imageData[i][j][1]); // Green
            color[2] = static_cast<uchar>(_imageData[i][j][2]); // Red
        }
    }

    return image;
}

void Image::showImage() const
{
    cv::Mat image = convertImageDataToMat();
    cv::imshow("Image", image);
    cv::waitKey(0);
}

void Image::saveImage() const
{
    cv::Mat image = convertImageDataToMat();

    std::string image_name;

    std::cout << "New Image Name (with file ending (e.g. .jpg)): ";
    std::cin >> image_name;
    std ::cout << "Saving the image." << std::endl << std::endl;

    cv::imwrite(image_name, image);
}

std::vector<std::vector<std::vector<int>>> Image::getImageData() const
{
    return _imageData;
}

void Image::setImageData(std::vector<std::vector<std::vector<int>>> imageData)
{
    _imageData = imageData;
}