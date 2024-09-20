## The Size Data Type

:notebook_with_decorative_cover: Size data types are instantiated from the <a href = "https://docs.opencv.org/4.8.0/d6/d50/classcv_1_1Size__.html">cv::Size_<></a> template class

:notebook_with_decorative_cover: It has two data members named: `width` & `height`, which we will discuss later.

:notebook_with_decorative_cover: It is usually used to hold the dimensions of an image or rectangle

:notebook_with_decorative_cover: **Size** data types can be cast to and from the **Point** data type class, but cannot be cast to **Vector** data type class hence have restricted member functions

:notebook_with_decorative_cover: There are 5 defined aliases for **Size** data types: 
1. `cv::Size`   -> integer size object
2. `cv::Size2i` -> same as above
3. `cv::Size2f` -> 32-bit floating-point size object 
4. `cv::Size2d` -> double-precision floating-point size object
5. `cv::Size2l` -> 64-bit integer size object. Can hold values larger than `cv::Size2i`

**N.B:** If you don't remember the range of the above data types, refer back to notes on **Point** data types.

### Creating Size data objects

:notebook_with_decorative_cover: Just like all OpenCV basic data types, you can use default, value and copy constructors to create **Size** data objects. This is shown in the following example.

**Example 1**
```c++
#include "opencv2/core.hpp" // For OpenCV core types
#include <iostream>         // For std::cout
#include <iomanip>          // For std::setprecision()

int main()
{
    
    // 1. Default Constructor - values will be set to width = 0 & height = 0
    const cv::Size sz;
    
    // 2. Value Constructors - here you provide the width and height of your 2-D Size object
    // By now you should be familiar with using Uniform Initialization as per Modern C++
    
    const cv::Size   sz1 { 345, 890 };                        // integer Size object (default alias) of width = 345 & height = 890
    const cv::Size2i sz2 { 345, 890 };                        // integer Size object
    const cv::Size2l sz3 { 3147483648, 4147483648 };          // 64-bit integer Size object
    const cv::Size2f sz4 { 234.5f, 789.6f };                  // 32-bit floating-point size object
    const cv::Size2d sz5 { 346.89213456, 456.08765536 };   // double-precision floating-point size object

    // Use copy constructor to copy values from one Size object (sz2) into another (sz6)

    const cv::Size2i sz6(sz2);

    //                               Print Size objects
    //                               ==================

    // Take note of how we can use std::setprecision() to print a numeric 
    // value to the precision we want.
    std::cout << "\nsz = " << sz 
              << "\nsz1 = " << sz1
              << "\nsz2 = " << sz2
              << "\nsz3 = " << sz3
              << "\nsz4 = " << sz4
              << "\nsz5 = " << std::setprecision(11) << sz5
              << "\nsz6 = " << sz6;

    // Set precision size back to the default 6 significant values
    std::cout << std::setprecision(6);
    std::cout << '\n';

    return 0;

}
```

**Output**

    sz = [0 x 0]
    sz1 = [345 x 890]
    sz2 = [345 x 890]
    sz3 = [3147483648 x 4147483648]
    sz4 = [234.5 x 789.6]
    sz5 = [346.89213456 x 456.08765536]
    sz6 = [345 x 890]


### Member Access

:notebook_with_decorative_cover: As mentioned earlier **Size** objects have two data members, `width` and `height`. These are implemented as public attributes hence we can access them directly without having to go through a function. 

**Example 2**
```c++
#include "opencv2/core.hpp"
#include <iostream>

int main()
{    
    const cv::Size   sz1 { 345, 890 };                        

    // Access individual elements using the key data members 'width' & 'height'
    std::cout << "\nObject sz1 has width: " << sz1.width << " and height: " 
              << sz1.height << '\n';

    return 0;

}
```

**Output**

Object sz1 has width: 345 and height: 890

### Member Functions

:notebook_with_decorative_cover: The Size data type has 3 member functions directly associated with it.

1. `T cv::Size_<T>::area() const` - compute the area using $width * height$
2. `double cv::Size_<T>::aspectRatio() const` - compute aspect ratio using $width / height$
3. `bool cv::Size_<T>::empty() const` - Check if a Size object is empty, that is its values are (0, 0)

**Example 3**
```c++
#include "opencv2/core.hpp"
#include <iostream>

int main()
{
    // Use Default Constructor - values will be set to width = 0 & height = 0
    const cv::Size sz {}; 
    
    // integer Size object (default alias) of width = 345 & height = 890 
    const cv::Size   sz1 { 345, 890 };  

    //                              Member Functions
    //                              ================

    // 1. Compute the area of a Size object (width x height)
    std::cout << "\nArea of object " << sz1 << " = " << sz1.area() << '\n';

    // 2. Compute the aspect ratio (width/height)
    std::cout << "\nAspect ratio of image with dimensions " << sz1 
              << " is " << sz1.aspectRatio() << '\n';

    // 3. Check if a Size object is empty, that is its values are (0, 0)
    std::cout << std::boolalpha; 
    std::cout << '\n' << sz << " is empty: " << sz.empty() << '\n';

    std::cout << '\n';

    return 0;

}
```

**Output**

    Area of object [345 x 890] = 307050

    Aspect ratio of image with dimensions [345 x 890] is 0.38764

    [0 x 0] is empty: true

## Casting 

:notebook_with_decorative_cover: We can cast Size objects to Point objects. Prefer using explicit casting - this makes it clear what you want to do.

**Example 4**
```c++
#include "opencv2/core.hpp"
#include <iostream>

int main()
{
    const cv::Size2d sz7 {10.5, 6.8};

    // Explicitly cast to Point data type
    auto point_object = static_cast<cv::Point2d>(sz7);  
    std::cout << "\nData type of " << point_object << " is " 
              << typeid(point_object).name();  

    std::cout << '\n';

    return 0;
}
```

**Output**

Data type of [10.5, 6.8] is N2cv6Point_IdEE