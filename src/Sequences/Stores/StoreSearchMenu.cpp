//
//  Sequences/Stores/StoreSearchMenu.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/26.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Sequences/Stores/StoreSearchMenu.hpp"
#include "Sequences/Stores/Input.hpp"
#include "Sequences/Stores/StoreInfo.hpp"
#include "Utility.hpp"
#include "Record/Database.hpp"
#include "Interface/Menu.hpp"
#include "Interface/Paginator.hpp"
#include <cassert>
#include <iostream>

using namespace std;


void StoreSearchByID(Menu* menu);
void StoreSearchByName(Menu* menu);


// 店舗情報検索メニュー
void StoreSearchMenu() {
	Menu menu;
	
	menu.SetTitle("店舗情報検索");
	menu.AddItem('1', "店舗IDで検索", bind(&StoreSearchByID, &menu));
	menu.AddItem('2', "店舗名で検索", bind(&StoreSearchByName, &menu));
	menu.AddItem('0', "終了", bind(&Menu::Quit, &menu));
	
	menu.Run();
}


// 店舗ID入力画面 (検索)
void StoreSearchByID(Menu* menu) {
	int input = InputStoreID("店舗ID", nullptr);
	Store* store = gDB.FindStore(input);
	
	if(store == nullptr) {
		cout << "店舗が見つかりません。\n";
	} else {
		StoreInfo(store);
		menu->Quit();
	}
}


// 店舗名入力画面 (検索)
void StoreSearchByName(Menu* menu) {
	string input = InputStoreName("店舗名", nullptr);
	
	vector<Store*> searchResult;
	
	Paginator p;
	p.SetItemsPerPage(9);
	
	// 検索
	for(const auto& store : gDB.Stores()) {
		if(store.mName.find(input) != string::npos) {
			searchResult.push_back(const_cast<Store*>(&store));
			p.AddItem(Sprintf("%02d : %s", store.mID, store.mName.c_str()));
		}
	}
	
	// 結果選択
	if(searchResult.empty()) {
		cout << "店舗が見つかりません。\n";
	} else if(searchResult.size() == 1) {
		StoreInfo(searchResult[0]);
		menu->Quit();
	} else {
		p.SetSelectionHandler([&](int selection){
			assert(0 <= selection && selection < searchResult.size());
			StoreInfo(searchResult[selection]);
			menu->Quit();
		});
		p.Run();
	}
}
