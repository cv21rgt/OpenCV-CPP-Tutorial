# Copying data from a cv::Mat object

:notebook_with_decorative_cover: When working with cv::Mat objects you are encouraged to avoid making copies of data. This is also supported by the fact that the majority of OpenCV functions do not copy the data passed to them. Instead data is shared between cv::Mat objects through the use of pointers as discused in greate detail <a href = "https://docs.opencv.org/4.8.0/d6/d6d/tutorial_mat_the_basic_image_container.html">**here**</a>. This decision was taken to stop the unnecessary copying of potentially large image data, which can reduce the speed of your programs.
     
:notebook_with_decorative_cover: However, in the event that you want to go ahead and copy cv::Mat objects underlying data, you can use one of two member functions: 

1. `cv::Mat clone() const` - creates a full copy of the cv::Mat array and the underlying data. Modifying a copy will not affect the original matrix/array.
   
2.  `void copyTo(cv::OutputArray m) const` - copies current array to output/destination array `m`. `m` is expected to have the same size and type as the input array. If the user does not set a proper size or type for `m` before the operation, OpenCV will take care of this, something you should take advantage of - as you will see in the example that follows. This function is overloaded as `void copyTo(cv::OutputArray m, cv::InputArray mask) const` - `m` is the same as before. `mask` defines an area of interest. It is also defined as a matrix of type `CV_8U` and can have 1 or multiple channels. `mask` should be the same size as the input array (the array you want to copy). Its non-zero elements indicate which matrix/array elements need to be copied. Also remember that `cv::OutputArray` and `cv::InputArray` are collective names for any of the OpenCV types we have already discussed so far.  

**Example 1**

```c++
#include "opencv2/core.hpp" 
#include <iostream>

int main()
{
    // A 1-D array with 100 values of type 'float'
    float dataArray[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 
                    11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 
                    21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 
                    31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 
                    42, 42, 43, 44, 45, 46, 47, 48, 49, 50, 
                    51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 
                    61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 
                    71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 
                    81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 
                    91, 92, 93, 94, 95, 96, 97, 98, 99, 100};

    // Create a 10x10 array with 32-bit float values
    const cv::Mat m1 { 10, 10, CV_32F, dataArray }; 
    std::cout << "\nm1 (Original array)= \n" << m1 << '\n';

    // 1a. Use the function clone() to copy m1 into m2 
    cv::Mat m2 = m1.clone(); 

    // 1b. Alter the value at location (0,0) to 101 in array m2
    // This should not affect array m1
    m2.at<float>(0,0) = 101;
    std::cout << "\nm2 (modified array)  = \n" << m2 << '\n';
    std::cout << "\nm1 (original array is unchanged) = \n" << m1 << '\n';

    // 2. Use the function 'void copyTo(cv::OutputArray m)' to copy 
    //    array m2 to array m3
    cv::Mat m3; // No need to specify size and type, let OpenCV do this for us
    m2.copyTo(m3); 
    std::cout << "\nm3 (copy of m2) = \n" << m3 << '\n';

    std::cout << '\n';

    return 0;
}
```

**Output**

    m1 (Original array)= 
    [1, 2, 3, 4, 5, 6, 7, 8, 9, 10;
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20;
    21, 22, 23, 24, 25, 26, 27, 28, 29, 30;
    31, 32, 33, 34, 35, 36, 37, 38, 39, 40;
    42, 42, 43, 44, 45, 46, 47, 48, 49, 50;
    51, 52, 53, 54, 55, 56, 57, 58, 59, 60;
    61, 62, 63, 64, 65, 66, 67, 68, 69, 70;
    71, 72, 73, 74, 75, 76, 77, 78, 79, 80;
    81, 82, 83, 84, 85, 86, 87, 88, 89, 90;
    91, 92, 93, 94, 95, 96, 97, 98, 99, 100]

    m2 (modified array)  = 
    [101, 2, 3, 4, 5, 6, 7, 8, 9, 10;
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20;
    21, 22, 23, 24, 25, 26, 27, 28, 29, 30;
    31, 32, 33, 34, 35, 36, 37, 38, 39, 40;
    42, 42, 43, 44, 45, 46, 47, 48, 49, 50;
    51, 52, 53, 54, 55, 56, 57, 58, 59, 60;
    61, 62, 63, 64, 65, 66, 67, 68, 69, 70;
    71, 72, 73, 74, 75, 76, 77, 78, 79, 80;
    81, 82, 83, 84, 85, 86, 87, 88, 89, 90;
    91, 92, 93, 94, 95, 96, 97, 98, 99, 100]

    m1 (original array is unchanged) = 
    [1, 2, 3, 4, 5, 6, 7, 8, 9, 10;
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20;
    21, 22, 23, 24, 25, 26, 27, 28, 29, 30;
    31, 32, 33, 34, 35, 36, 37, 38, 39, 40;
    42, 42, 43, 44, 45, 46, 47, 48, 49, 50;
    51, 52, 53, 54, 55, 56, 57, 58, 59, 60;
    61, 62, 63, 64, 65, 66, 67, 68, 69, 70;
    71, 72, 73, 74, 75, 76, 77, 78, 79, 80;
    81, 82, 83, 84, 85, 86, 87, 88, 89, 90;
    91, 92, 93, 94, 95, 96, 97, 98, 99, 100]

    m3 (copy of m2) = 
    [101, 2, 3, 4, 5, 6, 7, 8, 9, 10;
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20;
    21, 22, 23, 24, 25, 26, 27, 28, 29, 30;
    31, 32, 33, 34, 35, 36, 37, 38, 39, 40;
    42, 42, 43, 44, 45, 46, 47, 48, 49, 50;
    51, 52, 53, 54, 55, 56, 57, 58, 59, 60;
    61, 62, 63, 64, 65, 66, 67, 68, 69, 70;
    71, 72, 73, 74, 75, 76, 77, 78, 79, 80;
    81, 82, 83, 84, 85, 86, 87, 88, 89, 90;
    91, 92, 93, 94, 95, 96, 97, 98, 99, 100]

**Example 2** - In the following example, we use a mask to copy every second element from the original array

```c++
#include "opencv2/core.hpp" 
#include <iostream>

int main 
{
    // A 1-D array with 100 values of type 'float'
    float dataArray[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 
                    11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 
                    21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 
                    31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 
                    42, 42, 43, 44, 45, 46, 47, 48, 49, 50, 
                    51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 
                    61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 
                    71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 
                    81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 
                    91, 92, 93, 94, 95, 96, 97, 98, 99, 100};

    // Create a 10x10 array with 32-bit float values
    const cv::Mat m1 { 10, 10, CV_32F, dataArray }; 
    std::cout << "\nm1 (Original array)= \n" << m1 << '\n';

    // Use the function 'void copyTo(cv::OutputArray m, cv::InputArray mask)' 
    // to create an array by copying each second element

    // 1. Create our mask. This should be the same size as array m1.
    //    Our mask will contain '0' and '1' values
    //    The value 1 in the mask indicates which element in array m1 will be copied
    //    The value 0 in the mask indicates which element in array m1 will not be copied

    //    mask data will originally be held in a C-style array
    //    Take note of the data type 'std::uint8_t' - unsigned 8-bit integer
    //    This is because our mask should be of type 'CV_8U' - unsigned 8-bit integer
    std::uint8_t mask_data[100]; 

    // 2. Fill mask_data array with '0' and '1'
    for(std::size_t i {0}; i < std::size(mask_data); ++i)
    {
        if(i % 2 == 0)
        {
            mask_data[i] = static_cast<std::uint8_t>(0);
        }
        else 
        {
            mask_data[i] = static_cast<std::uint8_t>(1);
        }
    }

    // 3. Use 'mask_data' to create a mask as a cv::Mat array with data type 'CV_8U'
    cv::Mat mask {m1.rows, m1.cols, CV_8U, mask_data};
    std::cout << "\nmask = \n" << mask << '\n';

    // 4. We can now copy every second element from array m1
    cv::Mat m4; // Array to store every second element from m1
    m1.copyTo(m4, mask);
    std::cout << "\nm4 (contains every second element from array m1) = \n" 
              << m4 << '\n';
              
    std::cout << '\n';

    return 0;
}
```

**Output**

    m1 (Original array)= 
    [1, 2, 3, 4, 5, 6, 7, 8, 9, 10;
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20;
    21, 22, 23, 24, 25, 26, 27, 28, 29, 30;
    31, 32, 33, 34, 35, 36, 37, 38, 39, 40;
    42, 42, 43, 44, 45, 46, 47, 48, 49, 50;
    51, 52, 53, 54, 55, 56, 57, 58, 59, 60;
    61, 62, 63, 64, 65, 66, 67, 68, 69, 70;
    71, 72, 73, 74, 75, 76, 77, 78, 79, 80;
    81, 82, 83, 84, 85, 86, 87, 88, 89, 90;
    91, 92, 93, 94, 95, 96, 97, 98, 99, 100]

    mask = 
    [  0,   1,   0,   1,   0,   1,   0,   1,   0,   1;
    0,   1,   0,   1,   0,   1,   0,   1,   0,   1;
    0,   1,   0,   1,   0,   1,   0,   1,   0,   1;
    0,   1,   0,   1,   0,   1,   0,   1,   0,   1;
    0,   1,   0,   1,   0,   1,   0,   1,   0,   1;
    0,   1,   0,   1,   0,   1,   0,   1,   0,   1;
    0,   1,   0,   1,   0,   1,   0,   1,   0,   1;
    0,   1,   0,   1,   0,   1,   0,   1,   0,   1;
    0,   1,   0,   1,   0,   1,   0,   1,   0,   1;
    0,   1,   0,   1,   0,   1,   0,   1,   0,   1]

    m4 (contains every second element from array m1) = 
    [0, 2, 0, 4, 0, 6, 0, 8, 0, 10;
    0, 12, 0, 14, 0, 16, 0, 18, 0, 20;
    0, 22, 0, 24, 0, 26, 0, 28, 0, 30;
    0, 32, 0, 34, 0, 36, 0, 38, 0, 40;
    0, 42, 0, 44, 0, 46, 0, 48, 0, 50;
    0, 52, 0, 54, 0, 56, 0, 58, 0, 60;
    0, 62, 0, 64, 0, 66, 0, 68, 0, 70;
    0, 72, 0, 74, 0, 76, 0, 78, 0, 80;
    0, 82, 0, 84, 0, 86, 0, 88, 0, 90;
    0, 92, 0, 94, 0, 96, 0, 98, 0, 100]
