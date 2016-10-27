//
//  Sequences/Members/Input.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/27.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Sequences/Members/Input.hpp"
#include <iostream>

using namespace std;


string InputMemberID(const string& msg, Member* member, bool allowCancel) {
	string input;
	
	while(true) {
		cout << msg << "> ";
		cin >> input;
		
		string err;
		if(allowCancel && input == "0") {
			return string();
		} else if(!Member::CheckIDSyntax(input, &err)) {
			cout << err << "\n";
		} else {
			break;
		}
	}
	
	if(member != nullptr) {
		member->mID = input;
	}
	
	return input;
}
