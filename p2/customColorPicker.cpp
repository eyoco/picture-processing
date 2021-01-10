#include "customColorPicker.h"

customColorPicker::customColorPicker(){
}

HSLAPixel customColorPicker::operator()(point p)
{
	HSLAPixel t;

	t.h = p.c.color.h * 1.5;
	t.s = p.c.color.s * 0.7;
	t.l = p.c.color.l * 0.6;

	return t;
}
