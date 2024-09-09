# The Point Data Type


:notebook_with_decorative_cover: Of the **OpenCV** basic types, the **Point** data type is probably the simplest.

**N.B**: Before we go any further, you should know that classes, functions or anything related to OpenCV is written within the namespace **cv**.

:notebook_with_decorative_cover: The Point data class is implemented based on two class templates. 

1. <a href = "https://docs.opencv.org/4.8.0/db/d4e/classcv_1_1Point__.html">cv::Point_<></a>  - for objects with 2 values e.g 2-dimensional point with an x-coordinate and y-coordinate
2. <a href = "https://docs.opencv.org/4.8.0/df/d6c/classcv_1_1Point3__.html">cv::Point3_<></a> - for objects with 3 values e.g. 3-dimensional point with an x-coordinate, y-coordinate and z-coordinate

:notebook_with_decorative_cover: When defining Point data types you are encouraged to use their aliases rather than template definitions. Aliases take forms like **cv::Point2i** or **cv::Point3f**, with the last letter indicating the desired primitive basic data types, which were borrowed from **C++**. In OpenCV, the primitive types are as follows:

- **i** - integer -> 32-bit integer in the range: -2 147 483 648 to 2 147 483 647 (inclusive)
- **f** - float -> 32-bit floating/decimal point number accurate to between 6 and 9 digits
- **d** - double -> 64-bit floating/decimal point number, which is more accurate than the 32-bit floating number. Can be accurate to between 15 and 18 digits of precision. 
- **b** - unsigned char -> used to hold any integer in the range: 0 to 255 (inclusive)
- **s** - short -> holds positive and negative integers, with the range: -32 768 to 32 767 (inclusive) 
- **w** - unsigned short -> holds only positive integers with the range: 0 to 65535 (inclusive)

:notebook_with_decorative_cover: Using the above primitive types OpenCV builds aliases for Point data types using the format: **{cv::Point}{2,3}{i, f, d, b, s, w}**, for example **cv::Point2i**. You need to master how to use type aliases as you will encounter them from this lesson onwards. The following table gives some of the common aliases used when dealing with Point data types.

| Template Definition| Aliase      | Description |
|--------------------|-------------|-------------|
| **cv::Point_\<int>**   | `cv::Point2i` | Point object with 2 integer values|
| **cv::Point_\<float>** | `cv::Point2f` | Point object with 2 values of type float |
| **cv::Point_\<double>**| `cv::Point2d` | Point object with 2 values of type double |
| **cv::Point3_\<int>**  | `cv::Point3i` | Point object with 3 integer values|
| **cv::Point3_\<float>**| `cv::Point3f` | Point object with 3 values of type float|
| **cv::Point3_\<double>**| `cv::Point3d` | Point object with 3 values of type double|

:notebook_with_decorative_cover: **Point** data types do not have a lot of operations defined on them, but they can be cast to other types such as the fixed **Vector** class or the fixed **Matrix** classes, when needed. We will discuss the Vector and Matrix data types in a future tutorial. Casting can be implicit (C++ compiler will automatically do this for you) or explicit (use `static_cast<new type>(value)` from C++ to explicitly tell the compiler what to cast to). However, I think if you find yourself having to cast to other types frequently - it's best you just use another data type with all the functionality you need.

## Creating Point data objects

:notebook_with_decorative_cover: This is often known as **object instantiation** in Object Oriented Programming (OOP) languages such as C++, Java, Python etc.

:notebook_with_decorative_cover: The Point data classes provide 3 constructors you can use to create or instantiate a Point object:

1. **Default Constructors** - for creating Point objects with default values provided by OpenCV. The objects will most likely contain zero's as values.
2. **Value Constructors** - allow the user to provide the values for the Point object.
3. **Copy Constructor** - create a new Point object by copying values from another already created Point data type. To avoid loss of information e.g. rounding off errors or missing decimal values, make sure both objects have the same data type. Depending on your compiler set up, you might get a warning about information loss if for example you try to copy values from a Point object with float or double values to a Point object expecting integer values since this results in the decimal part being removed as it cannot fit into memory set asside for integer values.

:notebook_with_decorative_cover: Before we start to code, you should know that all OpenCV core data types are found in the header file **core.hpp**. As such you should include this header file at the top of your code files.

**Example**

```c++
#include "opencv2/core.hpp" // include path to header file with all our basic data types

int main()
{
    // 1. Create Point objects with default values 
    //    We are using Default constructors

    cv::Point2i p1; // Point object with 2 default integer values (0, 0)
    cv::Point3f p2; // Point object with 3 default floating point values (0.0, 0.0, 0.0)

    // 2. Create Point objects with values provided by the user 
    //    We are using Value constructors
    
    cv::Point2i p3 {5, 6};              // Point object with 2 integer values
    cv::Point3i p4 {12, -18, 9};        // Point object with 3 integer values
    cv::Point3f p5 {3.4f, 9.8f, 0.9f};  // Point object with 3 32-bit float values
    cv::Point2d p6 {2.65, 4.97};        // Point object with 2 double precision values

    // 3. Use Copy constructor to copy values from one point object (p5) into another (p7). 
    
    cv::Point3f p7(p5); // both objects have the same primitive data type (float)

    return 0;
}
```

## Printing Point data objects

:notebook_with_decorative_cover: OpenCV offers support for output of its common OpenCV data structures via the C++ **insertion (<<) operator**. This means we can use `std::cout` with the `<<` operator to print OpenCV core data types as we would most C++ types.

**Example**
```c++
#include "opencv2/core.hpp" // Include path to header file with all our basic data types
#include <iostream>         // Gives us access to std::cout

int main()
{
    // 1. Create Point objects with default values 
    //    We are using Default constructors

    cv::Point2i p1; // Point object with 2 default integer values (0, 0)
    cv::Point3f p2; // Point object with 3 default floating point values (0.0, 0.0, 0.0)

    // 2. Create Point objects with values provided by the user 
    //    We are using Value constructors
    
    cv::Point2i p3 {5, 6};              // Point object with 2 integer values
    cv::Point3i p4 {12, -18, 9};        // Point object with 3 integer values
    cv::Point3f p5 {3.4f, 9.8f, 0.9f};  // Point object with 3 32-bit float values
    cv::Point2d p6 {2.65, 4.97};        // Point object with 2 double precision values

    // 3. Use Copy constructor to copy values from one point object (p5) into another (p7). 
    
    cv::Point3f p7(p5); // both objects have the same primitive data type (float)

    // print Point data objects on console
    std::cout << "\nPoint p1 = " << p1 << '\n';
    std::cout << "Point p2 = " << p2 << '\n';
    std::cout << "Point p3 = " << p3 << '\n';
    std::cout << "Point p4 = " << p4 << '\n';
    std::cout << "Point p5 = " << p5 << '\n';
    std::cout << "Point p6 = " << p6 << '\n';
    std::cout << "Point p7 = " << p7 << '\n';

    return 0;
}

```

**Output**

    Point p1 = [0, 0]
    Point p2 = [0, 0, 0]
    Point p3 = [5, 6]
    Point p4 = [12, -18, 9]
    Point p5 = [3.4, 9.8, 0.9]
    Point p6 = [2.65, 4.97]
    Point p7 = [3.4, 9.8, 0.9]

## Member access

:notebook_with_decorative_cover: Since Point data types are implemented as class templates, to access the individual values, use the data attributes `x` and `y` for 2-dimensional Point and `x`, `y` and `z` for 3-dimensional Point objects. These attributes are implemented as **public** member variables hence we can access them directly without the need for a member function.

**Example**

```c++
#include "opencv2/core.hpp" // include path to header file with all our basic data types
#include <iostream>         // For std::cout

int main()
{
    // 1. Create Point objects 

    cv::Point2i p1;                     // 2D point object with default integer coordinates (0, 0)
    cv::Point3f p5 {3.4f, 9.8f, 0.9f};  // 3D point whose coordinates are 32-bit float

    // Access indivudual values of Point data object 'p1'
    std::cout << "\nX-coordinate of p1 = " << p1.x 
              << ", Y-coordinate of p1 = " << p1.y 
              << "\n";

    // Access individual values of Point data object 'p5'
    std::cout << "X-coordinate of p5 = " << p5.x 
              << ", Y-coordinate of p5 = " << p5.y 
              << ", Z-coordinate of p5 = " << p5.z 
              << "\n";

    return 0;
}

```

**Output**

    X-coordinate of p1 = 0, Y-coordinate of p1 = 0
    X-coordinate of p5 = 3.4, Y-coordinate of p5 = 9.8, Z-coordinate of p5 = 0.9

## Member functions

:notebook_with_decorative_cover: Compared to other OpenCV basic data types you will encounter in later tutorials, the Point data type has the fewest functions associated with its class. At this early stage of your learning you might struggle to visualize scenarios were you will need some of these functions - but trust me you will. For the mean time you just need to know how to use the functions and where to find these functions. For 2D Point objects the member functions have the following signatures. The letter `T` stands for any of the basic data type: integer, float, double, unsigned char, short, unsigned short

1. `T dot(const cv::Point_<T>& pt) const` - Compute the <a href = "https://www.mathsisfun.com/algebra/vectors-dot-product.html">**dot product**</a> between two <a href = "https://www.bbc.co.uk/bitesize/guides/zgcrjty/revision/1">**vectors**</a>. Vectors that originate from the origin (0,0) or (0,0,0) in 2D or 3D space, respectively, are usually just defined by the amount of movement along the x-axis, y-axis and/or z-axis from the origin to their end point. We can use the Point data type to define such vectors. The computed dot product between such vectors is a scalar value and when using this function it will be returned as the *same data type as that of the Point objects used*. There is a good introduction <a href = "https://www.mathsisfun.com/algebra/vectors-dot-product.html">**here**</a> and <a href = "https://www.cuemath.com/algebra/dot-product/">**here**</a> for dot product.   
2. `double ddot(const cv::Point_<T>& pt) const` - the dot product is computed in double-precision arithmetics
3. `double cross(const cv::Point_<T>& pt) const` - cross product between two Point objects. The value returned is a scalar value. See <a href = "https://www.mathsisfun.com/algebra/vectors-cross-product.html">**here**</a> or <a href = "https://byjus.com/maths/cross-product/">**here**</a> for more details on cross product.
4. `bool inside(const cv::Rect_<T>& r)` - query if a point object is inside a rectangle, r. We will discuss Rectangle objects in a future tutorial.

:notebook_with_decorative_cover: In the following example, we will use the C++ function `typeid(variable).name()` to get the primitive data type of a variable. This is returned as a single letter e.g. `i` for integer, `f` for float, `d` for double etc.

**Example**

```c++
#include "opencv2/core.hpp" // include path to header file with all our basic data types
#include <iostream>              // for std::cout

int main()
{
    // Define Point objects of various basic data types
    cv::Point2i p8 {1, 2}; 
    cv::Point2i p9 {5, 6}; 
    cv::Point2f p10 {3.4f, 11.8f};
    cv::Point2f p11 {2.65f, 4.97f};
    cv::Point2d p12 {3.4, 9.8};
    cv::Point2d p13 {2.65, 4.97};

    // 1. Compute the Dot products between two vectors
    //    We should expect the dot product to be a scalar of the same type  
    //    as the basic type of our Point objects

    auto dot_product_p8_p9 = p8.dot(p9); 
    std::cout << "\nDot product of " << p8 << " and " 
              << p9 << " is " << dot_product_p8_p9 << '\n';
    std::cout << "Data type of dot product is: " 
              << typeid(dot_product_p8_p9).name() << '\n';

    auto dot_product_p10_p11 = p10.dot(p11);
    std::cout << "\nDot product of " << p10 << " and " 
              << p11 << " is " << dot_product_p10_p11 << '\n';
    std::cout << "Data type of dot product is: " 
              << typeid(dot_product_p10_p11).name() << '\n';
    
    auto dot_product_p12_p13 = p12.dot(p13);
    std::cout << "\nDot product of " << p12 << " and " 
              << p13 << " is " << dot_product_p12_p13 << '\n';
    std::cout << "Data type of dot product is: " 
              << typeid(dot_product_p12_p13).name() << '\n';

    // 2. Compute the Dot product using double precision
    //    We should expect the dot product to be of type double

    auto double_dot_product_p8_p9 = p8.ddot(p9); 
    std::cout << "\nDouble Dot product of " << p8 << " and " 
              << p9 << " is " << double_dot_product_p8_p9 << '\n';
    std::cout << "Data type of dot product is: " 
              << typeid(double_dot_product_p8_p9).name() << '\n';

    auto double_dot_product_p10_p11 = p10.ddot(p11);
    std::cout << "\nDouble Dot product of " << p10 << " and " 
              << p11 << " is " << double_dot_product_p10_p11 << '\n';
    std::cout << "Data type of dot product is: " 
              << typeid(double_dot_product_p10_p11).name() << '\n';
    
    auto double_dot_product_p12_p13 = p12.ddot(p13);
    std::cout << "\nDouble Dot product of " << p12 << " and " 
              << p13 << " is " << double_dot_product_p12_p13 << '\n';
    std::cout << "Data type of dot product is: " 
              << typeid(double_dot_product_p12_p13).name() << '\n';


    // 3. Compute the Cross product
    //    We should expect the cross product to be scalar value of type 'double'

    auto cross_product_p8_p9 = p8.cross(p9);
    std::cout << "\nCross product between " << p8 << " and " 
              << p9 << " is " << cross_product_p8_p9 << '\n';
    std::cout << "Data type of cross product is: " 
              << typeid(cross_product_p8_p9).name() << '\n';

    auto cross_product_p10_p11 = p10.cross(p11);
    std::cout << "\nCross product between " << p10 << " and " 
              << p11 << " is " << cross_product_p10_p11 << '\n';
    std::cout << "Data type of cross product is: " 
              << typeid(cross_product_p10_p11).name() << '\n';

    auto cross_product_p12_p13 = p12.cross(p13);
    std::cout << "\nCross product between " << p12 << " and " 
              << p13 << " is " << cross_product_p12_p13 << '\n';
    std::cout << "Data type of cross product is: " 
              << typeid(cross_product_p12_p13).name() << '\n';

    // 4. Query if a point is inside a rectangle

    // Define a 2-D rectangle whose origin or top-left corner coordinates 
    // are (0, 0), has width equal to 10 and height equal to 10
    // You will learn more about Rectangle objects in the Rectangle tutorial
    cv::Rect2i r1 { 0, 0, 10, 10 }; 

    // Check if Point data object p8 is inside our rectangle object
    bool query_1 { p8.inside(r1) };
    std::cout << std::boolalpha; // allows us to print 'true' or 'false' rather than '1' or '0' when dealing with boolean values
    std::cout << "\nIs point " << p8 << " inside the rectangular object " << r1 << " ? " << query_1 << '\n';

     // Check if Point data object p10 is inside our rectangle object
    bool query_2 { p10.inside(r1) };
    //std::cout << std::boolalpha; // allows us to print 'true' or 'false' rather than '1' or '0' when dealing with boolean values
    std::cout << "\nIs point " << p10 << " inside the rectangular object " << r1 << " ? " << query_2 << '\n';

    return 0;

}
```

**Output**

    Dot product of [1, 2] and [5, 6] is 17
    Data type of dot product is: i

    Dot product of [3.4, 11.8] and [2.65, 4.97] is 67.656
    Data type of dot product is: f

    Dot product of [3.4, 9.8] and [2.65, 4.97] is 57.716
    Data type of dot product is: d

    Double Dot product of [1, 2] and [5, 6] is 17
    Data type of dot product is: d

    Double Dot product of [3.4, 11.8] and [2.65, 4.97] is 67.656
    Data type of dot product is: d

    Double Dot product of [3.4, 9.8] and [2.65, 4.97] is 57.716
    Data type of dot product is: d

    Cross product between [1, 2] and [5, 6] is -4
    Data type of cross product is: d

    Cross product between [3.4, 11.8] and [2.65, 4.97] is -14.372
    Data type of cross product is: d

    Cross product between [3.4, 9.8] and [2.65, 4.97] is -9.072
    Data type of cross product is: d

    Is point [1, 2] inside the rectangular object [10 x 10 from (0, 0)] ? true

    Is point [3.4, 11.8] inside the rectangular object [10 x 10 from (0, 0)] ? false

:notebook_with_decorative_cover: For 3D Point objects we have the following 3 member functions.
1. `T dot(const cv::Point3_<T>& pt) const`
2. `double ddot(const cv::Point3_<T>& pt) const`
3. `cv::Point3_ cross(const cv::Point3_<T>& pt) const` - Unlike 2D
Point objects, the cross product for 3D Point objects is another vector not a scalar value.

:notebook_with_decorative_cover: In the following example, when we try to get the primitive data type of an OpenCV core type such as a Point object using the C++ function `typeid(variable).name()` you will get a wierd string such as N2cv7Point3_I**i**EE. The primitive type is the letter I have placed in bold text. The same applies to other primitive types such as float or double e.g. N2cv7Point3_I**f**EE, N2cv7Point3_I**d**EE. I am yet to find a better way of returning the primitive types. If anyone knows a better way please leave a comment.

**Example**
```c++
#include "opencv2/core.hpp" // include path to header file with all our basic data types
#include <iostream>         // for std::cout

int main()
{
    // Define Point objects of various basic data types
    cv::Point3i p14 {1, 2, 1}; 
    cv::Point3i p15 {5, 6, 10}; 
    cv::Point3f p16 {3.4f, 9.8f, 0.9f};
    cv::Point3f p17 {2.65f, 4.97f, 3.2f};
    cv::Point3d p18 {3.4, 9.8, 0.9};
    cv::Point3d p19 {2.65, 4.97, 3.2};

    // 1. Compute the Dot products between two vectors
    //    We should expect the dot product to be a scalar of the same type  
    //    as the basic type of our Point objects

    auto dot_product_p14_p15 = p14.dot(p15); 
    std::cout << "\nDot product of " << p14 << " and " 
              << p15 << " is " << dot_product_p14_p15 << '\n';
    std::cout << "Data type of dot product is: " 
              << typeid(dot_product_p14_p15).name() << '\n';

    auto dot_product_p16_p17 = p16.dot(p17);
    std::cout << "\nDot product of " << p16 << " and " 
              << p17 << " is " << dot_product_p16_p17 << '\n';
    std::cout << "Data type of dot product is: " 
              << typeid(dot_product_p16_p17).name() << '\n';
    
    auto dot_product_p18_p19 = p18.dot(p19);
    std::cout << "\nDot product of " << p18 << " and " 
              << p19 << " is " << dot_product_p18_p19 << '\n';
    std::cout << "Data type of dot product is: " 
              << typeid(dot_product_p18_p19).name() << '\n';

    // 2. Compute the Dot product using double precision
    //    We should expect the dot product to be of type 'double'

    auto double_dot_product_p14_p15 = p14.ddot(p15); 
    std::cout << "\nDouble Dot product of " << p14 << " and " 
              << p15 << " is " << double_dot_product_p14_p15 << '\n';
    std::cout << "Data type of dot product is: " 
              << typeid(double_dot_product_p14_p15).name() << '\n';

    auto double_dot_product_p16_p17 = p16.ddot(p17);
    std::cout << "\nDouble Dot product of " << p16 << " and " 
              << p17 << " is " << double_dot_product_p16_p17 << '\n';
    std::cout << "Data type of dot product is: " 
              << typeid(double_dot_product_p16_p17).name() << '\n';
    
    auto double_dot_product_p18_p19 = p18.ddot(p19);
    std::cout << "\nDouble Dot product of " << p18 << " and " 
              << p19 << " is " << double_dot_product_p18_p19 << '\n';
    std::cout << "Data type of dot product is: " 
              << typeid(double_dot_product_p18_p19).name() << '\n';


    // 3. Compute the Cross product
    //    We should expect the cross product to be another Point object
    //    representing a Vector. Output basic data type should be the same as 
    //    that of input Point data

    auto cross_product_p14_p15 = p14.cross(p15);
    std::cout << "\nCross product between " << p14 << " and " 
              << p15 << " is " << cross_product_p14_p15 << '\n';
    std::cout << "Data type of cross product is: " 
              << typeid(cross_product_p14_p15).name() << '\n';

    auto cross_product_p16_p17 = p16.cross(p17);
    std::cout << "\nCross product between " << p16 << " and " 
              << p17 << " is " << cross_product_p16_p17 << '\n';
    std::cout << "Data type of cross product is: " 
              << typeid(cross_product_p16_p17).name() << '\n';

    auto cross_product_p18_p19 = p18.cross(p19);
    std::cout << "\nCross product between " << p18 << " and " 
              << p19 << " is " << cross_product_p18_p19 << '\n';
    std::cout << "Data type of cross product is: " 
              << typeid(cross_product_p18_p19).name() << '\n';

    return 0;
}
```

**Output**

    Dot product of [1, 2, 1] and [5, 6, 10] is 27
    Data type of dot product is: i

    Dot product of [3.4, 9.8, 0.9] and [2.65, 4.97, 3.2] is 60.596
    Data type of dot product is: f

    Dot product of [3.4, 9.8, 0.9] and [2.65, 4.97, 3.2] is 60.596
    Data type of dot product is: d

    Double Dot product of [1, 2, 1] and [5, 6, 10] is 27
    Data type of dot product is: d

    Double Dot product of [3.4, 9.8, 0.9] and [2.65, 4.97, 3.2] is 60.596
    Data type of dot product is: d

    Double Dot product of [3.4, 9.8, 0.9] and [2.65, 4.97, 3.2] is 60.596
    Data type of dot product is: d

    Cross product between [1, 2, 1] and [5, 6, 10] is [14, -5, -4]
    Data type of cross product is: N2cv7Point3_IiEE

    Cross product between [3.4, 9.8, 0.9] and [2.65, 4.97, 3.2] is [26.887, -8.495, -9.072]
    Data type of cross product is: N2cv7Point3_IfEE

    Cross product between [3.4, 9.8, 0.9] and [2.65, 4.97, 3.2] is [26.887, -8.495, -9.072]
    Data type of cross product is: N2cv7Point3_IdEE

