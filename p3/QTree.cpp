/**
 *
 * Balanced Quad Tree (pa3)
 *
 * This file will be used for grading.
 *
 */

#include "QTree.h"

// Return the biggest power of 2 less than or equal to n
int biggestPow2(int n) {
  if( n < 1 ) return 0;
  int v = 1;
  while( v <= n ) v <<= 1;
  return v >> 1;
}

QTree::Node::Node(PNG & im, pair<int,int> ul, int sz, Node *par)
  :upLeft(ul),size(sz),parent(par),nw(NULL),ne(NULL),sw(NULL),se(NULL)
{
  var = varAndAvg(im,ul,size,avg);
}

QTree::~QTree(){
  clear();
}

QTree::QTree(const QTree & other) {
  copy(other);
}


QTree & QTree::operator=(const QTree & rhs){
  if (this != &rhs) {
    clear();
    copy(rhs);
  }
  return *this;
}


QTree::QTree(PNG & imIn, int leafB, RGBAPixel frameC, bool bal)
  : leafBound(leafB), balanced(bal), drawFrame(true), frameColor(frameC)
{

  /* YOUR CODE HERE */
	im = imIn;
	size = biggestPow2(min((int)imIn.height(), (int)imIn.width()));
	root = new Node(im, pair<int, int>(0, 0), size, NULL);
	numLeaf = 1;
	Q.push(root);
	while (numLeaf < leafBound) {
		Node* temp = Q.top();
		Q.pop();
		split(temp);
	}
}


QTree::QTree(PNG & imIn, int leafB, bool bal)
  : leafBound(leafB), balanced(bal), drawFrame(false)
{
  
  /* YOUR CODE HERE */
	frameColor = NULL;
	im = imIn;
	size = biggestPow2(min((int)imIn.height(), (int)imIn.width()));
	root = new Node(im, pair<int, int>(0, 0), size, NULL);
	numLeaf = 1;
	Q.push(root);
	while (numLeaf < leafBound) {
		Node* temp = Q.top();
		Q.pop();
		split(temp);
	}
}



bool QTree::isLeaf( Node *t ) {
  
  /* YOUR CODE HERE */
	if (t == NULL) return false;
	return t->ne == NULL && t->nw == NULL && t->se == NULL && t->sw == NULL;
}
  
void QTree::split( Node *t ) {
  
  /* YOUR CODE HERE */

  // FOR BALANCED QTREES-------------------------------------------------
  // A split might cause one or two nbrs of the parent of t to split
  // to maintain balance.  Note that these two nbrs exist (unless they're
  // not in the image region) because the current set of leaves are
  // balanced.
  // if( t is a NW (or NE or SW or SE) child ) then we need to check that
  // the North and West (or North and East or South and West or
  // South and East) nbrs of t->parent have children. If they don't
  // we need to split them.
	if (!isLeaf(t)) return;
	if (t == NULL) return;

	if (balanced == true && t->parent != NULL) {
		if (t == t->parent->nw) {
			if (isLeaf(NNbr(t->parent))) split(NNbr(t->parent));
			if (isLeaf(WNbr(t->parent))) split(WNbr(t->parent));
		} else if (t == t->parent->ne) {
			if (isLeaf(NNbr(t->parent))) split(NNbr(t->parent));
			if (isLeaf(ENbr(t->parent))) split(ENbr(t->parent));
		} else if (t == t->parent->sw) {
			if (isLeaf(SNbr(t->parent))) split(SNbr(t->parent));
			if (isLeaf(WNbr(t->parent))) split(WNbr(t->parent));
		} else if (t == t->parent->se) {
			if (isLeaf(SNbr(t->parent))) split(SNbr(t->parent));
			if (isLeaf(ENbr(t->parent))) split(ENbr(t->parent));
		}
	}

	int splitSize = t->size / 2;

	t->nw = new Node(im, t->upLeft, splitSize, t);
	t->ne = new Node(im, pair<int, int> ((t->upLeft).first + splitSize, (t->upLeft).second),splitSize, t);
	t->sw = new Node(im, pair<int, int>((t->upLeft).first, (t->upLeft.second) + splitSize), splitSize, t);
	t->se = new Node(im, pair<int, int>((t->upLeft).first + splitSize, (t->upLeft).second + splitSize), splitSize, t);

	if (t->nw->size > 0) { Q.push(t->nw); }
	if (t->ne->size > 0) { Q.push(t->ne); numLeaf++; }
	if (t->sw->size > 0) { Q.push(t->sw); numLeaf++; }
	if (t->se->size > 0) { Q.push(t->se); numLeaf++; }
  
}


/* NNbr(t)
 * return the same-sized quad tree node that is north of Node t.
 * return NULL if this node is not in the QTree.
 */
QTree::Node * QTree::NNbr(Node *t) {

  /* YOUR CODE HERE */
	if (t == NULL) return NULL;
	if (t->parent == NULL) return NULL;

	if (t == t->parent->sw) return t->parent->nw;
	if (t == t->parent->se) return t->parent->ne;

	Node* parentN = NNbr(t->parent);
	if (parentN == NULL) return NULL;
	if (isLeaf(parentN) && (parentN->size = 2 * t->size)) return parentN; 

	if (t == t->parent->nw) return parentN->sw;
	if (t == t->parent->ne) return parentN->se;

	return NULL; 
  
}

/* SNbr(t)
 * return the same-sized quad tree node that is south of Node t.
 * return NULL if this node is not in the QTree.
 */
QTree::Node * QTree::SNbr(Node *t) {

  /* YOUR CODE HERE */
	if (t == NULL) return NULL;
	if (t->parent == NULL) return NULL;

	if (t == t->parent->nw) return t->parent->sw;
	if (t == t->parent->ne) return t->parent->se;

	Node* parentN = SNbr(t->parent);
	if (parentN == NULL) return NULL;
	if (isLeaf(parentN) && (parentN->size = 2 * t->size)) return parentN;

	if (t == t->parent->sw) return parentN->nw;
	if (t == t->parent->se) return parentN->ne;

	return NULL;

  
}

/* ENbr(t)
 * return the same-sized quad tree node that is east of Node t.
 * return NULL if this node is not in the QTree.
 */
QTree::Node * QTree::ENbr(Node *t) {

  /* YOUR CODE HERE */
	if (t == NULL) return NULL;
	if (t->parent == NULL) return NULL;

	if (t == t->parent->nw) return t->parent->ne;
	if (t == t->parent->sw) return t->parent->se;

	Node* parentN = ENbr(t->parent);
	if (parentN == NULL) return NULL;
	if (isLeaf(parentN) && (parentN->size = 2 * t->size)) return parentN;

	if (t == t->parent->ne) return parentN->nw;
	if (t == t->parent->se) return parentN->sw;

	return NULL;
  
}

/* WNbr(t)
 * return the same-sized quad tree node that is west of Node t.
 * return NULL if this node is not in the QTree.
 */
QTree::Node * QTree::WNbr(Node *t) {

  /* YOUR CODE HERE */
	if (t == NULL) return NULL;
	if (t->parent == NULL) return NULL;

	if (t == t->parent->ne) return t->parent->nw;
	if (t == t->parent->se) return t->parent->sw;

	Node* parentN = WNbr(t->parent);
	if (parentN == NULL) return NULL;
	if (isLeaf(parentN) && (parentN->size = 2 * t->size)) return parentN;

	if (t == t->parent->nw) return parentN->ne;
	if (t == t->parent->sw) return parentN->se;

	return NULL;


  
}

bool QTree::write(string const & fileName){

  /* YOUR CODE HERE */
	PNG img(size, size);
	writeHelper(root, img);

  // include the following line to write the image to file.
	return(img.writeToFile(fileName));
}

void QTree::writeHelper(Node * n, PNG & img) {
	if (isLeaf(n)) {
		int x = (n->upLeft).first;
		int y = (n->upLeft).second;
		for (int i = 0; i < n->size; i++) {
			for (int j = 0; j < n->size; j++) {
				RGBAPixel* p = img.getPixel(x + i, y + j);
				if ((drawFrame == true) &&
					((i == 0) || (i + 1 == n->size) || (j == 0) || (j + 1 == n->size))) {
					*p = frameColor;
				}
				else {
					*p = n->avg;
				}
			}
		}
	}
	else {
		writeHelper(n->nw, img);
		writeHelper(n->ne, img);
		writeHelper(n->sw, img);
		writeHelper(n->se, img);
	}
}

void QTree::clear() {

  /* YOUR CODE HERE */
	clearHelper(root);
}

void QTree::clearHelper(Node* n) {
	if (n == NULL) return;
	clearHelper(n->nw);
	clearHelper(n->ne);
	clearHelper(n->sw);
	clearHelper(n->se);
	delete n;
}


void QTree::copy(const QTree & orig) {
  /* YOUR CODE HERE */
	leafBound = orig.leafBound;
	im = orig.im;
	balanced = orig.balanced;
	drawFrame = orig.drawFrame;
	frameColor = orig.frameColor;
	Q = priority_queue < Node*, vector<Node*>, compare>();
	size = biggestPow2(min((int)orig.im.height(), (int)orig.im.width()));
	root = new Node(im, pair<int, int>(0, 0), size, NULL);
	numLeaf = 1;
	Q.push(root);
	while (numLeaf < leafBound) {
		Node* temp = Q.top();
		Q.pop();
		split(temp);
	}

}
