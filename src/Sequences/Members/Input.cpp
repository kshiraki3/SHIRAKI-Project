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
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
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


string InputMemberName(const string& msg, Member* member) {
	string input;
	
	cout << msg << "> ";
	cin >> input;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	if(member != nullptr) {
		member->mName = input;
	}
	
	return input;
}

string InputMemberAddress(const string& msg, Member* member) {
	string input;
	
	cout << msg << "> ";
	getline(cin, input, '\n');
	
	if(member != nullptr) {
		member->mAddress = input;
	}
	
	return input;
}

string InputMemberPhoneNumber(const string& msg, Member* member) {
	string input;
	
	while(true) {
		cout << msg << "> ";
		cin >> input;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		if(!Member::CheckPhoneNumber(input)) {
			cout << "電話番号は0000-00-0000、000-000-0000, 00-0000-0000の形で入力してください。\n";
		} else {
			break;
		}
	}
	
	if(member != nullptr) {
		member->mPhoneNumber = input;
	}
	
	return input;
}

Date InputMemberBirthday(const string& msg, Member* member) {
	Date input;
	
	if(!msg.empty()) {
		cout << msg << "\n";
	}
	input.InputFromCin();
	
	if(member != nullptr) {
		member->mBirthday = input;
	}
	
	return input;
}
