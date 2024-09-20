## The Rect Data Type
        
:notebook_with_decorative_cover: The Rect class template, <a href = "https://docs.opencv.org/4.8.0/d2/d44/classcv_1_1Rect__.html">cv::Rect_<></a> is used for representing 2-dimensional rectangular objects. We can use cv::Rect_<> objects to define an image or **Region of Interest (ROI)** within an image.

:notebook_with_decorative_cover: It has 4 data members: 
1. `x` & `y` of the **Point** class (representing the **upper-left corner** coordinates of a rectangle)
2. `width` & `height` of the **Size** class (representing the rectangle's size)
        
:notebook_with_decorative_cover: Just like previous data types we have encountered so far, the **cv::Rect_<>** template class also makes          use of aliases, which we will use when instantiating objects of the **Rect** data type.

:notebook_with_decorative_cover: OpenCV typically assumes that the top and left boundary of the rectangle are inclusive, while the right and bottom boundaries are not.

### Creating Rect data objects

:notebook_with_decorative_cover: There are a number of ways we can create objects of data type **Rect**.
1. Use of a default constructor - where OpenCV will provide all the values, which will be zeros, which is really not very useful since we can't really do much with a rectangle whose width & height are both zero's.
2. Value constructor - the user provides the starting coordinates (or upper-left corner coordinates) of our rectangle, plus its width and height
3. Use a copy constructor to copy values from one Rect object to another.
4. Provide the origin of a rectangle as a Point data type and the width and height as a Size data type. This constructor will have the syntax `cv::Rect(cv::Point p, cv::Size sz)`.
5. Provide the coordinates of the upper-left corner and bottom-right corner of the rectangle as Point data types. This constructor will have the syntax `cv::Rect(cv::Point p1, cv::Point p2)`.

:notebook_with_decorative_cover: The above methods are shown in the following example:

**Example 1**
```c++
#include "opencv2/core.hpp"
#include <iostream>

int main()
{  

    //                                  Instantiating Rectangular Objects
    //                                  =================================

    // 1. Use the Default constructor
    const cv::Rect r {};  // all values will be zeros and are considered to be integers

    // 2. Use Value contructor with syntax cv::Rect(x, y, width, height)
    const cv::Rect2i  r1   { 0, 0, 230, 456 };            // Rectangle with width = 230, height = 456 and starting from coordinates (0, 0)
    const cv::Rect2d  r2   { 4.0, 3.0, 345.67, 590.76 };  // Rectangle with width = 345.67, height = 590.76 and starting from coordinates (4.0, 3.0)

    // 3. Create a Rectangle using Point and Size data types, 
    //    syntax is cv::Rect(cv::Point, cv::Size)

    const cv::Point2i p_1  { 5, 10 };     // upper-left coorner coordinates
    const cv::Size2i  sz_1 { 125, 300 };  // width and height of rectangle
    const cv::Rect    r3   { p_1, sz_1 };

    // 4. Create a Rectangle using Point data types for the 
    //    'upper-left corner' and 'bottom-right corner' coordinates
    //    It has the syntax ->  cv::Rect(cv::Point, cv::Point)

    const cv::Point2d p_2  { 0.0, 0.0 };       // upper-left corner coordinates
    const cv::Point2d p_3  { 346.9, 400.78 };  // bottom-right corner coordinates
    const cv::Rect2d  r4   { p_2, p_3 };

    // 5. Use a copy constructor to copy values from a rect object (r1) to another(r5)
    const cv::Rect2i r5(r1);

    //                                 Printing Rect Objects
    //                                 =====================
    std::cout << "\nr = " << r << '\n';
    std::cout << "r1 = " << r1 << '\n';
    std::cout << "r2 = " << r2 << '\n';
    std::cout << "r3 = " << r3 << '\n';
    std::cout << "r4 = " << r4 << '\n';
    std::cout << "r5 = " << r5 << '\n';

    return 0;
}
```

**Output**

    r = [0 x 0 from (0, 0)]
    r1 = [230 x 456 from (0, 0)]
    r2 = [345.67 x 590.76 from (4, 3)]
    r3 = [125 x 300 from (5, 10)]
    r4 = [346.9 x 400.78 from (0, 0)]
    r5 = [230 x 456 from (0, 0)]


### Member Access

:notebook_with_decorative_cover: **Rect** objects have 4 data members `x`, `y`, `width` & `height`, which are public attributes. We can access them directly using their names as in the following example.

**Example 2**
```c++
#include "opencv2/core.hpp"
#include <iostream>

int main()
{
    
    // Use value contructor with syntax cv::Rect(x, y, width, height)
    // to create a cv::Rect object
    const cv::Rect2i  r1   { 0, 0, 230, 456 }; 


    /*                                  Member access
     *                                  =============
     *
     * Rect objects have 4 data members 'x', 'y', 'width' & 'height', and we can 
     * access them individually.
     */

    std::cout << "\nRectangle r1 : " 
              << "\n\tupper_left_corner: (" << r1.x << ", " << r1.y << ") "
              << "\n\twidth: " << r1.width
              << " \n\theight: " << r1.height << '\n';

    return 0;
}
```

**Output**

    Rectangle r1 : 
            upper_left_corner: (0, 0) 
            width: 230 
            height: 456

### Member Functions

:notebook_with_decorative_cover:  **cv::Rect_<>** provides the following member functions:

1. `T cv::Rect_<T>::area() const` - compute the area of a cv::Rect object using $width * height$. Data type `T` of the computed value will match basic type of cv::Rect.
2. `cv::Point_<T> cv::Rect_<T>::br() const` - get the co-ordinates of the bottom-right (br) corner of a cv::Rect object. These are returned as a 2D cv::Point object.
3. `cv::Point_<T> cv::Rect_<T>::tl() const` - get the co-ordinates of the top-left (tl) corner of a cv::Rect object. These are returned as a 2D cv::Point object.
4. `cv::Size_<T> cv::Rect_<T>::size() const` - returns the width and height of a cv::Rect object as a cv::Size object
5. `bool cv::Rect_<T>::contains(const cv::Point_<T>& pt) const` - this function checks whether the point `pt` can be found within the cv::Rect object.
6. `bool cv::Rect_<T>::empty() const` this function checks whether the width and height of a cv::Rect object are `0` values.

**Example 3**
```c++
#include "opencv2/core.hpp"
#include <iostream>

int main()
{
    
    const cv::Rect r {};
    const cv::Rect2i  r1   { 0, 0, 230, 456 };     
    
    //                                 Member functions
    //                                 ================

     // 1. Compute the area of a rectangle
    std::cout << "\nArea of " << r1 << " = " << r1.area() << '\n';

    // 2. Extract the upper-left corner coordinates
    std::cout << "\nUpper-left corner coordinates of " << r1 << " = " << r1.tl() << '\n';

    // 3. Extract bottom-right corner coordinates
    std::cout << "\nBottom-right corner coordinates of " << r1 << " = " << r1.br() << '\n';

    // 4. Extract the 'width' and 'height' as a cv::Size object
    std::cout << "\nWidth and Height dimensions of " << r1 << " = " << r1.size() << '\n'; 
    
    // 5. Determine if a cv::Point object is inside a cv::Rect object
    const cv::Point2i p {23, 50};
    std::cout << std::boolalpha; // to print 'true' or 'false' NOT '1' or '0'
    std::cout << "\nIs point " << p << " inside rectangle " << r1 << " = " 
              << r1.contains(p) << '\n'; 

    // 6. Check if a cv::Rect object is empty
    std::cout << "\nIs rect " << r << " empty? " << r.empty() << '\n';
    std::cout << "\nIs rect " << r1 << " empty? " << r1.empty() << '\n';

    std::cout << '\n';

    return 0;
}
```

**Output**

    Area of [230 x 456 from (0, 0)] = 104880

    Upper-left corner coordinates of [230 x 456 from (0, 0)] = [0, 0]

    Bottom-right corner coordinates of [230 x 456 from (0, 0)] = [230, 456]

    Width and Height dimensions of [230 x 456 from (0, 0)] = [230 x 456]

    Is point [23, 50] inside rectangle [230 x 456 from (0, 0)] = true

    Is rect [0 x 0 from (0, 0)] empty? true

    Is rect [230 x 456 from (0, 0)] empty? false


:notebook_with_decorative_cover: In addition to the above member functions, cv:;Rect_<> also implements math, logical and comparison operators. These operators enable us to for example:

* shift a cv::Rect left/right/top/bottom, 
* increase/decrease the size of a cv::Rect object, 
* find the union/intersection of two cv::Rect objects,
* find out if two cv::Rect object are equal/not equal.

**Example 4**
```c++
#include "opencv2/core.hpp"
#include <iostream>

int main()
{
    // 1. Use the default constructor
    const cv::Rect r {};  // all values will be zeros and are considered to be integers

    // 2. Use value contructors with syntax cv::Rect(x, y, width, height)
    const cv::Rect2i  r1   { 0, 0, 230, 456 };            // Rectangle with width = 230, height = 456 and starting from coordinates (0, 0)
    const cv::Rect2d  r2   { 4.0, 3.0, 345.67, 590.76 };  // Rectangle with width = 345.67, height = 590.76 and starting from coordinates (4.0, 3.0)

    // 3. Create a Rectangle using Point and Size data types, syntax is cv::Rect(cv::Point, cv::Size)

    const cv::Point2i p_1  { 5, 10 };     // upper-left coorner coordinates
    const cv::Size2i  sz_1 { 125, 300 };  // width and height of rectangle
    const cv::Rect    r3   { p_1, sz_1 };

    // 4. Create a Rectangle using Point data types for the 'upper-left corner' and 'bottom-right corner' coordinates
    //    It has the syntax =  cv::Rect(cv::Point, cv::Point)

    const cv::Point2d p_2  { 0.0, 0.0 };       // upper-left corner coordinates
    const cv::Point2d p_3  { 346.9, 400.78 };  // bottom-right corner coordinates
    const cv::Rect2d  r4   { p_2, p_3 };

    // 5. Use a copy constructor to copy values from a rect object (r1) to another(r5)
    const cv::Rect2i r5(r1);


    //                           Compute geometrical properties of two rectangles
    //                           ================================================

    // 1. Shift a rectangle by a certain offset

    std::cout << "\nMove or translate rectangle r1 to the right by 10 units along the x-axis: " 
              << (r1 + cv::Point(10, 0)) << '\n';

    std::cout << "\nMove or translate rectangle r3 to the left by 2 units along the x-axis: " 
              << (r3 - cv::Point(-2, 0)) << '\n';

    std::cout << "\nMove or translate rectangle r3 up by 3 units along the y-axis: " 
              << (r3 + cv::Point(0, -3)) << '\n';

    std::cout << "\nMove or translate rectangle r3 down by 3 units along the y-axis: " 
              << (r3 + cv::Point(0, 3)) << '\n';

    // 2. Expand or shrink a rectangle

    std::cout << "\nEnlarge rectangle r2 by 5 units along the width and 15 units along the height: "
              << (r2 + cv::Size2d(5.0, 15.0)) << '\n';

    std::cout << "\nShrink rectangle r2 by 5 units along the width and 15 units along the height: "
              << (r2 - cv::Size2d(5.0, 15.0)) << '\n';

    // 3. Find the intersection/union between rectangles

    std::cout << "\nRectangle formed by the Union between r2 & r4: " << (r2 | r4) << '\n'; 

    std::cout << "\nRectangle formed by the Intersection of rectangles r2 & r4: " << (r2 & r4) << '\n'; 

    // 4. Check if two rectangles are equal

    std::cout << "\nAre rectangles r1 & r5 equal: " << (r1 == r5) << '\n';

    std::cout << "\nAre rectangles r1 & r3 equal: " << (r1 == r3) << '\n';    

    std::cout << '\n';

    return 0;
}
```

**Output**

    Move or translate rectangle r1 to the right by 10 units along the x-axis: [230 x 456 from (10, 0)]

    Move or translate rectangle r3 to the left by 2 units along the x-axis: [125 x 300 from (7, 10)]

    Move or translate rectangle r3 up by 3 units along the y-axis: [125 x 300 from (5, 7)]

    Move or translate rectangle r3 down by 3 units along the y-axis: [125 x 300 from (5, 13)]

    Enlarge rectangle r2 by 5 units along the width and 15 units along the height: [350.67 x 605.76 from (4, 3)]

    Shrink rectangle r2 by 5 units along the width and 15 units along the height: [340.67 x 575.76 from (4, 3)]

    Rectangle formed by the Union between r2 & r4: [349.67 x 593.76 from (0, 0)]

    Rectangle formed by the Intersection of rectangles r2 & r4: [342.9 x 397.78 from (4, 3)]

    Are rectangles r1 & r5 equal: true

    Are rectangles r1 & r3 equal: false