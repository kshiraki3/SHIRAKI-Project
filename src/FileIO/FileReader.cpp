//
//  FileIO/FileReader.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/20.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "FileIO/FileReader.hpp"
#include "FileIO/Exception.hpp"


FileReader::FileReader(const std::string& fileName) {
	mStream = fopen(fileName.c_str(), "rb");
	if(mStream == nullptr) {
		throw FileOpenException();
	}
	
	// シード値を読み込み
	fread(&mSeed, sizeof(mSeed), 1, mStream);
	mRandom.Reseed(mSeed);
}

FileReader::~FileReader() {
	fclose(mStream);
}

void FileReader::Read(void* _buf, size_t size, size_t n) {
	auto buf = static_cast<unsigned char*>(_buf);
	
	if(mSeed != 0) {
		for(size_t i = 0; i < n; ++i) {
			unsigned char key = mRandom.GetRandom() & 0xff;
			
			fread(buf, size, 1, mStream);
			for(size_t j = 0; j < size; ++j ) {
				buf[j] ^= key;
			}
			
			buf += size;
		}
	} else {
		fread(buf, size, n, mStream);
	}
}
