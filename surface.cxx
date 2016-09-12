#include "surface.h"

Surface::Surface(double Isovalue_start, double Isovalue_end)
{
    this->isovalue_start = Isovalue_start;
    this->isovalue_end = Isovalue_end;
}

double Surface::getIsovalueStart() {
    return isovalue_start;
}

double Surface::getIsovalueEnd() {
    return isovalue_end;
}
