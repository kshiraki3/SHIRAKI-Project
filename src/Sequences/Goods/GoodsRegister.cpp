//
//  Sequences/Goods/GoodsRegister.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/27.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Sequences/Goods/GoodsRegister.hpp"
#include "Sequences/Goods/Input.hpp"
#include "Record/Database.hpp"
#include "Interface/Menu.hpp"
#include <iostream>

using namespace std;

void NewGoodsInfo(DVD* newDVD);
void GoodsRegisterNotify(DVD* newDVD);


// 新規商品情報入力画面
void GoodsRegister() {
	DVD newDVD;
	
	cout << "***** 新規商品情報入力 *****\n";
	
	InputGoodsID("商品ID (0: 自動生成)", &newDVD, true);
	if(newDVD.mID.empty()) {
		newDVD.mID = gDB.GenerateGoodsID();
	}
	
	InputGoodsTitle("タイトル", &newDVD);
	InputGoodsGenre("ジャンル", &newDVD);
	InputGoodsReleaseDate("発売日", &newDVD);
	
	newDVD.mLendTime = 0;
	newDVD.mLendableFlag = 0;
	newDVD.mPlace = gDB.CurrentStore();
	
	NewGoodsInfo(&newDVD);
}


// 新規商品情報確認画面
void NewGoodsInfo(DVD* newDVD) {
	Menu menu;
	
	menu.SetTitle("新規商品情報確認");
	menu.SetCustomText([=](){
		cout << "商品ID: " << newDVD->mID << "\n";
		cout << "タイトル: " << newDVD->mTitle << "\n";
		cout << "ジャンル: " << newDVD->mGenre << "\n";
		cout << "発売日: " << newDVD->mReleaseDate << "\n";
	});
	
	menu.AddItem('1', "登録", [&](){
		GoodsRegisterNotify(newDVD);
		menu.Quit();
	});
	menu.AddItem('2', "商品IDを変更", [=](){ InputGoodsID("", newDVD); });
	menu.AddItem('3', "タイトルを変更", [=](){ InputGoodsTitle("", newDVD); });
	menu.AddItem('4', "ジャンルを変更", [=](){ InputGoodsGenre("", newDVD); });
	menu.AddItem('5', "発売日を変更", [=](){ InputGoodsReleaseDate("", newDVD); });
	menu.AddItem('0', "キャンセル", bind(&Menu::Quit, &menu));
	
	menu.Run();
}


// 商品登録通知画面
void GoodsRegisterNotify(DVD* newDVD) {
	gDB.AddDVD(*newDVD);
	cout << "商品情報が登録されました。\n";
}
