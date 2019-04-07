#include<boost/gil/extension/io/jpeg.hpp>
#include<boost/gil.hpp>
#include<iostream>

using namespace boost::gil;

template<typename srcView, typename dstView>
void conv(srcView const& src, dstView &dst, float * filter, int fsize_x, int fsize_y)
{ 
  int origin_x = (fsize_x - 1) / 2; 
  int origin_y = (fsize_y - 1) / 2;
  
  /// assigning a locator to the leftmost image pixel 
  typename srcView::xy_locator src_loc = src.xy_at(0,0);
  typename srcView::xy_locator::cached_location_t loc[fsize_x][fsize_y];
  
  /// loop to flip the corresponding image patch for convolution
  for (int i = 0; i < fsize_x; i++)
  	for (int j = 0; j < fsize_y; j++)
  		loc[i][j] = src_loc.cache_location(origin_x - i, origin_y - j);  
  
  /// computing the convolution for a (x,y) position in the image
  for (int y = 0; y < src.height(); ++y)
  {
    typename dstView::x_iterator dst_it = dst.row_begin(y);
      for (int x = 0; x < src.width(); ++x)
  	  {
  		auto temp = 0;
  		for (int i = 0; i < fsize_x; i++) 
  			for(int j = 0; j < fsize_y; j++)
	  			temp = temp + src_loc[loc[i][j]] * filter[i * fsize_x + j];
	  	 
	  	 /// adjusting the output to save appropriately in JPEG format
	  	 temp = temp + 128;
	  	 if(temp < 0)
	  	    temp = 0;
	  	 if(temp > 255)
	  	  	temp = 255;

         (*dst_it) = temp;
         ++dst_it;
         ++src_loc.x();
      }
      src_loc += point<std::ptrdiff_t>(-src.width(),1);
  }
}

int main()
{
  /** Specify the filter parameters -:
   * fsize_x - filter width in x direction, should be an odd number
   * fsize_y - filter width in y direction, should be an odd number
   * filter - elements of the filter. Currently using the sobel filter for edge detection
   */
  const int fsize_x = 3; 
  const int fsize_y = 3;
  float filter[fsize_x][fsize_y] = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
  
  /// Read the gray scale input, and declare a destination image to save the convolved output
  gray8_image_t src;
  read_image("grayscale.jpg", src, jpeg_tag());
  gray8_image_t dst(src.width(), src.height());

  /// calling the conv function and writing output
  conv(const_view(src), view(dst), (float*)filter, fsize_x, fsize_y); 
  write_view("convolved.jpg", view(dst), jpeg_tag());
  return 0;
}
