//
//  StoreManageMenu.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/26.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Sequences/Stores/StoreManageMenu.hpp"
#include "Sequences/Stores/StoreSearchMenu.hpp"
#include "Sequences/Stores/StoreRegister.hpp"
#include "Sequences/Stores/StoreList.hpp"
#include "Interface/Menu.hpp"

using namespace std;


void StoreManageMenu() {
	Menu menu;
	
	menu.SetTitle("店舗情報管理メニュー");
	menu.AddItem('1', "店舗情報検索メニュー", &StoreSearchMenu);
	menu.AddItem('2', "新規店舗登録", &StoreRegister);
	menu.AddItem('3', "店舗一覧表示", &StoreList);
	menu.AddItem('0', "終了", bind(&Menu::Quit, &menu));
	
	menu.Run();
}
