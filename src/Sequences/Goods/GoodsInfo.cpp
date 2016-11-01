//
//  Sequences/Goods/GoodsInfo.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/27.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Sequences/Goods/GoodsInfo.hpp"
#include "Sequences/Goods/Input.hpp"
#include "Record/Database.hpp"
#include "Interface/Menu.hpp"
#include "Interface/YesNo.hpp"
#include <iostream>

using namespace std;


void ShowGoodsInfo(DVD* dvd);

void GoodsModify(DVD* dvd);
void GoodsDeleteComfirmation(DVD* dvd, Menu& menu);
void GoodsDeleteNotify(DVD* dvd);

// 商品情報確認画面
void GoodsInfo(DVD* dvd) {
	Menu menu;
	
	menu.SetTitle("商品情報確認");
	menu.SetCustomText([=](){
		ShowGoodsInfo(dvd);
	});
	menu.AddItem('1', "変更", bind(&GoodsModify, dvd));
	menu.AddItem('2', "削除", bind(&GoodsDeleteComfirmation, dvd, menu));
	menu.AddItem('0', "商品情報確認メニューに戻る", bind(&Menu::Quit, &menu));
	
	menu.Run();
}

void ShowGoodsInfo(DVD* dvd) {
	cout << "商品ID: " << dvd->mID << "\n";
	cout << "タイトル: " << dvd->mTitle << "\n";
	cout << "ジャンル: " << dvd->mGenre << "\n";
	cout << "発売日: " << dvd->mReleaseDate << "\n";
	cout << "貸出回数: " << dvd->mLendTime << "回\n";
	cout << "貸出状況: " << (dvd->mLendableFlag ? "貸出可" : "貸出中") << "\n";
	cout << "保管場所: ";
	
	if(dvd->mPlace == -1) {
		cout << "倉庫\n";
	} else {
		cout << gDB.FindStore(dvd->mPlace)->mName << "\n";
	}
}


// 商品情報変更メニュー
void GoodsModify(DVD* dvd) {
	Menu menu;
	
	menu.SetCustomText([](){ cout << "どの項目を変更しますか?\n"; });
	menu.AddItem('1', "タイトル", [=](){ InputGoodsTitle("", dvd); });
	menu.AddItem('2', "ジャンル", [=](){ InputGoodsGenre("", dvd); });
	menu.AddItem('3', "発売日", [=](){ InputGoodsReleaseDate("", dvd); });
	menu.AddItem('4', "貸出回数", [=](){ InputGoodsLendTime("", dvd); });
	menu.AddItem('5', "保管場所", [=](){ InputGoodsPlace("", dvd); });
	menu.AddItem('0', "商品情報確認に戻る", bind(&Menu::Quit, &menu));
	
	menu.Run();
}


// 商品情報削除確認画面
void GoodsDeleteComfirmation(DVD* dvd, Menu& menu) {
	YesNo yn("商品を削除しますか?");
	
	if(yn.Run()) {
		GoodsDeleteNotify(dvd);
		menu.Quit();
	}
}


// 商品情報削除通知画面
void GoodsDeleteNotify(DVD* dvd) {
	gDB.RemoveDVD(dvd->mID);
	cout << "商品が削除されました。\n";
}
