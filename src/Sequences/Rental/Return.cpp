//
//  Sequences/Rental/Return.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/27.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Sequences/Rental/Return.hpp"
#include "Sequences/Goods/Input.hpp"
#include "Record/Database.hpp"
#include "Interface/YesNo.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;


void ReturnGoodsInfo(RentalData* rd);
void ReturnNotify(RentalData* rd);

// 商品ID入力画面 (返却)
void InputReturnGoodsID() {
	DVD* dvd;
	
	while(true) {
		string input = InputGoodsID("商品IDを入力 (0: キャンセル)", nullptr, true);
		dvd = gDB.FindDVD(input);
		
		if(input.empty()) {
			return;
		} else if(dvd == nullptr) {
			cout << "商品が見つかりません。\n\n";
		} else if(dvd->mLendableFlag) {
			cout << "この商品は貸し出されていません。\n\n";
		} else {
			break;
		}
	}
	
	// 貸出データを検索
	auto i = find_if(begin(gDB.RentalDatas()), end(gDB.RentalDatas()), [&](const RentalData& rd){
		return rd.mGoodsID == dvd->mID && rd.mReturned == false;
	});
	assert(i != end(gDB.RentalDatas()));
	
	ReturnGoodsInfo(const_cast<RentalData*>(&(*i)));
}


// 返却商品情報確認画面
void ReturnGoodsInfo(RentalData* rd) {
	DVD* dvd = gDB.FindDVD(rd->mGoodsID);
	assert(dvd != nullptr);
	
	cout << "***** 返却商品情報確認 *****\n";
	cout << dvd->mID << ": ";
	cout << dvd->mTitle << " : ";
	cout << (rd->IsDelayed() ? "延滞あり" : "延滞なし") << "\n";
	
	YesNo question("この商品を返却しますか?");
	
	if(question.Run()) {
		ReturnNotify(rd);
	}
}


// 返却通知画面
void ReturnNotify(RentalData* rd) {
	// 返却処理
	gDB.Return(rd);
	
	// 通知
	cout << "商品が返却されました。";
}
