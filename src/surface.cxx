#include "surface.h"

Surface::Surface(double Isovalue_start, double Isovalue_end)
{
    this->isovalue_start = Isovalue_start;
    this->isovalue_end = Isovalue_end;
}
/*
double Surface::getIsovalueStart() {
    return isovalue_start;
}

double Surface::getIsovalueEnd() {
    return isovalue_end;
}

void Surface::setIsovalueStart(double val) {
    isovalue_start = val;
}

void Surface::setIsovalueEnd(double val) {
    isovalue_end = val;
}

vector < vector<double> > Surface::getPtsOnSlice()
{
    return points_on_slice;
}

void Surface::setPtsOnSlice(vector < vector<double> > pts)
{
    points_on_slice = pts;
}
*/
