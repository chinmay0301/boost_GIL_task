# Competency Task Boost GIL

- Implemented a convolution function in the `read_test.cpp` file, which allows convolving an image with a specified filter. The filter can be specified in the file. The images show the results for edge detection using the sobel filter for a grayscale image. The current implementation is supported for jpeg images only. 

- Specify the filter parameters, input image, and path/name for the output (convolved image) in the file. The code can be compiled using the following command. Make sure libjpeg installed properly.
> g++ -std=c++11 -ljpeg read_test.cpp -o out          


Run the generated executable as follows -:
> ./out     

- The repository shows two images `grayscale.jpg`, which is the input image and `convolved.jpg` which is the output image obtained by convolving the inpu with a sobel filter, which is used for edge detection. 

