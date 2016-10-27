//
//  Sequences/Rental/Lend.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/27.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Sequences/Rental/Lend.hpp"
#include "Record/Database.hpp"
#include "Sequences/Members/Input.hpp"
#include "Sequences/Goods/Input.hpp"
#include "YesNo.hpp"
#include <iostream>

using namespace std;


void LendGoodsInfo(DVD* dvd);
void InputLendMemberID(DVD* dvd);
void LendNotify(Member* member, DVD* dvd);

// 商品ID入力画面 (貸出)
void InputLendGoodsID() {
	DVD* dvd;
	
	while(true) {
		string input = InputGoodsID("商品IDを入力 (0: キャンセル)", nullptr, true);
		dvd = gDB.FindDVD(input);
		
		if(input.empty()) {
			return;
		} else if(dvd == nullptr) {
			cout << "商品が見つかりません。\n\n";
		} else if(!dvd->mLendableFlag) {
			cout << "この商品はすでに貸出中です。\n\n";
		} else {
			break;
		}
	}
	
	LendGoodsInfo(dvd);
}


// 貸出商品情報確認画面
void LendGoodsInfo(DVD* dvd) {
	cout << "***** 貸出商品情報確認 *****\n";
	cout << dvd->mID << dvd->IsNew() << "\n";
	
	YesNo question("この商品を貸し出しますか?");
	
	if(question.Run()) {
		InputLendMemberID(dvd);
	}
}

// 会員ID入力画面 (貸出)
void InputLendMemberID(DVD* dvd) {
	Member* member;
	
	while(true) {
		cout << "どの会員に貸し出しますか?\n";
		string input = InputMemberID("会員ID", nullptr);
		
		member = gDB.FindMember(input);
		
		if(member == nullptr) {
			cout << "会員が見つかりませんでした。";
		} else {
			break;
		}
	}
	
	LendNotify(member, dvd);
}


// 貸出通知画面
void LendNotify(Member* member, DVD* dvd) {
	// 貸出処理
	gDB.Lend(member->mID, dvd->mID);
	
	// 貸出通知
	cout << "商品が貸し出されました。\n";
}
