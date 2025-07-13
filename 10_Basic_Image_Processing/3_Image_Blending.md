# Image Blending

:notebook_with_decorative_cover: We use **image blending** to combine two or more images into a single image. There are various <a href = "http://dev.cs.ovgu.de/tutorials/Grokking-the-GIMP-v1.0/node55.html#:~:text=Multiply%2C%20Divide%2C%20Screen%2C%20and%20Overlay%20are%20all,product%20of%20the%20foreground%20and%20background%20pixels.">blending methods</a>, most of which can be found in photo editing software packages such as GIMP or Photoshop. 

:notebook_with_decorative_cover: In the previous tutorial, we looked at the image arithmetic operators - addition, subtraction, multiplication and division. These operators are considered to be simple blend modes as they also combine two or more images into a single image. This kind of blending involves using mathematical operations to directly manipulate the pixel values of the input images - also known as **Pixel-level blending**. 

:notebook_with_decorative_cover: We should also mention two other common blending methods - **Layer-based blending** and **Gradient blending**. We will not discuss these further as they include image techniques we have not looked at yet - which will only serve to confuse you. 

:notebook_with_decorative_cover: In this tutorial, we will concentrate on a form of Pixel-level blending that gives us more control than simple arithmetic operators. It is a **linear blend operator**, which allows us to use weights to determine the level of influence of each input image in the output image. It is defined by the equation $Q(row, column) = \alpha \times P_1(row, column) + (1 - \alpha) \times P_2(row, column)$, where:

* $Q$ - is the output image
* $P_1$ and $P_2$ - are the two input images. In some applications $P_2$ can also be a constant scalar value, thus allowing a constant offset value to be added to a single image.
* $\alpha$ - weight or level of influence assigned to an image. This is a value between `0` and `1`.

:notebook_with_decorative_cover: OpenCV implements the linear blend operator through the function `void cv::addWeighted(cv::InputArray src1, double alpha, cv::InputArray src2, double beta, double gamma, cv::OutputArray dst, int dtype = -1)`, which you can find in the header `<opencv2/core.hpp>`. The function parameters are defined as follows:

* `src` - first input array
* `alpha` - weight value (between `0` and `1`) of the first array elements
* `src2` - second input array of the same size and channel number as `src1`
* `beta` - weight of second array elements. `beta` should be equal to `1-alpha`.
* `gamma` - scalar added to the output array
* `dst` - output array that has the same size and number of channels as the input arrays
* `dtype` - optional depth of the output array; when both input arrays have the same depth, dtype can be set to -1, which will be equivalent to src1.depth().

:notebook_with_decorative_cover: The function `cv::addWeighted()` calculates the weighted sum of two arrays as $dst = ((src1 * \alpha) + (src2 * \beta)) + gamma$.