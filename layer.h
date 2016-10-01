#ifndef TISSUE_H
#define TISSUE_H

#include <string>

using namespace std;

typedef struct Layer {
    string name;
    float isovalueStart;
    float isovalueEnd;
    bool on;

    Layer(string n, float isoStart, float isoEnd, bool b) {
        name = n;
        isovalueStart = isoStart;
        isovalueEnd  = isoEnd;
        on = b;
    }

} Layer;

#endif // TISSUE_H
