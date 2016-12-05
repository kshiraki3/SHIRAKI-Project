//
//  Sequences/Members/MemberSearchMenu.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/27.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Sequences/Members/MemberSearchMenu.hpp"
#include "Sequences/Members/Input.hpp"
#include "Sequences/Members/MemberInfo.hpp"
#include "Utility.hpp"
#include "Record/Database.hpp"
#include "Interface/Menu.hpp"
#include "Interface/Paginator.hpp"
#include <cassert>
#include <iostream>

using namespace std;


void MemberSearchByID(Menu* menu);
void MemberSearchByName(Menu* menu);


// 会員情報検索メニュー
void MemberSearchMenu() {
	Menu menu;
	
	menu.SetTitle("会員情報検索");
	menu.AddItem('1', "会員IDで検索", bind(&MemberSearchByID, &menu));
	menu.AddItem('2', "会員名で検索", bind(&MemberSearchByName, &menu));
	menu.AddItem('0', "終了", bind(&Menu::Quit, &menu));
	
	menu.Run();
}


// 会員ID入力画面 (検索)
void MemberSearchByID(Menu* menu) {
	string input = InputMemberID("会員ID", nullptr);
	Member* member = gDB.FindMember(input);
	
	if(member == nullptr) {
		cout << "会員が見つかりません。\n";
	} else {
		MemberInfo(member);
		menu->Quit();
	}
}


// 会員名入力画面 (検索)
void MemberSearchByName(Menu* menu) {
	string input = InputMemberName("会員名", nullptr);
	
	vector<Member*> searchResult;
	
	Paginator p;
	p.SetItemsPerPage(9);
	
	// 検索
	for(const auto& member : gDB.Members()) {
		if(member.mName.find(input) != string::npos) {
			searchResult.push_back(const_cast<Member*>(&member));
			p.AddItem(Sprintf("%s : %s", member.mID.c_str(), member.mName.c_str()));
		}
	}
	
	// 結果選択
	if(searchResult.empty()) {
		cout << "会員が見つかりません。\n";
	} else if(searchResult.size() == 1) {
		MemberInfo(searchResult.front());
		menu->Quit();
	} else {
		p.SetSelectionHandler([&](int selection){
			assert(0 <= selection && selection < searchResult.size());
			MemberInfo(searchResult[selection]);
			menu->Quit();
			p.Quit();
		});
		p.Run();
	}
}
