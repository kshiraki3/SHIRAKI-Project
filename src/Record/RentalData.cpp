//
//  Record/RentalData.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/21.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Record/RentalData.hpp"
#include "Record/Member.hpp"
#include "Record/DVD.hpp"


RentalData::RentalData() {
	
}
RentalData::RentalData(const std::string& memberID) : mMemberID(memberID) {
	
}

RentalData::RentalData(FileReader* fr) {
	// 会員ID
	mMemberID.resize(Member::mIDLength);
	fr->Read(&mMemberID[0], 1, Member::mIDLength);
	
	// 商品ID
	mGoodsID.resize(DVD::mIDLength);
	fr->Read(&mGoodsID[0], 1, DVD::mIDLength);
	
	// 貸出日
	mDate = Date(fr);
	
	// 返却済みフラグ
	char returned;
	fr->Read(&returned, 1, 1);
	mReturned = returned;
}

void RentalData::WriteToFile(FileWriter* fw) const {
	// 会員ID
	fw->Write(&mMemberID[0], 1, Member::mIDLength);
	
	// 商品ID
	fw->Write(&mGoodsID[0], 1, DVD::mIDLength);
	
	// 貸出日
	mDate.WriteToFile(fw);
	
	// 返却済みフラグ
	auto returned = static_cast<char>(mReturned);
	fw->Write(&returned, 1, 1);
}

bool RentalData::operator ==(const RentalData& rhs) const {
	return mMemberID == rhs.mMemberID;
}
bool RentalData::operator <(const RentalData& rhs) const {
	return mMemberID < rhs.mMemberID;
}

bool RentalData::IsDelayed() const {
	return (Date::Today() - mDate) > 8;
}
