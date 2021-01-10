/**
 * @file deque.cpp
 * Implementation of the Deque class.
 *
 */

/* No argument constructor */
template <class T>
Deque<T>::Deque():n1(/* your code here*/0),n2(/* your code here*/0){}



/**
 * Adds the parameter object to the right of the Deque.
 *
 * @param newItem object to be added to the Deque.
 */
template <class T>
void Deque<T>::pushR(T newItem)
{
    /**
     * @todo Your code here!
     */
	 data.push_back(newItem);
	 n1++;
}

/**
 * Removes the object at the left of the Deque, and returns it to the
 * caller.
 *
 * See .h file for implementation notes. 
 *
 * @return The item that used to be at the left of the Deque.
 */
template <class T>
T Deque<T>::popL()
{
    /**
     * @todo Your code here! 
     */
    T t = data[n2];
	n2++;
	if(n2 >= n1 - n2){
		vector<T> dataNew;
		for(int i = n2; i < n1; i++){
			dataNew.push_back(data[i]);
		}
		data = dataNew;
		n1 = n1 - n2;
		n2 = 0;
	}
	return t;
}



/**
 * Removes the object at the right of the Deque, and returns it to the
 * caller.
 *
 * @return The item that used to be at the right of the Deque.
 */
template <class T>
T Deque<T>::popR()
{
    /**
     * @todo Your code here! 
     */
	 T t = data[n1-1];
	 n1--;
	 data.pop_back();
	 if (n2 >= n1 - n2) {
		 vector<T> dataNew;
		 for (int i = n2; i < n1; i++) {
			 dataNew.push_back(data[i]);
		 }
		 data = dataNew;
		 n1 = n1 - n2;
		 n2 = 0;
	 }
	 return t;
}

/**
 * Finds the object at the left of the Deque, and returns it to the
 * caller. Unlike popL(), this operation does not alter the deque.
 *
 * @return The item at the front of the deque.
 */
template <class T>
T Deque<T>::peekL()
{
    /**
     * @todo Your code here! 
     */
	 return data[n2];
}



/**
 * Finds the object at the right of the Deque, and returns it to the
 * caller. Unlike popR(), this operation does not alter the deque.
 *
 * @return the value of The item at the right of the deque.
 */
template <class T>
T Deque<T>::peekR()
{
    /**
     * @todo Your code here! 
     */
	 return data[n1-1];
}



/**
 * Determines if the Deque is empty.
 *
 * @return bool which is true if the Deque is empty, false otherwise.
 */
template <class T>
bool Deque<T>::isEmpty() const
{
    /**
     * @todo Your code here! 
     */
	 if (n2 == n1) return true;
	 return false;
}

