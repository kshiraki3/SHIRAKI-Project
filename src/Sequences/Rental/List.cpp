//
//  Sequences/Rental/List.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/11/24.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Sequences/Rental/List.hpp"
#include "Sequences/Members/Input.hpp"
#include "Record/Database.hpp"
#include <iostream>

using namespace std;


void RentalList(Member* member);


void InputListMemberID() {
	while(true) {
		auto id = InputMemberID("会員ID", nullptr, true);
		Member* member = gDB.FindMember(id);
		
		if(member == nullptr) {
			cout << "会員がみつかりません。\n";
		} else {
			RentalList(member);
			break;
		}
	}
}

void RentalList(Member* member) {
	unsigned rentalFee = 0, delayFee = 0;
	
	for(auto i = gDB.RentalDatas().find(member->mID); i->mMemberID == member->mID; ++i) {
		DVD* dvd = gDB.FindDVD(i->mGoodsID);
		
		cout << dvd->mID << " : ";
		cout << dvd->mTitle << " : ";
		cout << dvd->mGenre << " : ";
		cout << i->mDate << " : ";
		cout << (i->IsDelayed() ? "延滞あり" : "延滞なし") << "\n";
		
		rentalFee += (dvd->IsNew() ? 300 : 100);
		if(i->IsDelayed()) {
			delayFee += (Date::Today() - i->mDate - 8) * 100;
		}
	}
	
	cout << "貸出料金: " << rentalFee << "円\n";
	cout << "延滞料金: " << delayFee << "円\n";
	cout << "計: " << (rentalFee + delayFee) << "円\n";
}
