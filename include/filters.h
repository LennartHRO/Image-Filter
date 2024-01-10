#ifndef FILTERS_H
#define FILTERS_H
#include "image.h"

// Abstract base class for filters
class Filter
{
public:
    // Pure virtual function for applying the filter to an image
    virtual void apply(Image &image) = 0;

    // Virtual function for configuring the filter, can be overridden (but not a must)
    // This function is called afer the filter is created
    // Here the user is asked to provide the necessary parameters for the filter
    // If the filter does not require any parameters, this empty function can be used
    virtual void configure();
};

// Invert filter class
class InvertFilter : public Filter
{
public:
    void apply(Image &image) override;
};

// Brightness filter class
class BrightnessFilter : public Filter
{
private:
    // Private member to store brightness value
    int _brightness;

public:
    void apply(Image &image) override;
    void configure();
    BrightnessFilter();
};

// Contrast filter class
class ContrastFilter : public Filter
{
private:
    // Private member to store contrast value
    float _contrast;

public:
    void apply(Image &image) override;
    void configure() override;
    ContrastFilter();
};

// Gray filter class
class GrayFilter : public Filter
{
public:
    void apply(Image &image) override;
};

// Convolution filter class, inherits from Filter and serves as a base for convolution-based filters
class ConvolutionFilter : public Filter
{
private:
    // Private method for padding the image
    void pad(Image &image, const int kernelSize);

protected:
    // Method for performing convolution
    void convolve(Image &image, const std::vector<std::vector<int>> &kernel, const int kernel_factor);

public:
    virtual void apply(Image &image) = 0;
};

// Gaussian filter class
class GaussianFilter : public ConvolutionFilter
{
private:
    // Private member to store kernel size
    int _kernelSize;

public:
    void apply(Image &image) override;
    void configure() override;
    GaussianFilter();
};

// Box linear filter class
class BoxBlur : public ConvolutionFilter
{
private:
    // Private member to store kernel size
    int _kernelSize;

public:
    void apply(Image &image) override;
    void configure() override;
    BoxBlur();
};

// This filter has the ability to apply multiple filters to an image at once
class SuperFilter : public Filter
{
private:
    // Private member to store all the filters which should be applied when calling apply()
    std::vector<std::unique_ptr<Filter>> _filters;

public:
    void apply(Image &image) override;
    void configure() override;
    SuperFilter();
};

#endif