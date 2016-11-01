//
//  Sequences/Members/MemberInfo.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/27.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Sequences/Members/MemberInfo.hpp"
#include "Sequences/Members/Input.hpp"
#include "Record/Database.hpp"
#include "Interface/Menu.hpp"
#include "Interface/YesNo.hpp"
#include <iostream>

using namespace std;


void ShowInfo(Member* member);

void MemberModify(Member* member);
void MemberDeleteComfirmation(Member* member, Menu& meun);
void MemberDeleteNotify(Member* member);


// 会員情報確認画面
void MemberInfo(Member* member) {
	Menu menu;
	
	menu.SetTitle("会員情報確認");
	menu.SetCustomText(bind(&ShowInfo, member));
	menu.AddItem('1', "変更", bind(&MemberModify, member));
	menu.AddItem('2', "削除", bind(&MemberDeleteComfirmation, member, menu));
	menu.AddItem('0', "会員情報管理メニューに戻る", bind(&Menu::Quit, &menu));
	
	menu.Run();
}


// 会員情報を表示
void ShowInfo(Member* member) {
	cout << "会員ID : " << member->mID << "\n";
	cout << "氏名 : " << member->mName << "\n";
	cout << "住所 : " << member->mAddress << "\n";
	cout << "電話番号 : " << member->mPhoneNumber << "\n";
	cout << "生年月日 : " << member->mBirthday << "\n";
}


// 会員情報変更メニュー
void MemberModify(Member* member) {
	Menu menu;
	
	menu.SetCustomText([](){ cout << "どの項目を変更しますか?\n"; });
	menu.AddItem('1', "氏名", [=](){ InputMemberName("", member); });
	menu.AddItem('1', "住所", [=](){ InputMemberAddress("", member); });
	menu.AddItem('1', "電話番号", [=](){ InputMemberPhoneNumber("", member); });
	menu.AddItem('1', "生年月日", [=](){ InputMemberBirthday("", member); });
	menu.AddItem('0', "会員情報確認に戻る", bind(&Menu::Quit, &menu));
	
	menu.Run();
}


// 会員情報削除確認画面
void MemberDeleteComfirmation(Member* member, Menu& menu) {
	YesNo question("会員情報を削除しますか?");
	if(question.Run()) {
		MemberDeleteNotify(member);
		menu.Quit();
	}
}


// 会員情報削除通知画面
void MemberDeleteNotify(Member* member) {
	gDB.RemoveMember(member->mID);
	cout << "会員情報が削除されました。\n";
}
