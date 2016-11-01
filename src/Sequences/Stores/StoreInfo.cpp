//
//  Sequences/Stores/StoreInfo.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/26.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Sequences/Stores/StoreInfo.hpp"
#include "Sequences/Stores/Input.hpp"
#include "Record/Database.hpp"
#include "Record/Store.hpp"
#include "Interface/Menu.hpp"
#include "Interface/YesNo.hpp"
#include <iostream>

using namespace std;


void StoreSetNotify(Store* store);
void StoreNameModify(Store* store);
void StoreDeleteConfirmation(Store* store, Menu& menu);
void StoreDeleteNotify(Store* store);


// 店舗情報確認画面
void StoreInfo(Store* store) {
	Menu menu;
	
	menu.SetTitle("店舗情報確認");
	menu.SetCustomText([&](){
		cout << "店舗ID : " << store->mID << "\n";
		cout << "店舗名 : " << store->mName << "\n";
	});
	menu.AddItem('1', "現在の店舗として設定", bind(&StoreSetNotify, store));
	menu.AddItem('2', "店舗名変更", bind(&StoreNameModify, store));
	menu.AddItem('3', "削除", bind(&StoreDeleteConfirmation, store, menu));
	menu.AddItem('0', "店舗情報管理メニューに戻る", bind(&Menu::Quit, &menu));
	
	menu.Run();
}


// 店舗設定通知画面
void StoreSetNotify(Store* store) {
	gDB.SetCurrentStore(store->mID);
	cout << store->mName << "が現在の店舗として設定されました。";
}


// 店舗名変更画面
void StoreNameModify(Store* store) {
	InputStoreID("", store);
}


// 店舗情報削除確認画面
void StoreDeleteConfirmation(Store* store, Menu& menu) {
	YesNo question("店舗情報を削除しますか?");
	
	if(question.Run()) {
		StoreDeleteNotify(store);
		menu.Quit();
	}
}


// 店舗情報削除通知画面
void StoreDeleteNotify(Store* store) {
	gDB.RemoveStore(store->mID);
}
