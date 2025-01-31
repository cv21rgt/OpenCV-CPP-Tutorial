## Other cv::Mat Functions

:notebook_with_decorative_cover: So far we have discussed some of the members of the cv::Mat class. However, there are some which we left out, but are very important in your daily OpenCV programming.

### Convert array values from one data type to another

:notebook_with_decorative_cover: Sometimes you want to change the data type of values in a cv::Mat array to another type. There are two member functions we can take advantage of: 

1. `void convertTo(cv::OutputArray m, int rtype, double alpha=1, double beta=0) const` - Converts an array to another data type with optional scaling. The parameters are: 

* `m` -	output matrix/array - this can be any of OpenCV types as long as it can handle the new array; if it does not have a proper size or type before the operation, it is reallocated.
* `rtype` -	desired output matrix type or, rather, the depth since the number of channels are the same as the input has; if rtype is negative, the output matrix will have the same type as the input.
* `alpha` -	optional scale factor.
* `beta` -	optional delta added to the scaled values. 

2. `void assignTo(cv::Mat& m, int type=-1) const` - Converts a cv::Mat array to another data type **without** optional scaling. `m` is the destination cv::Mat array and `type` is the desired destination array depth (or -1 if it should be the same as the source type). 

**Example 1**

```c++
#include "opencv2/core.hpp"
#include "UtilityFunctions/utility_functions.h"  // Header file with our own functions we have written
#include <iostream>

int main()
{
    // 1. How to convert array values from one data type to another

    // Create a 3x3, 3-channel 2D array with data type CV_64F
    cv::Mat m0 {3, 3, CV_64FC3, cv::Scalar(1.2f, 2.5f, 0.4f)}; 
    std::cout << "\nm0 = \n" << m0 << '\n';    

    // We will use the function 'openCVDescriptiveDataType()' from our library
    // to display a more descriptive data type
    std::cout << "\nm0 data type = " << CPP_CV::General::openCVDescriptiveDataType(m0.type()) << '\n';
    
    // a) Convert data type from CV_64F to CV_8S  
    //    This should get rid of decimal values
    cv::Mat m3;
    m0.convertTo(m3, CV_8SC3); 
    std::cout << "\nm3 (data type converted from CV_64F to CV_8S) = \n" << m3 << '\n';

    std::cout << "\nm3 data type = " << CPP_CV::General::openCVDescriptiveDataType(m3.type()) << '\n';

    // b) Convert data type from CV_64F to CV_8S
    //    We will scale the values by a scale factor of 2
    //    We will also add the value '1' to the scaled values

    cv::Mat m4;
    double alpha {2};
    double beta {1};
    m0.convertTo(m4, CV_8SC3, alpha, beta);
    std::cout << "\nm4 (data type converted from CV_64F to CV_8S and scaled) = \n" << m4 << '\n';

    std::cout << "\nm4 data type = " << CPP_CV::General::openCVDescriptiveDataType(m4.type()) << '\n';

    // 2. Use 'assignTo()' to convert array values to another data type

    cv::Mat m5;

    // convert from CV_64F to CV_32F. 
    // This reduces the degree of accuracy for floating point values
    // Check by comparing number of decimal values in m0 & those in m5 
    m0.assignTo(m5, CV_32FC3); 

    std::cout << "\nm5 (data type converted from CV_64F to CV_32F) = \n" << m5 << '\n';

    std::cout << "\nm5 data type = " << CPP_CV::General::openCVDescriptiveDataType(m5.type()) << '\n';
    
    std::cout << '\n';

    return 0;
}
```

**Output** 

    m0 = 
    [1.200000047683716, 2.5, 0.4000000059604645, 1.200000047683716, 2.5, 0.4000000059604645, 1.200000047683716, 2.5, 0.4000000059604645;
    1.200000047683716, 2.5, 0.4000000059604645, 1.200000047683716, 2.5, 0.4000000059604645, 1.200000047683716, 2.5, 0.4000000059604645;
    1.200000047683716, 2.5, 0.4000000059604645, 1.200000047683716, 2.5, 0.4000000059604645, 1.200000047683716, 2.5, 0.4000000059604645]

    m0 data type = CV_64FC3 -> Array with 3 channels and primitive data type 64-bit decimal values of type float with range (-1.797693134862315E+308 to 1.797693134862315E+308)

    m3 (data type converted from CV_64F to CV_8S) = 
    [  1,   2,   0,   1,   2,   0,   1,   2,   0;
    1,   2,   0,   1,   2,   0,   1,   2,   0;
    1,   2,   0,   1,   2,   0,   1,   2,   0]

    m3 data type = CV_8SC3 -> Array with 3 channels and primitive data type 8-bit signed integers with range (-127 to 128)

    m4 (data type converted from CV_64F to CV_8S and scaled) = 
    [  3,   6,   2,   3,   6,   2,   3,   6,   2;
    3,   6,   2,   3,   6,   2,   3,   6,   2;
    3,   6,   2,   3,   6,   2,   3,   6,   2]

    m4 data type = CV_8SC3 -> Array with 3 channels and primitive data type 8-bit signed integers with range (-127 to 128)

    m5 (data type converted from CV_64F to CV_32F) = 
    [1.2, 2.5, 0.40000001, 1.2, 2.5, 0.40000001, 1.2, 2.5, 0.40000001;
    1.2, 2.5, 0.40000001, 1.2, 2.5, 0.40000001, 1.2, 2.5, 0.40000001;
    1.2, 2.5, 0.40000001, 1.2, 2.5, 0.40000001, 1.2, 2.5, 0.40000001]

    m5 data type = CV_32FC3 -> Array with 3 channels and primitive data type 32-bit decimal values of type float with range (-3.40282347E+38 to 3.40282347E+38)

### Set all elements of a cv::Mat object to a single value

:notebook_with_decorative_cover: Here we can make use of the `cv::Mat& setTo(cv::InputArray value, cv::InputArray mask = cv::noArray())` function. `value` is the assigned scalar converted to the actual array type. `mask` is the operation mask of the same size as cv::Mat object you want to create. Its non-zero elements indicate which matrix elements need to be copied. The mask has to be of type CV_8U and can have 1 or multiple channels. Usually its an optional parameter. We will talk about masks in a later chapter. 

**Example 2**

```c++
#include "opencv2/core.hpp"
#include <iostream>

int main()
{
    // 3. Set all elements of a cv::Mat object to a single value
    
    // a) Single-channel 2D-array
    cv::Mat m6;
    m6.create(5, 5, CV_8S); // create a 5x5 array to hold 8-bit signed integers
    m6.setTo(-5);           // set each value to '-5' in array
    std::cout << "\nm6 (each element is set to the same value) = \n" << m6 << '\n';
    
    // b) Multi-channel 2D-array

    cv::Mat m7;
    m7.create(5, 5, CV_32FC3); // create an empty 5x5 array with three channels
    // In the following: 
    //      1. Channel 1 will have all values set to '1.0'
    //      2. Channel 2 will have all values set to '0.3'
    //      3. Channel 3 will have all values set to '-2,3'
    m7.setTo(cv::Scalar(1.0f, 0.3f, -2.3f)); 
    std::cout << "\nm7 (each channel set to the same value) = \n" << m7 << '\n';

    std::cout << '\n';

    return 0;
}
```

**Output**

    m6 (each element is set to the same value) = 
    [ -5,  -5,  -5,  -5,  -5;
    -5,  -5,  -5,  -5,  -5;
    -5,  -5,  -5,  -5,  -5;
    -5,  -5,  -5,  -5,  -5;
    -5,  -5,  -5,  -5,  -5]

    m7 (each channel set to the same value) = 
    [1, 0.30000001, -2.3, 1, 0.30000001, -2.3, 1, 0.30000001, -2.3, 1, 0.30000001, -2.3, 1, 0.30000001, -2.3;
    1, 0.30000001, -2.3, 1, 0.30000001, -2.3, 1, 0.30000001, -2.3, 1, 0.30000001, -2.3, 1, 0.30000001, -2.3;
    1, 0.30000001, -2.3, 1, 0.30000001, -2.3, 1, 0.30000001, -2.3, 1, 0.30000001, -2.3, 1, 0.30000001, -2.3;
    1, 0.30000001, -2.3, 1, 0.30000001, -2.3, 1, 0.30000001, -2.3, 1, 0.30000001, -2.3, 1, 0.30000001, -2.3;
    1, 0.30000001, -2.3, 1, 0.30000001, -2.3, 1, 0.30000001, -2.3, 1, 0.30000001, -2.3, 1, 0.30000001, -2.3]

### Change the shape of a 2-D cv::Mat object. 

:notebook_with_decorative_cover: We can change the shape of a cv::Mat object. However, data is not copied in this instance.  Before reshaping a matrix, make sure you can get the new shape from the original matrix elements. We use the `reshape()` member function, which is overloaded into 3 functions as follows:

1. `cv::Mat reshape(int cn, int rows=0) const` - `cn` is number of channels. If you set `cn = 0`, the number of channels in cv::Mat object stays the same, which is what we want in most cases. `rows` is the new number of rows. If the parameter is 0, the number of rows remains the same.
2. `cv::Mat reshape(int cn, int newndims, const int* newsz)` - parameter `cn` is the same as above. `newndims` is the new number of dimensions. `newsz` - a C-style array with new matrix size by all dimensions. If some sizes are zero, the original sizes in those dimensions are presumed.
3. `cv::Mat reshape(int cn, const std::vector<int>& newshape) const` - parameter `cn` is the same as above. `newshape` is a std::vector with new matrix size by all dimentions. If some sizes are zero, the original sizes in those dimensions are presumed. 

**Example 3**

```c++
#include "opencv2/core.hpp"
#include <iostream>

int main()
{
    /*                     4. Reshaping cv::Mat objects
     *                     ============================
     *
     * We can change the shape of a 2D matrix. However, data is not 
     * copied in this instance. Before reshaping a matrix, make sure 
     * you can get the new shape from the original matrix elements
     * 
    */    
    
    // create a 4x4 array with 3 channels
    cv::Mat m8 {cv::Size(4, 4), CV_8UC3, cv::Scalar(0, 120, 255)}; 
    std::cout << "\nm8 (original 4 x 4 array) = \n" << m8 << '\n';

    // a) Use the reshape(cn, rows=0) function where cn = no. of channels, 
    //    rows = new number of rows 
    //    Reshape to a [2 x 8] 3-channel array 

    int rows {2};
    auto m9 = m8.reshape(0, rows);
    std::cout << "\nm9 (Reshape to 2 x 8 3-channel array) = \n" 
              << m9 << '\n';

    // b) Use the reshape(cn, rows=0) function where cn = no. of channels, 
    //    rows = new number of rows 
    //    Reshape to a  1-channel array with a single row

    auto m10 = m8.reshape(1, 1);
    std::cout << "\nm10 (Reshape to 1 x 16 1-channel array) = \n" 
              << m10 << '\n'; 

    // c) Use the reshape(int cn, int newndims, const int* newsz) function where 
    //    cn = no. of channels, newndims = is the new number of dimensions, 
    //    newsz = a C-style array with new matrix size by all dimensions.     

    cv::Mat m11 {cv::Size(2,2), CV_8UC3, cv::Scalar(1, 2, 3)};
    std::cout << "\nm11 (original 2 x 2 3-channel array) = \n" << m11 << '\n';

    //    Reshape a 3-channel 2x2 array to a 1-channel 4x3 array
    int cn {1}; // No. of channels
    int newdims {2}; // No. of dimensions
    const int newsz[] {4, 3}; // New array shape
    auto m12 = m11.reshape(cn, newdims, newsz);
    std::cout << "\nm12 (Reshape from 3-channel 2x2 array to a 1-channel 4x3 array = \n" 
              << m12 << '\n';

    // d) Reshape a 3-channel 2x2 array to a 1-channel 6x2 array but using the function: 
    //    reshape(int cn, const std::vector<int>& newshape)
    
    int ch {1}; // No. of channels
    const std::vector<int> newshape {6, 2}; // New array shape
    auto m13 = m11.reshape(ch, newshape); 
    std::cout << "\nm13 (Reshape from 3-channel 2x2 array to a 1-channel 6x2 array = \n" 
              << m13 << '\n'; 

    std::cout << '\n';

    return 0;
}
```

**Output**

    m8 (original 4 x 4 array) = 
    [  0, 120, 255,   0, 120, 255,   0, 120, 255,   0, 120, 255;
    0, 120, 255,   0, 120, 255,   0, 120, 255,   0, 120, 255;
    0, 120, 255,   0, 120, 255,   0, 120, 255,   0, 120, 255;
    0, 120, 255,   0, 120, 255,   0, 120, 255,   0, 120, 255]

    m9 (Reshape to 2 x 8 3-channel array) = 
    [  0, 120, 255,   0, 120, 255,   0, 120, 255,   0, 120, 255,   0, 120, 255,   0, 120, 255,   0, 120, 255,   0, 120, 255;
    0, 120, 255,   0, 120, 255,   0, 120, 255,   0, 120, 255,   0, 120, 255,   0, 120, 255,   0, 120, 255,   0, 120, 255]

    m10 (Reshape to 1 x 16 1-channel array) = 
    [  0, 120, 255,   0, 120, 255,   0, 120, 255,   0, 120, 255,   0, 120, 255,   0, 120, 255,   0, 120, 255,   0, 120, 255,   0, 120, 255,   0, 120, 255,   0, 120, 255,   0, 120, 255,   0, 120, 255,   0, 120, 255,   0, 120, 255,   0, 120, 255]

    m11 (original 2 x 2 3-channel array) = 
    [  1,   2,   3,   1,   2,   3;
    1,   2,   3,   1,   2,   3]

    m12 (Reshape from 3-channel 2x2 array to a 1-channel 4x3 array = 
    [  1,   2,   3;
    1,   2,   3;
    1,   2,   3;
    1,   2,   3]

    m13 (Reshape from 3-channel 2x2 array to a 1-channel 4x3 array = 
    [  1,   2;
    3,   1;
    2,   3;
    1,   2;
    3,   1;
    2,   3]


### Remove rows of data from a cv::Mat object

:notebook_with_decorative_cover: OpenCV provides the `void pop_back(size_t nelems = 1)` function for removing elements from the end or bottom of a cv::Mat object. The function parameter `nelems` is the number of rows we want to remove from the bottom of a cv::Mat object. If it is greater than the total number of rows, an **exception** is thrown. 

:notebook_with_decorative_cover: You should also know that the data in the original cv::Mat object will be affected by this operation. If your intention is to create a different array with less rows than the original array, copy the original cv::Mat object first before applying this function. 

:notebook_with_decorative_cover: According to the OpenCV documentation, the data type of `nelems` should be **size_t**, an alias for an **unsigned integer**. For most C++ compilers if you supply a positive **int** value you should be ok as the compiler will implicitly convert your **int** to **size_t**. However, on other compilers you may have to supply a **size_t** value. All you have to do is just use **saturate_cast** to convert your integer value to a **size_t** as follows: `pop_back(cv::saturate_cast<size_t>(number of rows as integer value))` or replace **cv::saturate_cast** with the equivalent C++ alternative **static_cast** e.g., `pop_back(static_cast<size_t>(number of rows as integer value))`.

**Example 4**

```c++
#include "opencv2/core.hpp"
#include <iostream>

int main()
{
    // 5. Remove a number of rows from a cv::Mat object using the pop_back()
    //    Rows are removed from the end or bottom of the cv::Mat object

    // Original data in a C-style array
    double data[] { 1.2, 5.6, 9.0, 2.3, 5.6, 2.4, 4.6, 6.8, 10.2 }; 
    
    // Create a 3x3 array with 1 channel and 64-bit floating data type. 
    // N.B: 64-bit can handle type 'double'
    cv::Mat m14 { cv::Size(3,3), CV_64F, data }; 

    std::cout << "\nOriginal m14 array = \n" << m14 << '\n';

    // Use pop_back() to remove the last row in m9
    // data type of 'number of rows to remove' is 'size_t'
    // you can also use 'pop_back(static_cast<size_t>(1))'
    int nRows {1};
    m14.pop_back(cv::saturate_cast<size_t>(nRows)); 

    std::cout << "\nArray m14 after removing the last row = \n" << m14 << '\n';

    std::cout << '\n';

    return 0;
}
```

**Output**

    Original m14 array = 
    [1.2, 5.6, 9;
    2.3, 5.6, 2.4;
    4.6, 6.8, 10.2]

    Array m14 after removing the last row = 
    [1.2, 5.6, 9;
    2.3, 5.6, 2.4]


### Add rows of data to a cv::Mat object

:notebook_with_decorative_cover: OpenCV provides the **push_back()** function for increasing the number of elements to an already existing cv::Mat array. This function will add elements to the bottom of the array, and will also affect the original cv::Mat object. There are currently three ways we can use this function.

1. `void push_back(const_T& elem)` - this version allows us to add a single element or value of type `T` to the end of the array. The array we wish to add values to should have **1 column and any number of rows**. Parameter `elem` is the single value we want to add. It should ideally be the same data type as the values in the original array, otherwise implicit data type conversions will be applied were necessary or you get a compiler warning.
2. `push_back(const std::vector<T>& elem)` - this version allows us to add more than one value at once. The array we wish to add values to should have **1 column and any number of rows**. The values are provided in a C++ STL container std::vector.
3. `push_back(const cv::Mat& m)` - this version allows you to add values from another cv::Mat array. Note that the data type and number of columns of **m** must be the same as in the array you want to add new values to.

**Example 5**

```c++
#include "opencv2/core.hpp"
#include <iostream>
#include <vector>

int main()
{
    // 6. Add a single value, number of values or number 
    //    of rows to the end of a cv::Mat object

    // Original data in a C-style array
    double data[] { 1.2, 5.6, 9.0, 2.3, 5.6, 2.4, 4.6, 6.8, 10.2 }; 
    
    // a) Add a single value to the end of a cv::Mat object using 
    //    the 'push_back(const T& elem)' function
    //    Original cv::Mat object should have any number of rows 
    //    but only 1 column

    // N.B cv::Size(width/columns, height/rows)
    cv::Mat m15 { cv::Size(1, 9), CV_64F, data }; // Create a 9x1 array 
    std::cout << "\nOriginal m15 array = \n" << m15 << '\n'; 

    double value {11.5};
    m15.push_back(value); // add the single value to m15
    std::cout << "\nArray m15 after adding a single value at the end  = \n" 
              << m15 << '\n';

    // b) Add more than one value to the end of a cv::Mat object 
    //    It is best to have the values in std::vector container 
    //    We will use the function 'push_back(const std::vector<T>& elem)'

    const std::vector<double> vectorElements { 12.3, 3.56, 4.56 }; 
    m15.push_back(vectorElements); // add values to end of array
    std::cout << "\nArray m15 after adding 3 more elements = \n" 
              << m15 << '\n';

    // c) Add values from another cv::Mat object to the end of another cv::Mat object
    //    We will use the function 'push_back(const cv::Mat& m)'

    // Create a 3x3 array with 1 channel and 64-bit floating data type. 
    // N.B: 64-bit can handle type 'double'
    cv::Mat m16 { cv::Size(3, 3), CV_64F, data }; 
    std::cout << "\nOriginal m16 array = \n" << m16 << '\n';

    // Create a 2x3 array 
    // Make sure 'data type' and 'number of columns' matches that of m16
    double tempData[] { 2.11, 5.6, 4.56, 3.34, 1.24, 0.34 }; 
    cv::Mat temp { cv::Size(3, 2), CV_64F, tempData }; 
    std::cout << "\nData to add to end of m16 = \n" << temp << '\n';
    
    m16.push_back(temp); // add another cv::Mat to end of m16
    std::cout << "\nArray m16 after adding data in a 2x3 array = \n" 
              << m16 << '\n';

    std::cout << '\n';
    
    return 0;
}

```

**Output**

    Original m15 array = 
    [1.2;
    5.6;
    9;
    2.3;
    5.6;
    2.4;
    4.6;
    6.8;
    10.2]

    Array m15 after adding a single value at the end  = 
    [1.2;
    5.6;
    9;
    2.3;
    5.6;
    2.4;
    4.6;
    6.8;
    10.2;
    11.5]

    Array m15 after adding 3 more elements = 
    [1.2;
    5.6;
    9;
    2.3;
    5.6;
    2.4;
    4.6;
    6.8;
    10.2;
    11.5;
    12.3;
    3.56;
    4.56]

    Original m16 array = 
    [1.2, 5.6, 9;
    2.3, 5.6, 2.4;
    4.6, 6.8, 10.2]

    Data to add to end of m16 = 
    [2.11, 5.6, 4.56;
    3.34, 1.24, 0.34]

    Array m16 after adding data in a 2x3 array = 
    [1.2, 5.6, 9;
    2.3, 5.6, 2.4;
    4.6, 6.8, 10.2;
    2.11, 5.6, 4.56;
    3.34, 1.24, 0.34]
