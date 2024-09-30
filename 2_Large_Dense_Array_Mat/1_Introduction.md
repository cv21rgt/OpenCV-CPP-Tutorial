## The cv::Mat Class and N-Dimensional Arrays

:notebook_with_decorative_cover: So far we have looked at OpenCV core types (cv::Point, cv::Scalar, cv::Vec, cv::Matx, cv::Size etc) that are optimized for use with only a few values. When it comes to storing large arrays we need a more suitable data structure, and that is **cv::Mat**. 

:notebook_with_decorative_cover: The <a href = "https://docs.opencv.org/4.8.0/d3/d63/classcv_1_1Mat.html">cv::Mat</a> class represents an n-dimensional dense numerical array. In this context, **dense** means that for every entry in the array, there is a data value stored in memory corresponding to that entry, even if that entry is zero. As we dive deeper into cv::Mat you will learn that this class can be used to represent `1, 2, 3, ...N` dimensional data structures. These multi-dimensional large data structures can be either single-channel (e.g. 100 x 100 matrix) or multi-channel (e.g. an image whose width is 500 pixels and height is 500 pixels and has 3 color channels red, green and blue).

:notebook_with_decorative_cover: **cv::Mat** is actually a base class from which <a href = "https://docs.opencv.org/4.8.0/df/dfc/classcv_1_1Mat__.html">cv::Mat_<\_Tp></a> template classes can be derived from. Here **\_Tp** is the data type, which can be double, float, uchar etc. You can use cv::Mat or if you want to be more specific use the template definition cv::Mat_<\_Tp>.

:notebook_with_decorative_cover: In a one-dimensional array, the elements are stored in sequential order.

:notebook_with_decorative_cover: In a two-dimensional array, the data is organized into rows, and each row appears one after the other in memory. You will mostly deal with 2-D arrays in OpenCV. The 2-D arrays will with very few exceptions have either 1 channel (e.g. grayscale images) or 3 channels (e.g. color images). When laid out in memory, the rows of multichannel arrays may not be absolutely sequential; there may be small gaps that buffer each row before the next. This padding or gaps will always occur at the end of full rows. 

:notebook_with_decorative_cover: For three-dimensional arrays, the data is stored as planes, each plane is filled out row by row, and then the planes are packed one after the other.

## Crucial information about cv::Mat

:notebook_with_decorative_cover: **cv::Mat** is basically a class with two data parts: 
1. the **matrix header** (containing information such as the size of the matrix/array, the method used for storing, at which address is the matrix stored, and so on) and, 
2. a **pointer to the matrix** containing the pixel values (taking any dimensionality depending on the method chosen for storing) . The matrix header size is constant, however the size of the matrix itself may vary from array to array and usually is larger by orders of magnitude.

:notebook_with_decorative_cover: You have to remember that **OpenCV** is an image processing library. It contains a large collection of image processing functions. To solve a computational challenge, most of the time you will end up using multiple functions of the library. Because of this, passing images to functions is a common practice. We should not forget that we are talking about image processing algorithms, which tend to be quite computational heavy. The last thing you want to do is further decrease the speed of your program by making unnecessary copies of potentially large images.

:notebook_with_decorative_cover: To tackle this issue OpenCV uses a **reference counting system**. The idea is that each **cv::Mat** object has its own header, however a matrix may be shared between two **cv::Mat** objects by having their matrix pointers point to the same address. Moreover, the copy operators in OpenCV will only copy the headers and the pointer to the large matrix, not the data itself.

:notebook_with_decorative_cover: Now you may ask – if the matrix itself may belong to multiple **cv::Mat** objects, who takes responsibility for cleaning it up when it's no longer needed? The short answer is: the last object that used it. This is handled by using a **reference counting mechanism**. Whenever somebody copies a header of a **cv::Mat** object, a counter is increased for the matrix. Whenever a header is cleaned, this counter is decreased. When the counter reaches zero the matrix is freed from memory. 

### cv::Mat Data Types

:notebook_with_decorative_cover: When you create a **cv::Mat** object you have to specify:

1. The number of bits occupied by each array element. This can be 8, 16, 32 or 64-bit. 
2. The fundamental data type of the array elements. This is represented by a single uppercase letter, **U** (unsigned integer), **S** (signed integer) and **F** (float). There is no letter for type double, and decimal values should use type float. 
3. The number of channels the array has. These mainly range from 1 to 4. 

:notebook_with_decorative_cover: All this information is put together using the syntax: **CV_{8, 16, 32, 64}{U, S, F}C{1, 2, 3, 4}**. For example `CV_32FC3` would imply a **32-bit floating-point three-channel array**. If you are dealing with arrays that have 1 channel, you can leave out the last bit with **C{1, 2, 3}**. For example **CV_8U** would imply an array whose values are 8-bit unsigned integers (i.e. range of 0 to 255). You will start to include the number of channels in your data type when dealing with image data.

:notebook_with_decorative_cover: Let's have a detailed look at what the data types actually mean:
1. **8U** - 8-bit unsigned integers with range (0 to 255)
2. **8S** - 8-bit signed integers with range (-127 to 128)
3. **16S** - 16-bit signed integers with range (-32,768 to 32,767)
4. **16U** - 16-bit unsigned integers with range (0 to 65,535)
5. **32S** - 32-bit signed integers with range (-2,147,483,648 to 2,147,483,647)
6. **32F** - 32-bit decimal values of type float with range (-3.40282347E+38 to 3.40282347E+38)
7. **64F** - 64-bit decimal values of type float with range (-1.797693134862315E+308 to 1.797693134862315E+308)

:notebook_with_decorative_cover: cv::Mat data types are actually stored as integer types within OpenCV. You will notice this if you look at the constructors for cv::Mat objects as the data type for **type** is **int**, short for integer. The following figure can help you identify which integer value represents which data type.

![Image showing OpenCV data types](./images/opencv_data_types.png)

:notebook_with_decorative_cover: Using the above figure, **CV_32F** or **CV_32FC1** is represented by the integer value **5**, **CV_8UC3** is represented by the integer value **16**, **CV_8U** or **CV_8UC1** is represented by the integer value **0**. This means if you were to ask OpenCV what data type is held by a cv::Mat object using a function like `type()`, OpenCV will return the integer value and it will be up to you to know the full description of the data type. The problem with these integer values is they are not descriptive and do not give you a full picture of a cv::Mat objects data type hence they are not used that often unless you offer a full explanation. In addition, there are too many integer values to remember. To help, I have created a function with the signature (`std::string_view openCVDescriptiveDataType(int value)`) that I can use to find out the full description of a data type given its integer value equivalent. This function has been added to a header and source files with the names **utility_functions.h** and **utility_functions.cpp**. As we go along our journey, we will add more utility functions or classes to these files. At the end we can build a library that can be used with any other computer vision project. Check the **include** and **src** folders for these files.


### Creating cv::Mat objects

:notebook_with_decorative_cover: The cv::Mat class has several constructors that allow for a variety of ways to create an array. These constructors fall into a number of categories:
1. Default constructor
2. Constructors that take the shape of an array, its data type and initialization values.
3. Constructors that copy data from other data containers such as std::vector, std::array, cv::Vec, cv::Matx, cv::Point etc.
4. Constructors for creating *n*-dimensional arrays (n > 2) and require you to specify the number of dimensions and pass in an array of integers specifying the size of each of the dimensions.

**N.B:** The following examples have small values for the rows and columns for illustration purposes only. In future examples involving images, your **cv::Mat** objects will contain rows and columns in their hundreds or even thousands hence **large dense arrays**.

**Example 1**: Create 2-D cv::Mat objects using default contructors. Using default constructors is usually accompanied by two other functions that help you to allocate memory for your cv::Mat object as well as fill it with data values other than `0` values.

1. The function `create()` - allocates array data so it matches number of rows, columns and data type of cv::Mat array. It is an overloaded function with the following definitions:
    * `void create(int rows, int cols, int type)` - `rows` is the number of rows of the array, `cols` is the number of columns and `type` is the data type of array elements e.g. `CV_8UC1` or use the integer equivalent value `0`.
    * `void create(cv::Size size, int type)` - rows and columns are provided as cv::Size object e.g. `cv::Size(cols, rows)`. Don't get confused here, remember a cv::Size contains width & height - for 2D arrays, width is represented by the number of columns and height by the number of rows.
    * `void create(const std::vector<int>& sizes, int type)` - rows and columns are provided as std::vector values e.g. `const std::vector<int> v {rows, cols};`
    * `void create(int ndims, const int* sizes, int type)` - `ndims` is the array dimensionality, `sizes` is a C-style array of integers specifying array shape e.g. `const int sizes[] {rows, cols}`.
2. `cv::Mat& setTo(cv::InputArray value, cv::InputArray mask = cv::noArray())` - This functions sets all or some of the array elements to the specified `value`. Because you can only set array elements to one value, this limits the use of this function. `mask` defines a region of interest - which we will start to deal with when dealing with actual images. For now, use the default value provided. The data type `cv::InputArray` is an aliase for all OpenCV data types that can be used to provide input data to a function e.g. cv::Scalar, cv::Point, cv::Size, cv::Vec etc. It also includes std::vector for some functions. We will discuss this aliase and others in a seperate topic and you will see how special it is.

```c++
#include "opencv2/core.hpp"
#include <iostream>
#include <vector>

int main()
{
    //                                 Use Default Constructor
    //                                 =======================

    // Use a default constructor to create a cv::Mat arrays
    cv::Mat default_m;
    cv::Mat default_m1;
    cv::Mat default_m2;
    cv::Mat default_m3;                  

    //    You can then use the functions create() & setTo() 
    //    to assign size, data and data type

    // 1. Use the function 'void create(int rows, int cols, int type)'

    // Create 2D array that has 3 rows and 10 columns. 
    // The array has 1 Channel
    // Primitive data type is 32-bit floats
    default_m.create(3, 10, CV_32F);    

    // We will use cv::Scalar to set all the values in the array to 1.5
    default_m.setTo(cv::Scalar(1.5f));

    std::cout << "\ncv::Mat array that has 3 rows and 10 columns. " 
              << "\nPrimitive data type is 32-bit floats. " 
              << "\nAll values have been set to 1.5 = \n" << default_m << '\n';

    // 2. Use the function 'void create(cv::Size size, int type)'

    // Create 2D array that has 5 rows and 6 columns. 
    // The array has 1 Channel
    // Primitive data type is 8-bit unsigned
    default_m1.create(cv::Size(6, 5), CV_8U);
    default_m1.setTo(cv::Scalar(10)); // All values are set to '10'
    std::cout << "\ncv::Mat array that has 5 rows and 6 columns. " 
              << "\nPrimitive data type is 8-bit unsigned integers. " 
              << "\nAll values have been set to 10 = \n" << default_m1 << '\n';

    // 3. Use the function 'void create(const std::vector<int>& sizes, int type)'

    // Create 2D array that has 2 rows and 12 columns. 
    // The array has 1 Channel
    // Primitive data type is 64-bit floats
    const std::vector<int> shape {2, 12};
    default_m2.create(shape, CV_64F);
    default_m2.setTo(cv::Scalar(0.05)); // All values are set to '0.05'
    std::cout << "\ncv::Mat array that has 2 rows and 12 columns. " 
              << "\nPrimitive data type is 64-bit floats. " 
              << "\nAll values have been set to 0.05 = \n" << default_m2 << '\n';

    // 4. Use the function 'void create(int ndims, const int* sizes, int type)'
    // Create 2D array that has 3 rows and 4 columns. 
    // The array has 1 Channel
    // Primitive data type is 16-bit signed
    const int ndims {2};
    const int sizes[] {3, 4};
    default_m3.create(ndims, sizes, CV_16S);
    default_m3.setTo(cv::Scalar(12)); // All values set to `12`
    std::cout << "\ncv::Mat array that has 3 rows and 4 columns. " 
              << "\nPrimitive data type is 16-bit signed integers. " 
              << "\nAll values have been set to 12 = \n" << default_m3 << '\n';

    return 0;
}
```

**Output**

    cv::Mat array that has 3 rows and 10 columns. 
    Primitive data type is 32-bit floats. 
    All values have been set to 1.5 = 
    [1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5;
    1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5;
    1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5]

    cv::Mat array that has 5 rows and 6 columns. 
    Primitive data type is 8-bit unsigned integers. 
    All values have been set to 10 = 
    [ 10,  10,  10,  10,  10,  10;
    10,  10,  10,  10,  10,  10;
    10,  10,  10,  10,  10,  10;
    10,  10,  10,  10,  10,  10;
    10,  10,  10,  10,  10,  10]

    cv::Mat array that has 2 rows and 12 columns. 
    Primitive data type is 64-bit floats. 
    All values have been set to 0.05 = 
    [0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05;
    0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05]

    cv::Mat array that has 3 rows and 4 columns. 
    Primitive data type is 16-bit signed integers. 
    All values have been set to 12 = 
    [12, 12, 12, 12;
    12, 12, 12, 12;
    12, 12, 12, 12]

**Example 2**: Create 2-D cv::Mat objects by supplying size of array, data type and initialization values

```c++
#include "opencv2/core.hpp"
#include <iostream>
#include <vector>

int main()
{
    //                             Use Constructors that accept array size, data type and initialization values
    //                             ============================================================================

    // 1. Use the constructor cv::Mat(int rows, int cols, int type, const cv::Scalar& s) 
    //    Array will have 2 rows and 3 columns. 
    //    Data type is 8-bit unsigned integers (0 - 255)
    //    All values have been set to 15
    const int rows = 2;
    const int cols = 3;        
    const cv::Mat m1 {rows, cols, CV_8U, cv::Scalar(15)}; 
    std::cout << "\ncv::Mat array that has 2 rows and 3 columns. " 
              << "\nData type is 8-bit unsigned integers " 
              << "\nAll values have been set to 15 = \n" 
              << m1 << '\n';

    
    // 2. Use the constructor cv::Mat(cv::Size size, int type, const cv::Scalar& s)
    const cv::Size s {10, 3}; // This sets columns = 10 & rows = 3
    const cv::Mat  m2 {s, CV_32F, cv::Scalar(2.5f)};
    std::cout << "\ncv::Mat array with 3 rows and 10 columns "
              << "\nData type is 32-bit float " 
              << "\nAll values set to 2.5 = \n" 
              << m2 << '\n';

    // 3. Use the constructor cv::Mat(int ndims, const int* sizes, int type, const cv::Scalar& s)
    //    Create 2D array that has 3 rows and 4 columns. 
    //    The array has 1 Channel
    //    Primitive data type is 16-bit signed
    const int no_dims {2};
    const int array_size[] {3, 4};
    const cv::Mat m3 {no_dims, array_size, CV_16S, cv::Scalar(16)};
    std::cout << "\ncv::Mat array that has 3 rows and 4 columns. " 
              << "\nPrimitive data type is 16-bit signed integers. " 
              << "\nAll values have been set to 16 = \n" << m3 << '\n';

    // 4. Use the constructor cv::Mat(const std::vector<int>& sizes, int type, const cv::Scalar& s)
    const std::vector<int> array_shape {2, 12};
    const cv::Mat m4 {array_shape, CV_64F, cv::Scalar(3.14)};
    std::cout << "\ncv::Mat array that has 2 rows and 12 columns. " 
              << "\nPrimitive data type is 64-bit floats. " 
              << "\nAll values have been set to 3.14 = \n" << m4 << '\n';


    return 0;
}
```

**Output**

    cv::Mat array that has 2 rows and 3 columns. 
    Data type is 8-bit unsigned integers 
    All values have been set to 15 = 
    [ 15,  15,  15;
    15,  15,  15]

    cv::Mat array with 3 rows and 10 columns 
    Data type is 32-bit float 
    All values set to 2.5 = 
    [2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 2.5;
    2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 2.5;
    2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 2.5]

    cv::Mat array that has 3 rows and 4 columns. 
    Primitive data type is 16-bit signed integers. 
    All values have been set to 16 = 
    [16, 16, 16, 16;
    16, 16, 16, 16;
    16, 16, 16, 16]

    cv::Mat array that has 2 rows and 12 columns. 
    Primitive data type is 64-bit floats. 
    All values have been set to 3.14 = 
    [3.14, 3.14, 3.14, 3.14, 3.14, 3.14, 3.14, 3.14, 3.14, 3.14, 3.14, 3.14;
    3.14, 3.14, 3.14, 3.14, 3.14, 3.14, 3.14, 3.14, 3.14, 3.14, 3.14, 3.14]
