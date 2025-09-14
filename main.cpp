#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Header {
  char idlength;
  char colorMapType;
  char dataTypeCode;
  short colorMapOrigin;
  short colorMapLength;
  char colorMapDepth;
  short xOrigin;
  short yOrigin;
  short width;
  short height;
  char bitsPerPixel;
  char imageDescriptor;

};

struct Pixel{
  unsigned char BLUE;
  unsigned char GREEN;
  unsigned char RED;
};

struct Image{
  Header header;
  vector<Pixel> pixelData;
}

Image ReadTGA(const string& path){
  ifstream file(path, ios::binary);
  Image image;

  if(!file.is_open()){
    cerr << "Error input file " << path << "not found" << endl;
    return image;
  }

  Header header;
  file.read(reinterpret_cast<char*>(&header.idlength), sizeof(header.idlength));
  file.read(reinterpret_cast<char*>(&header.colorMapType), sizeof(header.colorMapType));
  file.read(reinterpret_cast<char*>(&header.dataTypeCode), sizeof(header.dataTypeCode));
  file.read(reinterpret_cast<char*>(&header.colorMapOrigin), sizeof(header.colorMapOrigin));
  file.read(reinterpret_cast<char*>(&header.colorMapLength), sizeof(header.colorMapLength));
  file.read(reinterpret_cast<char*>(&header.colorMapDepth), sizeof(header.colorMapDepth));
  file.read(reinterpret_cast<char*>(&header.xOrigin), sizeof(header.xOrigin));
  file.read(reinterpret_cast<char*>(&header.yOrigin), sizeof(header.yOrigin));
  file.read(reinterpret_cast<char*>(&header.width), sizeof(header.width));
  file.read(reinterpret_cast<char*>(&header.height), sizeof(header.height));
  file.read(reinterpret_cast<char*>(&header.bitsPerPixel), sizeof(header.bitsPerPixel));
  file.read(reinterpret_cast<char*>(&header.imageDescriptor), sizeof(header.imageDescriptor));

  image.header = header;

  if (header.width <= 0 || header.height <- 0){
    cerr << "Error: Invalid image dimensions." << endl;
    return image;
  }

  int pixelCount = header.width * header.height;

  for (int i = 0; i < pixelCount; i++){
    Pixel pixel;
    file.read(reinterpret_cast<char*>(&pixel.BLUE), sizeof(pixel.BLUE));
    file.read(reinterpret_cast<char*>(&pixel.GREEN), sizeof(pixel.GREEN));
    file.read(reinterpret_cast<char*>(&pixel.RED), sizeof(pixel.RED));

    image.pixelData.push_back(pixel);
  }

  file.close();
  return image;

}

void WriteFile(Image& image, const string& outputPath){
  ofstream outputFile(outputPath, ios::binary);
  if (!outputFile.is_open()){
    cout << "Failed to open output file: " << outputPath << endl;
    return;
  }
  outputFile.write(reinterpret_cast<char*>(&image.header.idlength), sizeof(image.header.idlength));
  outputFile.write(reinterpret_cast<char*>(&image.header.colorMapType), sizeof(image.header.colorMapType));
  outputFile.write(reinterpret_cast<char*>(&image.header.dataTypeCode), sizeof(image.header.dataTypeCode));
  outputFile.write(reinterpret_cast<char*>(&image.header.colorMapOrigin), sizeof(image.header.colorMapOrigin));
  outputFile.write(reinterpret_cast<char*>(&image.header.colorMapLength), sizeof(image.header.colorMapLength));
  outputFile.write(reinterpret_cast<char*>(&image.header.colorMapDepth), sizeof(image.header.colorMapDepth));
  outputFile.write(reinterpret_cast<char*>(&image.header.xOrigin), sizeof(image.header.xOrigin));
  outputFile.write(reinterpret_cast<char*>(&image.header.yOrigin), sizeof(image.header.yOrigin));
  outputFile.write(reinterpret_cast<char*>(&image.header.width), sizeof(image.header.width));
  outputFile.write(reinterpret_cast<char*>(&image.header.height), sizeof(image.header.height));
  outputFile.write(reinterpret_cast<char*>(&image.header.bitsPerPixel), sizeof(image.header.bitsPerPixel));
  outputFile.write(reinterpret_cast<char*>(&image.header.imageDescriptor), sizeof(image.header.imageDescriptor));

  for (int i = 0; i < (image.header.width*image.header.height); i++){
    Pixel currentPixel = image.pixelData[i];
    unsigned char currentBlue = currentPixel.BLUE;
    unsigned char currentGreen = currentPixel.GREEN;
    unsigned char currentRed = currentPixel.RED;
    outputFile.write(reinterpret_cast<char*>(&currentBlue), sizeof(currentBlue));
    outputFile.write(reinterpret_cast<char*>(&currentGreen), sizeof(currentGreen));
    outputFile.write(reinterpret_cast<char*>(&currentRed), sizeof(currentRed));
  }

  outputFile.close();

}

int main() {

  string path = "input/car.tga";
  Image image = ReadTGA(path);
  string outpath = "output/task1.tga";
  WriteFile(image, outpath);
  cout << "done" << endl;

  return 0;
}