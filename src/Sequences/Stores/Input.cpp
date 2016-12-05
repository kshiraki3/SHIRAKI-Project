//
//  Sequences/Stores/Input.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/26.
//  Copyright © 2016年 SHIRAKI System. All rights reserved.
//

#include "Sequences/Stores/Input.hpp"
#include <iostream>
#include <limits>

using namespace std;


int InputStoreID(const string& msg, Store* store) {
	int input;
	
	while(true) {
		cout << msg << "> ";
		cin >> input;
		
		if(cin.fail() || input < 0 || 99 < input) {
			cout << "店舗IDは0から99までの整数で入力してください。\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} else {
			break;
		}
	}
	
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	if(store != nullptr) {
		store->mID = input;
	}
	
	return input;
}

std::string InputStoreName(const string& msg, Store* store) {
	cout << msg << "> ";
	
	string input;
	cin >> input;
	
	if(store != nullptr) {
		store->mName = input;
	}
	
	return input;
}
