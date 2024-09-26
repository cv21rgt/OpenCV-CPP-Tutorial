## Vector Data Type

:notebook_with_decorative_cover: The fixed vector classes are derived from the fixed matrix classes (**cv::Matx<>**).

:notebook_with_decorative_cover: This means that vector objects inherit the majority of member functions from **cv::Matx<>**. 

:notebook_with_decorative_cover: The fixed vector template <a href = "https://docs.opencv.org/4.8.0/d6/dcf/classcv_1_1Vec.html">cv::Vec<></a> is a **cv::Matx<>** whose number of columns in 1.

:notebook_with_decorative_cover: You can use aliases of the form **cv::Vec{1,2,3,4,5,6}{b,s,w,i,f,d}** to declare a fixed vector object. Aliases end at vectors with 6 elements; after that use the template form (**cv::Vec<data type, number of elements>**) to define larger cv::Vec data objects.

### Creating cv::Vec<> objects

:notebook_with_decorative_cover: By now you should be familiar with the use of Default, Value and Copy constructors:
1. Default constructor - OpenCV will provide zero's as the elements of your vector.
2. Value constructor - The user provides the vector elements. **cv::Vec<>** provides value constructors that accept up to 14 elements. Even though the **cv::Vec<>** template class provides value constructors up to 14 elements, you can still create vector objects with more than 14 elements as shown in the examples below. 
3. Copy constructor - copy elements from an existing vector to a new vector as long as they both have the same primitive data type.

**Example 1**

```c++
#include "opencv2/core.hpp" // for OpenCV basic data types
#include <iostream>         

int main()
{
    //                                     Instantiating cv::Vec<> objects
    //                                     ===============================

    // 1. Use the Default constructor to create a 2 x 1 vector of 0's of 
    //     integer data type
    const cv::Vec2i v1 {};                       
    
    /* 2. Use the Value constructors - here the user supplies all vector elements
     *    The cv::Vec<> template class provides value constructors up to 14 
     *    elements, but you can still create vector objects with more than 14 elements.
     *    
     *    N.B: Aliases end at vectors with 6 elements, after that use the 
     *    template form to create your vector objects as shown below for 
     *    objects 'vv7', 'vv14' & 'vv16'
    */
    
    const cv::Vec3d v2 { 1.2, 3.4, 8.9 };  // 3 x 1 vector with double precision
    
    // Create a 4 x 1 vector with 32-bit floating point precision
    const cv::Vec4f v3 { 1.0f, 2.0f, 3.0f, 6.0f }; 
    
    // Create a 7 x 1 vector with elements of type 'double'
    const cv::Vec<double, 7> vv7 { 100.01, 100.02, 100.03, 100.04, 
                             100.05, 100.06, 100.07 }; 
    
    // Create a 14 x 1 vector with integer values
    const cv::Vec<int, 14> vv14 { 2, 4, 6, 8, 10, 12, 14, 16, 18, 
                            20, 22, 24, 26, 28 }; 
    
    // Create a 16 x 1 vector of integer values
    const cv::Vec<int, 16> vv16 { 10, 11, 12, 13, 14, 15, 16, 17, 
                            18, 19, 20, 21, 22, 23, 24, 25};  
    

    // 3. Use a Copy constructor to copy contents of an existing 
    //    vector into a new vector object
    const cv::Vec3d v4(v2);
    
    //                                     Print cv::Vec<> objects
    //                                     =======================

    std::cout << "\n********************* Print cv::Vec<> objects *********************************\n";

    // Just like cv::Matx<> data types you can change the way cv::Vec<> objects
    // are printed by manipulating cv::format() as in the following examples

    std::cout << "\nv1 (Default 'R' format) = \n" << v1 << '\n'; 

    std::cout << "\nv2 (Python format) = \n" 
              << cv::format(v2, cv::Formatter::FMT_PYTHON) << '\n';

    std::cout << "\nv3 (CSV format) = \n" 
              << cv::format(v3, cv::Formatter::FMT_CSV) << '\n';

    std::cout << "\nvv7 (MATLAB format) = \n" 
              << cv::format(vv7, cv::Formatter::FMT_MATLAB) << '\n';

    std::cout << "\nvv14 (NumPy format) = \n" 
              << cv::format(vv14, cv::Formatter::FMT_NUMPY) << '\n';

    std::cout << "\nvv16 (C format) = \n" 
              << cv::format(vv16, cv::Formatter::FMT_C) << '\n';

    std::cout << '\n';

    return 0;

}
```

**Output**

********************* Print cv::Vec<> objects *********************************

    v1 (Default 'R' format) = 
    [0, 0]

    v2 (Python format) = 
    [1.2,
    3.4,
    8.9]

    v3 (CSV format) = 
    1
    2
    3
    6


    vv7 (MATLAB format) = 
    (:, :, 1) = 
    100.01;
    100.02;
    100.03;
    100.04;
    100.05;
    100.06;
    100.07

    vv14 (NumPy format) = 
    array([2,
        4,
        6,
        8,
        10,
        12,
        14,
        16,
        18,
        20,
        22,
        24,
        26,
        28], dtype='int32')

    vv16 (C format) = 
    {10,
    11,
    12,
    13,
    14,
    15,
    16,
    17,
    18,
    19,
    20,
    21,
    22,
    23,
    24,
    25}

### Member Access

:notebook_with_decorative_cover: You can use either **operator[]** or **operator()** to access individual elements of **cv::Vec<>** objects.

:notebook_with_decorative_cover: If you want to know the number of elements in a **cv::Vec<>** object use the data member `channels`.

**Example 2**

```c++
#include "opencv2/core/core.hpp" // for OpenCV basic data types
#include <iostream>              // for std::cout

int main()
{

    const cv::Vec4f v3 { 1.0f, 2.0f, 3.0f, 6.0f }; 
   

    //                                    cv::Vec<> member access
    //                                    ========================

    std::cout << "\n********************* cv::Vec<> member access *********************************\n";

    // You can use either operator[] or operator() to access 
    // individual elements of cv::Vec<> objects

    std::cout << "\nWe will be using the following vector to illustrate member access = " 
              << v3 << '\n';
    std::cout << "\nElement at index 0 = " << v3[0] << '\n'; // operator[]
    std::cout << "\nElement at index 1 = " << v3(1) << '\n'; // operator()
    std::cout << "\nElement at index 2 = " << v3[2] << '\n';
    std::cout << "\nElement at index 3 = " << v3(3) << '\n';

    // If you want to know the number of elements in your 
    // cv::Vec<> object use data member 'channels'
    std::cout << "\nNumber of elements in v3 = " << v3.channels << '\n';

    return 0;

}
```

**Output**

    We will be using the following vector to illustrate member access = [1, 2, 3, 6]

    Element at index 0 = 1

    Element at index 1 = 2

    Element at index 2 = 3

    Element at index 3 = 6

    Number of elements in v3 = 4

### cv::Vec<> Algebra

:notebook_with_decorative_cover: You can use the basic math operations to perform basic algebra (+, -, *, /) on elements in a **cv::Vec<>** object.

:notebook_with_decorative_cover: You can also use compound operations (+=, -=, *=, /=).

**Example 3**

```c++
#include "opencv2/core.hpp" // for OpenCV basic data types
#include <iostream>              

int main()
{
    /*                                    cv::Vec<> algebra
     *                                    ==============
     *
     * 1. You can use the basic math operations to perform vector algebra
     * 2. You can also use compound operations (+=, -=, *=)
     * 
    */ 

    cv::Vec2i v5 { 1, 2};
    const cv::Vec2i v6 { 3, 4};
    const int scalar {2};

    std::cout << "\nAdd two vectors: " << v5 << " + " << v6 
              << " = " << v5 + v6 << '\n';

    std::cout << "\nSubtract two vectors: " << v6 << " - " << v5 
              << " = " << v6 - v5 << '\n';

    std::cout << "\nMultiply vector elements by a scalar value: " 
              << " = " << v5 * scalar << '\n';

    std::cout << "\nChange the sign of vector elements v5: " 
              << -v5 << '\n';

    v5 += v6;
    std::cout << "\nUse compound operator (+=). (v5 += v6 is the same as v5 = v5 + v6). " 
                 "\nThis will change the value of v5 to " << v5 << '\n';

    return 0;
}
```

**Output**

    Add two vectors: [1, 2] + [3, 4] = [4, 6]

    Subtract two vectors: [3, 4] - [1, 2] = [2, 2]

    Multiply vector elements by a scalar value:  = [2, 4]

    Change the sign of vector elements v5: [-1, -2]

    Use compound operator (+=). (v5 += v6 is the same as v5 = v5 + v6). 
    This will change the value of v5 to [4, 6]

### Member Functions

:notebook_with_decorative_cover: Remember that **cv::Vec<>** class inherits directly from **cv::Matx<>** class hence it has access to member functions from the **cv::Matx<>** class. There are too many to mention so we will only use a few here. For more see: https://docs.opencv.org/4.8.0/d6/dcf/classcv_1_1Vec.html .

**Example 4**

```c++
#include "opencv2/core.hpp" // for OpenCV basic data types
#include <iostream>             

int main()
{
    /*                                    cv::Vec<> member functions
     *                                    ==========================
     *
     * Remember that cv::Vec<> class inherits directly from cv::Matx<> class hence it has access
     * to member functions from the cv::Matx<> class. There are too many to mention so we will only
     * use a few here. For more see: https://docs.opencv.org/4.8.0/d6/dcf/classcv_1_1Vec.html
     *
    */
    
    // 1. Create a cv::Vec<> object with all elements with the same value
    const cv::Vec4d v7 {cv::Vec<double, 4>::all(6.0)}; 
    std::cout << "\nVector v7 with all elements equal to 6 = " << v7 << '\n';
    
    // 2. Create a cv::Vec<> object with all elements equal to 1
    const cv::Vec4i v8 { cv::Vec<int, 4>::ones() }; 
    std::cout << "\nVector v8 with all elements equal to 1 = " << v8 << '\n';

    // 3. Create a cv::Vec<> object with all elements equal to 0
    const cv::Vec3i v9 { cv::Vec<int, 3>::zeros() }; 
    std::cout << "\nVector v9 with all elements equal to 0 = " << v9 << '\n';
    
    // 4. Cross product of 2 3D vectors
    cv::Vec3f v10 {1.2f, 2.3f, 1.9f};
    cv::Vec3f v11 {1.0f, 2.0f, 3.0f};
    std::cout << "\nCross product of " << v10 << " and " << v11 
              << " = " << v10.cross(v11) << '\n';

    // 5. Per - element multiplication 
    cv::Vec3i v12 { 1, 2, 3};
    cv::Vec3i v13 { 3, 4, 5};
    std::cout << "\nPer -element multiplication of " << v12 << " and " << v13 
              << " = " << v12.mul(v13) << '\n';  


    return 0;

}
```

**Output**

    Vector v7 with all elements equal to 6 = [6, 6, 6, 6]

    Vector v8 with all elements equal to 1 = [1, 1, 1, 1]

    Vector v9 with all elements equal to 0 = [0, 0, 0]

    Cross product of [1.2, 2.3, 1.9] and [1, 2, 3] = [3.1, -1.7, 0.1]

    Per -element multiplication of [1, 2, 3] and [3, 4, 5] = [3, 8, 15]