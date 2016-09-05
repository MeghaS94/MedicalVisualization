#include "slice.h"

Slice::Slice(int type)
{
    this->type = type;
}

int Slice::getType() {
    return type;
}
