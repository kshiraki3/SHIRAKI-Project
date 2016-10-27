//
//  Interface/Menu.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/20.
//	Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Interface/Menu.hpp"
#include <iostream>
#include <limits>

using namespace std;


Menu::Menu() {
	
}

Menu::Menu(const string& title, const initializer_list<MenuItem>& items) : mTitle(title), mItems(items) {
	
}

Menu::~Menu() {
	
}


/* ********************************************************************************************************* */
// 制御

void Menu::Run() {
	mQuit = false;
	
	do {
		// タイトル表示
		if(!mTitle.empty()) {
			cout << "***** " << mTitle << " *****\n";
		}
		
		// カスタムテキストを表示
		if(mShowText) {
			mShowText();
			cout << "\n";
		}
		
		// 項目表示
		for(const auto& item : mItems) {
			cout << item.mCommand << ". " << item.mText << "\n";
		}
		
		// 入力
		char input;
		
		cout << "\n入力> ";
		cin >> input;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		// 実行
		bool acted = false;
		
		for(const auto& item : mItems) {
			if(input == item.mCommand) {
				item.mAction();
				acted = true;
				break;
			}
		}
		
		// 入力が不正だったら再入力を促す
		if(!acted) {
			cout << "入力が間違っています。\n";
		}
		
		cout << "\n";
	} while(!mQuit);
}

void Menu::Quit() {
	mQuit = true;
}


/* ********************************************************************************************************* */
// 設定

void Menu::SetTitle(const string& title) {
	mTitle = title;
}

void Menu::SetCustomText(const std::function<void()>& showText) {
	mShowText = showText;
}

void Menu::AddItem(const MenuItem& items) {
	mItems.push_back(items);
}

void Menu::AddItem(char command, const string& text, const MenuAction& action) {
	mItems.push_back({ command, text, action });
}
