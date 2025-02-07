## Saturation Casting

:notebook_with_decorative_cover: One of the issues you will encounter when dealing with data types is that some of your operations may result in a solution that goes beyond the range of the data type for the destination variable. For example, `short int x = 20 000 + 16 000` or `short int y = -22 000 - 13 000`, are operations that result in the solutions `36 000` and `-35 000`, respectively, both of which are out of range for the **short integer** data type (-32 768 to 32 767). This is called overflowing and underflowing, respectively. Different libraries have different ways of dealing with this issue. C++ will give you a warning along the lines "*overflow in conversion from* **'int'** *to* **'short int'**", but the program will still compile and run with unexpected results. OpenCV on the other hand relies on a construct called **saturation casting**.

:notebook_with_decorative_cover: What this means is that instead of letting the user deal with the problem, OpenCV operations will automatically check for underflows and overflows. In each case, OpenCV will replace the solution with the lowest or highest available value depending on whether it is undeflow or overflow. Using our examples above and if they were OpenCV operations, **x** will be set to *32 767* because it is an overflow, and **y** will be set to *-32 768* because it is an underflow. In the following examples we will see how OpenCV applies saturation casting for different data types.

**Example 1**

```c++
#include "opencv2/core.hpp" // for OpenCV core data types
#include <iostream>
#include <cstdint> // for std::int8_t - C++ 8-bit signed integer data type


int main()
{
    
    // Create arrays whose data type is 8-bit unsigned integers (0 to 255)
    // ===================================================================

    // 2x2 2D array with all values equal to 15
    const cv::Mat m1 { cv::Size(2, 2), CV_8U, cv::Scalar(15)}; 
    std::cout << "\nm1 = \n" << m1 << '\n';

    // 2x2 2D array with all values equal to 245
    const cv::Mat m2 { cv::Size(2, 2), CV_8U, cv::Scalar(245)}; 
    std::cout << "\nm2 = \n" << m2 << '\n';

    // 2x2 2D array with all values equal to 10
    const cv::Mat m3 { cv::Size(2, 2), CV_8U, cv::Scalar(10)};  
    std::cout << "\nm3 = \n" << m3 << '\n';

    // Operation 1: Overflow
    //              ========

    // m4 expects all values to be 8-bit unsigned in the range 0 to 255 
    cv::Mat m4 {cv::Size(2, 2), CV_8U}; 
    m4 = m1 + m2;   // this operation will result in 'overflow'. 
                    // Any addition that results in a solution out of range, 
                    // is replaced by the minimum (0) or maximum (255) range 
                    // value of the unsigned data type
    std::cout << "\n(m1 + m2) shows saturation casting applied to 'overflow' = \n" 
              << m4 << '\n';

    // Operation 2: Underflow
    //              =========

    // m5 expects all values to be 8-bit unsigned in the range 0 to 255
    cv::Mat m5 { cv::Size(2, 2), CV_8U}; 
    m5 = m3 - m1;   // this operation will result in 'undeflow'
                    // Any subtraction that results in a solution out of range, 
                    // is replaced by the minimum (0) or maximum (255) range 
                    // value of the unsigned data type
    std::cout << "\n(m3 - m1) shows saturation casting applied to 'underflow' = \n" 
              << m5 << '\n';

     // Operation 3: Underflow and Overflow
     //              ======================

    // C-style array with 8-bit signed integers
    std::int8_t a1[] { -36, -125, -48, 52, -75, 78, 109, -119, 54 }; 

    // Use data from above C-style array to create a 2D cv::Mat 3X3 array whose 
    // values are 8-bit signed integers, range (-128 to 127)
    const cv::Mat m6 { cv::Size(3, 3), CV_8S, a1 }; 
    std::cout << "\nm6  = \n" << m6 << '\n';
    std::cout << "\n m6 data type = " 
              << CPP_CV::General::openCVDescriptiveDataType(m6.type()) << '\n';

    // m7 expects all values to be 8-bit signed integers in the range -128 to 127
    cv::Mat m7 { cv::Size(3, 3), CV_8S }; 
    m7 = m6 * 2;    // this will cause both underflow and overflow. Underflow values 
                    // will be replaced by -128 & overflow values by 127
                    // Any multiplication that results in a solution out of range, 
                    // is replaced by the minimum (-128) or maximum (127) range value 
                    // of the 8-bit signed data type

    std::cout << "\n(m6 x 2) shows saturation casting applied to both 'undeflow' and 'overflow' = \n" 
              << m7 << '\n';

    std::cout << '\n';

    return 0;
}
```

**Output**

    m1 = 
    [ 15,  15;
    15,  15]

    m2 = 
    [245, 245;
    245, 245]

    m3 = 
    [ 10,  10;
    10,  10]

    (m1 + m2) shows saturation casting applied to 'overflow' = 
    [255, 255;
    255, 255]

    (m3 - m1) shows saturation casting applied to 'underflow' = 
    [  0,   0;
    0,   0]

    m6  = 
    [-36, -125, -48;
    52, -75,  78;
    109, -119,  54]

    m6 data type = CV_8S or CV_8SC1 -> Array with 1 channel and primitive data type 8-bit signed integers with range (-128 to 127)

    (m6 x 2) shows saturation casting applied to both 'undeflow' and 'overflow' = 
    [-72, -128, -96;
    104, -128, 127;
    127, -128, 108]

:notebook_with_decorative_cover: OpenCV also provides a template function that you can use if you want to implement saturation casting in your own operations. The function has the syntax **cv::saturate_cast<*target data type*>(*operation or input value*)**. This template function is also used for accurate conversion from one primitive type to another. The function **cv::saturate_cast** resembles the standard C++ cast operations, such as **std::static_cast\<T>()** and others. It perform an efficient and accurate conversion from one primitive type to another. *saturate* in the name means that when the input value is out of the range of the target type, the result is not formed just by taking low bits of the input, but instead the value is clipped. 

1. Such clipping is done when the target type is *unsigned char* , *signed char* , *unsigned short* or *signed short* . 
2. For 32-bit integers, no clipping is done. 
3. When the input value is a floating-point value and the target type is an integer (8-, 16- or 32-bit), the floating-point value is first rounded to the nearest integer and then clipped if needed (when the target type is 8- or 16-bit).

**Example 2**

```c++
#include "opencv2/core.hpp" // for all OpenCV core data types 
#include <iostream>

int main()
{
    // Implement user-defined saturation casting
    // =========================================

    const int a {-36}; 
    const int b {360};

    // 1. Cast '32-bit int' to 'unsigned char'
    auto v1 = (int)cv::saturate_cast<uchar>(a); // This will be clipped to 0 because operation 
                                                // results in an underflow and range for 8-bit 
                                                // unsigned char is 0 to 255
    std::cout << "\nInteger value " << a << " cast to unsigned char = " 
              << v1 << '\n';

    auto v2 = (int)cv::saturate_cast<uchar>(b); // This will be clipped to 255 because operation 
                                                // results in an overflow and range for 8-bit 
                                                // unsigned char is 0 to 255
    std::cout << "\nInteger value " << b << " cast to unsigned char = " 
              << v2 << '\n';

    // 2. Cast '32-bit int' to 'signed char'
    auto v3 = (int)cv::saturate_cast<schar>(a); // This will remain as -36 because it is within 
                                                // range for 8-bit signed char (-128 to 127)
    std::cout << "\nInteger value " << a << " cast to signed char = " 
              << v3 << '\n';

    auto v4 = (int)cv::saturate_cast<schar>(b); // This will be clipped to 127 because operation 
                                                // results in an overflow and range for 8-bit 
                                                // signed char is -128 to 127
    std::cout << "\nInteger value " << b << " cast to signed char = " 
              << v4 << '\n';

    // 3. Cast '32-bit int' to 'short int'
    const int c {33333};
    auto v5 = cv::saturate_cast<short>(c); // input value will be clipped to 32 767 because 
                                           // this is an overflow and range for short integer 
                                           // is -32 768 to 32 767
    std::cout << "\nInteger value " << c << " cast to short integer = " 
              << v5 << '\n';

    // 4. Cast 'float' to '32-bit integer'
    const float d {23456.89765f};
    auto v6 = cv::saturate_cast<int>(d); // input value is float & is therefore 
                                         // rounded to the nearest integer 
    std::cout << "\nFloat value " << d << " cast to 32-bit integer = " 
              << v6 << '\n';

    // 5. Cast 'float' to 'short integer'
    const double e {-33789.000023451234}; // input value is first rounded to the 
                                          // to the nearest integer and then clipped 
                                          // to fall within the range -32 768 to 32 767
    auto v7 = cv::saturate_cast<short>(e);
    std::cout << "\nFloat value " << e << " cast to short integer = " 
              << v7 << '\n';

    std::cout << '\n';
    
    return 0;    
}
```

**Output**

    Integer value -36 cast to unsigned char = 0

    Integer value 360 cast to unsigned char = 255

    Integer value -36 cast to signed char = -36

    Integer value 360 cast to signed char = 127

    Integer value 33333 cast to short integer = 32767

    Float value 23456.9 cast to 32-bit integer = 23457

    Float value -33789 cast to short integer = -32768