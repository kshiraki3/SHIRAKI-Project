//
//  Sequences/Members/MemberRegister.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/27.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Sequences/Members/MemberRegister.hpp"
#include "Sequences/Members/Input.hpp"
#include "Record/Database.hpp"
#include "Interface/Menu.hpp"
#include <iostream>

using namespace std;


void NewMemberInfo(Member* newMember);
void MemberRegisterNotify(Member* newMember);

// 新規会員情報入力画面
void MemberRegister() {
	Member newMember;
	
	cout << "***** 新規会員情報入力 *****\n";
	
	while(true) {
		InputMemberID("会員ID (0: 自動生成)", &newMember, true);
		if(newMember.mID.empty()) {
			try {
				newMember.mID = gDB.GenerateMemberID();
				break;
			} catch(const IDGenerationException& exception) {
				cout << exception.what() << "\n";
			}
		} else if(gDB.FindMember(newMember.mID) != nullptr) {
			// 重複チェック
			cout << "会員IDが重複しています。別のIDを入力してください。\n";
		} else {
			break;
		}
	}
	
	InputMemberName("氏名", &newMember);
	InputMemberAddress("住所", &newMember);
	InputMemberPhoneNumber("電話番号", &newMember);
	InputMemberBirthday("生年月日", &newMember);
	
	NewMemberInfo(&newMember);
}


// 新規会員情報確認画面
void NewMemberInfo(Member* newMember) {
	Menu menu;
	
	menu.SetTitle("新規会員情報確認");
	menu.SetCustomText([=](){
		cout << "会員ID : " << newMember->mID << "\n";
		cout << "氏名 : " << newMember->mName << "\n";
		cout << "住所 : " << newMember->mAddress << "\n";
		cout << "電話番号 : " << newMember->mPhoneNumber << "\n";
		cout << "生年月日 : " << newMember->mBirthday << "\n";
	});
	menu.AddItem('1', "登録", [&](){
		MemberRegisterNotify(newMember);
		menu.Quit();
	});
	menu.AddItem('2', "会員IDを変更 (0: 自動生成)", [=](){
		string id;
		while(true) {
			id = InputMemberID("", nullptr, true);
			if(id.empty()) {
				try {
					id = gDB.GenerateMemberID();
					break;
				} catch(const IDGenerationException& exception) {
					cout << exception.what() << "\n";
				}
			} else if(gDB.FindMember(id) != nullptr) {
				// 重複チェック
				cout << "会員IDが重複しています。別のIDを入力してください。\n";
			} else {
				break;
			}
		}
		
		newMember->mID = id;
	});
	menu.AddItem('3', "氏名を変更", [=](){ InputMemberName("", newMember); });
	menu.AddItem('4', "住所を変更", [=](){ InputMemberAddress("", newMember); });
	menu.AddItem('5', "電話番号を変更", [=](){ InputMemberPhoneNumber("", newMember); });
	menu.AddItem('6', "生年月日を変更", [=](){ InputMemberBirthday("", newMember); });
	menu.AddItem('0', "キャンセル", bind(&Menu::Quit, &menu));
	
	menu.Run();
}


// 会員登録通知画面
void MemberRegisterNotify(Member* newMember) {
	gDB.AddMember(*newMember);
	cout << "会員が登録されました。\n";
}
