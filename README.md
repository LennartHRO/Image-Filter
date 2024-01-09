# 52: Image Filter Program
This C++ program allows you to apply various image filters to an input picture. The supported filters include inversion, brightness adjustment, contrast adjustment, grayscale conversion, fuzzy/gaussian filter, edge detection and sharpening.
### Table of Contents

- [Prerequisites](#prerequisites)
  - [Install OpenCV on Ubuntu/Linux](#install-opencv-on-ubuntulinux)
  - [Install OpenCV on Windows](#install-opencv-on-windows)
- [Getting Started](#getting-started)
  - [Run the software with cmake & make (tested on Ubuntu/Linux)](#run-the-software-with-cmake--make--tested-on-ubuntulinux)
  - [Run the software in VSC on Windows](#run-the-software-in-vsc-on-windows)
  - [First steps](#first-steps)
- [Filter](#filter)
  - [Change Brightness](#change-brightness)
  - [Change Contrast](#change-contrast)
  - [Invert Image](#invert-image)
  - [Gray Image](#gray-image)
  - [Fuzzy (Gaussian) Filter](#fuzzy-gaussian-filter)
  - [Box Blur](#box-blur)
  - [Super Filter](#super-filter)

## Prerequisites

Before running the program, ensure that you have OpenCV installed on your system. Even thoug the software not uses OpenCV to convert the images, we need OpenCV to load and to display the images. Follow the instructions below to install OpenCV.

### Install OpenCV on Ubuntu/Linux

``` bash
sudo apt-get update
sudo apt-get install libopencv-dev
```

### Install OpenCV on Windows
Follow the instructions on the [OpenCV official website](https://docs.opencv.org/master/d3/d52/tutorial_windows_install.html)


## Getting started

### Run the software with cmake & make 
_(testet on Ubuntu/Linux)_

First navigate into the project folder where the Cmake file is located. Here run the follwig lines in the terminal to buid an executable file:

``` bash
cmake .
make
```
Then run the software with the following command:

``` bash
./52 <name (and location) of your image file>
```

### Run the software in VSC on Windows

An alternative to execute the program in VSC is configuring the project by using the shortcut Ctrl + Shift + P and then searching for the command "CMake: Configure". After selecting the compiler "Visual Studio Build Tools XXXX Release - x86_amd64" a new build folder will be created as well as a button "build" on the bottom bar on the left (or Ctrl+Shift+P "CMake: Build"). After building the project the 52.exe file will be created in the Debug folder inside the build folder. So you can run the software with the following command:

``` bash
 ./build/Debug/52.exe  ./Examples/"Name of your image file"
```

Those steps are also explained in this video: https://youtube.com/watch?v=m9HBM1m_EMU

### First steps

Now you have to type a charcter to apply the respective filte to the image. following options are allowed:

- **Invert (i):** Inverts the colors of the image.
- **Brightness (b):** Adjusts the brightness of the image.
- **Contrast (c):** Adjusts the contrast of the image.
- **Grayscale (g):** Converts the image to grayscale.
- **Fuzzy/Gaussian Filter (f):** Applies a fuzzy/Gaussian filter to the image.
- **Box Blur (l):** Applies a box linear filter to the image.
- **Super Filter (x):** Provides the possibility of combining multiple filters together.
- **Save (s):** Saves the current image with a new name.
- **Quit (q):** Exits the program.
If the selected filter needs some additional information it will ask you to enter them. After the filter has succesfully be applied, you are able to apply another filter. To exit the program type ``q``.

Under this Link you can find a demo: <https://www.loom.com/share/c9f261ffe2b64b16a7a6aaefec6a565d?sid=50122a95-986f-4302-91a6-c862d9a17669> .

## Filter

### Change Brightness
This filter adjusts the overall brightness of the image. Positive values increase brightness, while negative values decrease it.
<table>
  <tr>
    <td>Original Image</td>
    <td>Brightness = 100</td>
  </tr>
  <tr>
    <td><img src="Examples/muenchen.jpg" alt="Original Image" width="400"/></td>
    <td><img src="Examples/0_brightness100.jpg" alt="Brightness = 100" width="400"/></td>
  </tr>
</table>

### Change Contrast
Higher contrast values enhance the distinction, while lower values reduce it.
<table>
  <tr>
    <td>Original Image</td>
    <td>Contrast = 2</td>
  </tr>
  <tr>
    <td><img src="Examples/muenchen.jpg" alt="Original Image" width="400"/></td>
    <td><img src="Examples/0_contrast2.jpg" alt="Contrast = 2" width="400"/></td>
  </tr>
</table>

### Invert Image
The inversion filter transforms the colors of the image by replacing each color value with its opposite on the color scale. This results in a negative-like effect.

<table>
  <tr>
    <td>Original Image</td>
    <td>Edited Image</td>
  </tr>
  <tr>
    <td><img src="Examples/muenchen.jpg" alt="Original Image" width="400"/></td>
    <td><img src="Examples/0_inverted.jpg" alt="Edited Image" width="400"/></td>
  </tr>
</table>

### Gray Image
The grayscale filter converts the image to shades of gray, removing color information. 

<table>
  <tr>
    <td>Original Image</td>
    <td>Edited Image</td>
  </tr>
  <tr>
    <td><img src="Examples/muenchen.jpg" alt="Original Image" width="400"/></td>
    <td><img src="Examples/0_gray.jpg" alt="Edited Image" width="400"/></td>
  </tr>
</table>

### Fuzzy (Gaussian) Filter
The Fuzzy or Gaussian filter applies a convolution operation using a kernel to smooth the image. This can reduce noise and blur details. The kernel size determines the extent of blurring, with larger sizes producing more pronounced effects. The examples show the impact of different kernel sizes.
<table>
  <tr>
    <td>Original Image</td>
    <td>Kernel size = 5</td>
    <td>Kernel size = 21</td>
  </tr>
  <tr>
    <td><img src="Examples/muenchen.jpg" alt="Original Image" width="400"/></td>
    <td><img src="Examples/0_fuzzy5.jpg" alt="kernel size = 5" width="400"/></td>
    <td><img src="Examples/0_fuzzy21.jpg" alt="kernel size = 21" width="400"/></td>
  </tr>
</table>

You can find a good explanation of the gaussian filter in this video: <https://youtu.be/-LD9MxBUFQo?si=P5Uy1HH7WalOFtLM>.

### Box Blur
A Box linear filter (also known as a box blur) is a form of a low-pass ("blurring") filter in which the value of each pixel of the resulting image is equal to the average value of its neighboring pixels. Similar to the Fuzzy/Gaussian filter, the blurring effect increases with larger kernel sizes.

<table>
  <tr>
    <td>Original Image</td>
    <td>Kernel size = 5</td>
    <td>Kernel size = 21</td>
  </tr>
  <tr>
    <td><img src="Examples/muenchen.jpg" alt="Original Image" width="400"/></td>
    <td><img src="Examples/0_box5.jpg" alt="kernel size = 5" width="400"/></td>
    <td><img src="Examples/0_box21.jpg" alt="kernel size = 21" width="400"/></td>
  </tr>
</table>

### Super Filter
The Super Filter makes it possible to combine and execute the above-mentioned filters in any combination. The examples show a combination of the inversion filter and the Fuzzy/Gaussian filter (kernel size = 5) and a combination of the grayscale filter and the Box linear filter (kernel size = 5).  

<table>
  <tr>
    <td>Original Image</td>
    <td>Inverted & Fuzzy</td>
    <td>Gray & Box Blur</td>
  </tr>
  <tr>
    <td><img src="Examples/muenchen.jpg" alt="Original Image" width="400"/></td>
    <td><img src="Examples/0_super_inverted_fuzzy5.jpg" alt="inverted & fuzzy" width="400"/></td>
    <td><img src="Examples/0_super_gray_box5.jpg" alt="gray & box" width="400"/></td>
  </tr>
</table>





