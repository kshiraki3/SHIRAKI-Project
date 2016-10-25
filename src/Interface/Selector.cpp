//
//  Interface/Selector.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/20.
//	Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Interface/Selector.hpp"
#include <algorithm>
#include <iostream>
#include <limits>

using namespace std;


Selector::Selector() {
	
}

Selector::Selector(const initializer_list<SelectItem>& items) : mItems(items) {
	
}

Selector::~Selector() {
	
}

char Selector::Run() {
	do {
		// 表示
		for(const auto& item : mItems) {
			cout << item.mCommand << ". " << item.mText << "\n";
		}
		
		// 入力
		char input;
		
		cout << "\n入力> ";
		cin >> input;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		// 結果判定
		bool found = find_if(begin(mItems), end(mItems), [=] (const SelectItem& item) {
			return item.mCommand == input;
		}) != end(mItems);
		
		if(found) {
			return input;
		} else {
			cout << "入力が間違っています。\n\n";
		}
	} while(true);
}

void Selector::AddItem(const SelectItem& item) {
	mItems.push_back(item);
}
void Selector::AddItem(char command, const string& text) {
	mItems.push_back({ command, text });
}
