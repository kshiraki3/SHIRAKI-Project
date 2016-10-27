//
//  Sequences/Goods/Input.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/27.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Sequences/Goods/Input.hpp"
#include <iostream>

using namespace std;


string InputGoodsID(const string& msg, DVD* dvd, bool allowCancel) {
	string input;

	while(true) {
		cout << msg << "> ";
		cin >> input;
		
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
