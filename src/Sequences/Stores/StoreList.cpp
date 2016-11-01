//
//  Sequences/Stores/StoreList.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/27.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Sequences/Stores/StoreList.hpp"
#include "Utility.hpp"
#include "Record/Database.hpp"
#include "Interface/Menu.hpp"
#include "Interface/Selector.hpp"
#include "Interface/Paginator.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;


void StoreSortByID(vector<const Store*>& stores);
void StoreSortByName(vector<const Store*>& stores);
void ShowStoreList(const vector<const Store*>& stores);

// 店舗一覧表示画面
void StoreList() {
	// データ取得
	vector<const Store*> stores;
	stores.reserve(gDB.Stores().size());
	
	for(const auto& store : gDB.Stores()) {
		stores.push_back(&store);
	}
	
	// メニュー
	Menu menu;
	menu.SetTitle("店舗一覧表示");
	menu.SetCustomText([](){
		cout << "どの項目で並び替えますか?\n";
	});
	menu.AddItem('1', "店舗ID", bind(&StoreSortByID, stores));
	menu.AddItem('2', "店舗名", bind(&StoreSortByName, stores));
	menu.AddItem('0', "店舗情報管理メニューに戻る", bind(&Menu::Quit, &menu));
	
	menu.Run();
}


// IDで並び替え
void StoreSortByID(vector<const Store*>& stores) {
	Selector sel;
	
	sel.AddItem('1', "昇順");
	sel.AddItem('2', "降順");
	
	cout << "\nどの順で並び替えますか?\n";
	char input = sel.Run();
	
	if(input == '1') {
		sort(begin(stores), end(stores), [](const Store* x, const Store* y){ return x->mID < y->mID; });
	} else if(input == '2') {
		sort(begin(stores), end(stores), [](const Store* x, const Store* y){ return x->mID > y->mID; });
	}
	
	ShowStoreList(stores);
}


// 店舗名で並び替え
void StoreSortByName(vector<const Store*>& stores) {
	Selector sel;
	
	sel.AddItem('1', "昇順");
	sel.AddItem('2', "降順");
	
	cout << "\nどの順で並び替えますか?\n";
	char input = sel.Run();
	
	if(input == '1') {
		sort(begin(stores), end(stores), [](const Store* x, const Store* y){ return x->mName < y->mName; });
	} else if(input == '2') {
		sort(begin(stores), end(stores), [](const Store* x, const Store* y){ return x->mName > y->mName; });
	}
	
	ShowStoreList(stores);
}


// リスト表示
void ShowStoreList(const vector<const Store*>& stores) {
	vector<string> items;
	
	Paginator p;
	
	for(auto store : stores) {
		p.AddItem(Sprintf("%02d | %s", store->mID, store->mName.c_str()));
	}
	
	p.SetHeaderText("ID | 店舗名");
	p.SetReturnMessage("戻る");
	p.SetItemsPerPage(20);
	
	p.Run();
}
