/////////////////////////////////////////////////
//
//	File: 537malloc.h
//
//	CS537 Project 4
//	Author: Mike Tuchler
//		Drew Kyser
//
/////////////////////////////////////////////////

#ifndef MALLOC537_H
#define MALLOC537_H

#include "RBtree.h"

void* malloc537(size_t size);
void free537(void* ptr);
void* realloc537(void* ptr, size_t size);
void memcheck537(void* ptr, size_t size);

#endif
