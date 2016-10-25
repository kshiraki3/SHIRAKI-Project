//
//  FileIO/RandomGenerator.hpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/20.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#ifndef Included_FileIO_RandomGenerator_hpp
#define Included_FileIO_RandomGenerator_hpp

// 乱数生成器
class RandomGenerator {
public:
	RandomGenerator();
	explicit RandomGenerator(unsigned seed);
	~RandomGenerator();
	
	void Reseed(unsigned seed);
	unsigned GetRandom();
	
private:
	unsigned mX;
};

#endif
