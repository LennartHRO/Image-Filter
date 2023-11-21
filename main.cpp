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

    char input;
    while (true)
    {
        std::cout << "Enter 'i' to invert the image, 'b' to change the brightness, or 'q' to quit: ";
        std::cin >> input;
        switch (input)
        {
        case 'i':
            std::cout << "Inverting the image." << std::endl;
            invert_image(matrix);
            break;
        case 'b':
            std::cout << "Enter the brightness value: ";
            int brightness;
            std::cin >> brightness;
            std::cout << "Changing the brightness of the image by " << brightness << std::endl;
            change_brightness(matrix, brightness);
            break;
        case 's':
            std::cout << "Showing the image." << std::endl;
            image = convertMatrixToMat(matrix);
            cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
            cv::imshow("Display Image", image);
            cv::waitKey(0);
            break;
        default:
            std::cout << "Quitting." << std::endl;
            return 0;
            break;
        }
    }

    return 0;
}