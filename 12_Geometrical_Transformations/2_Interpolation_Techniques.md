# Introduction

:memo: In the last chapter, we discussed inverse mapping as the most preferred technique for image geometrical transformation. Within that discussion we mentioned that during inverse mapping, a pixel in the output image may map to a non-integer coordinate in the input image, meaning we have to estimate its new color or intensity value using data from the input image. **Interpolation** is the technique used for estimating the pixel values in the output image using data from neighbourhood pixels in the input image.

:memo: There are a number of interpolation techniques - the choice of which, involves a trade-off between speed and image quality. In the following sub-sections, we will look in detail at some of the most common interpolation methods we use in image geometrical transformation. 

## Nearest-neighbor interpolation

:memo: This is the simplest and fastest interpolation method. For each pixel in the destination image, it finds the single closest/nearest pixel in the source image and copies its intensity value.

:memo: In image processing, nearest neighbor interpolation is used for tasks like resizing or resampling, where new pixel values need to be determined for the new, larger image. The process works as follows: 

1. Map output to input coordinates: For every new pixel in the output image, its coordinates are mapped back to a corresponding location in the original input image.

2. Find the nearest neighbor: The algorithm identifies the single closest pixel in the original image to that mapped location.

3. Assign the value: The value of the nearest neighbor pixel is assigned to the new output pixel. 

:memo: Figure 1 is a simplistic view of how the nearest neighbour interpolation technique estimates values in the destination image.

<p style="text-align: center;"><b>Figure 1:</b> A simplistic view of the nearest neighbour interpolation technique when enlarging an image</p>

<p align = "center">
    <img src="./images/nearest-neighbour.png"
        alt="Inverse mapping spatial transformation">
</p>


:memo: If you look closely at the final pixel values in Figure 1 you will notice that the nearest neighbour technique tends to replicate the input image pixels into blocks in the enlarged image. The area around each original data point (or pixel) becomes a constant region.

:memo: The nearest neighbour technique has the following advantages:

* **Speed and simplicity**: As the most basic interpolation method, it is computationally very efficient, making it ideal for real-time applications such as video games and image previews.

* **Preserves pixel values**: Unlike more complex methods that calculate an average, nearest neighbor interpolation retains the original pixel values. This is beneficial for applications like medical imaging or satellite imagery, where data accuracy is critical.

* **Maintains sharp edges**: This method does not blur or smooth image details. It is particularly effective for images with sharp edges, text, or geometric elements. 

:memo: While computationally cheap, this technique has the following downsides:

* **Poor image quality**: When scaling images, especially for magnification, the replication of pixels can create a "blocky" or "pixelated" appearance with jagged edges. This can lead to a significant loss of visual quality.

* **Limited accuracy**: Since the algorithm does not consider the values of other neighboring points, it can produce less accurate results for complex datasets compared to more advanced techniques.

* **Not suitable for continuous data**: Because it creates step-like, discontinuous transitions, the method is not suitable for interpolating continuous data sets or functions.

:memo: Common applications of nearest neighbour interpolation include:

1. **Image resizing**: Resampling images to new dimensions, especially in applications where speed is prioritized over image quality.

2. **Real-time 3D rendering**: Selecting color values for textured surfaces in computer graphics.

3. **Geographic information systems (GIS)**: Creating raster data grids from scattered data points, such as with weather or elevation data.
