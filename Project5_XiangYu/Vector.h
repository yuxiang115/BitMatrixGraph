#pragma once
#ifndef _VECTOR_H
#define _VECTOR_H
#include"ArrayClass.h"
template<class DT>
class Vector : public ArrayClass<DT> {
protected:
	int _currSize;
	int _incFactor;
public:
	Vector();
	Vector(int n);
	Vector(int n, DT& ac);
	Vector(const Vector<DT>& ac);
	Vector(const ArrayClass<DT>& ac);
	void operator= (const Vector<DT>& ac);
	void operator= (const ArrayClass<DT>& ac);
	void insert(const DT& data, int index);
	void setCapacity(int c);
	void remove(int index);
	void add(const DT& data);
	int size() const;
};

template<class DT>
Vector<DT>::Vector() : ArrayClass<DT>() {
	_currSize = 0;
	_incFactor = 5;
}

template<class DT>
Vector<DT>::Vector(int n) : ArrayClass<DT>(n) {
	_currSize = 0;
	_incFactor = (n + 1)/2;
}

template<class DT>
Vector<DT>::Vector(int n, DT& ac) : ArrayClass<DT>(n, ac) {
	_currSize = 0;
	_incFactor = n/2;
}

template<class DT>
Vector<DT>::Vector(const Vector<DT>& ac) : ArrayClass<DT>(ac) {
	_currSize = ac._currSize;
	_incFactor = ac._incFactor;
}

template<class DT>
Vector<DT>::Vector(const ArrayClass<DT>& ac) : ArrayClass<DT>(ac) {
	_currSize = ac.size();
	_incFactor = (_currSize + 1)/2;
}

template<class DT>
void Vector<DT>::operator=(const Vector<DT>& ac) {
	ArrayClass<DT>::copy(ac);
	_currSize = ac._currSize;
	_incFactor = ac._incFactor;
}

template<class DT>
void Vector<DT>::operator=(const ArrayClass<DT>& ac) {
	ArrayClass<DT>::copy(ac);
	_currSize = ac.size();
	_incFactor = (_currSize + 1) / 2;
}

template<class DT>
int Vector<DT>::size() const {
	return _currSize;
}

template<class DT>
void Vector<DT>::setCapacity(int c) {
	int len = _currSize;
	
	DT* paNew = new DT[c];

	for (int i = 0; i < len; i++) {
		paNew[i] = paObject[i];
	}
	
	_size = c;
	
}

template<class DT>
void Vector<DT>::insert(const DT& data, int index) {
	if (_currSize + 1 == _size) {
		setCapacity(_size + _incFactor);
	}
	_currSize++;

	for (int i = _currSize - 1; i > index; i--) {
		(*this)[i] = (*this)[i - 1];
	}
	(*this)[index] = data;
}

template<class DT>
void Vector<DT>::add(const DT& data) {
	insert(data, _currSize);
}

template<class DT>
void Vector<DT>::remove(int index) {
	if (_currSize <= _size - _inFactor) {
		setCapacity(_size - _incFactor);
	}

	for (int i = index; i < _currSize - 1; i++) {
		(*this)[i] = (*this)[i + 1];
	}
	_currSize--;
}

#endif // !_VECTOR_H
