//
//  FileReader/FileReader.hpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/20.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#ifndef Included_FileIO_FileReader_hpp
#define Included_FileIO_FileReader_hpp

#include "FileIO/RandomGenerator.hpp"
#include <cstdio>
#include <string>


// 復号機能付き読み込みファイルポインタ
class FileReader {
public:
	explicit FileReader(const std::string& fileName);
	~FileReader();
	
	void Read(void* buf, size_t size, size_t n);
	
private:
	unsigned mSeed;	// 暗号化しない場合は0
	RandomGenerator mRandom;
	FILE* mStream;
};

#endif
