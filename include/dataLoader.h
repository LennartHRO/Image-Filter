#include <vector>
#include <opencv2/opencv.hpp>
#include "image.h"

class DataLoader
{
private:
    // Function to convert a Tensor to a image
    // Input: Tensor: Rows x Cols x Channels (RGB)
    // Output: Image
    Image convertMatToImage(const cv::Mat &image);

public:
    // Function to read an image file and return a cv::Mat image
    // Input: argc and argv from main()
    // Output: Image
    Image loadImage(int argc, char **argv);
};