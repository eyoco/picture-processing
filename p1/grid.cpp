#include "grid.h"
#include "grid_given.cpp"

// PA1 functions


/**
 * Destroys the current Grid. This function should ensure that
 * memory does not leak on destruction of a grid.
 */
Grid::~Grid(){ /*your code here*/
	clear();
}

/**
 * Rotate row r (row 0 is the first) by count positions.
 * If row r is ABCDE (left to right) in grid g then row r
 * in grid g should be DEABC after the call g.rotateR(r, 2).
 * Rotate headOfCol_ if necessary.
 */
void Grid::rotateR(int r, int count) { /* your code here */
	
	r = r % numRows();
	Node* currHeadR = headOfRow_[r];
	Node* temp = headOfRow_[r];
	Node* headUp = headOfRow_[r] -> up;
	Node* currheadU = headOfRow_[r]->up;
	Node* headDown = headOfRow_[r] -> down;
	Node* currheadD = headOfRow_[r]->down;
	
	if (count < 0 || r < 0) return;
	for(int countRow = 0; countRow < count; countRow++){
		for(int countCol = 0; countCol < numCols(); countCol++){
		if(countCol == numCols() - 1){
			currheadD = currheadD->right;
			currheadU = currheadU->right;
			temp->up = headUp;
			temp->down = headDown;
			currheadD->up = temp;
			currheadU->down = temp;
		}else{
			currheadD = currheadD->right;
			currheadU = currheadU->right;
			temp->up = currheadU;
			temp->down = currheadD;
			currheadD->up = temp;
			currheadU->down = temp;
			temp = temp->right;
		}
		}
	}
	for (int numberRotate = 0; numberRotate < count; numberRotate++){
		currHeadR = currHeadR->left;
		if (r == 0) {
			for (int i = 0; i < numCols(); i++) {
				headOfCol_[i] = headOfCol_[i]->left;
			}
		}
	}
	headOfRow_[r] = currHeadR;

}

/**
 * Rotate column c (column 0 is the first) by count positions.
 * If column c is ABCDE (top to bottom) in grid g then column c
 * in grid g should be DEABC after the call g.rotateC(c, 2). 
 * Rotate headOfRow_ if necessary.
 */
void Grid::rotateC(int c, int count) { /* your code here */

	c = c % numCols();
	Node* currHeadC = headOfCol_[c];
	Node* tempC = headOfCol_[c];
	Node* headLeft = headOfCol_[c] -> left;
	Node* currHeadL = headOfCol_[c]->left;
	Node* headRight = headOfCol_[c] -> right;
	Node* currHeadR = headOfCol_[c]->right;


	if (count < 0 || c < 0) return;
	for(int countCol = 0; countCol < count; countCol++){
		for(int countRow = 0; countRow < numRows(); countRow++){
		if(countRow == numRows() - 1){
			currHeadL = currHeadL->down;
			currHeadR = currHeadR->down;
			tempC->left = headLeft;
			tempC->right = headRight;
			currHeadL->right = tempC;
			currHeadR->left = tempC;
		}else{
			currHeadL = currHeadL->down;
			currHeadR = currHeadR->down;
			tempC->left = currHeadL;
			tempC->right = currHeadR;
			currHeadL->right = tempC;
			currHeadR->left = tempC;
			tempC = tempC->down;
		}
		}
	}	
	for (int numberRotate = 0; numberRotate < count; numberRotate++){
		currHeadC = currHeadC-> up;
		if (c == 0) {
			for (int i = 0; i < numRows(); i++) {
				headOfRow_[i] = headOfRow_[i]->up;
			}
		}
	}	
	headOfCol_[c] = currHeadC;
}


/**
 * Destroys all dynamically allocated memory associated with the
 * current Grid class. Clears headOfRow_ and headOfCol_ vectors.
 * Sets bwidth_, bheight_ to zero.
 * After clear() the grid represents an empty grid.
 */
void Grid::clear() { /*your code here*/
	//Node* tempNext;
		Node* temp = headOfRow_[0];
	Node* tempNext = headOfRow_[0];
	
	for(int countRow = 0; countRow < numRows(); countRow++){
	/*	Node* temp = headOfRow_[countRow];
		Node* tempNext = headOfRow_[countRow];*/
		for(int countCol = 0; countCol < numCols(); countCol++){
			if (countCol == numCols() - 1 && countRow == numRows() - 1) {
				tempNext = NULL;
				delete temp;
				temp = NULL;
			} else
			if(countCol == numCols() - 1){
				tempNext = temp -> down -> right;
				delete temp;
				temp = tempNext;
			} else{
				tempNext = temp->right;
				delete temp;
				temp = tempNext;
			} 
		}
	}

	headOfRow_.clear();
	headOfCol_.clear();
	headOfRow_.resize(0);
	headOfCol_.resize(0);
	bwidth_ = 0;
	bheight_ = 0;
}


/**
 * Makes the current Grid a copy of the "other" Grid.
 * The dimensions should be the same.  The Nodes should
 * contain the same blocks, but the Nodes should be newly
 * allocated. This function is used in both the copy
 * constructor and the assignment operator for Grids.
 */
void Grid::copy(Grid const& other) { /*your code here*/

	bwidth_ = other.bwidth_;
	bheight_ = other.bheight_;
	int nRows = other.numRows();
	int nCols = other.numCols();
	Node* currTemp = NULL;
	
	
	vector < vector < Node* > > A;
	for (int j = 0; j < nRows; j++) {
		vector < Node* > temp;
		currTemp = other.headOfRow_[j];
		for (int i = 0; i < nCols; i++) {
			if (i == 0) {
				Node* p = new Node(currTemp->block);
				temp.push_back(p);
			}
			else {
				currTemp = currTemp->right;

				Node* p = new Node(currTemp->block);
				temp.push_back(p);
			}
		}
		A.push_back(temp);
	}

	for (int j = 0; j < nRows; j++) {
		for (int i = 0; i < nCols; i++) {
			Node* p = A[j][i];
			p->up = A[(j == 0) ? nRows - 1 : j - 1][i];
			p->down = A[(j == nRows - 1) ? 0 : j + 1][i];
			p->left = A[j][(i == 0) ? nCols - 1 : i - 1];
			p->right = A[j][(i == nCols - 1) ? 0 : i + 1];
		}
	}

	for (int j = 0; j < nRows; j++) {
		headOfRow_.push_back(A[j][0]);
	}
	for (int i = 0; i < nCols; i++) {
		headOfCol_.push_back(A[0][i]);
	}
}	