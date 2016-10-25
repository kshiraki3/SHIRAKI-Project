//
//  Record/Store.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/21.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Record/Store.hpp"


Store::Store() {
	
}

Store::Store(int id) : mID(id) {
	
}

Store::Store(FileReader* fr) {
	// ID
	unsigned char id;
	fr->Read(&id, 1, 1);
	mID = id;
	
	// 店舗名
	unsigned char nameSize;
	fr->Read(&nameSize, 1, 1);
	mName.resize(nameSize);
	fr->Read(&mName[0], 1, nameSize);
}

void Store::WriteToFile(FileWriter* fw) const {
	// ID
	auto id = static_cast<unsigned char>(mID);
	fw->Write(&id, 1, 1);
	
	// 店舗名
	auto nameSize = static_cast<unsigned char>(mName.size());
	fw->Write(&nameSize, 1, 1);
	fw->Write(&mName[0], 1, nameSize);
}

bool Store::operator ==(const Store& rhs) const {
	return mID == rhs.mID;
}
bool Store::operator <(const Store& rhs) const {
	return mID < rhs.mID;
}
