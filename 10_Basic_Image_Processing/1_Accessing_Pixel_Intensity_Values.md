# Introduction

:notebook_with_decorative_cover: Before we get into accessing pixel values, we need to remind ourself that OpenCV images are represented by the same structure as matrices as shown in Figure 1. 

**Figure 1** - OpenCV matrix or array coordinate system

![Matrix coordinate system](./images/matrix-coordinate-system.png)

**Image source**: https://mikamustonen.com/2019-06-22-how-to-rotate-an-image-with-opencv.html

:notebook_with_decorative_cover: Figure 1 shows the following: 

1. The origin of this system is the top-left pixel with location `(0,0)`. 
2. The system is `0`-based - meaning we start counting from `0`. 
3. Each pixel represents `1` unit.
4. The y-coordinates which represent the image rows increase downwards, while the x-coordinates (image columns) increase from left to right.
5. The system uses the convention `(y-coordinate, x-coordinate)` when defining the location of a pixel. y-coordinate defines the row of the pixel, and the x-coordinate defines the column.  

:notebook_with_decorative_cover: This system is different from the Cartesian coordinate system which we used in the earlier tutorial on Drawing and Annotation. Cartesian uses `(x-coordinate, y-coordinate)` combination.

## Accessing pixel intensity values

:notebook_with_decorative_cover: In order to get the pixel intensity value, you need to know two things about the image:

1. The data type of the pixel values
2. The number of channels

:notebook_with_decorative_cover: This is because these two pieces of information are important inputs to the template function `at<>()` which we use for accessing intensity values at each pixel location. There are a few things to note about this function:

1. It is a member function of the `cv::Mat` class hence you access it using an object of type `cv::Mat`.
2. Within the documentation there are `12` overloaded functions with various definitions that allow you to access 1D, 2D, 3D matrices, while others allow you to access single-channel or multi-channel images, etc.
3. Each function definition has two versions: 
   * One that returns a constant reference to the pixel value/values, that is `const T&`. Using this version means you cannot alter the pixel value/s.
   * One that returns a non-constant reference to the pixel value/s, that is, `T&`. Using this version means you can alter the pixel value/s.

### Single-channel 2-D images

:notebook_with_decorative_cover: To access pixel values for single-channel 2-D images we use the function definition `T& at<T>(int row, int col)` or `const T& at<T>(int row, int col) const`. `T` is the data type of pixel values in image, `row` is the row/y-coordinate of pixel, `col` is the column/x-coordinate of pixel. Since we are dealing with single-channel images, the returned value is a reference to a single value.

:notebook_with_decorative_cover: The value of `T` that you place within the angle brackets `<T>` depends on the image data type from which you are trying to retrieve the data. The following gives a better insight: 

* If image is of type `CV_8U` then use `cv::Mat.at<uchar>(y,x)`.
* If image is of type `CV_8S` then use `cv::Mat.at<schar>(y,x)`.
* If image is of type `CV_16U` then use `cv::Mat.at<ushort>(y,x)`.
* If image is of type `CV_16S` then use `cv::Mat.at<short>(y,x)`.
* If image is of type `CV_32S` then use `cv::Mat.at<int>(y,x)`.
* If image is of type `CV_32F` then use `cv::Mat.at<float>(y,x)`.
* If image is of type `CV_64F` then use `cv::Mat.at<double>(y,x)`.

:notebook_with_decorative_cover: The following is an example for a single channel gray scale image (type `CV_8UC1`) and pixel location defined by `row` and `column`. The image has been read into a `cv::Mat` object `img`.

```c++
uchar pixelValue = img.at<uchar>(row, column);
```

:notebook_with_decorative_cover: Although the above code works as it should, you will find that if for example the image pixel value was `64` and you try to print `pixelValue` to screen e.g `std::cout << pixelValue`, it will print the character `@`. That is because types such as `unsigned char` (or `uchar`) or `signed char` (or `schar`) are printed as ASCII values, which is not what we want. There are various ways to convert ASC11 values to integers, but it is not easy to remember everytime. The best solution is to use the data type `cv::Scalar` as the return type. OpenCV automatically converts `uchar` or `schar` values to the appropriate values if using `cv::Scalar`. You should also remember from earlier tutorials that `cv::Scalar` can hold `4` values, which can be accessed through indices `0` to `3`. For single-channel images, we return `1` value - which will be stored at index `0` in `cv::Scalar`. To improve the previous code we should write it as follows:

```c++
cv::Scalar pixelValue = img.at<uchar>(row, column)
std::cout << "Pixel value = " << pixelValue[0];
```

:notebook_with_decorative_cover: By taking advantage of the object `cv::Scalar` we can write a function that can return the pixel value of a single-channel image of any data type.

```c++
/**
 * @brief Return the pixel value from a single-channel image
 * 
 * @param image Single-channel image
 * @param type OpenCV data type of pixel values in image e.g. CV_8U or CV_8UC1
 * @param y Row index to find pixel. We start counting indices from '0'. 
 *          The first row is found at the top of the image, and increases 
 *          from top to bottom of image.
 * @param x Column index to fnd pixel. We start counting indices from '0'.
 *          The first column is found on the left of the image, and increases 
 *          from left to right of image. 
 * @return cv::Scalar Pixel value, which will be stored at index '0' 
 *                    of the cv::Scalar object
 */
cv::Scalar pixelValue_C1(const cv::Mat& image, int type, int y, int x)
{
    
   switch (type)
	{
      case CV_8U:
         return image.at<uchar>(y, x);

      case CV_8S:
         return image.at<schar>(y, x);

      case CV_16U: 
         return image.at<ushort>(y, x);

      case CV_16S:
         return image.at<short>(y, x);

      case CV_32S:
         return image.at<int>(y, x);

      case CV_32F:
         return image.at<float>(y, x);

      case CV_64F:
         return image.at<double>(y, x);
                
      default: // Use type 'double' as it can hold any of the above types
         return image.at<double>(y, x);
	}
}
```

:notebook_with_decorative_cover: Since it is likely that we will re-use the above function we will add it to our library we are building. We will add the function under the namespace `BasicImageProcessing`. Remember to add the function declaration in the header file `Example-Code/include/UtilityFunctions/utility_functions.h` and the full definition in the source file `Example-Code/src/UtilityFunctions/utility_functions.cpp`.

:notebook_with_decorative_cover: As mentioned earlier on, we can also use the `at<>()` function to alter/change the pixel value by simply placing this function on the left-hand side of the equal sign `=` and the new pixel value on the right-hand side. This is how you can alter a non-const reference value. In the following example we alter the pixel value at location `(row, column)` to `128`. The `cv::Mat` image object `img` must NOT be a const object.

```c++
img.at<uchar>(row, column) = 128;
```

:notebook_with_decorative_cover: If you try to alter the pixel value using a value out of range of the data type, OpenCV will use **saturation casting** to convert your input to the appropriate range. We have already extensively covered saturation casting in an earlier tutorial. 
