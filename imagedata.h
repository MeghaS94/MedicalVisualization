#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include <string>

using namespace std;

class ImageData
{
public:
    ImageData();
    virtual void loadData(string foldername)=0;
    virtual int* getExtent()=0;
};

#endif // IMAGEDATA_H
