//
//  FileIO/FileWriter.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/20.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "FileIO/FileWriter.hpp"
#include "FileIO/Exception.hpp"
#include <ctime>
#include <stdexcept>


FileWriter::FileWriter(const std::string& fileName, bool crypt) : mSeed(crypt ? (unsigned)time(nullptr) : 0), mRandom(mSeed) {
	mStream = fopen(fileName.c_str(), "wb");
	if(mStream == nullptr) {
		throw FileOpenException();
	}
	
	// シード値を書き込み
	fwrite(&mSeed, sizeof(mSeed), 1, mStream);
}

FileWriter::~FileWriter() {
	fclose(mStream);
}

void FileWriter::Write(const void* _buf, size_t size, size_t n) {
	auto buf = static_cast<const unsigned char*>(_buf);
	
	if(mSeed != 0) {
		for(size_t i = 0; i < n; ++i) {
			unsigned char key = mRandom.GetRandom() & 0xff;
			char tmp[size];
			
			for(size_t j = 0; j < size; ++j) {
				tmp[j] = *buf ^ key;
				++buf;
			}
			
			fwrite(tmp, size, 1, mStream);
		}
	} else {
		fwrite(buf, size, n, mStream);
	}
}
