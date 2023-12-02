#include "filters.h"

#include <vector>
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
    int kernel_factor;
    if (kernelSize == 3)
    {
        kernel = {
            {1, 2, 1},
            {2, 4, 2},
            {1, 2, 1}};
        kernel_factor = 16;
    }
    else if (kernelSize == 5)
    {
        kernel = {
            {1, 4, 6, 4, 1},
            {4, 16, 24, 16, 4},
            {6, 24, 36, 24, 6},
            {4, 16, 24, 16, 4},
            {1, 4, 6, 4, 1}};
        kernel_factor = 256;
    }

    convolution(matrix, kernel, kernel_factor);
}

void convolution(std::vector<std::vector<std::vector<int>>> &matrix, const std::vector<std::vector<int>> &kernel, const int kernel_factor)
{
    int m = matrix.size();
    int n = matrix[0].size();
    int d = matrix[0][0].size();

    // edge needed to avoid border
    int edge = kernel.size() / 2;
    // matrix rows
    for (int i = edge; i < m - edge; ++i)
    {
        // matrix columns
        for (int j = edge; j < n - edge; ++j)
        {
            // matrix depth
            for (int k = 0; k < d; ++k)
            {
                int sum_pixel = 0;
                // kernel rows
                for (int ki = -edge; ki <= edge; ++ki)
                {
                    // kernel columns
                    for (int kj = -edge; kj <= edge; ++kj)
                    {
                        // convolution
                        sum_pixel = sum_pixel + matrix[i - ki][j - kj][k] * kernel[ki + edge][kj + edge];
                    }
                }
                matrix[i][j][k] = sum_pixel / kernel_factor;
            }
        }
    }
}