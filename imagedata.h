#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include <string>
#include <vector>

using namespace std;

class ImageData
{
public:
    ImageData();
    virtual void loadData(string foldername)=0;
    virtual int* getExtent()=0;
    virtual vector<double> Spacing()=0;
};

#endif // IMAGEDATA_H
