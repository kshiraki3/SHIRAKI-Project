//
//  FileIO/FileWriter.hpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/20.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#ifndef Included_FileIO_FileWriter_hpp
#define Included_FileIO_FileWriter_hpp

#include "FileIO/RandomGenerator.hpp"
#include <cstdio>
#include <string>


// 暗号化機能付き書き込みファイルポインタ
class FileWriter {
public:
	FileWriter(const std::string& fileName, bool crypt);
	~FileWriter();
	
	void Write(const void* buf, size_t size, size_t n);
	
private:
	unsigned mSeed;	// 暗号化しない場合は0
	RandomGenerator mRandom;
	FILE* mStream;
};

#endif
