//
//  Sequences/Rental/RentalMenu.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/27.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Sequences/Rental/RentalMenu.hpp"
#include "Interface/Menu.hpp"

using namespace std;


// レンタルメニュー
void RentalMenu() {
	Menu menu;
	
	menu.SetTitle("レンタルメニュー");
	menu.AddItem('1', "貸出", nullptr);
	menu.AddItem('2', "返却", nullptr);
	menu.AddItem('3', "貸出商品リスト", nullptr);
	menu.AddItem('0', "終了", bind(&Menu::Quit, &menu));
	
	menu.Run();
}
