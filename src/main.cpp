#include "dataLoader.h"
#include "filters.h"
#include <vector>
#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char **argv)
{
    // Read image file
    cv::Mat image = read_image_file(argc, argv);

    // Convert the image to a matrix
    std::vector<std::vector<std::vector<int>>> matrix = convertMatToMatrix(image);

    std::string save_image;

    char input;
    while (true)
    {
        std::cout << "Enter the operation to perform on the image:" << std::endl;
        std::cout << "i: Invert the image" << std::endl;
        std::cout << "b: Change the brightness of the image" << std::endl;
        std::cout << "c: Change the contrast of the image" << std::endl;
        std::cout << "g: Make the image gray" << std::endl;
        std::cout << "f: Gaussian filter" << std::endl;
        std::cout << "s: Show the image" << std::endl;
        std::cout << "j: Save image" << std::endl;
        std::cout << "q: Quit" << std::endl;
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

        case 'c':
            std::cout << "Enter the contrast value: ";
            float contrast;
            std::cin >> contrast;
            std::cout << "Changing the contrast of the image by " << contrast << std::endl;
            change_contrast(matrix, contrast);
            break;

        case 'g':
            std::cout << "Making the image gray." << std::endl;
            make_image_gray(matrix);
            break;

        case 's':
            std::cout << "Showing the image." << std::endl;
            image = convertMatrixToMat(matrix);
            cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
            cv::imshow("Display Image", image);
            cv::waitKey(0);
            break;

        case 'j':
            std::cout << "New Image Name: ";
            std::cin >> save_image;
            std::cout << std::endl;
            write_img(matrix, save_image);
            break;

        case 'f':
            int kernelSize;
            std::cout << "kernel size (3 or 5): ";
            std::cin >> kernelSize;
            std::cout << std::endl;
            mod_gaussian(matrix, kernelSize);
            break;

        case 'e':
            edge_detection(matrix);
            break;

        case 'x':
            std::cout << "Sharpen" << std::endl;
            sharpen(matrix);
            break;

        case 'q':
            std::cout << "Quitting." << std::endl;
            return 0;

        default:
            std::cout << "Unknown command" << std::endl;
            break;
        }
    }

    return 0;
}