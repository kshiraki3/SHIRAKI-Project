//
//  Sequences/Recommend/RecommendationSearch.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/11/22.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Sequences/Recommend/RecommendationSearch.hpp"
#include "Record/Database.hpp"
#include "Interface/Paginator.hpp"
#include "Sequences/Members/Input.hpp"
#include <cmath>
#include <iostream>
#include <map>

using namespace std;


void RecommendationList(Member* member);

void RecommendationSearch() {
	cout << "***** おすすめ検索 *****\n";
	
	string id;
	while(true) {
		id = InputMemberID("会員ID", nullptr, true);
		if(gDB.FindMember(id) == nullptr) {
			cout << "会員が見つかりません。\n";
		} else {
			break;
		}
	}
	
	if(!id.empty()) {
		RecommendationList(gDB.FindMember(id));
	}
}

// 正規分布
double NormalDistribution(double x, double avg, double sd) {
	return (1.0 / sqrt(2 * 3.141592 * sd * sd)) * exp(-((x - avg) * (x - avg)) / (2.0 * sd * sd));
}

// おすすめリストの表示
void RecommendationList(Member* member) {
	const set<DVD>& dvds = gDB.DVDs();
	auto it = gDB.RentalDatas().find(member->mID);
	
	if(it == gDB.RentalDatas().end()) {
		// memberは一回も商品を借りていない
	} else {
		int totalLend = 0;	// 総貸出回数
		map<string, double> genreRate;	// memberが借りたジャンルの回数
		multimap<double, const DVD*> recList;	// おすすめリスト
		
		// ジャンル別借りた回数を計算//0.00045 1e-8
		for(; it->mMemberID == member->mID; ++it) {
			++totalLend;
			DVD* goods = gDB.FindDVD(it->mGoodsID);	// 借りた商品の情報
			
			if(genreRate.find(goods->mGenre) == genreRate.end()) {
				genreRate.insert({ goods->mGenre, 1.0 });
			} else {
				++genreRate[goods->mGenre];
			}
		}
		
		for(auto& rate : genreRate) {
			rate.second /= totalLend;
		}
		
		// 商品ごとに点数計算
		for(const auto& dvd : dvds) {
			double score = genreRate[dvd.mGenre] * dvd.mLendTime;
			recList.insert({ score, &dvd });
		}
		
		// おすすめリストを表示
		Paginator p;
		
		p.SetItemsPerPage(9);
		p.SetReturnMessage("戻る");
		
		for(auto& d : recList) {
			if(!d.second->mLendableFlag) {
				continue;
			}
			
			bool hasRented = false;
			for(auto it = gDB.RentalDatas().find(member->mID); it->mMemberID != member->mID; ++it) {
				if(it->mGoodsID == d.second->mID) {
					hasRented = true;
					break;
				}
			}
			
			if(hasRented) {
				continue;
			}
			
			p.AddItem(d.second->mTitle);
			if(p.ItemCount() == 9) {
				break;
			}
		}
		
		p.Run();
	}
}
