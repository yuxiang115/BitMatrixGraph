
#pragma once
#ifndef _ARRAYCLASS_H
#define _ARRAYCLASS_H
#include<iostream>
using namespace std;

/**
this is class is array list class
*/
template <class DT>
class ArrayClass {
protected:
	DT* paObject;
	int _size;
	void copy(const ArrayClass<DT>& ac);

public:
	ArrayClass();
	ArrayClass(int n);
	ArrayClass(int n, const DT& ac);
	ArrayClass(const ArrayClass<DT>& ac);
	virtual int size() const;
	virtual DT& operator[] (int k);
	void operator= (const ArrayClass<DT>& ac);	
};
/**
empty constructor
*/
template<class DT>
ArrayClass<DT>::ArrayClass() {
	_size = 0;
	paObject = new DT[1];
	_size = 1;

}
/**
@paramter int initiate the size of list
*/
template<class DT>
ArrayClass<DT>::ArrayClass(int n) {
	_size = 0;
	paObject = new DT[n];
	_size = n;
}
/**
@paramter int initiate the size of list
@paramater DT& ac value of the list
*/
template<class DT>
ArrayClass<DT>::ArrayClass(int n, const DT& ac) {
	_size = 0;
	paObject = new DT[n];
	_size = n;
	for (int i = 0; i < _size; i++) {
		paObject[i] = ac;
	}
}
/**
copy constructor
@paramter Arrayclass<DT>& other object to copy
*/
template<class DT>
ArrayClass<DT>::ArrayClass(const ArrayClass<DT>& ac) {
	if (&ac != this)
		copy(ac);
}

/**copy method
@paramter Arrayclass<DT>& other object to copy
*/

template <class DT>
void ArrayClass<DT>::copy(const ArrayClass<DT>& ac) {
	_size = 0;
	paObject = new DT[ac._size];
	_size = ac._size;
	for (int i = 0; i < _size; i++) {
		paObject[i] = ac.paObject[i];
	}
}
/**
copy operator
@paramter Arrayclass<DT>& other object to copy
@return void
*/
template<class DT>
void ArrayClass<DT>::operator= (const ArrayClass<DT>& ac) {
	if (&ac != this) {
		if (paObject != NULL) delete[] paObject;
		copy(ac);
	}
}
/**
@return size of the list
*/
template<class DT>
int ArrayClass<DT>::size() const {
	return _size;
}
/**opearator overlaod []
@paramater index the user want the object the index indicating
@return return the object that related to the index 
*/
template<class DT>
DT& ArrayClass<DT>::operator[] (int k) {
	return paObject[k];
}

#endif