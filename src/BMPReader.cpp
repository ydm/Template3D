#include <cassert>
#include <iostream>
#include "BMPReader.hpp"


BMPReader::BMPReader()
  : data(nullptr)
{
  clear();
}

BMPReader::~BMPReader()
{
  clear();
}

void BMPReader::read(const std::string& path)
{
  clear();
  FILE *f = fopen(path.c_str(), "rb");
  if (!f)
    {
      return;
    }

  assert(fread(header, 1, 54, f) == 54);
  assert(header[0] == 'B' && header[1] == 'M');

  // Read header data
  dataPos = *reinterpret_cast<int *>(header + 0x0a);
  imageSize = *reinterpret_cast<int *>(header + 0x22);
  width = *reinterpret_cast<int *>(header + 0x12);
  height = *reinterpret_cast<int *>(header + 0x16);

  // Repair header data
  if (dataPos <= 0)
    dataPos = 54;
  if (imageSize <= 0)
    imageSize = width * height * 3;

  // Read image data
  data = new unsigned char[imageSize];
  fread(data, 1, imageSize, f);

  // Close file
  fclose(f);
  
  //std::cout << "dataPos=" << dataPos << ", "
  //          << "imageSize=" << imageSize << ", "
  //          << "width=" << width << ", "
  //          << "height=" << height << "\n";
}

void BMPReader::clear()
{
  for (int i = 0; i < 54; i++)
    {
      header[i] = '\0';
    }
  dataPos = 0;
  width = height = 0;
  imageSize = 0;
  if (data != nullptr)
    {
      delete [] data;
    }
}
