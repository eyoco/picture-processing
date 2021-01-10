#include "block.h"

/**
 * Returns the width of the block.
 */
int Block::width() const{/*your code here*/
	return data[0].size();
}

/**
 * Returns the height of the block.
 */
int Block::height() const{/*your code here*/
	return data.size();
}

/**
 * Default Block constructor.
 */
Block::Block() {/* nothing */}

/**
 * Useful Block constructor.
 * Makes a block from the rectangle of width by height pixels in im
 * whose upper-left corner is at position (x,y).
 */
Block::Block(PNG & im, int x, int y, int width, int height) {/*your code here*/
	data.resize(height, vector<HSLAPixel>(width));	
	for(int blocky = 0; blocky < height; blocky++){
		for(int blockx = 0; blockx < width; blockx++){
			if((blocky+y) >= int(im.height()) || (blockx+x) >= int(im.width())){
				cout << "finish build" << endl;
				return;
			}
			data[blocky][blockx] = *(im.getPixel(blockx+x, blocky+y));
		}
	}	
	

}

/**
 * Draws the block at position (x,y) in the image im
 */
void Block::render(PNG & im, int x, int y) const {/*your code here*/
	int im_h = im.height();
	int im_w = im.width();
	for(int blockh = 0; blockh < height(); blockh++){
		if (blockh+y >= im_h) return;
		for(int blockw = 0; blockw < width(); blockw++){
			if (blockw+x >= im_w) return;
			/*for(int countCol = x; countCol < sizeOfCol + x; countCol++){*/
			(im.getPixel(blockw+x,blockh+y)) -> h = (data[blockh][blockw]).h;
			(im.getPixel(blockw+x,blockh+y)) -> s = (data[blockh][blockw]).s;
			(im.getPixel(blockw+x,blockh+y)) -> l = (data[blockh][blockw]).l;
			(im.getPixel(blockw+x,blockh+y)) -> a = (data[blockh][blockw]).a;
		}
	}
}

/**
 * Changes the saturation of every pixel in the block to 0,
 * which removes the color, leaving grey.
 */
void Block::greyscale() {/*your code here*/
	for(unsigned int countRow= 0; countRow < data.size(); countRow++){
		for(unsigned int countCol = 0; countCol < data[0].size(); countCol++){
			data[countRow][countCol].s = 0;
		}
	}
}
