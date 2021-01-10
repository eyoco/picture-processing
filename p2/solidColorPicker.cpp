#include "solidColorPicker.h"

solidColorPicker::solidColorPicker()
{
/* your code here  :)  */
}

HSLAPixel solidColorPicker::operator()(point p)
{
/* your code here */
	HSLAPixel r;
	r.h = p.c.color.h;
	r.s = p.c.color.s;
	r.l = p.c.color.l;
	return r;
}
