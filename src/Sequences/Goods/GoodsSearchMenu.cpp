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
#include "Record/Database.hpp"
#include "Interface/Menu.hpp"
#include <iostream>

using namespace std;


void GoodsSearchByID();
void GoodsSearchByTitle();

// 商品情報検索メニュー
void GoodsSearchMenu() {
	Menu menu;
	
	menu.SetTitle("商品情報検索メニュー");
	menu.AddItem('1', "商品IDで検索", &GoodsSearchByID);
	menu.AddItem('2', "タイトルで検索", &GoodsSearchByTitle);
	menu.AddItem('0', "商品情報管理メニューに戻る", bind(&Menu::Quit, &menu));
	
	menu.Run();
}


// 商品ID入力画面 (検索)
void GoodsSearchByID() {
	string input = InputGoodsID("商品ID (0: キャンセル)", nullptr, true);
	
	if(!input.empty()) {
		DVD* dvd = gDB.FindDVD(input);
		
		if(dvd == nullptr) {
			cout << "商品が見つかりません。\n";
		} else {
			GoodsInfo(dvd);
		}
	}
}

// タイトル入力画面 (検索)
void GoodsSearchByTitle() {
	
}
