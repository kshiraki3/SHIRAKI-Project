//
//  Interface/YesNo.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/20.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Interface/YesNo.hpp"
#include <iostream>
#include <limits>

using namespace std;


YesNo::YesNo() {
	
}

YesNo::YesNo(const string& text) : mText(text) {
	
}

YesNo::~YesNo() {
	
}

bool YesNo::Run() {
	do {
		// 表示
		cout << mText << " (y/n) > ";
		
		// 入力
		char input;
		cin >> input;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		// 処理
		if(input == 'Y' || input == 'y') {
			return true;
		} else if(input == 'N' || input == 'n') {
			return false;
		} else {
			cout << "入力が間違っています。\n\n";
		}
	} while(true);
}

void YesNo::SetText(const string& text) {
	mText = text;
}
