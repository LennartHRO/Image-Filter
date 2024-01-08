#include "image.h"

class Filter {
    public:
        virtual void apply(Image &image) = 0;
};

class InvertFilter : public Filter {
    public:
        void apply(Image &image) override;
};

/* ---------- OLD FILTER ----------
#include <vector>
#include <iostream>

// Function to change the brightness of the image
void change_brightness(std::vector<std::vector<std::vector<int>>> &matrix, int brightness);

// Function to invert the image
void invert_image(std::vector<std::vector<std::vector<int>>> &matrix);

// Function to change the contrast of the image
void change_contrast(std::vector<std::vector<std::vector<int>>> &matrix, float contrast);

// Function to make the image gray
void make_image_gray(std::vector<std::vector<std::vector<int>>> &matrix);

// Function to pad the image
std::vector<std::vector<std::vector<int>>> padding(std::vector<std::vector<std::vector<int>>> &matrix, const int kernelSize);

// Function to perform convolution
void convolution(std::vector<std::vector<std::vector<int>>> &matrix, const std::vector<std::vector<int>> &kernel, const int kernel_factor);

// Function to perform gaussian blur
void gaussian(std::vector<std::vector<std::vector<int>>> &matrix, const int kernelSize);

// Function to perform edge detection
void edge_detection(std::vector<std::vector<std::vector<int>>> &matrix);

// Function to perform sharpening
void sharpen(std::vector<std::vector<std::vector<int>>> &matrix);

*/