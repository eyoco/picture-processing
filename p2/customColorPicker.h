/**
 * @file customColorPicker.h
 * Definition of a custom color picker.
 *
 */
#ifndef CUSTOMCOLORPICKER_H
#define CUSTOMCOLORPICKER_H

#include "colorPicker.h"
#include "cs221util/HSLAPixel.h"
#include "point.h"
#include "center.h"
#include <cmath>
using namespace std;

class customColorPicker : public colorPicker
{
  public:

    customColorPicker();

    virtual HSLAPixel operator()(point p);
};

#endif