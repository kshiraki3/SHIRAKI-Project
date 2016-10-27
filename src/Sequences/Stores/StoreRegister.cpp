//
//  Sequences/Stores/StoreRegister.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/27.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Sequences/Stores/StoreRegister.hpp"
#include "Sequences/Stores/Input.hpp"
#include "Record/Database.hpp"
#include "Interface/Menu.hpp"
#include <iostream>

using namespace std;


void NewStoreInfo(Store* newStore);
void StoreRegisterNotify(Store* newStore);

// 新規店舗情報入力画面
void StoreRegister() {
	Store newStore;
	
	InputStoreID("店舗ID", &newStore);
	InputStoreName("店舗名", &newStore);
	
	NewStoreInfo(&newStore);
}


// 新規店舗情報確認画面
void NewStoreInfo(Store* newStore) {
	Menu menu;
	
	menu.SetTitle("新規店舗情報確認");
	menu.SetCustomText([=](){
		cout << "店舗ID : " << newStore->mID << "\n";
		cout << "店舗名 : " << newStore->mName << "\n";
	});
	menu.AddItem('1', "登録",[&](){
		StoreRegisterNotify(newStore);
		menu.Quit();
	});
	menu.AddItem('2', "店舗IDを変更", [=](){ InputStoreID("", newStore); });
	menu.AddItem('3', "店舗名を変更", [=](){ InputStoreName("", newStore); });
	menu.AddItem('0', "キャンセル", bind(&Menu::Quit, &menu));
	
	menu.Run();
}


// 店舗登録通知画面
void StoreRegisterNotify(Store* newStore) {
	gDB.AddStore(*newStore);
	cout << "店舗情報が追加されました。\n";
}
