//
//  Record/Store.hpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/21.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#ifndef Included_Record_Store_hpp
#define Included_Record_Store_hpp

#include "FileIO/FileReader.hpp"
#include "FileIO/FileWriter.hpp"
#include <string>


struct Store {
	static const int mNull = 255;
	
	Store();
	Store(int id);
	Store(FileReader* fr);
	
	void WriteToFile(FileWriter* fw) const;
	
	bool operator ==(const Store& rhs) const;
	bool operator <(const Store& rhs) const;
	
	int mID;	// 店舗ID
	std::string mName;	// 店舗名
};

#endif
