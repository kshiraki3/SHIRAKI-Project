//
//  RentalData.hpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/21.
//  Copyright © 2016年 SHIRAKI System. All rights reserved.
//

#ifndef Included_Record_RentalData_hpp
#define Included_Record_RentalData_hpp

#include "FileIO/FileReader.hpp"
#include "FileIO/FileWriter.hpp"
#include "Record/Date.hpp"
#include <string>

struct RentalData {
	RentalData();
	RentalData(const std::string& memberID);
	RentalData(FileReader* fr);
	
	void WriteToFile(FileWriter* fw) const;
	
	bool operator ==(const RentalData& rhs) const;
	bool operator <(const RentalData& rhs) const;
	
	std::string mMemberID;	// 会員ID
	std::string mGoodsID;	// 商品ID
	Date mDate;	// 貸出日
	bool mReturned;	// 返却済みフラグ
};

#endif
