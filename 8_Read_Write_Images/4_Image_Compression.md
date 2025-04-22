# Codecs

:notebook_with_decorative_cover: Early on we mentioned that image data is memory consuming and the best way to handle it is compressing  it when not in use and then decompressing it when you need to process the data. This process is performed by software packages generically referred to as **codecs** - short for **co**-mpression and **dec**-compression librarie-**s**. 

:notebook_with_decorative_cover: Every operating system (on your computer, phone etc) will have a few codecs available for each of the common image file types. This is how they handle the images you take and save on your computer system or phone. 

:notebook_with_decorative_cover: If your system does not have a codec for a specific image format you can install it yourself. We did that when we installed packages such as `libjpeg` (On Unix systems you also need the development file `libjpeg-dev`) early on in our tutorials. These codecs then become part of your operating system.

:notebook_with_decorative_cover: In addition, image processing software or libraries also come with their own codecs. OpenCV comes with codecs for common image file formats such as `jpeg`, `png`, `tiff`, etc., but also codecs for uncommon image file types e.g. `OpenEXR`, `PAM`, `LogLov` etc.

:notebook_with_decorative_cover: If both OpenCV and your operating system provide the same codec, which codec is used depends on the following options:

a) use the codec supplied with OpenCV - these are included if you add them to your **CMake** file when building your OpenCV modules.

b) use the external codec libraries such as `libjpeg` or `libpng`. In Linux, you have to install these codecs together with their development files e.g., install `libjpeg` with its development file `libjpeg-dev`.

:notebook_with_decorative_cover: If you are using Windows O/S, option (a) above is the default way of using codecs. On OS X/Linux, the default option is (b); if however CMake cannot find the codec for some reason then it will use option (a). 

# Image compression

:notebook_with_decorative_cover: Since image files are large and require a lot of memory for storage, we use **image compression** to reduce their size without significantly affecting visual quality. This is achieved by either removing redundant data or approximating parts of the image.

:notebook_with_decorative_cover: There are two main types of image compression: <a href = "https://en.wikipedia.org/wiki/Lossless_compression">lossless compression</a> and <a href = "https://en.wikipedia.org/wiki/Lossy_compression">lossy compression</a>. **Lossless compression** retains the original image data, while **lossy compression** discards some information to achieve a smaller file size, potentially reducing the image quality.

## Why is Image Compression Important?

:notebook_with_decorative_cover: Image compression is essential for the following reasons:

1. **Reduced storage space**: Compressed images occupy less storage space, allowing you to store more images or use the saved space for other purposes.

2. **Faster transmission**: Smaller file sizes enable faster transmission of images over networks, which is particularly important in applications like video streaming and remote sensing.

3. **Reduced bandwidth usage**: Compressed images consume less bandwidth, which is crucial for data transfer on limited or metered connections.

## The Theory Behind Image Compression

:notebook_with_decorative_cover: Image compression techniques typically exploit the **spatial** and **color** redundancies in images. Spatial redundancy arises from the correlation between neighboring pixels, while color redundancy stems from the similarity of color values in adjacent regions.

:notebook_with_decorative_cover: **Lossless compression** involve no loss of information. If data have been losslessly compressed, the original data can be recovered exactly from the compressed data after a compress/expand cycle. Lossless compression is generally used for so-called "discrete" data, such as database records, spreadsheets, word-processing files, and even some kinds of image and video information. A good example of using lossless compression would be with medical images. We want to be able to reconstruct the original image as is because any differences would potentially mislead radiologists. Because the price for this kind of mishap may be a human life, it makes sense to be very careful about using a compression scheme that generates a reconstruction that is different from the original. In essence, lossless compression algorithms are needed in cases that require compression where we want the reconstruction to be identical to the original. <a href = "https://en.wikipedia.org/wiki/Portable_Network_Graphics">PNG</a> and <a href = "https://en.wikipedia.org/wiki/GIF">GIF</a>, use lossless techniques like <a href = "https://en.wikipedia.org/wiki/Run-length_encoding">Run-Length Encoding</a> and <a href = "https://en.wikipedia.org/wiki/Huffman_coding">Huffman coding</a> for image compression.

* **Run-Length Encoding (RLE)** - Faced with sequences of data in which the same value appears more than once consecutively, RLE stores the data as a single data value and count, rather than as the original sequence. Consider an image containing plain black text on a solid white background. There will be many long runs of white pixels in the blank space, and many short runs of black pixels within the text. A hypothetical scan line, with **B** representing a black pixel and **W** representing white, might read as follows:

    **WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWBWWWWWWWWWWWWWW**

    Applying RLE data compression algorithm to the above hypothetical scan line, we can store the data as follows:

    **12W1B12W3B24W1B14W**

    This can be interpreted as a sequence of twelve Ws, one B, twelve Ws, three Bs, etc., and represents the original 67 characters in only 18. While the actual format used for the storage of images is generally binary rather than ASCII characters like this, the principle remains the same. Even binary data files can be compressed with this method.

:notebook_with_decorative_cover: **Lossy compression** methods result in some amount of data being lost in the process.  Thus, after a compression/decompression cycle, the data set will be modified from the uncompressed original and information may be lost. This loss of data can be tolerated. Lossy compression techniques attempt to eliminate unnecessary or redundant information, focusing more on saving space over preserving the accuracy of the data. Ideally, the loss is either minimal or undetectable by human observations. Lossy compression techniques are used for pictures and music files that can be trimmed at the edges. Unlike text files and processing files, pictures and music do not require reconstruction to be identical to the original, especially if the data dropped is insignificant or undetectable. Lossy compression is used with <a href = "https://en.wikipedia.org/wiki/JPEG">JPEG</a> and <a href = "https://cs.stanford.edu/people/eroberts/courses/soco/projects/data-compression/lossy/mp3/index.htm">MP3</a> technology. Examples of lossy compression methods are: 

* <a href = "https://en.wikipedia.org/wiki/Discrete_cosine_transform">**Discrete Cosine Transform</a> (DCT)** - a mathematical transformation that takes the spatial information from an image and convert it into numeric data in the form of frequency values. In this way the information in an image now exists in a quantitative form that can be manipulated for compression.

* <a href = "https://en.wikipedia.org/wiki/Quantization_(image_processing)">**Quantization**</a> - is the process of reducing the number of bits needed to store an integer value by reducing the precision of the integer. For example reducing 16-bit images to be 8-bit images. This means you will need less space to store the image as 8-bit values require less storage space than 16-bit values. However, it means you loose some degree of precision with your integer values as you move from 16-bit to 8-bit.


:notebook_with_decorative_cover: Knowing about the theory of image compression is important especially when choosing which image file format to use in your projects. *Are you concerned about loss of information, image quality or smaller file sizes that enable faster transmission and processing?*

:notebook_with_decorative_cover: There is more information out there about image compression techniques. This can be an interesting research area if you can come up with new compression techniques. **Go and explore!!!!!**