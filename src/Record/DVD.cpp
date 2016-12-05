//
//  Record/DVD.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/21.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Record/DVD.hpp"


DVD::DVD() : mLendableFlag(true) {
	
}

DVD::DVD(const std::string& id) : mID(id) {
	
}

DVD::DVD(FileReader* fr) {
	// 商品ID
	mID.resize(mIDLength);
	fr->Read(&mID[0], 1, mIDLength);
	
	// タイトル
	unsigned char titleSize;
	fr->Read(&titleSize, 1, 1);
	mTitle.resize(titleSize);
	fr->Read(&mTitle[0], 1, titleSize);
	
	// ジャンル
	unsigned char genreSize;
	fr->Read(&genreSize, 1, 1);
	mGenre.resize(genreSize);
	fr->Read(&mGenre, 1, genreSize);
	
	// 発売日
	mReleaseDate = Date(fr);
	
	// 貸出回数
	fr->Read(&mLendTime, 2, 1);
	
	// 貸出可能フラグ
	unsigned char lendableFlag;
	fr->Read(&lendableFlag, 1, 1);
	mLendableFlag = lendableFlag;
	
	// 保管場所
	unsigned char place;
	fr->Read(&place, 1, 1);
	mPlace = place;
}

void DVD::WriteToFile(FileWriter* fw) const {
	// 商品ID
	fw->Write(&mID[0], 1, mIDLength);
	
	// タイトル
	auto titleSize = static_cast<unsigned char>(mTitle.size());
	fw->Write(&titleSize, 1, 1);
	fw->Write(&mTitle[0], 1, titleSize);
	
	// ジャンル
	auto genreSize = static_cast<unsigned char>(mGenre.size());
	fw->Write(&genreSize, 1, 1);
	fw->Write(&mGenre[0], 1, genreSize);
	
	// 発売日
	mReleaseDate.WriteToFile(fw);
	
	// 貸出回数
	fw->Write(&mLendTime, 2, 1);
	
	// 貸出可能フラグ
	auto lendableFlag = static_cast<unsigned char>(mLendableFlag);
	fw->Write(&lendableFlag, 1, 1);
	
	// 保管場所
	auto place = static_cast<char>(mPlace);
	fw->Write(&place, 1, 1);
}

bool DVD::IsNew() const {
	return (Date::Today() - mReleaseDate) < 180;
}

bool DVD::CheckIDSyntax(const std::string& id, std::string* msg) {
	// チェック
	if(id.size() != mIDLength) {
		if(msg != nullptr) { *msg = "商品IDは13桁で入力してください"; }
		return false;
	}
	
	for(char c : id) {
		if(c < '0' || '9' < c) {
			if(msg != nullptr) { *msg = "商品IDは数字のみで入力してください"; }
			return false;
		}
	}
	
	return true;
}

bool DVD::operator <(const DVD& rhs) const {
	return mID < rhs.mID;
}

bool DVD::operator ==(const DVD& rhs) const {
	return mID == rhs.mID;
}
