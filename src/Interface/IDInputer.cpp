//
//  Interface/IDInputer.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/21.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Interface/IDInputer.hpp"
#include "Record/Database.hpp"
#include "Record/Member.hpp"
#include <limits.h>
#include <iostream>

using namespace std;


/* ********************************************************************************************************* */
// 会員ID入力

MemberIDInputer::MemberIDInputer(const string& text, bool allowCencel) : mText(text), mAllowCancel(allowCencel) {
	
}

MemberIDInputer::~MemberIDInputer() {
	
}

string MemberIDInputer::Input() {
	while(true) {
		// 表示
		cout << mText << "> ";
		
		// 入力
		string input;
		cin >> input;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		// 判定
		if(mAllowCancel && input == "0") {
			return string();
		}
		
		string msg;
		if(Member::CheckIDSyntax(input, &msg)) {
			return input;
		} else {
			cout << msg << "\n\n";
		}
	}
}

Member* MemberIDInputer::Find() {
	while(true) {
		// 表示
		cout << mText << "> ";
		
		// 入力
		string input;
		cin >> input;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		// 判定
		if(mAllowCancel && input == "0") {
			return nullptr;
		}
		
		string msg;
		if(Member::CheckIDSyntax(input)) {
			Member* result = gDB.FindMember(input);
			if(result == nullptr) {
				cout << "この会員は存在しません。\n\n";
			} else {
				return result;
			}
		} else {
			cout << msg << "\n\n";
		}
	}
}
