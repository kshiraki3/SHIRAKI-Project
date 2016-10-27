//
//  Record/DVD.hpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/21.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#ifndef Included_Record_DVD_hpp
#define Included_Record_DVD_hpp

#include "FileIO/FileReader.hpp"
#include "FileIO/FileWriter.hpp"
#include "Record/Date.hpp"
#include <string>

struct DVD {
	DVD();
	DVD(const std::string& id);
	DVD(FileReader* fr);
	
	void WriteToFile(FileWriter* fw) const;
	
	// ソート用
	bool operator <(const DVD& rhs) const;
	bool operator ==(const DVD& rhs) const;
	
	// 状態
	bool IsNew() const;
	
	// チェック
	static bool CheckIDSyntax(const std::string& id, std::string* msg = nullptr);
	
	// 定数
	static const unsigned mIDLength = 13;
	
	// レコード
	std::string mID;	// 商品ID
	std::string mTitle;	// タイトル
	std::string mGenre;	// ジャンル
	Date mReleaseDate;	// 発売日
	unsigned short mLendTime;	// 貸出回数
	bool mLendableFlag;	// 貸出可能フラグ
	int mPlace;	// 保管場所
};

#endif
