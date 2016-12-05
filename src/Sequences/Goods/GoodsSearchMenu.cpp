//
//  Sequences/Goods/GoodsSearchMenu.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/27.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Sequences/Goods/GoodsSearchMenu.hpp"
#include "Sequences/Goods/Input.hpp"
#include "Sequences/Goods/GoodsInfo.hpp"
#include "Interface/Paginator.hpp"
#include "Record/Database.hpp"
#include "Interface/Menu.hpp"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;


void GoodsSearchByID(Menu* menu);
void GoodsSearchByTitle(Menu* menu);

// 商品情報検索メニュー
void GoodsSearchMenu() {
	Menu menu;
	
	menu.SetTitle("商品情報検索メニュー");
	menu.AddItem('1', "商品IDで検索", bind(&GoodsSearchByID, &menu));
	menu.AddItem('2', "タイトルで検索", bind(&GoodsSearchByTitle, &menu));
	menu.AddItem('0', "商品情報管理メニューに戻る", bind(&Menu::Quit, &menu));
	
	menu.Run();
}


// 商品ID入力画面 (検索)
void GoodsSearchByID(Menu* menu) {
	string input = InputGoodsID("商品ID (0: キャンセル)", nullptr, true);
	
	if(!input.empty()) {
		DVD* dvd = gDB.FindDVD(input);
		
		if(dvd == nullptr) {
			cout << "商品が見つかりません。\n";
		} else {
			GoodsInfo(dvd);
			menu->Quit();
		}
	}
}

// タイトル入力画面 (検索)
void GoodsSearchByTitle(Menu* menu) {
	vector<DVD*> searchResult;	// 検索結果
	
	Paginator p;
	p.SetItemsPerPage(9);
	
	string input = InputGoodsTitle("タイトル", nullptr);
	
	for(const DVD& dvd : gDB.DVDs()) {
		if(dvd.mTitle.find(input) != string::npos) {
			searchResult.push_back(const_cast<DVD*>(&dvd));
			p.AddItem(Sprintf("%s : %s", dvd.mID.c_str(), dvd.mTitle.c_str()));
		}
	}
	
	if(searchResult.empty()) {
		cout << "商品が見つかりませんでした。\n";
	} else if(searchResult.size() == 1) {
		GoodsInfo(searchResult.front());
		menu->Quit();
	} else {
		p.SetSelectionHandler([&](int selection){
			assert(0 <= selection && selection < searchResult.size());
			GoodsInfo(searchResult[selection]);
			menu->Quit();
			p.Quit();
		});
		p.Run();
	}
}
