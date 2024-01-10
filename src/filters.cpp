#include "filters.h"

#include <vector>
#include <iostream>
#include <cmath>

void Filter::configure()
{
}

void InvertFilter::apply(Image &image)
{
    std::vector<std::vector<std::vector<int>>> matrix = image.getImageData();
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
    image.setImageData(matrix);
}

void BrightnessFilter::apply(Image &image)
{
    std::vector<std::vector<std::vector<int>>> matrix = image.getImageData();
    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix[0].size(); ++j)
        {
            for (int k = 0; k < matrix[0][0].size(); ++k)
            {
                matrix[i][j][k] += _brightness;
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
    image.setImageData(matrix);
}

void BrightnessFilter::configure()
{
    std::cout << "Please enter the brightness value(-100 is very dark, 100 is very bright): ";
    std::cin >> _brightness;
    std::cout << std::endl;
}

BrightnessFilter::BrightnessFilter() : _brightness(0)
{
}

void ContrastFilter::apply(Image &image)
{
    std::vector<std::vector<std::vector<int>>> matrix = image.getImageData();
    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix[0].size(); ++j)
        {
            for (int k = 0; k < matrix[0][0].size(); ++k)
            {
                matrix[i][j][k] *= _contrast;
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
    image.setImageData(matrix);
}

void ContrastFilter::configure()
{
    do
    {
        std::cout << "Please enter the contrast value (0.5 is a very low and 2 is a very high contrast value): ";
        std::cin >> _contrast;
        if (_contrast <= 0 || _contrast > 10)
        {
            std::cout << "Contrast value must be between 0 and 10." << std::endl;
        }
    } while (_contrast <= 0 || _contrast > 10);
    std::cout << std::endl;
}

ContrastFilter::ContrastFilter() : _contrast(0)
{
}

void GrayFilter::apply(Image &image)
{
    std::vector<std::vector<std::vector<int>>> matrix = image.getImageData();
    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix[0].size(); ++j)
        {
            int gray = 0.3 * matrix[i][j][0] + 0.6 * matrix[i][j][1] + 0.1 * matrix[i][j][2];
            matrix[i][j][0] = gray;
            matrix[i][j][1] = gray;
            matrix[i][j][2] = gray;
        }
    }
    image.setImageData(matrix);
}

void ConvolutionFilter::pad(Image &image, const int kernelSize)
{
    std::vector<std::vector<std::vector<int>>> matrix = image.getImageData();

    int n = matrix.size();
    int m = matrix[0].size();
    int d = matrix[0][0].size();

    int edge = kernelSize - 1;

    std::vector<std::vector<std::vector<int>>> pad_matrix;

    // initialize pad_matrix with zeros
    for (int i = 0; i < n + 2 * edge; ++i)
    {
        std::vector<std::vector<int>> row;
        for (int j = 0; j < m + 2 * edge; ++j)
        {
            std::vector<int> pixelValues = {0, 0, 0};
            row.push_back(pixelValues);
        }
        pad_matrix.push_back(row);
    }

    // copy matrix to the middle of pad_matrix
    // matrix rows
    for (int i = 0; i < n; ++i)
    {
        // matrix columns
        for (int j = 0; j < m; ++j)
        {
            pad_matrix[i + edge][j + edge] = matrix[i][j];
        }
    }

    image.setImageData(pad_matrix);
}

void ConvolutionFilter::convolve(Image &image, const std::vector<std::vector<int>> &kernel, const int kernel_factor)
{
    std::vector<std::vector<std::vector<int>>> new_matrix = image.getImageData();

    int m = new_matrix.size();
    int n = new_matrix[0].size();
    int d = new_matrix[0][0].size();

    pad(image, kernel.size());
    std::vector<std::vector<std::vector<int>>> pad_matrix = image.getImageData();

    int edge = kernel.size() - 1;

    int kernelOffset = kernel.size() / 2;

    // matrix rows
    for (int i = 0; i < m; ++i)
    {
        // matrix columns
        for (int j = 0; j < n; ++j)
        {
            // matrix depth
            for (int k = 0; k < d; ++k)
            {
                int sum_pixel = 0;
                // kernel rows
                for (int ki = -kernelOffset; ki <= kernelOffset; ++ki)
                {
                    // kernel columns
                    for (int kj = -kernelOffset; kj <= kernelOffset; ++kj)
                    {
                        // convolution
                        sum_pixel = sum_pixel + pad_matrix[edge + i - ki][edge + j - kj][k] * kernel[ki + (kernel.size() / 2)][kj + (kernel.size() / 2)];
                    }
                }
                new_matrix[i][j][k] = sum_pixel / kernel_factor;
            }
        }
    }

    image.setImageData(new_matrix);
}

void GaussianFilter::apply(Image &image)
{
    std::vector<std::vector<int>> kernel;
    int kernel_factor = 0;
    int kernel_value = 0;

    float std_dev = _kernelSize / (2.0 * 3.14);

    for (int i = -_kernelSize / 2; i <= _kernelSize / 2; ++i)
    {
        std::vector<int> row;
        for (int j = -_kernelSize / 2; j <= _kernelSize / 2; ++j)
        {
            kernel_value = 100 * std::exp(-(std::pow(i, 2) + std::pow(j, 2)) / (2.0 * std::pow(std_dev, 2))); // 1.0 / (2.0 * M_PI * std::pow(std_dev, 2))
            kernel_factor += kernel_value;
            row.push_back(kernel_value);
        }
        kernel.push_back(row);
    }

    convolve(image, kernel, kernel_factor);
}

void GaussianFilter::configure()
{
    do
    {
        std::cout << "Please enter the kernel size: ";
        std::cin >> _kernelSize;
        if (_kernelSize < 1)
        {
            std::cout << "Kernel size must be greater than 0." << std::endl;
        }
    } while (_kernelSize < 1);
    std::cout << std::endl;
}

GaussianFilter::GaussianFilter() : _kernelSize(0)
{
}

void BoxBlur::apply(Image &image)
{
    int kernel_factor = _kernelSize * _kernelSize;

    std::vector<std::vector<int>> kernel;

    kernel.assign(_kernelSize, std::vector<int>(_kernelSize, 1));

    /*if (kernel_factor % 2 == 1)
    {
        kernel.assign(_kernelSize, std::vector<int>(_kernelSize, 1));
    }
    else
    {
        kernel.assign(_kernelSize + 1, std::vector<int>(_kernelSize + 1, 0));
        for (int i = 1; i < _kernelSize; i++)
        {
            for (int j = 1; j < _kernelSize; j++)
            {
                kernel[i][j] = 1;
            }
        }
        kernel_factor = (_kernelSize - 1) * (_kernelSize - 1);
    }*/

    convolve(image, kernel, kernel_factor);
}

void BoxBlur::configure()
{
    do
    {
        std::cout << "Please enter the kernel size (odd): ";
        std::cin >> _kernelSize;
        if (_kernelSize < 1)
        {
            std::cout << "Kernel size must be greater than 0." << std::endl;
        }
        else if (_kernelSize % 2 == 0)
        {
            std::cout << "Kernel size must be an odd number." << std::endl;
        }

    } while (_kernelSize < 1 || _kernelSize % 2 == 0);
    std::cout << std::endl;
}

BoxBlur::BoxBlur() : _kernelSize(0)
{
}

SuperFilter::SuperFilter()
{
}

// Apply method
void SuperFilter::apply(Image &image)
{
    for (auto &filter : _filters)
    {
        filter->apply(image);
    }
}

// Configure method
void SuperFilter::configure()
{
    char input;
    std::cout << "Configure your SuperFilter. Add as many filters as you want:" << std::endl;
    while (true)
    {
        std::cout << "i: Invert the image" << std::endl;
        std::cout << "b: Change the brightness of the image" << std::endl;
        std::cout << "c: Change the contrast of the image" << std::endl;
        std::cout << "g: Make the image gray" << std::endl;
        std::cout << "f: Fuzzy/Gaussian filter" << std::endl;
        std::cout << "l: Box linear filter" << std::endl;
        std::cout << "d: Done with adding filters" << std::endl;
        std::cin >> input;
        switch (input)
        {
        case 'i':
            _filters.push_back(std::make_unique<InvertFilter>());
            _filters.back()->configure();
            break;
        case 'b':
            _filters.push_back(std::make_unique<BrightnessFilter>());
            _filters.back()->configure();
            break;
        case 'c':
            _filters.push_back(std::make_unique<ContrastFilter>());
            _filters.back()->configure();
            break;
        case 'g':
            _filters.push_back(std::make_unique<GrayFilter>());
            _filters.back()->configure();
            break;
        case 'f':
            _filters.push_back(std::make_unique<GaussianFilter>());
            _filters.back()->configure();
            break;
        case 'l':
            _filters.push_back(std::make_unique<BoxBlur>());
            _filters.back()->configure();
            break;
        case 'd':
            return;
        default:
            std::cout << "Unknown command. Try again." << std::endl;
            break;
        }
        std::cout << "Filter added." << std::endl;
        std::cout << "Now, you can add another filter:" << std::endl;
    }
}