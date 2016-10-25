//
//  Member.hpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/20.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#ifndef Included_Record_Member_hpp
#define Included_Record_Member_hpp

#include "FileIO/FileReader.hpp"
#include "FileIO/FileWriter.hpp"
#include "Record/Date.hpp"
#include "Record/RentalData.hpp"
#include <string>
#include <vector>


// 会員情報
struct Member {
	Member();
	Member(const std::string& id);
	Member(FileReader* fr);
	
	void WriteToFile(FileWriter* fw) const;
	
	// ソート用
	bool operator <(const Member& rhs) const;
	bool operator ==(const Member& rhs) const;
	
	// チェック
	static bool CheckIDSyntax(const std::string& id, std::string* msg = nullptr);
	static bool CheckPhoneNumber(const std::string& num);
	
	// 定数
	static const unsigned mIDLength = 12;	// 会員IDの長さ
	static const unsigned mPhoneNumberLength = 12;	// 電話番号の長さ
	
	// レコード
	std::string mID;	// 会員ID
	std::string mName;	// 氏名
	std::string mRuby;	// フリガナ
	std::string mAddress;	// 住所
	std::string mPhoneNumber;	// 電話番号
	Date mBirthday;	// 生年月日
};

#endif
