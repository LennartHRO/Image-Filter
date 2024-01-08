#include <vector>
#include <opencv2/opencv.hpp>

class Image{
    private:
        std::vector<std::vector<std::vector<int>>> _imageData;
        cv::Mat convertImageDataToMat() const;

    public:
        Image(std::vector<std::vector<std::vector<int>>> imageData);
        void showImage() const;
        void saveImage() const;
};