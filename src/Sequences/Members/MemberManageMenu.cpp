//
//  Sequences/Members/MemberManageMenu.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/27.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Sequences/Members/MemberManageMenu.hpp"
#include "Sequences/Members/MemberSearchMenu.hpp"
#include "Sequences/Members/MemberRegister.hpp"
#include "Sequences/Members/MemberList.hpp"
#include "Interface/Menu.hpp"

using namespace std;


// 会員情報管理メニュー
void MemberManageMenu() {
	Menu menu;
	
	menu.SetTitle("会員情報管理メニュー");
	menu.AddItem('1', "会員情報検索メニュー", &MemberSearchMenu);
	menu.AddItem('2', "新規会員登録", &MemberRegister);
	menu.AddItem('3', "会員一覧表示", &MemberList);
	menu.AddItem('0', "スタッフメインメニューに戻る", bind(&Menu::Quit, &menu));
	
	menu.Run();
}
