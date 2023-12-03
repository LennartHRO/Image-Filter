#include <vector>
#include <iostream>

void change_brightness(std::vector<std::vector<std::vector<int>>> &matrix, int brightness);

void invert_image(std::vector<std::vector<std::vector<int>>> &matrix);

void change_contrast(std::vector<std::vector<std::vector<int>>> &matrix, float contrast);

void make_image_gray(std::vector<std::vector<std::vector<int>>> &matrix);

std::vector<std::vector<std::vector<int>>> padding(std::vector<std::vector<std::vector<int>>> &matrix, const int kernelSize);

void convolution(std::vector<std::vector<std::vector<int>>> &matrix, const std::vector<std::vector<int>> &kernel, const int kernel_factor);

void gaussian(std::vector<std::vector<std::vector<int>>> &matrix, const int kernelSize);

void mod_gaussian(std::vector<std::vector<std::vector<int>>> &matrix, const int kernelSize);

void edge_detection(std::vector<std::vector<std::vector<int>>> &matrix);

void sharpen(std::vector<std::vector<std::vector<int>>> &matrix);