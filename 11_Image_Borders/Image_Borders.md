# Introduction

:notebook_with_decorative_cover: Up to this point of our tutorials we have not been required to deal with image processing techniques that require the use of a source image pixel neighbours to compute a value in the destination image. The question would be what do we do when we encounter a pixel that does not have enough neighbours for us to compute a new value from. Such pixels are found at the image borders.

:notebook_with_decorative_cover: OpenCV handles such a problem by creating what are known as **virtual pixels** outside of the image at the borders. This is also known as **padding out** an image. This process always results in a somewhat larger image than the original. The process of creating these artificial pixels in also known as **extrapolation**. Extrapolation takes advantage of existing pixels to artificially create other pixels that fall outside the image boundary. 

:notebook_with_decorative_cover: This tutorial is going to set you up so that you go into future topics (e.g. Filtering, Geometrical Transformation, Thresholding, etc.) knowing how pixels are handled at image borders by various image processing techniques.


**Border Extrapolation**

:notebook_with_decorative_cover: In most cases OpenCV functions will create these virtual pixels for you, all you have to do is supply a **flag** specifying how you want the pixels to be created. These flags can be found under the enumerator <a href = "https://docs.opencv.org/4.8.0/d2/de8/group__core__array.html#ga209f2f4869e304c82d07739337eae7c5">cv::BorderTypes</a>. 

:notebook_with_decorative_cover: The following table gives a brief description of the border types you can create. We have also provided images to show how the virtual pixels at the borders are created. We also show examples of how an image would look if you applied the various borders. The following image was used as the original:

**Figure 1** Input image for creating various border types

![Source image for making borders](./images/source_img_make_borders.jpeg)

**Table 1** How OpenCV exprapolates pixels when creating image borders. Images in the table use a border size of 20 pixels on all sides.

| Border type | Effect | Pixels | Image example|
| ----------- | ------ | ------ | ----- |
| cv::BORDER_CONSTANT | Extend pixels by using a supplied (constant) value | ![cv::BORDER_CONSTANT](./images/border_constant.png)|Constant value = 25 ![cv::BORDER_CONSTANT with value 25](./images/constant_border_v25.png)Constant value = 200 ![cv::BORDER_CONSTANT with value 200](./images/constant_border_v200.png) |
| cv::BORDER_REPLICATE | Extend pixels by copying edge pixel | ![cv::BORDER_REPLICATE](./images/border_replicate.png) | ![cv::BORDER_REPLICATE](./images/replicate_border.png) |
| cv::BORDER_REFLECT | Extend pixels by mirror reflection | ![cv::BORDER_REFLECT](./images/border_reflect.png) | ![cv::BORDER_REFLECT](./images/reflect_border.png) |
| cv::BORDER_WRAP | Extend pixels by replicating from opposite side | ![cv::BORDER_WRAP](./images/border_wrap.png) | ![cv::BORDER_WRAP](./images/wrapped_border.png) |
| cv::BORDER_REFLECT_101 | Extend pixels by reflection, edge pixel is not "doubled" | ![cv::BORDER_REFLECT_101](./images/border_reflect_101.png) | ![cv::BORDER_REFLECT_101](./images/reflect_border_101.png) |
| cv:: BORDER_REFLECT101 | Same as cv::BORDER_REFLECT_101 | | |
| cv:: BORDER_DEFAULT | Same as cv::BORDER_REFLECT_101 | | |
| cv::BORDER_ISOLATED | Do not look outside of image or region of interest | We will discuss this type on its own later | |
