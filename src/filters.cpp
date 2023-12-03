#include "filters.h"

#include <vector>
#include <iostream>
#include <cmath>

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

void change_contrast(std::vector<std::vector<std::vector<int>>> &matrix, float contrast)
{
    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix[0].size(); ++j)
        {
            for (int k = 0; k < matrix[0][0].size(); ++k)
            {
                matrix[i][j][k] *= contrast;
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

void make_image_gray(std::vector<std::vector<std::vector<int>>> &matrix)
{
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
}

void gaussian(std::vector<std::vector<std::vector<int>>> &matrix, const int kernelSize)
{
    std::vector<std::vector<int>> kernel;
    int kernel_factor = 0;
    float std_dev = kernelSize / (2.0 * 3.14);
    int kernel_value = 0;

    for (int i = -kernelSize / 2; i <= kernelSize / 2; ++i)
    {
        std::cout << "i : " << i << std::endl;
        std::vector<int> row;
        for (int j = -kernelSize / 2; j <= kernelSize / 2; ++j)
        {
            std::cout << "j : " << j << std::endl;
            kernel_value = 100 * std::exp(-(std::pow(i, 2) + std::pow(j, 2)) / (2.0 * std::pow(std_dev, 2))); // 1.0 / (2.0 * M_PI * std::pow(std_dev, 2))
            kernel_factor += kernel_value;
            row.push_back(kernel_value);
        }
        kernel.push_back(row);
    }

    // print kernel
    for (int i = 0; i < kernelSize; ++i)
    {
        for (int j = 0; j < kernelSize; ++j)
        {
            std::cout << kernel[i][j] << " ";
        }
        std::cout << std::endl;
    }

    convolution(matrix, kernel, kernel_factor);
}

void edge_detection(std::vector<std::vector<std::vector<int>>> &matrix)
{
    std::vector<std::vector<int>> kernel;
    kernel = {
        {-1, -1, -1},
        {-1, 8, -1},
        {-1, -1, -1}};

    convolution(matrix, kernel, 1);
}

void sharpen(std::vector<std::vector<std::vector<int>>> &matrix)
{
    std::vector<std::vector<int>> kernel;
    /*kernel = {
        {0, -1, 0},
        {-1, 5, -1},
        {0, -1, 0}};*/
    kernel = {
        {-1, -4, -6, -4, -1},
        {-4, -16, -24, -16, -4},
        {-6, -24, 476, -24, -6},
        {-4, -16, -24, -16, -4},
        {-1, -4, -6, -4, -1}};

    convolution(matrix, kernel, 256);
}

std::vector<std::vector<std::vector<int>>> padding(std::vector<std::vector<std::vector<int>>> &matrix, const int kernelSize)
{
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
    return pad_matrix;
}

void convolution(std::vector<std::vector<std::vector<int>>> &matrix, const std::vector<std::vector<int>> &kernel, const int kernel_factor)
{
    int m = matrix.size();
    int n = matrix[0].size();
    int d = matrix[0][0].size();

    std::vector<std::vector<std::vector<int>>> new_matrix = matrix;

    std::vector<std::vector<std::vector<int>>> pad_matrix = padding(matrix, kernel.size());

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

    matrix = new_matrix;
}
