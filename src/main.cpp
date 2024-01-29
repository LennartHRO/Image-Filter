#include "dataLoader.h"
#include "filters.h"
#include "image.h"
#include <vector>
#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char **argv)
{
    DataLoader dataLoader;
    Image image = dataLoader.loadImage(argc, argv);

    char input;
    std::unique_ptr<Filter> filter;
    while (true)
    {
        std::cout << "Enter the operation you want to perform on the image:" << std::endl;
        std::cout << "i: Invert the image" << std::endl;
        std::cout << "b: Change the brightness of the image" << std::endl;
        std::cout << "c: Change the contrast of the image" << std::endl;
        std::cout << "g: Make the image gray" << std::endl;
        std::cout << "f: Fuzzy/Gaussian filter" << std::endl;
        std::cout << "l: Box linear filter" << std::endl;
        std::cout << "x: Make your own super filter" << std::endl;
        std::cout << "s: Save Image" << std::endl;
        std::cout << "q: Quit" << std::endl;
        std::cin >> input;
        switch (input)
        {
        case 'i':
            std::cout << "Inverting the image." << std::endl;
            filter = std::make_unique<InvertFilter>();
            break;

        case 'b':
            std::cout << "Brightness Filter" << std::endl;
            filter = std::make_unique<BrightnessFilter>();
            break;

        case 'c':
            std::cout << "Contrast Filter" << std::endl;
            filter = std::make_unique<ContrastFilter>();
            break;

        case 'g':
            std::cout << "Making the image gray." << std::endl;
            filter = std::make_unique<GrayFilter>();
            break;

        case 'f':
            std::cout << "Fuzzy/Gaussian filter" << std::endl;
            filter = std::make_unique<GaussianFilter>();
            break;

        case 'l':
            std::cout << "Box linear filter" << std::endl;
            filter = std::make_unique<BoxBlur>();
            break;
        case 'x':
            filter = std::make_unique<SuperFilter>();
            break;
        case 's':
            image.saveImage();
            filter = NULL;
            break;
        case 'q':
            std::cout << "Quitting." << std::endl;
            return 0;

        default:
            std::cout << "Unknown command" << std::endl;
            filter = NULL;
            break;
        }

        if (filter)
        {
            filter->configure();
            filter->apply(image);
            image.showImage();
        }
    }
    return 0;
}