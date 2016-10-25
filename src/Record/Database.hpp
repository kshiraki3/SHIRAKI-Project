//
//  Record/Database.hpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/20.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#ifndef Included_Record_Database_hpp
#define Included_Record_Database_hpp

#include "Record/Member.hpp"
#include "Record/DVD.hpp"
#include "Record/Store.hpp"
#include "Record/RentalData.hpp"
#include <functional>
#include <set>


class Database {
public:
	Database();
	~Database();
	
	// ファイル処理
	void Save();
	void Load();
	
	// 会員情報
	const std::set<Member>& Members() const;
	unsigned MemberCount();
	void ForeachMembers(const std::function<void(Member*)>& func);
	void AddMember(const Member& member);
	void RemoveMember(const std::string& id);
	Member* FindMember(const std::string& id);
	
	// 商品情報
	const std::set<DVD>& DVDs() const;
	unsigned DVDCount();
	void ForeachDVDs(const std::function<void(DVD*)>& func);
	void AddDVD(const DVD& dvd);
	void RemoveDVD(const std::string& id);
	DVD* FindDVD(const std::string& id);
	
	// 店舗情報
	const std::set<Store>& Stores() const;
	unsigned StoreCount();
	void ForeachStores(const std::function<void(Store*)>& func);
	void AddStore(const Store& store);
	void RemoveStore(int id);
	Store* FindStore(int id);
	
	// 貸出情報
	const std::multiset<RentalData>& RentalDatas() const;
	
	// ID自動生成
	std::string GenerateMemberID();
	std::string GenerateGoodsID();
	
private:
	std::set<Member> mMembers;	// 会員情報
	std::set<DVD> mDVDs;	// 商品情報
	std::set<Store> mStores;	// 店舗情報
	std::multiset<RentalData> mRentalData;	// 貸出情報
};

extern Database gDB;

#endif /* Database_hpp */
