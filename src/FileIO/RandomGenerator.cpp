//
//  FileIO/RandomGenerator.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/20.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "FileIO/RandomGenerator.hpp"
#include <cstdlib>


RandomGenerator::RandomGenerator() : mX(0) {
	
}

RandomGenerator::RandomGenerator(unsigned seed) {
	srand(seed);
	mX = rand();
}
RandomGenerator::~RandomGenerator() {
	
}

void RandomGenerator::Reseed(unsigned seed) {
	srand(seed);
	mX = rand();
}

// XorShift法
unsigned RandomGenerator::GetRandom() {
	mX = mX ^ (mX << 13);
	mX = mX ^ (mX >> 17);
	mX = mX ^ (mX << 5);
	return mX;
}
