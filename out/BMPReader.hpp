#ifndef __T3D_BMP_READER_HPP__
#define __T3D_BMP_READER_HPP__

#include <string>

namespace t3d
{

/**
 * Reads a BMP image and converts it to a convenient format for use as
 * OpenGL texture.
 */
class BMPReader
{
public:
  BMPReader();
  ~BMPReader();
  void read(const std::string& path);
  void clear();

public:
  unsigned char header[54];
  int dataPos;
  int width, height;
  int imageSize;
  unsigned char *data;
};

} // namespace

#endif // __T3D_BMP_READER_HPP__
