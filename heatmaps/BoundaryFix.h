#include "clipper.h"
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <stdio.h>
#include <ios>
#include <map>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <fts.h>
#include <sstream>

using namespace std;

void processBoundaryFixing(stringstream &text, stringstream &outstream);
void processBoundaryFixing2(stringstream &instream, stringstream &outstream);

struct points
    {
        float x;
        float y;
    };



