#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <opencv2/opencv.hpp>

// The Image class encapsulates image data and provides functionality
// to display and save images using the OpenCV library.
class Image
{
private:
    // _imageData stores the image data in a 3D vector format.
    // Each pixel is represented by a vector of three integers (presumably RGB values).
    // Format: Rows x Cols x Channels (RGB)
    std::vector<std::vector<std::vector<int>>> _imageData;

    // convertImageDataToMat is a private method that converts _imageData
    // into an OpenCV Mat object. This method is used internally by other
    // public methods to interact with OpenCV functionalities.
    cv::Mat convertImageDataToMat() const;

public:
    // Constructor: Initializes an Image object with given image data.
    // imageData: 3D vector representing the image data. (Rows x Cols x Channels (RGB))
    Image(std::vector<std::vector<std::vector<int>>> imageData);

    // showImage displays the image in a window using OpenCV's imshow function.
    // The window will display until it is manually closed by the user.
    void showImage() const;

    // saveImage saves the image to a file named 'image.jpg' in the current directory.
    // The image is saved using OpenCV's imwrite function.
    void saveImage() const;

    // getImageData returns the image data as a 3D vector.
    std::vector<std::vector<std::vector<int>>> getImageData() const;

    // setImageData sets the image data to the given 3D vector.
    void setImageData(std::vector<std::vector<std::vector<int>>> imageData);
};

#endif