#ifndef DATALOADER_H
#define DATALOADER_H

#include <opencv2/opencv.hpp>
#include "dataLoader.h"
#include "image.h"

Image DataLoader::convertMatToImage(const cv::Mat &matImage)
{
    std::vector<std::vector<std::vector<int>>> imageData;

    for (int y = 0; y < matImage.rows; ++y)
    {
        std::vector<std::vector<int>> row;
        for (int x = 0; x < matImage.cols; ++x)
        {
            std::vector<int> pixel;
            cv::Vec3b color = matImage.at<cv::Vec3b>(y, x);
            // OpenCV uses BGR format by default
            pixel.push_back(color[0]); // Blue
            pixel.push_back(color[1]); // Green
            pixel.push_back(color[2]); // Red
            row.push_back(pixel);
        }
        imageData.push_back(row);
    }

    return Image(imageData);
}

Image DataLoader::loadImage(int argc, char **argv)
{
    // Check if the image file path is provided
    if (argc < 2)
    {
        std::cerr << "Not enough arguments. Please provide an image path." << std::endl;
        exit(1);
    }

    // Read the image file
    cv::Mat image = cv::imread(argv[1], cv::IMREAD_COLOR);

    // Check if the image file is empty
    if (image.empty())
    {
        std::cerr << "Could not open or find the image. Please check your image file/path and try again." << std::endl;
        exit(1);
    }

    return convertMatToImage(image);
}

#endif