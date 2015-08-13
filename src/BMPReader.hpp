#ifndef __BMP_READER_HPP__
#define __BMP_READER_HPP__

#include <string>

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

#endif // __BMP_READER_HPP__
