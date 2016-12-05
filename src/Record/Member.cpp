//
//  Record/Member.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/20.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Record/Member.hpp"

Member::Member() {
	
}

Member::Member(const std::string& id) : mID(id) {
	
}

Member::Member(FileReader* fr) {
	// 会員ID
	mID.resize(mIDLength);
	fr->Read(&mID[0], 1, mIDLength);
	
	// 氏名
	unsigned char nameSize;
	fr->Read(&nameSize, 1, 1);
	mName.resize(nameSize);
	fr->Read(&mName[0], 1, nameSize);
	
	// フリガナ
	unsigned char rubySize;
	fr->Read(&rubySize, 1, 1);
	mRuby.resize(rubySize);
	fr->Read(&mRuby[0], 1, rubySize);
	
	// 住所
	unsigned char addressSize;
	fr->Read(&addressSize, 1, 1);
	mAddress.resize(addressSize);
	fr->Read(&mAddress[0], 1, addressSize);
	
	// 電話番号
	mPhoneNumber.resize(mPhoneNumberLength);
	fr->Read(&mPhoneNumber[0], 1, mPhoneNumberLength);
	
	// 生年月日
	mBirthday = Date(fr);
}

void Member::WriteToFile(FileWriter* fw) const {
	// 会員ID
	fw->Write(&mID[0], 1, 12);
	
	// 氏名
	auto nameSize = static_cast<unsigned char>(mName.size());
	fw->Write(&nameSize, 1, 1);
	fw->Write(&mName[0], 1, nameSize);
	
	// フリガナ
	auto rubySize = static_cast<unsigned char>(mRuby.size());
	fw->Write(&rubySize, 1, 1);
	fw->Write(&mRuby[0], 1, rubySize);
	
	// 住所
	auto addressSize = static_cast<unsigned char>(mAddress.size());
	fw->Write(&addressSize, 1, 1);
	fw->Write(&mAddress[0], 1, addressSize);
	
	// 電話番号
	fw->Write(&mPhoneNumber[0], 1, mPhoneNumberLength);
	
	// 生年月日
	mBirthday.WriteToFile(fw);
}


bool Member::operator <(const Member& rhs) const {
	return mID < rhs.mID;
}
bool Member::operator ==(const Member& rhs) const {
	return mID == rhs.mID;
}


// チェック
bool Member::CheckIDSyntax(const std::string& id, std::string* msg) {
	if(id.size() != mIDLength) {
		if(msg != nullptr) { *msg = "会員IDは12桁で入力してください"; }
		return false;
	}
	
	for(char c : id) {
		if(c < '0' || '9' < c) {
			if(msg != nullptr) { *msg = "会員IDは数字のみで入力してください"; }
			return false;
		}
	}
	
	return true;
}


bool Member::CheckPhoneNumber(const std::string& num) {
	if(num.size() != mPhoneNumberLength) {
		return false;
	}
	
	for(char c : num) {
		if((c < '0' || '9' < c) && c != '-') {
			return false;
		}
	}
	
	if(num[2] == '-' && num[7] == '-') {
		return true;
	} else if(num[3] == '-' && num[7] == '-') {
		return true;
	} else if(num[4] == '-' && num[7] == '-') {
		return true;
	} else {
		return false;
	}
}
