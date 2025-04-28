# Introduction

:notebook_with_decorative_cover: OpenCV allows us to draw basic shapes (lines, squares, circles etc.) on top of images.

:notebook_with_decorative_cover: For color images, OpenCV's drawing functions affect only the first `3` channels. For `4`-channel images, the last channel (also known as the **alpha channel**) is ignored.

:notebook_with_decorative_cover: For single-channel images, OpenCV drawing functions only use the `1` channel.

:notebook_with_decorative_cover: Drawing on top of images is considered part of image processing hence you will find the drawing functions in the header file `<imgproc.hpp>`.

:notebook_with_decorative_cover: Once we start using OpenCV's drawing functions you will notice that most will require `thickness`, `lineType` and `shift` parameters. We will discuss these first as they are important to how your drawing will visually appear.

1. `thickness` - This parameter represents the thickness of the line measured in pixels. For most shapes, you provide an integer value starting from `1`. However, for closed shapes (circles, rectangles, polygons etc), you can also provide the value `-1` (which is an alias for `cv::FILLED`) if you want the shape to be filled with the same color as the shape edges.
2. `lineType` - This is also an integer parameter which accepts the values `4` (aliase for `cv::LINE_4`), `8` (aliase for `cv::LINE_8`) or `cv::LINE_AA`. This value indicates whether the lines should be **4-connected**, **8-connected** or **anti-aliased**. **4-connected** and **8-connected** lines use the <a href = "https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm">Bresenham line algorithm</a> - which determines the pixels that should be selected in order to form a close approximation to a straight line between two points. There is a lot of literature on the Bresenham algorithm online that you can look at to expand your knowledge. Some links are in the **References** section at the end of this tutorial. `cv::LINE_AA` or <a href = "https://en.wikipedia.org/wiki/Spatial_anti-aliasing">anti-aliased</a> uses <a href = "https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://www.southampton.ac.uk/~msn/book/new_demo/gaussian/&ved=2ahUKEwj44YWW6vKMAxWjUUEAHUO3K_EQFnoECCMQAw&usg=AOvVaw3lybc2WphSBVIKrSEv17uI">Gausian filtering</a> to select which pixels to use when connecting lines. Anti-aliasing minimizes distortions (e.g. jagged polygon edges) thus making lines, edges etc., appear smooth when high-resolution images are viewed at a lower resolution (also called **zooming in**). As such if you want smooth lines use `cv::LINE_AA` followed by `cv::LINE_8` and then `cv::LINE_4` in your drawing functions. 
3. `shift` - Most of the drawing functions accept endpoints (for lines), center points (for circles), corner points (for rectangles) pixel coordinates as integer values. However, these functions also support sub-pixel accuracy through the `shift` parameter. This parameter specifies the fractional bits and the real point coordinates are computed as $cv::Point(x,y) = cv::Point2f(x*2^{-shift}, y*2^{-shift})$. For example, if you want a circle centered at `(5, 5)`, but set shift to `1`, then the circle will be drawn at `(2.5, 2.5)`. The effect of this will typically be quite subtle, and depend on the line type used. The effect is most noticiable for anti-aliased lines.

## Image Coordinate System

:notebook_with_decorative_cover: When drawing you mainly use coordinates to establish the starting point/s of your shapes. In order to do this, you need a good understanding of the 2-D image coordinate system used in OpenCV. 

1. The 2-D image coordinate system is represented as a grid made out of pixels.
2. Each pixel represents `1` unit.
3. The origin of the coordinate system is the top left pixel of the image and has the coordinates `x = 0` and `y = 0` or `(0,0)`.
4. The coordinate system is left-handed, i.e. x-axis is positive to the right and y-axis is positive downwards as shown in Figure 1.

**Figure 1:** 2-Dimensional image coordinate system in OpenCV

![OpenCV 2-D image coordinate system](./images/image-coordinate-system.png)

5. When writing coordinates you always start with the x-coordinate followed by the y-coordinate.



## References

1. https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
2. https://digitalbunker.dev/bresenhams-line-algorithm/
3. https://www.tutorialspoint.com/computer_graphics/bresenhams_line_generation_algorithm.htm
4. https://en.wikipedia.org/wiki/Spatial_anti-aliasing