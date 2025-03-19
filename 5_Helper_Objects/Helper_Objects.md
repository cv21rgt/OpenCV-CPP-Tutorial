# Helper Objects

:notebook_with_decorative_cover: In addition to the basic data types and containers we have looked at, there is another family of classes or objects that we need to know about before we get to use various algorithms in OpenCV.

:notebook_with_decorative_cover: These classes or objects are crucial to the way you will: 

1. Run computer vision algorithms
2. Handle errors gracefully
3. Write your own functions in such a way they can be used with a variety of OpenCV data types
4. Handle user input

## The cv::TermCriteria class

:notebook_with_decorative_cover: As you start to use image processing algorithms in OpenCV, you will notice that many iterative algorithms require a stopping condition to know when to quit processing the input data. OpenCV provides the <a href = "https://docs.opencv.org/4.8.0/d9/d5d/classcv_1_1TermCriteria.html">cv::TermCriteria</a>  class to help users control how long an algorithm should run. The `cv::TermCriteria` class contains three public member variables - `type`, `maxCount` and `epsilon`, which can be set directly or through a constructor of the form `cv::TermCriteria(int type, int maxCount, double epsilon)`.

1. The variable `type` refers to the termination criteria and can be set to one of 3 values:
    
   1. `cv::TermCriteria::COUNT` - you want the algorithm to terimate after `maxCount` iterations. This is a synonym for `cv::TermCriteria::MAX_ITER`, so you can use that if you prefer.
    
   2. `cv::TermCriteria::EPS` - you want the algorithm to terminate after come accuracy metric associated with the algorithm's convergence falls below the value `epsilon`.

   3. You can have both of the above by using the 'or' symbol (`|`) (i.e., `cv::TermCriteria::EPS | cv::TermCriteria::COUNT`). This is the most desirable cases as it ensures that the algorithm will quit one way or another at some point. If you want both to be true use the `+` symbol (i.e., `cv::TermCriteria::EPS + cv::TermCriteria::COUNT`).

2. The variable `maxCount` refers to the maximum number of iterations to compute

3. The variable `epsilon` is a very small number that refers to the algorithms desired accuracy or change in parameters at which the algorithm should stop.

:notebook_with_decorative_cover: We will use the famous k-means algorithm (for finding clusters within a dataset) to demonstrate how to set up the termination criteria. The function to execute k-means clustering is found in the header `<core.hpp>` and has the signature: `double cv::kmeans(cv::InputArray data, int K, cv::InputOutputArray bestLabels, cv::TermCriteria criteria, int attempts, int flags, cv::OutputArray centers = cv::noArray())`. Most of the parameters will be alien to you, just pay attention to the parameter `criteria` - which requires an object of the `cv::TermCriteria` class. This is were we will determine how far the algorithm will run before we stop it.

**Example 1** - The following example will not display anything. It just demonstrates how to set up the termination criteria of an algorithm.

```c++
#include "opencv2/core.hpp" // for OpenCV core types, cv::TermCriteria and kmeans()
#include <iostream>

int main()
{
    // Don't worry about this group of arguments
    // It is the next group that is important for now
    cv::RNG rng(12345);
    const int MAX_CLUSTERS = 5;
    int k, clusterCount = rng.uniform(2, MAX_CLUSTERS+1);
    int i, sampleCount = rng.uniform(1, 1001);
    cv::Mat points(sampleCount, 1, CV_32FC2);
    cv::Mat labels;
    clusterCount = MIN(clusterCount, sampleCount);
    std::vector<cv::Point2f> centers;

    // This is the important bit where we set our termination criteria
    // ===============================================================

    // We want to use either maxCount or epsilon to terminate algorithm
    int type = cv::TermCriteria::EPS | cv::TermCriteria::COUNT; 
    int maxCount = 10; // terminate after 10 iterations
    double epsilon = 1.0; // terminate if accuracy approaches 1.0

    // Use constructor to set everything up
    // We want our algorithm to run and terminate after 10 iterations
    // or if accuracy reaches 1.0
    cv::TermCriteria terminationCriteria { type, maxCount, epsilon };

    // Now execute the kmeans algorithm
    double compactness = cv::kmeans(points, 
                                    clusterCount, 
                                    labels, 
                                    terminationCriteria, // this is our termination criteria object
                                    3, 
                                    cv::KMEANS_PP_CENTERS, 
                                    centers);
    
    std::cout << '\n';

    return 0;
}
```

## The cv::Range class

:notebook_with_decorative_cover: The <a href = "https://docs.opencv.org/4.8.0/da/d35/classcv_1_1Range.html">cv::Range</a> class is a template class used for specifying a continuous sequence of integers. You can access this class by including the header `<core.hpp>`. To establish the boundary of the sequence you have to specify the **start** value (inclusive) and the **end** value (exclusive). Such a half-opened interval is usually denoted as `[start, end)`. `cv::Range` objects are often set with the constructor `cv::Range(int start, int end)`. You can also use the default constructor `cv::Range()`, and then set the `start` and `end` values later since they are public attributes.

:notebook_with_decorative_cover: `cv::Range` class has three member functions:

1. `int size() const` - returns the number of elements in a range or sequence.
2. `bool empty() const` - tests if a range object has no elements. Returns `true` if the range has no elements, `false` otherwise.
3. `Range all()` - returns a special variable that means *the whole sequence* defined by a range object.

:notebook_with_decorative_cover: The `cv::Range` class is mainly used with OpenCV container data types such as cv::Mat as we will see in the following example.

**Example 2**

```c++
#include "opencv2/core.hpp"       // for OpenCV core types and cv::Range
#include <iostream>

int main()
{
    // 1. Define sequence of integer values between 1 and 5 (inclusive)
    cv::Range r { 1, 6 };

    // a. Check if a sequence is empty or not
    bool isEmpty { r.empty() };
    std::cout << "\nIs the sequence empty? = " 
              << std::boolalpha << isEmpty << '\n';

    // b. Check how many elements are in our sequence
    int nElements = r.size();
    std::cout << "\nSize of sequence = " << nElements << '\n';

    
    // 2. Using cv::Range with cv::Mat

    // We will first create a cv::Mat object to work with. 
    // Original data is in a C-style array

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

    // create a 10x10 array with 32-bit float values
    const cv::Mat m1 { cv::Size(10, 10), CV_32F, dataArray }; 

    std::cout << "\nm1 = \n" << m1 << '\n';

    // We want to create another cv::Mat object by selecting rows 
    // and columns from the original matrix 'm1'
    // We will use cv::Range class to define which rows and columns we want

    cv::Range rows {2, 5};    // get rows between 2 (inclusive) and 5 (exclusive)
    cv::Range columns { cv::Range::all() }; // get all the columns 

    cv::Mat m2 {m1, rows, columns};

    std::cout << "\nm2 array derived from m1 by defining a range = \n" 
              << m2 << '\n';
    
    std::cout << '\n';

    return 0;
}
```

**Output**

    Is the sequence empty? = false

    Size of sequence = 5

    m1 = 
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

    m2 array derived from m1 by defining a range = 
    [21, 22, 23, 24, 25, 26, 27, 28, 29, 30;
    31, 32, 33, 34, 35, 36, 37, 38, 39, 40;
    42, 42, 43, 44, 45, 46, 47, 48, 49, 50]


## The cv::Ptr smart pointer

:notebook_with_decorative_cover: OpenCV provides a smart pointer `cv::Ptr`. Actually, `cv::Ptr` is simply an alias or another name for the templated shared smart pointer (<a href = "https://www.learncpp.com/cpp-tutorial/stdshared_ptr/">std::shared_ptr</a>) in modern C++. This pointer allows us to create a reference to an object and then pass the pointer around instead of the object. We can also create more than one reference to the same object and OpenCV will keep track of how many pointers refer to that object. If a reference goes out of scope (for example when passed to a function and we get to the end of the function), the reference count for `cv::Ptr` is decremented. Once all the references (instances of the pointer) have gone out of scope the memory occupied by the object is de-allocated automatically without the programmer not having to do anything hence the term **smart pointer**.

:notebook_with_decorative_cover: To create a `cv::Ptr` smart pointer we make use of the `cv::Ptr<T>cv::makePtr<T>(const T& a)` template function. `T` is the data type of object we want to reference, and `a` is the object. For example, to create a pointer, `p`,  to a `cv::Matx22f` object called `mtx` we write: `cv::Ptr<cv::Matx22f> p = cv::makePtr<cv::Matx22f>(mtx);`. Once you have the pointer you can access all the members (member functions and attributes) of the object in question by using the operator `->`. 

:notebook_with_decorative_cover: If you look at the parameter for `cv::makePtr` it is a reference to a `const` object. This means any changes you make through the pointer (e.g. `p`) **WILL NOT** be reflected in the original object (e.g. `mtx`).

**Example 3** - Demonstrate how to use the smart pointer `cv::Ptr`.

```c++
#include "opencv2/core.hpp"       // for OpenCV core types
#include <iostream>

int main()
{
    // Create a 2x2 matrix object to attach our pointer to
    cv::Matx22f matx { 1, 2, 3, 4 };

    // 1. We will create a pointer using the cv::makePtr() and attach it to 'matx'
    //   ========================================================================

    cv::Ptr<cv::Matx22f> p = cv::makePtr<cv::Matx22f>(matx);

    // We can use the pointer to access any functions relevant to 'matx'

    std::cout << "\nPrint matrix 'matx' through pointer 'p' = \n" << (*p) << '\n';

    std::cout << "\nNo. of rows in 'matx' through pointer 'p' = " << p->rows << '\n';

    std::cout << "\nNo. of columns in 'matx' through pointer 'p' = " << p->cols << '\n';

    std::cout << "\nNo. of elements in 'matx' through pointer 'p' = " << p->channels << '\n';

    std::cout << "\nTranspose of matrix 'matx' through pointer 'p'  = \n" << p->t() << '\n';


    // 2. Lets create another smart pointer and attach it to 'matx'
    //    ========================================================

    cv::Ptr<cv::Matx22f> q = p; // simply assign the value of 'p' to 'q'

    // Just like with pointer 'p', we can use pointer 'q' to 
    // access any functions relevant to 'matx'

    std::cout << "\nPrint matrix 'matx' through pointer 'q' = \n" << (*q) << '\n'; 

    std::cout << "\nNo. of rows in 'matx' through pointer 'q' = " << q->rows << '\n';

    std::cout << "\nNo. of columns in 'matx' through pointer 'q' = " << q->cols << '\n';

    std::cout << "\nNo. of elements in 'matx' through pointer 'q' = " << q->channels << '\n';

    std::cout << "\nTranspose of matrix 'matx' through pointer 'q'  = \n" << q->t() << '\n';


    // 3. Alter element values in matrix through pointers
    //    ===============================================

    // We will create another pointer using the cv::makePtr(), 
    // this time it will be independent of pointer 'p' 
    cv::Ptr<cv::Matx22f> r = cv::makePtr<cv::Matx22f>(matx);

    // Alter element value at index (0,0) using pointer 'p' 
    (*p)(0,0) = 5;

    // Print matrix through pointer 'p'
    // You should see changes here 
    std::cout << "\nPrint matrix using pointer 'p' after alterations made through pointer 'p' = \n" 
              << *p << '\n';

    // Any changes you make through pointers will NOT be 
    // reflected in the original object.
    std::cout << "\nPrint original matrix after alterations made through pointer 'p' = \n" 
              << matx << '\n';
    

    // Changes will apply to reference through pointer 'q' because it 
    // created through pointer 'p'
    std::cout << "\nPrint matrix using pointer 'q' after alterations made through pointer 'p' = \n" 
              << *q << '\n';

    // No changes should be reflected here
    std::cout << "\nPrint matrix using pointer 'r' after alterations made through pointer 'p' = \n" 
              << *r << '\n';

    std::cout << '\n';

    return 0;

} // smart pointers 'p', 'q' and 'r' go out of scope here 
  // and their memory will be de-allocated automatically 
```

**Output**

    Print matrix 'matx' through pointer 'p' = 
    [1, 2;
    3, 4]

    No. of rows in 'matx' through pointer 'p' = 2

    No. of columns in 'matx' through pointer 'p' = 2

    No. of elements in 'matx' through pointer 'p' = 4

    Transpose of matrix 'matx' through pointer 'p'  = 
    [1, 3;
    2, 4]



    Print matrix 'matx' through pointer 'q' = 
    [1, 2;
    3, 4]

    No. of rows in 'matx' through pointer 'q' = 2

    No. of columns in 'matx' through pointer 'q' = 2

    No. of elements in 'matx' through pointer 'q' = 4

    Transpose of matrix 'matx' through pointer 'q'  = 
    [1, 3;
    2, 4]



    Print matrix using pointer 'p' after alterations made through pointer 'p' = 
    [5, 2;
    3, 4]

    Print original matrix after alterations made through pointer 'p' = 
    [1, 2;
    3, 4]

    Print matrix using pointer 'q' after alterations made through pointer 'p' = 
    [5, 2;
    3, 4]

    Print matrix using pointer 'r' after alterations made through pointer 'p' = 
    [1, 2;
    3, 4]

## The cv::Exception class and exception handling

:notebook_with_decorative_cover: The standard way of handling errors in OpenCV is through exceptions. The <a href = "https://docs.opencv.org/4.8.0/d1/dee/classcv_1_1Exception.html">cv::Exception</a> class handles exceptions in OpenCV, and is derived from C++ STL exception class <a href = "https://en.cppreference.com/w/cpp/error/exception">std::exception</a>. `cv::Exception` class can be accessed through the header file `<core.hpp>`. The attributes of the `cv::Exception` class are public and have the following meanings:

1. `code` - a numerical error code used to represent common errors in OpenCV. You can find them <a href = "https://docs.opencv.org/4.8.0/d1/d0d/namespacecv_1_1Error.html#a759fa1af92f7aa7377c76ffb142abcca">here</a>.
2. `err` - a string indicating the nature of the error that generated the exception.
3. `func` - the name of the function in which the error occurred.
4. `file` - the name of the file in which the error occurred.
5. `line` - an integer indicating the line number on which the error occurred in that file.
6. `msg` - a `std::string` object, which contains a formatted error message.

:notebook_with_decorative_cover: There are also two public member functions you can access:

1. `void formatMessage()` - 
2. `virtual const char* what() const throw()` - this returns the error description as a text string. This function overides the one inherited from `std::exception` class. If you have ever used exceptions in C++ you should be familiar with this function.

:notebook_with_decorative_cover: To create a `cv::Exception` object you can either use the default constructor `cv::Exception()` or the value constructor `cv::Exception(int code, const std::string& err, const std::string& func, const std::string& file, int line)`. Normally the `cv::Exception` constructors are not called explicitly as you will notice in the following sub-sections.

### Handling errors in a try...catch block

:notebook_with_decorative_cover: From your C++ knowledge, remember that we use the **try...catch** block to catch and handle errors or exceptions raised during running of a block of code. For more notes on the basics of handling exceptions in C++ go <a href = "https://www.learncpp.com/cpp-tutorial/the-need-for-exceptions/">here</a>.

**Example 4** - Use a try...catch block to handle errors. Specifically, we will try to compute the inverse of matrix. Remember you can only compute the inverse of a **square matrix**. So we will try to catch the error generated when we try to compute the inverse of a non-square matrix. We will try to catch the error if its part of the `cv::Exception` class, if not, we will see if its part of `std::exception` from which `cv::Exceptions` inherits from. If all fails, we will use a general error handler.

```c++
#include "opencv2/core.hpp"       // for OpenCV core types, cv::Exception
#include <iostream>

int main()
{
    /* 
     *    Using cv::Exceptions in a try...catch block
     *    ===========================================
     * 
     *    We will try to compute the inverse of matrix. Remember you can 
     *    only compute the inverse of a square matrix. So we will try to 
     *    catch the error generated when we try to compute the inverse
     *    of a non-square matrix
     * 
     *    We will try to catch the error if its part of the cv::Exception 
     *    class, if not, we will see if its part of std::exception
     *    from which cv::Exceptions inherits from. If all fails, we will 
     *    use a general error handler.
     * 
    */ 
    
    // Create a 2x3 matrix
    const cv::Matx23f matx1 { 1, 2, 3, 4, 5, 6 };
    
    try // Code that may cause an error or raise an exception goes in this block
    {
        // try to compute the inverse of a matrix
        auto inverse = matx1.inv(); 

        std::cout << "\nInverse of 'matx1' = " << inverse << '\n';
        
    }
    catch(const cv::Exception& e) // catch the exception here if its part of the cv::Exception class
    {
        std::cerr << "Error: " << e.what() << '\n'; // print error message
    }
    catch (const std::exception& e) // If error is not part of cv::Exception, 
                                    // lets catch it here if its part of the base class std::exception
    {
        std::cerr << "Error: " << e.what() << '\n';
    }
    catch(...) // If the above fail, lets use a general error handler
    {
        std::cerr << "Error: Unknown exception\n";
    }

    std::cout << '\n';

    return 0;
}
```

**Output**

    Error: OpenCV(4.8.0) /Your/Home/Path/opencv/modules/core/src/lapack.cpp:875: error: (-215:Assertion failed) m == n in function 'invert'

:notebook_with_decorative_cover: From the output error message above we can see that it is not very clear what the problem is. You probably need some experience with errors generated by OpenCV for you to understand what message is being communicated to you. To get around this issue, OpenCV also offers function like <a href = "https://www.learncpp.com/cpp-tutorial/introduction-to-the-preprocessor/">macro</a>'s you can take advantage of to generate more meaningful error messages. In C++, a macro is a rule that defines how input text is converted into replacement output text. Macros are much better to use as they allow you to generate more meaningful error messages. They also automatically take care of the attributes `func`, `file`, and `line`.


### `CV_Error` macro

:notebook_with_decorative_cover: This macro is defined as `#define CV_ERROR(code, msg) cv::error(code, msg, CV_Func, __FILE__, __LINE__)`. You supply the error code (`code`) and meaningful message (`msg`). In turn a more detailed error message will be displayed to the user. This message will contain the error code (which you can find <a href = "https://docs.opencv.org/4.8.0/d1/d0d/namespacecv_1_1Error.html#a759fa1af92f7aa7377c76ffb142abcca">here</a>), message, name of function that generated the error, name of file in which the error was generated and line number from which the error originated from. The best way is to illustrate this through an example.

**Example 5** - Use `CV_ERROR` macro

```c++
#include "opencv2/core.hpp" // for OpenCV core types, CV_Error macro
#include <iostream>

int main()
{
    //    Use CV_Error when computing the inverse of a matrix. 
    //    Matrix should always be square i.e., no. of rows == no. of columns
    
    const cv::Matx23f matx2 { 1, 2, 3, 4, 5, 6 };

    if (matx2.rows != matx2.cols)
    {
        std::string msg = "Only square matrices with number of rows equal to number of columns are supported.";
        CV_Error(cv::Error::StsBadSize, msg); 
        
        return -1;
    }
    else 
    {
        auto inverse = matx2.inv();

        std::cout << "\ninverse = \n" << inverse;
    }

    std::cout << '\n';

    return 0;
}
```

**Output**

    terminate called after throwing an instance of 'cv::Exception'

    what():  OpenCV(4.8.0) /Your/Home/Path/Helper_Objects/Example-Code/Helper-Objects-app/main.cpp:264: error: (-201:Incorrect size of input array) Only square matrices with number of rows equal to number of columns are supported. in function 'main'

:notebook_with_decorative_cover: The output message above says an error was generated in file `/home/gy08rgt/Documents/OpenCV/Image_Processing/Basic_Core_Types/Helper_Objects/Helper-Objects-app/main.cpp` by function `main` on line `264`. The error references incorrect input array size and is expanded to the meaningful message `Only square matrices with number of rows equal to number of columns are supported.`

### `CV_Error_` macro

:notebook_with_decorative_cover: This macro is defined as `#define CV_ERROR_(code, args) cv::error(code, cv::format args, CV_Func, __FILE__, __LINE__)`. This macro can be used to construct an error message to include some dynamic information for example if you want to include information stored in function variables as part of the error message. `args` is a formated error message that includes data stored in variables or obtained from an expression.

**Example 6** - Use `CV_ERROR_` macro. We are simply changing Example 5 to use the `CV_Error_` macro.

```c++
#include "opencv2/core.hpp"  // for OpenCV core types, CV_Error_ macro
#include <iostream>

int main()
{
    const cv::Matx23f matx2 { 1, 2, 3, 4, 5, 6 };

    // Use CV_Error_ macro
    if (matx2.rows != matx2.cols)
    {
        CV_Error_(cv::Error::StsBadSize, 
            ("The no. of matrix rows (%d) is not equal to no. of columns (%d)", matx2.rows, matx2.cols));
        
            return -1;
    }
    else 
    {
        auto inverse = matx2.inv();

        std::cout << "\ninverse = \n" << inverse;
    }

    std::cout << '\n';

    return 0;
}
```

**Output**

    terminate called after throwing an instance of 'cv::Exception'

    what():  OpenCV(4.8.0) /Your/Home/Path/Helper_Objects/Example-Code/Helper-Objects-app/main.cpp:278: error: (-201:Incorrect size of input array) The no. of matrix rows (2) is not equal to no. of columns (3) in function 'main'


### `CV_Assert` macro

:notebook_with_decorative_cover: This is defined as `#define CV_Assert(expr) do { if(!!(expr)) ; else cv::error(cv::Error::StsAssert, #expr, CV_Func, __FILE__, __LINE__ );} while(0)`. It is implemented as a C++ <a href = "https://www.learncpp.com/cpp-tutorial/do-while-statements/">do..while</a> loop. This macro checks a condition in the form of an expression (`expr`) at runtime and raises an error (see <a href = "https://docs.opencv.org/4.8.0/db/de0/group__core__utils.html#gacbd081fdb20423a63cf731569ba70b2b">cv::error</a>) if it fails. 

:notebook_with_decorative_cover: This macro checks the condition in both **Debug** and **Release** configurations of your program.

**Example 7** - Use `CV_Assert` macro. 

```c++
#include "opencv2/core.hpp" // for OpenCV core types, CV_Assert
#include <iostream>

int main()
{
    const cv::Matx23f matx1 { 1, 2, 3, 4, 5, 6 };

    // Use CV_Assert macro to test if our matrix is square
    // That is, no. of rows should be equal to no. of columns
    CV_Assert(matx1.rows == matx1.cols); 

    // Only compute inverse if the above condition is true
    auto i = matx1.inv(); 

    std::cout << "\ninverse = \n" << i;

    return 0;
}
```

**Output**

    terminate called after throwing an instance of 'cv::Exception'

    what():  OpenCV(4.8.0) /Your/Home/Path/Helper_Objects/Example-Code/Helper-Objects-app/main.cpp:299: error: (-215:Assertion failed) matx2.rows == matx2.cols in function 'main'


## The cv::InputArray and cv::OutputArray classes

:notebook_with_decorative_cover: OpenCV supports a number of array types, `cv::Vec`, `cv::Matx`, `cv::Scalar`, STL's `std::vector`, `cv::Mat`, `cv::Mat_`, `cv::SparseMat`, `cv::SparseMat_` etc. All these types (template and non-template forms) can be passed to functions as arguments or returned as return values. However, writing functions that would take into account all these data types would lead to repetetive code and make the OpenCV interface more complicated. 

:notebook_with_decorative_cover: As a solution, the designers of OpenCV defined two class types, <a href = "https://docs.opencv.org/4.8.0/d4/d32/classcv_1_1__InputArray.html">cv::_InputArray</a> and <a href = "https://docs.opencv.org/4.8.0/d2/d9e/classcv_1_1__OutputArray.html">cv::_OutputArray</a>, which can represent any of the many array forms supported by the library. They both were assigned aliases `cv::InputArray` and `cv::OutputArray`, respectively. Please note the removal of the underscore in the aliase names. 

### `cv::InputArray`

:notebook_with_decorative_cover: `cv::InputArray` is for read-only input arrays into OpenCV functions.

:notebook_with_decorative_cover: `cv::InputArray` can handle a variety of arrays that include `cv::Mat`, `cv::Mat_<T>`, `cv::Matx<T, m, n>`, `std::vector<T>`, `std::vector<std::vector<T> >`, `std::vector<cv::Mat>`, `std::vector<cv::Mat_<T> >`, `cv::UMat`, `std::vector<cv::UMat>`, `double`, `std::array<T, n>`, `std::array<cv::Mat, n>` etc. You can also use a matrix expression (`cv::MatExpr`)

:notebook_with_decorative_cover: The class is designed solely for passing parameters. That is, normally you *should not declare class members*, local and global variables of this type.

#### `cv::InputArrayOfArrays`

:notebook_with_decorative_cover:  It denotes function arguments that are either vectors of vectors or vectors of matrices. In general, type support is limited to `cv::Mat` types. Other types are forbidden. 

### `cv::OutputArray`

:notebook_with_decorative_cover: This class is used for input/output and output function parameters. You can use the same array types as those passed to `cv::InputArray` to handle output array data.

:notebook_with_decorative_cover: Just like with `cv::InputArray`, do not explicitly create `cv::OutputArray` class instances/objects. 

#### `cv::OutputArrayOfArrays`

:notebook_with_decorative_cover: If output from your functions is more than one array, you can use `cv::OutputArrayOfArrays` - this will take your multiple array outputs and place them into a single array. `cv::OutputArrayOfArrays` is an aliase for `cv::OutputArray`.

#### `cv::InputOutputArray`

:notebook_with_decorative_cover: There is also a <a href = "https://docs.opencv.org/4.8.0/d0/d46/classcv_1_1__InputOutputArray.html">cv::_InputOutputArray</a> class type, whose aliase is `cv::InputOutputArray` and is used for specifying an array for in-place computation, i.e., the input array elements will be over-written with the computed output elements.

#### `cv::InputOutputArrayOfArrays`

:notebook_with_decorative_cover: If you have multiple arrays for in-place computations, `cv::InputOutputArrayOfArrays` can help you handle these in one container.

### `cv::noArray()`

:notebook_with_decorative_cover: In addition, there is a special function `cv::noArray()` that returns a `cv::InputArray`. It is like a placeholder. You pass this function to any function in two situations:

1. Pass `cv::noArray()` in place of `cv::InputArray` to indicate that the input to that particular function is not to be used.
2. Pass `cv::noArray()` to functions that have optional output arrays. You are indicating that you do not need the corresponding output from that function.



**Example 8** -  We will demonstrate how `cv::InputArray` and `cv::OutputArray` classes are able to handle a variety of OpenCV array types in the following example. We will use the function `void cv::add(cv::InputArray src1, cv::InputArray src2, cv::OutputArray dst, cv::InputAray mask = cv::noArray(), int dtype = -1)`. This function calculates the per-element sum of two arrays or an array and a scalar. It can be found in the header `<core.hpp>`. Its function parameters can be defined as follows:

* `src1` - First input array or a scalar
* `src2` - Second input array or a scalar
* `dst` - Output array  that has the same size and number of channels as the input array(s); the depth is defined by dtype or src1/src2.
* `mask` - Optional operation mask - 8-bit single channel array, that specifies elements of the output array to be changed. 
* `dtype` - Optional data type of the output array. When both input arrays have the same data type, `dtype` can be set to `-1`


```c++
#include "opencv2/core.hpp" // for OpenCV core types, cv::add()
#include <iostream>

int main()
{
    // Possible values for 'InputArray'
    const cv::Matx22f matx3 { 1, 2, 3, 4 };
    const cv::Mat mat1 { matx3 };
    const cv::Scalar s { 2 };     

    // Possible values for 'OutputArray'
    cv::Mat mat_output {};
    cv::Matx22f matx_output {};

    // Option 1: InputArrays are cv::Matx and cv::Mat objects, whilst OutputArray is cv::Mat
    //           We don't want to use a 'mask' hence use of the function cv::noArray()
    cv::add(matx3, mat1, mat_output, cv::noArray(), -1);
    std::cout << "\nAdd 'cv::Matx' to 'cv::Mat' and save output in 'cv::Mat' = \n" 
              << mat_output << '\n';

    // Option 2: InputArrays are both cv::Matx, whilst OutputArray is cv::Mat
    //           We don't want to use a 'mask' hence use of the function cv::noArray()
    cv::add(matx3, matx3, mat_output, cv::noArray(), -1);
    std::cout << "\nAdd 'cv::Matx' to 'cv::Matx' and save output in 'cv::Mat' = \n" 
              << mat_output << '\n';

    // Option 3: InputArrays are cv::Matx and cv::Scalar, whilst OutputArray is cv::Matx 
    //           We don't want to use a 'mask' hence use of the function cv::noArray()
    cv::add(matx3, s, matx_output, cv::noArray(), -1);
    std::cout << "\nAdd 'cv::Matx' to 'cv::Scalar' and save output in 'cv::Matx' = \n" 
              << matx_output << '\n';
    
    std::cout << '\n';

    return 0;    
}
```

**Output**

    Add 'cv::Matx' to 'cv::Mat' and save output in 'cv::Mat' = 
    [2, 4;
    6, 8]

    Add 'cv::Matx' to 'cv::Matx' and save output in 'cv::Mat' = 
    [2, 4;
    6, 8]

    Add 'cv::Matx' to 'cv::Scalar' and save output in 'cv::Matx' = 
    [3, 4;
    5, 6]