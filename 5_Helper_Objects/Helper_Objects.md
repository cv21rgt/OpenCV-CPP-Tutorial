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