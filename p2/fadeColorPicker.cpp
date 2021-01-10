#include "fadeColorPicker.h"

fadeColorPicker::fadeColorPicker(double fade)
{
    /* your code here */
	fadeFactor = fade;
}

HSLAPixel fadeColorPicker::operator()(point p)
{
    /* your code here */
	double distToCentre;
	double distX;
	double distY;
	double l_new;
	
	distX = p.x - p.c.x;
	distY = p.y - p.c.y;
	distX = distX * distX;
	distY = distY * distY;
	distToCentre = pow(distX + distY, 0.5);
	
	l_new = p.c.color.l * pow(fadeFactor, distToCentre);

	return HSLAPixel(p.c.color.h, p.c.color.s, l_new);
}
