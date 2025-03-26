# Command Line Arguments

:notebook_with_decorative_cover: To be able to pass arguments to a program when run in a terminal, OpenCV provides the <a href = "https://docs.opencv.org/4.8.0/d0/d2e/classcv_1_1CommandLineParser.html">cv::CommandLineParser</a> class. This class is found in the `<utility.hpp>` header file in the `core` functions directory, and so is included as: `#include <opencv2/core/utility.hpp>`. The class has one value constructor that has the following syntax: `cv::CommandLinePaser(int argc, const char* const argv[], const cv::String& keys)`. 

1. `argc` - This is short for **Arg**ument **C**ount. It is the number of arguments passed by a user.

2. `argv` - This is short for **Arg**ument **V**ector. It is a C-style array of strings. This array will hold all user input in the form of strings. Please note that at all times index `0` will always be file path to application/program (i.e. `argv[0]`). The user inputs will actually start at index `1` (i.e. `argv[1], argv[2], ..., argv[argc]`).

3. `keys` - This is a text string describing command line arguments in greater detail. Its data type is `cv::String`, which is the same as `std::string`. The text string contains several blocks, each one is enclosed in curly braces and gives a detailed description of each argument. Each argument block contains 3 parts seperated by the `|` symbol:

    * **Argument name** - This is the name of the argument. If you have a number of names to refer to the same argument (or synonyms) simply seperate them by a space. To mark an argument as positional, prefix it with the `@` symbol.
    * **Default value** - This is the value to be used if the argument was not provided by the user, but can also be left empty. Use the special `<none>` default value to enforce that the argument cannot be left empty.
    * **Help message** - A helpful message that describes what the argument is. Can also be left empty, but I would encourage you to provide a message here to help the user understand what type of input is expected for that argument.

:notebook_with_decorative_cover: The following is an example of how we provide more information about the command line arguments through the `key` argument.

```c++
const cv::String keys = 
"{help h usage ? |        | print a message }"   // (1)
"{@image1        |        | image1 for compare }"   // (2) 
"{@image2        | <none> | image2 for compare }"   // (3) 
"{@repeat        | 1      | number }"               // (4) 
"{path           | .      | path to file }"         // (5) 
"{fps            | -1.0   | fps for output videoc}" // (6) 
"{N count        | 100    | count of objects }"     // (7) 
"{ts timestamp   |        | use time stamp }"       // (8) 
;
```
:notebook_with_decorative_cover: We will now provide further explanation for each of the 8 argument blocks above:

1. Argument name is `help`, `h`, `usage` or `?`. This first line is just a helpful message from the developer to the user briefly explaining the function of the program they are about to execute. It has no default value. Has a message to describe what the program is for. You can skip this line if you want.
2. This is the first argument that requires input from the user. This is a positional argument called `image1`. This means as the user your first input on your terminal should be for `image1`. Has no default value. Has a descriptive message.
3. This is also another positional argument called `image2`. Must never be empty hence the use of `<none>`. Has a descriptive message.
4. This is another positional argument called `repeat`. Has a default value of `1`. Has a descriptive message.
5. This is a non-positional argument named `path`. Has a default value (`.`), which is the current working directory. Has a descriptive message
6. This is also a non-positional argument named `fps`. Has a default value of `-1.0`. Has a descriptive message.
7. This non-positional argument can be referred to as either `N`, or `count`. Has a default value of `100`. Has a descriptive message.
8. The last non-positional argument is named `ts` or `timestamp`. Has no default value. Has a descriptive message.

## `int main()`

:notebook_with_decorative_cover: So far we have been using the function with the signature `int main()` as the entry point for our C++ programs. However, in order for us to pass command line arguments to the `cv::CommandLineParser` constructor, the arguments have to be passed through the `int main()` function as it is the main entry to any C++ program. However, this requires a `main()` function with a different signature than the one we have been using all along. We will now use `main()` with two function parameters: `int main(int argc, char* argv[])`. Older code use the signature `int main(int argc, char** argv)`. They mean the same thing, but prefer the first option as it makes clear we are dealing with a C-style array of strings when it comes to the parameter `argv`. Also notice that these two parameters are similar to the first two parameters for the `cv::CommandLineParser` constructor.

## `cv::CommandLineParse` Member Functions

:notebook_with_decorative_cover: Before we start providing examples of how to use `cv::CommandLineParser`, we need to look as some of its member functions that we will use in our examples. The good thing is this class contains a few member functions.

1. `void about(const cv::String& message)` - use this function to set out the message displayed to the user about what the program does. To print the message use the `printMessage()` function - which we will discuss later on. The message is displayed right before the arguments table.

2. `bool check() const` - use this function to check for any errors in accessing the command line arguments. Such errors include missing arguments, bad conversion from string to numeric value etc. Once you check for any errors, call `printErrors()` function to print error messages list.

3. `T get<T>(const cv::String&  name, bool space_delete = true) const` - this is a template function. We use it to access arguments by `name`. It returns argument converted to selected type `T`. If the argument is not known or can not be converted to selected type, an error flag is set, which can be checked with the `check()` function. The parameter `name` is the argument name, while `space_delete` removes any spaces from the left and right of the string argument. `T` is the type our argument will converted to if possible. when accessing positional arguments you should include the prefix `@`.

4. `T get<T>(int index, bool space_delete = true) const` - This is also a template function that performs a similar task to the function above. The difference is the **positional arguments** are accessed by their `index`. Indexes are counted from zero.

5. `cv::String getPathToApplication() const` - returns the program or application path minus the program name. Remember at all times, path to application occupies index `0` in array `argv`. 

6. `bool has(const cv::String& name) const` - check if an argument was provided a value by the user in the command line. Arguments with default values are considered to be always present. `name` is the argument name to check.

7. `void printErrors() const` - prints list of errors encountered when we use the `check()` function.

8. `void printMessage() const` - use this function to print the message set out in the `about()` function.


**Example 1:** Program that expects one argument, an image, and displays it. We have not discussed how to deal with images yet, for now just pay attention to user input and how we process them. If we have supplied appropriate inputs, the following program should display a window with an image in it. To close the window press any key.

```c++
#include "opencv2/core.hpp"       // for OpenCV core types, cv::CommandLineParser
#include "opencv2/highgui.hpp"    // for cv::imshow() and cv::waitKey() 
#include "opencv2/imgcodecs.hpp"  // for cv::imread()
#include <iostream>

int main(int argc, char* argv[])
{
    // Define the command line arguments
    // We only need 1 argument passed in by the user, which is the image 
    // to be displayed. We will enforce that this argument must not be 
    // empty by using the <none> value
    const cv::String keys = 
        "{help h usage ? | | Display an image in a window }"
        "{@image | <none> | Full path to image }";
    
    // Create a cv::CommandLineParser object
    auto parser = cv::CommandLineParser(argc, argv, keys);

    // We also want to display a message about the application
    parser.about("\nRead and Display Image v1.0.0\n");
    parser.printMessage();

    // Let's extract the user input under the positional argument name `image`
    // The path to a file should be a cv::String or std::string 
    cv::String imagePath = parser.get<cv::String>("@image");

    // Check for any errors encountered while extracting user input
    if(!parser.check())
    {
        parser.printErrors(); // Print any errors
        return -1; // Exit application early
    }

    // If there are no errors, we can now read our image data
    cv::Mat image { cv::imread(imagePath, cv::IMREAD_UNCHANGED) };

    // Check if we have successfully read the image data
    if(image.empty())
    {
        std::cerr << "\nCould not read input image file: " 
                  << imagePath << '\n';

        return -1; // Early exit from application
    }

    // If we have successfully read image data, display image in window
    cv::imshow("Image", image);

    cv::waitKey(0);   

    std::cout << '\n';

    return 0;
}
```
:notebook_with_decorative_cover: If you are not sure about what an application does or what are the inputs and their meaning - try running the program without providing any user input in your terminal. Remember, when running a program go to the folder with the compiled file. Since I am using CMake, my compiled application/program will be in a folder inside the **build** folder. Just type the application name and press enter. On a Linux system where my application is called `Command_Line_Args_app`, it should look close to the following:

    ~/Example-Code/build/Command_Line_Args_app$ ./Command_Line_Args_app

:notebook_with_decorative_cover: If you run the above line, you should get the following output: 

    Read and Display Image v1.0.0

    Usage: Command_Line_Args_app [params] image 

            -?, -h, --help, --usage
                    Display an image in a window

            image (value:<none>)
                    Full path to image

    ERRORS:
    Missing parameter: '@image'

:notebook_with_decorative_cover: From the output above, you can see helpful messages about what the application does and user input/s (and meaning) expected. Because we did not provide expected user input/s we get an error message about missing parameter values.

:notebook_with_decorative_cover: We are now going to run our application and providing user inputs, which in this case is the full path to your image. Our image file `highway.png` is found in this folder `Example-Code/images`. Always try to provide full file paths rather than relative file paths.

    ~/Example-Code/build/Command_Line_Args_app$ ./Command_Line_Args_app /Full Path/To/Image/.../Example-Code/images/highway.png

:notebook_with_decorative_cover: Running the application successfully will display an image in a small window. You will also see the following output in your terminal. Output even shows you the input values you entered as the user.

    Read and Display Image v1.0.0

    Usage: Command_Line_Args_app [params] image 

            -?, -h, --help, --usage
                    Display an image in a window

            image (value:/home/.../Example-Code/images/highway.png)
                    Full path to image

**Example 2:** Program that accepts 3 positional arguments; 2 are images and the third is a numerical argument. This program takes the 2 images and combines/blends them according to a numerical value determining the level of blend. 

```c++
#include "opencv2/core.hpp"       // for OpenCV core types, cv::CommandLineParser, cv::addWeighted()
#include "opencv2/highgui.hpp"    // for cv::imshow() and cv::waitKey() 
#include "opencv2/imgcodecs.hpp"  // for cv::imread()
#include "opencv2/imgproc.hpp"    // for cv::resize()
#include <iostream>


int main(int argc, char* argv[])
{
    /* 
     * Define the command line arguments
     * We need 3 inputs from the user
     * 
     * 1. first image
     * 2. second image to blend with first image
     * 3. blending value between 0 and 1
     * 
    */
    const cv::String keys = 
        "{help h usage ? | | Blend two images and display resulting image in a window }"
        "{@image1 | <none> | Full path to first image }"
        "{@image2 | <none> | Full path to second image. Image should have same data type as image1. }"
        "{@alpha | 0.5 | Blending value between 0 and 1 }";
    
    // Create a cv::CommandLineParser object
    auto parser = cv::CommandLineParser(argc, argv, keys);

    // We also want to display a message about the application
    parser.about("\nBlend/Combine two images v1.0.0\n");
    parser.printMessage();

    // Let's extract the user inputs 
    cv::String image1 = parser.get<cv::String>("@image1");
    cv::String image2 = parser.get<cv::String>("@image2");
    double alpha = parser.get<double>("@alpha");

    // Check for any errors encountered while extracting user input
    if(!parser.check())
    {
        parser.printErrors(); // Print any errors
        return -1; // Exit application early
    }

    // Check the value of 'alpha' if it is between 0 and 1, 
    // if not use 0.5
    if(alpha >= 0 && alpha <= 1)
    {
        alpha = alpha;
    }
    else 
    {
        alpha = 0.5;
    }

    // If there are no errors, we can now read our image data
    cv::Mat sourceImage1 { cv::imread(image1, cv::IMREAD_UNCHANGED) };
    cv::Mat sourceImage2 { cv::imread(image2, cv::IMREAD_UNCHANGED) };

    // Check if we have successfully read the image data
    if(sourceImage1.empty())
    {
        std::cerr << "\nCould not read input image file: " 
                  << image1<< '\n';
        return -1; // Early exit from application
    }

    if(sourceImage2.empty())
    {
        std::cerr << "\nCould not read input image file: " 
                  << image2<< '\n';
        return -1; // Early exit from application
    }

    // Blend/Combine our two images
    // ===========================

    // First make sure size of second image is the same as that
    // of the first image
    cv::Mat dst; // image2 converted to same size as image1
    cv::resize(sourceImage2, dst, cv::Size(sourceImage1.cols, sourceImage1.rows), 0.0, 0.0);

    // Blend images
    cv::Mat blendedImage; // array to save the blended image    

    // We will use the function cv::addWeighted() to blend the two images
    cv::addWeighted(sourceImage1, alpha, dst, (1.0 - alpha), 0.0, blendedImage);

    // Display the blended image in window
    cv::imshow("Blended Image", blendedImage);

    cv::waitKey(0);
        
    std::cout << '\n';

    return 0;
}
```

:notebook_with_decorative_cover: To run the above program successfully, you have to provide full paths to the two images `lake.jpg` and `jet.jpg` in this folder `Example-Code/images`, then the alpha value (`0.2`). Seperate inputs by a single space. 

    ~/Example-Code/build/Command_Line_Args_app$ ./Command_Line_Args_app /Full Path/To/Image/.../Example-Code/images/lake.jpg /Full Path/To/Image/.../Example-Code/images/jet.jpg 0.2

**Example 3** - All arguments are non-positional. We will repeat the above example, but this time all the arguments are non-positional. Remember that non-positional arguments are NOT preceeded by the `@` character.

```c++
#include "opencv2/core.hpp"       // for OpenCV core types, cv::CommandLineParser, cv::addWeighted()
#include "opencv2/highgui.hpp"    // for cv::imshow() and cv::waitKey() 
#include "opencv2/imgcodecs.hpp"  // for cv::imread()
#include "opencv2/imgproc.hpp"    // for cv::resize()
#include <iostream>


int main(int argc, char* argv[])
{
    /* 
     * Define the command line arguments
     * We need 3 non-positional inputs from the user
     * 
     * 1. first image
     * 2. second image to blend with first image
     * 3. blending value between 0 and 1
     * 
    */
    const cv::String keys = 
        "{help h usage ? | | Blend two images and display resulting image in a window }"
        "{image1 | <none> | Full path to first image }"
        "{image2 | <none> | Full path to second image. Image should have same data type as image1. }"
        "{alpha | 0.5 | Blending value between 0 and 1 }";
    
    // Create a cv::CommandLineParser object
    auto parser = cv::CommandLineParser(argc, argv, keys);

    // We also want to display a message about the application
    parser.about("\nBlend/Combine two images v1.0.0\n");
    parser.printMessage();

    // Let's extract the user inputs 
    cv::String image1 = parser.get<cv::String>("image1");
    cv::String image2 = parser.get<cv::String>("image2");
    double alpha = parser.get<double>("alpha");

    // Check for any errors encountered while extracting user input
    if(!parser.check())
    {
        parser.printErrors(); // Print any errors
        return -1; // Exit application early
    }

    // Check the value of 'alpha' if it is between 0 and 1, 
    // if not use 0.5
    if(alpha >= 0 && alpha <= 1)
    {
        alpha = alpha;
    }
    else 
    {
        alpha = 0.5;
    }

    // If there are no errors, we can now read our image data
    cv::Mat sourceImage1 { cv::imread(image1, cv::IMREAD_UNCHANGED) };
    cv::Mat sourceImage2 { cv::imread(image2, cv::IMREAD_UNCHANGED) };

    // Check if we have successfully read the image data
    if(sourceImage1.empty())
    {
        std::cerr << "\nCould not read input image file: " 
                  << image1<< '\n';
        return -1; // Early exit from application
    }

    if(sourceImage2.empty())
    {
        std::cerr << "\nCould not read input image file: " 
                  << image2<< '\n';
        return -1; // Early exit from application
    }

    // Blend/Combine our two images
    // ===========================

    // First make sure size of second image is the same as that
    // of the first image
    cv::Mat dst; // image2 converted to same size as image1
    cv::resize(sourceImage2, dst, cv::Size(sourceImage1.cols, sourceImage1.rows), 0.0, 0.0);

    // Blend images
    cv::Mat blendedImage; // array to save the blended image    

    // We will use the function cv::addWeighted() to blend the two images
    cv::addWeighted(sourceImage1, alpha, dst, (1.0 - alpha), 0.0, blendedImage);

    // Display the blended image in window
    cv::imshow("Blended Image", blendedImage);

    cv::waitKey(0);
        
    std::cout << '\n';

    return 0;
}
```

:notebook_with_decorative_cover: If you are running an application you have not written, how do you know that the arguments are non-positional. Best way is to run the application without any arguments as follows:

    ~/Example-Code/build/Command_Line_Args_app$ ./Command_Line_Args_app

**Output**

    Blend/Combine two images v1.0.0

    Usage: Command_Line_Args_app [params] 

            -?, -h, --help, --usage
                    Blend two images and display resulting image in a window
            --alpha (value:0.5)
                    Blending value between 0 and 1
            --image1 (value:<none>)
                    Full path to first image
            --image2 (value:<none>)
                    Full path to second image. Image should have same data type as image1.


    ERRORS:
    Missing parameter: 'image1'
    Missing parameter: 'image2'

:notebook_with_decorative_cover: Non-positional argument names of character length greater than 1 are preceeded by two dash characters `--` e.g. `--image1`. One character non-positional arguments are preceeded by a single dash character `-` e.g. `-h`. If you look at the order in which your arguments are displayed to the user, it is not the same as in the program. Single character arguments will be displayed first in alphabetical order (if there is more than 1), then the multi-character arguments next, also in alphabetical order. 

:notebook_with_decorative_cover: To run the above program successfully, you have to provide full paths to the two images `lake.jpg` and `jet.jpg` in this folder `Example-Code/images`, then the alpha value (`0.2`). Seperate inputs by a single space. Since we are dealing with non-positional arguments the user does not need to provide inputs in the exact order they were written in the application. The user can supply the inputs in any order, provided they accompany the input with the argument name e.g. `--alpha=0.2`. You will see this when we run the application as follows:

    ~/Example-Code/build/Command_Line_Args_app$ ./Command_Line_Args_app --image1=/Full Path/To/Image/.../Example-Code/images/lake.jpg --alpha=0.2 --image2=/Full Path/To/Image/.../Example-Code/images/jet.jpg









