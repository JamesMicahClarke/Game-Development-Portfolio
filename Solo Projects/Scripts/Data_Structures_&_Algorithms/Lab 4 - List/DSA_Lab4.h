/*
File:			DSA_Lab4.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Created:		12.27.2020
Last Modified:	02.26.2021
Purpose:		Usage of the std::list class
Notes:			Property of Full Sail University
*/

//Header protection
#pragma once

/***********/
/* Defines */
/***********/

/*
How to use:

	When working on a lab, turn that lab's #define from 0 to 1

		Example:	#define LAB_1	1

	When working on an individual unit test, turn that #define from 0 to 1

		Example:	#define DYNARRAY_DEFAULT_CTOR	1

NOTE: If the unit test is not on, that code will not be compiled!
*/


// Master toggle
#define LAB_4	1

// Individual unit test toggles
#define LIST_QUEUE_ADD				1
#define LIST_STACK_ADD				1
#define LIST_QUEUE_REMOVE			1
#define LIST_STACK_REMOVE			1
#define LIST_INSERT_INDEX			1
#define LIST_INSERT_ITER			0
#define LIST_REMOVE_DECIMAL			1

/************/
/* Includes */
/************/
#include <list>

#if LAB_4

class DSA_Lab4 {

	friend class DSA_TestSuite_Lab4;	// Giving access to test code

	// Data members
	std::list<float> mList;				// The list used in all methohods

public:

	// Add all of the values from the array into the list using queue ordering
	//
	// In:	_arr			The array of values
	//		_size			The number of elements in the array
	void QueueOrderingAdd(const float* _arr, size_t _size) {
		// TODO: Implement this method
		for (int i = 0; i < _size; i++)
		{
			mList.push_back(_arr[i]);

		}
	}

	// Add all of the values from the array into the list using queue ordering
	//
	// In:	_arr			The array of values
	//		_size			The number of elements in the array
	void StackOrderingAdd(const float* _arr, size_t _size) {
		// TODO: Implement this method
		for (int i = 0; i < _size; i++)
		{
			mList.push_front(_arr[i]);

		}
	}

	// Remove a single value from the list using queue ordering
	//
	// Return: The value that was removed
	float QueueOrderingRemove() {
		// TODO: Implement this method
		mList.remove(mList.back());
		return mList.front();
	}

	// Remove a single value from the list using stack ordering
	//
	// Return: The value that was removed
	float StackOrderingRemove() {
		// TODO: Implement this method
		mList.remove(mList.back());
		return mList.front();
	}

	// Insert a value _index nodes away from the head node
	//		If _index is 0 - insert in front of the head/front node
	//		If _index is 5 - insert in front of the 5th node in the list
	//
	// Example:	
	//			0<-[5]<->[1]<->[6]<->[4]<->[2]->0
	//	
	// Inserting a 7 at index 2
	//
	//			0<-[5]<->[1]<->[7]<->[6]<->[4]<->[2]->0
	//
	//
	// In:	_index		The "index" to add at
	//		_val		The value to insert
	void Insert(int _index, float _val) {
		// TODO: Implement this method
		std::list<float>::iterator it = mList.begin();
		if (_index >= 0)
		{
			std::advance(it, _index);
			mList.insert(it, _val);

		}
	}

	// Insert a value at the spot specified by the iterator passed in
	// 
	// In:	_iter		The iterator at the place to insert
	//		_val		The value to insert
	void Insert(std::list<float>::iterator _iter, float _val) {
		// TODO: Implement this method

		mList.insert(_iter, _val);


	}

	// Remove all values from mList that have a decimal place > _decimal
	//		Example:   If _decimal is 0.5, then 2.84 would be removed, but 0.5 would not be, and neither would 482.043
	//
	// In:	_decimal		The decimal value to check against
	//
	// Return: The total number of values removed


	int RemoveDecimalGreater(float _decimal) {
		// TODO: Implement this method
		int total = 0;
		bool removed = false;
		float greater = _decimal - (int)_decimal;
		std::round(greater);

		std::list<float>::iterator it;
		for (it = mList.begin(); it != mList.end(); it++)
		{
			if ( greater > _decimal)
			{
				mList.remove(greater);
				removed = true;
				if (removed == true)
				{
					total++;
					it--;
				}
			}
			else if(greater < _decimal)
			{
				it++;
			}
		}

		return total;
	}
};
#endif	// End LAB_4