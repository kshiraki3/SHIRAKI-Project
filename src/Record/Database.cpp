//
//  Record/Database.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/20.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Record/Database.hpp"
#include "FileIO/Exception.hpp"
#include "FileIO/FileReader.hpp"
#include "FileIO/FileWriter.hpp"
#include <cstdio>

using namespace std;



namespace {
	const string kDatabaseFileName = "Database.dat";
}

Database gDB;


Database::Database() {
	this->Load();
}

Database::~Database() {
	this->Save();
}


/* ********************************************************************************************************* */
// ファイル処理

void Database::Save() {
	FileWriter fw(kDatabaseFileName, true);
	
	// 会員情報
	auto memberNum = static_cast<unsigned>(mMembers.size());
	fw.Write(&memberNum, 4, 1);
	
	for(const auto& member : mMembers) {
		member.WriteToFile(&fw);
	}
	
	// 商品情報
	auto dvdNum = static_cast<unsigned>(mDVDs.size());
	fw.Write(&dvdNum, 4, 1);
	
	for(const auto& dvd : mDVDs) {
		dvd.WriteToFile(&fw);
	}
	
	// 店舗情報
	auto storeNum = static_cast<unsigned>(mStores.size());
	fw.Write(&storeNum, 4, 1);
	
	for(const auto& store : mStores) {
		store.WriteToFile(&fw);
	}
	
	// 貸出情報
	auto rentalDataNum = static_cast<unsigned>(mRentalData.size());
	fw.Write(&rentalDataNum, 4, 1);
	
	for(const auto& rentalData : mRentalData) {
		rentalData.WriteToFile(&fw);
	}
}

void Database::Load() {
	try {
		FileReader fr(kDatabaseFileName);
		
		// 会員情報
		unsigned memberNum;
		fr.Read(&memberNum, 4, 1);
		
		for(int i = 0; i < memberNum; ++i) {
			mMembers.insert(Member(&fr));
		}
		
		// 商品情報
		unsigned dvdNum;
		fr.Read(&dvdNum, 4, 1);
		
		for(int i = 0; i < dvdNum; ++i) {
			mDVDs.insert(DVD(&fr));
		}
		
		// 店舗情報
		unsigned storeNum;
		fr.Read(&storeNum, 4, 1);
		
		for(int i = 0; i < storeNum; ++i) {
			mStores.insert(Store(&fr));
		}
		
		// 貸出情報
		unsigned rentalDataNum;
		fr.Read(&rentalDataNum, 4, 1);
		
		for(int i = 0; i < rentalDataNum; ++i) {
			mRentalData.insert(RentalData(&fr));
		}
	} catch(FileOpenException) {
		
	}
}


/* ********************************************************************************************************* */
// 会員情報

const set<Member>& Database::Members() const {
	return mMembers;
}

unsigned Database::MemberCount() {
	return static_cast<unsigned>(mMembers.size());
}

void Database::ForeachMembers(const std::function<void(Member*)>& func) {
	for(const Member& member : mMembers) {
		func(const_cast<Member*>(&member));
	}
}

void Database::AddMember(const Member& member) {
	mMembers.insert(member);
}

void Database::RemoveMember(const std::string& id) {
	mMembers.erase(id);
}

Member* Database::FindMember(const std::string& id) {
	auto i = mMembers.find(id);
	return (i == mMembers.end()) ? nullptr : const_cast<Member*>(&(*i));
}


/* ********************************************************************************************************* */
// 商品情報

const set<DVD>& Database::DVDs() const {
	return mDVDs;
}

unsigned Database::DVDCount() {
	return static_cast<unsigned>(mDVDs.size());
}

void Database::ForeachDVDs(const std::function<void(DVD*)>& func) {
	for(const DVD& dvd : mDVDs) {
		func(const_cast<DVD*>(&dvd));
	}
}

void Database::AddDVD(const DVD& dvd) {
	mDVDs.insert(dvd);
}

void Database::RemoveDVD(const std::string& id) {
	mDVDs.erase(id);
}

DVD* Database::FindDVD(const std::string& id) {
	auto i = mDVDs.find(id);
	return (i == mDVDs.end()) ? nullptr : const_cast<DVD*>(&(*i));
}


/* ********************************************************************************************************* */
// 店舗情報

const set<Store>& Database::Stores() const {
	return mStores;
}

unsigned Database::StoreCount() {
	return static_cast<unsigned>(mStores.size());
}

void Database::ForeachStores(const std::function<void(Store*)>& func) {
	for(const Store& store : mStores) {
		func(const_cast<Store*>(&store));
	}
}

void Database::AddStore(const Store& store) {
	mStores.insert(store);
}

void Database::RemoveStore(int id) {
	mStores.erase(id);
}
Store* Database::FindStore(int id) {
	auto i = mStores.find(id);
	return (i == mStores.end()) ? nullptr : const_cast<Store*>(&(*i));
}


/* ********************************************************************************************************* */
// 貸出情報

const std::multiset<RentalData>& Database::RentalDatas() const {
	return mRentalData;
}


/* ********************************************************************************************************* */
// ID自動生成

std::string Database::GenerateMemberID() {
	string result;
	result.resize(Member::mIDLength);
	
	Date today = Date::Today();
	
	sprintf(&result[0], "%02d%04d%02d%02d%02d", 99, today.mYear, today.mMonth, today.mDay, 1);
	
	return result;
}

std::string Database::GenerateGoodsID() {
	string result;
	result.resize(Member::mIDLength);
	
	Date today = Date::Today();
	
	sprintf(&result[0], "%02d%04d%02d%02d%03d", 99, today.mYear, today.mMonth, today.mDay, 1);
	
	return result;
}
