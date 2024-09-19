## The Scalar Data Type

:notebook_with_decorative_cover: The Scalar data type is a class that can hold up to 4 numeric values. 
        
:notebook_with_decorative_cover: It is implemented as a template: <a href = "https://docs.opencv.org/4.8.0/d1/da0/classcv_1_1Scalar__.html">cv::Scalar_<></a>

:notebook_with_decorative_cover: It has some special member functions associated with uses of four-component vectors in Computer Vision e.g storing color values (red, green, blue, alpha)

:notebook_with_decorative_cover: **cv::Scalar_<>** inherits directly from a fixed Vector class template. This means it inherits all of the vector algebra operations, member access functions (i.e operator[]), and other properties from the fixed vector classes. This also means you do not have to cast Scalar types to Vector types in order to use the Vector member functions. We will discuss the Vector data types later.
         
:notebook_with_decorative_cover: If you don't include all 4 values when instantiating a Scalar object OpenCV will simply **add zeros for the missing values**.

:notebook_with_decorative_cover: cv::Scalar_<> has one alias **cv::Scalar** - which holds 4 double-precision floating-point values. As such if you want your Scalar object to contain values of another data type other than double precision floating-point values you have to use the actual template definition e.g., for a Scalar object with integer values use `cv::Scalar_<int>`.

### Create Scalar Data Types

:notebook_with_decorative_cover: There are three constructors you can use to create **Scalar** data types: 
1. Default constructor - you do not have to provide the values, OpenCV will do that for you. OpenCV will set every value to 0 and the default primitive type is `double`.
2. Value constructor - you have to provide values for Scalar objects when using value constructors. If you provide less than 4 values, OpenCV will add zero's for the missing values. Since there is only one alias (**cv::Scalar**) for **Scalar** objects of type double, if you want your values to be of type `float` or `int`, you have to use the template format e.g. `cv::Scalar_<int>` or `cv::Scalar_<float>`. Do not forget the **underscore (_)** after the word Scalar.
3. Copy constructor - you use this to create a new Scalar object by copying values from an existing Scalar object.

**Example 1**
```c++
#include "opencv2/core.hpp" // header file with OpenCV basic data types
#include <iostream>              

int main()
{
    //                               Instantiate Scalar objects
    //                               =========================

    // 1. Use default constructor to create Scalar objects
    const cv::Scalar s {};

    // 2. Use value constructors
    //    We will use uniform initialization to assign values to our 
    //    Scalar objects as per modern c++
    //    Unless specified Scalar objects holds values of type 'double'

    const cv::Scalar s1 { 5.6 };                            // OpenCV will add Zero's for the 3 missing values               
    const cv::Scalar s2 { 0.23, 5.6, 9.8, 3.4 };            // All values are of type 'double'
    const cv::Scalar_<float> s4 { 5.4f, 9.0f, 2.3f, 7.8f }; // Scalar object with 4 values of type 'float'
    const cv::Scalar_<int> s3 {7, 6, 8, 10};                // Scalar object with 4 integer values

    // 3. Use copy constructor to copy values from one Scalar object (s2) into another (s5)
    
    const cv::Scalar s5(s2); 
    

    //                              Print a Scalar object 
    //                              =====================
    std::cout << "\ns = " << s << '\n';
    std::cout << "s1 = " << s1 << '\n';
    std::cout << "s2 = " << s2 << '\n';
    std::cout << "s3 = " << s3 << '\n';
    std::cout << "s4 = " << s4 << '\n';
    std::cout << "s5 = " << s5 << '\n';    

    return 0;
}
```

**Output**

    s = [0, 0, 0, 0]
    s1 = [5.6, 0, 0, 0]
    s2 = [0.23, 5.6, 9.8, 3.4]
    s3 = [7, 6, 8, 10]
    s4 = [5.4, 9, 2.3, 7.8]
    s5 = [0.23, 5.6, 9.8, 3.4]

### Member Access

:notebook_with_decorative_cover: When accessing individual elements of a **Scalar** object we use the **subscript operator `[]`** usually in combination with a `for` loop that uses an integer index. As of OpenCV 4.8.0, unfortunately you cannot use the modern C++ range-based for loop `for (value : range)` with OpenCV core types because they do not have suitable iterators. 

:notebook_with_decorative_cover: The following example shows how to access data members of a Scalar object using an index based `for` loop. Like most containers, indices for a Scalar object start at `0`.

**Example 2**
```c++
#include "opencv2/core.hpp" // header file with OpenCV basic data types
#include <iostream>              

int main()
{   

    cv::Scalar s2 { 0.23, 5.6, 9.8, 3.4 };           
    
    std::cout << "\nAccessing individual values of s2: \n";
    
    // Use an index-based 'for' loop to traverse through a Scalar object
    for (int i { 0 }; i < 4; ++i)
    {
        std::cout << "\tValue at index " << i << " = " << s2[i] << '\n'; 
    }
    std::cout << '\n';

    return 0;
}
```

**Output**

    Accessing individual values of s2: 
        Value at index 0 = 0.23
        Value at index 1 = 5.6
        Value at index 2 = 9.8
        Value at index 3 = 3.4


### Member functions

:notebook_with_decorative_cover: There are too many member functions to mention here. You also have to remember that **Scalar** data types inherit other member functions directly from the **Vector** data class. The **Vector** class also inherits from the **Fixed Matrix Class `Matx`** - meaning Scalar objects also have access to the `Matx` member functions. For a detailed list if you are using OpenCV version 4.8.0 see the following web pages:
1. https://docs.opencv.org/4.8.0/d1/da0/classcv_1_1Scalar__.html
2. https://docs.opencv.org/4.8.0/d6/dcf/classcv_1_1Vec.html - these are the ones inherited from the Vector template class 

:notebook_with_decorative_cover: In the following example, we will show how to use some of these member functions.

**Example 3**
```c++
#include "opencv2/core.hpp" 
#include <iostream>             

int main()
{
    
    cv::Scalar s2 { 0.23, 5.6, 9.8, 3.4 };  // all values are of type 'double'
    
    cv::Scalar s5(s2);                      // use a copy constructor        
    
    // 1. all() - Used to create a Scalar object with all elements set to the same value
    //          - This is a member function of cv::Scalar
    const cv::Scalar_<int> sameValuesScalar = cv::Scalar_<int>::all(7);
    std::cout << "\nScalar object with all elements set to the same value: " << sameValuesScalar << '\n';

    // 2. conj() - Compute the conjugate of a Scalar object. Returns cv::Scalar(v0, -v1, -v2, -v3)
    //           - This is a member function of cv::Scalar
    std::cout << "\nConjugate of " << s2 << " is " << s2.conj() << '\n';

    // 3. mul() - Element-wise multiplication between two Scalar objects
    std::cout << "\nElement-wise multiplication of " 
              << s2 << " and " << s5 << " = "
              << s2.mul(s5) << '\n';

    // 4. Use basic math operators on Scalar objects
    //    These operations are inherited from cv::Vec
    std::cout << "\nAddition: " << s2 << " + " << s5 << " = " << s2 + s5 
              << "\nSubtraction: " << s2 << " - " << s5 << " = " << s2 - s5 
              << "\nMultiplication: " << s2 << " x " << 2 << " = "<< s2 * 2 
              << "\nDivision: " << s2 << " / " << 0.1 << " = " << s2 * 0.1 << '\n';

    // 5. Use comparison operators
    //    These are inherited from cv::Matx
    std::cout << "\nIs " << s2 << " equal to " << s5 << " : " 
              << std::boolalpha << (s2 == s5) << '\n';
    
    // 6. randn() - Generate normally distributed random numbers
    //            - Function is inherited from cv::Matx
    std::cout << "\nScalar object with normally distributed random numbers with " 
              << " mean value of 2.5 "
              << " and standard deviation of 0.1 = " 
              << cv::Scalar::randn(2.5, 0.1);

    // 7. randu() - Generate uniformly distributed random numbers between 2 values
    //            - Function is inherited from cv::Matx
    std::cout << "\nScalar object with uniformly distributed random integer numbers " 
              << " between 10 and 25 = "
              << cv::Scalar_<int>::randu(10, 25);

    
    std::cout << '\n';

    return 0;
}
```

**Output**

    Scalar object with all elements set to the same value: [7, 7, 7, 7]

    Conjugate of [0.23, 5.6, 9.8, 3.4] is [0.23, -5.6, -9.8, -3.4]

    Element-wise multiplication of [0.23, 5.6, 9.8, 3.4] and [0.23, 5.6, 9.8, 3.4] = [0.0529, 31.36, 96.04, 11.56]

    Addition: [0.23, 5.6, 9.8, 3.4] + [0.23, 5.6, 9.8, 3.4] = [0.46, 11.2, 19.6, 6.8]
    Subtraction: [0.23, 5.6, 9.8, 3.4] - [0.23, 5.6, 9.8, 3.4] = [0, 0, 0, 0]
    Multiplication: [0.23, 5.6, 9.8, 3.4] x 2 = [0.46, 11.2, 19.6, 6.8]
    Division: [0.23, 5.6, 9.8, 3.4] / 0.1 = [0.023, 0.56, 0.98, 0.34]

    Is [0.23, 5.6, 9.8, 3.4] equal to [0.23, 5.6, 9.8, 3.4] : true

    Scalar object with normally distributed random numbers with  mean value of 2.5  and standard deviation of 0.1 = [2.5, 2.51581, 2.42991, 2.45714]
    Scalar object with uniformly distributed random integer numbers  between 10 and 25 = [17, 20, 21, 18]


