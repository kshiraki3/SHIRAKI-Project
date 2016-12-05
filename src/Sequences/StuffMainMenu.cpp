//
//  Sequences/StuffMainMenu.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/26.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Sequences/StuffMainMenu.hpp"
#include "Sequences/Rental/RentalMenu.hpp"
#include "Sequences/Stores/StoreManageMenu.hpp"
#include "Sequences/Members/MemberManageMenu.hpp"
#include "Sequences/Goods/GoodsManageMenu.hpp"
#include "Sequences/Recommend/RecommendationSearch.hpp"
#include "Interface/Menu.hpp"
#include "Interface/YesNo.hpp"


// スタッフメインメニュー
void StuffMainMenu() {
	Menu menu;
	
	menu.SetTitle("スタッフメインメニュー");
	
	menu.AddItem('1', "レンタルメニュー", &RentalMenu);
	menu.AddItem('2', "会員情報管理メニュー", &MemberManageMenu);
	menu.AddItem('3', "商品情報管理メニュー", &GoodsManageMenu);
	menu.AddItem('4', "店舗情報管理メニュー", &StoreManageMenu);
	menu.AddItem('5', "おすすめ検索", &RecommendationSearch);
	menu.AddItem('0', "終了", [&](){
		// 終了確認画面
		YesNo yn("プログラムを終了しますか?");
		if(yn.Run()) {
			menu.Quit();
		}
	});
	
	
	// 実行
	menu.Run();
}
