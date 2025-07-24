# Introduction

:notebook_with_decorative_cover: In this tutorial, we continue to build on the material on bitwise operators from the previous tutorial, by looking at how to create **masks** for image processing.

:notebook_with_decorative_cover: **Masks** allow us to define a region of interest within an image. This allows us to restrict image operators, functions or algorithms to the area defined by the mask.

:notebook_with_decorative_cover: If you want a mask, you have to create a binary grayscale image whose pixel values consist of zero- and non-zero values.

## Creating masks in OpenCV

:notebook_with_decorative_cover: One thing you will notice with a lot of OpenCV functions that require a mask, is that, it should be an **8-bit single channel array** of the same size as the input image. Which means your mask should have the data type `CV_8UC1` or `CV_8SC1`. `CV_8UC1` is the more preferred option.

:notebook_with_decorative_cover: Once we have our mask, we can apply it on an image either using **pixel multiplication** or **bitwise operator AND**, the latter in general being faster. In the output image, all pixels which are zero in the mask are set to zero in the output image. All others remain unchanged.