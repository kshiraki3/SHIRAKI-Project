//
//  Sequences/Goods/Input.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/27.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Sequences/Goods/Input.hpp"
#include "Record/Database.hpp"
#include <iostream>

using namespace std;


string InputGoodsID(const string& msg, DVD* dvd, bool allowCancel) {
	string input;

	while(true) {
		cout << msg << "> ";
		cin >> input;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		string err;
		if(allowCancel && input == "0") {
			return string();
		} if(!DVD::CheckIDSyntax(input, &err)) {
			cout << err << "\n";
		} else {
			break;
		}
	}
	
	if(dvd != nullptr) {
		dvd->mID = input;
	}
	
	return input;
}


string InputGoodsTitle(const string& msg, DVD* dvd) {
	string input;
	
	cout << msg << "> ";
	cin >> input;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	if(dvd != nullptr) {
		dvd->mTitle = input;
	}
	
	return input;
}

string InputGoodsGenre(const string& msg, DVD* dvd) {
	string input;
	
	cout << msg << "> ";
	cin >> input;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	if(dvd != nullptr) {
		dvd->mGenre = input;
	}
	
	return input;
}

Date InputGoodsReleaseDate(const string& msg, DVD* dvd) {
	Date input;
	
	if(!msg.empty()) {
		cout << msg << "\n";
	}
	input.InputFromCin();
	
	if(dvd != nullptr) {
		dvd->mReleaseDate = input;
	}
	
	return input;
}

unsigned InputGoodsLendTime(const string& msg, DVD* dvd) {
	unsigned input;
	
	while(true){
		cout << msg << "> ";
		cin >> input;
		
		if(cin.fail()) {
			cout << "貸出回数は整数で入力してください。\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} else {
			break;
		}
	}
	
	if(dvd != nullptr) {
		dvd->mTitle = input;
	}
	
	return input;
}

bool InputGoodsLendableFlag(const string& msg, DVD* dvd) {
	int input;
	
	while(true){
		cout << msg << " (1: 貸出可, 0: 貸出中)> ";
		cin >> input;
		
		if(cin.fail() || (input != 0 && input != 1)) {
			cout << "入力が間違っています。\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} else {
			break;
		}
	}
	
	if(dvd != nullptr) {
		dvd->mLendableFlag = static_cast<bool>(input);
	}
	
	return static_cast<bool>(input);
}

int InputGoodsPlace(const string& msg, DVD* dvd) {
	int input;
	
	while(true) {
		cout << msg << " (-1: 倉庫)> ";
		cin >> input;
		
		if(cin.fail() || (input < 0 && 99 < input)) {
			cout << "保管場所は-1または有効な店舗IDで入力してください。\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} else if(gDB.FindStore(input) == nullptr) {
			cout << "店舗が見つかりません。\n";
		} else {
			break;
		}
	}
	
	if(dvd != nullptr) {
		dvd->mPlace = input;
	}
	
	return input;
}
