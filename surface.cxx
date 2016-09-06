#include "surface.h"

Surface::Surface(double Isovalue)
{
    this->isovalue = Isovalue;
}

double Surface::getIsovalue() {
    return isovalue;
}

