//
//  Sequences/Goods/GoodsManageMenu.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/27.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Sequences/Goods/GoodsManageMenu.hpp"
#include "Sequences/Goods/GoodsSearchMenu.hpp"
#include "Sequences/Goods/GoodsRegister.hpp"
#include "Sequences/Goods/GoodsList.hpp"
#include "Interface/Menu.hpp"


// 商品情報管理メニュー
void GoodsManageMenu() {
	Menu menu;
	
	menu.SetTitle("商品情報管理メニュー");
	menu.AddItem('1', "商品情報検索メニュー", &GoodsSearchMenu);
	menu.AddItem('2', "新規商品登録", &GoodsRegister);
	menu.AddItem('3', "商品一覧表示", &GoodsList);
	menu.AddItem('0', "スタッフメインメニューに戻る", std::bind(&Menu::Quit, &menu));
	
	menu.Run();
}
