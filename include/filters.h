#include <vector>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

void change_brightness(std::vector<std::vector<std::vector<int>>> &matrix, int brightness);

void invert_image(std::vector<std::vector<std::vector<int>>> &matrix);

void change_contrast(std::vector<std::vector<std::vector<int>>> &matrix, float contrast);

void make_image_gray(std::vector<std::vector<std::vector<int>>> &matrix);

void write_img(vector<vector<vector<int>>> &matrix, string saveimage);

void convolution(std::vector<std::vector<std::vector<int>>> &matrix, const std::vector<std::vector<int>> &kernel, const int kernel_factor);

void gaussian(std::vector<std::vector<std::vector<int>>> &matrix, const int kernelSize);