//
//  Sequences/Members/MemberList.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/27.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Sequences/Members/MemberList.hpp"
#include "Utility.hpp"
#include "Record/Database.hpp"
#include "Interface/Menu.hpp"
#include "Interface/Paginator.hpp"
#include "Interface/Selector.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

void MemberSortByID(vector<const Member*>& members);
void MemberSortByName(vector<const Member*>& members);
void MemberSortByBirthday(vector<const Member*>& members);
void ShowMemberList(const vector<const Member*>& members, bool id, bool name, bool address, bool birthday);


// 会員情報一覧表示メニュー
void MemberList() {
	// データ取得
	vector<const Member*> members;
	members.reserve(gDB.Members().size());
	
	for(const auto& member : gDB.Members()) {
		members.push_back(&member);
	}
	
	// メニュー
	Menu menu;
	
	menu.SetSingle(true);
	
	menu.SetCustomText([](){
		cout << "どの項目で並び替えますか?";
	});
	
	menu.AddItem('1', "会員ID", bind(&MemberSortByID, members));
	menu.AddItem('2', "氏名", bind(&MemberSortByName, members));
	menu.AddItem('3', "生年月日", bind(&MemberSortByBirthday, members));
	menu.AddItem('0', "会員情報管理メニューに戻る", bind(&Menu::Quit, &menu));
	
	menu.Run();
}


// IDで並び替え
void MemberSortByID(vector<const Member*>& members) {
	Selector sel;
	
	sel.AddItem('1', "昇順");
	sel.AddItem('2', "降順");
	
	cout << "\nどの順で並び替えますか?\n";
	char input = sel.Run();
	
	if(input == '1') {
		sort(begin(members), end(members), [](const Member* x, const Member* y){ return x->mID < y->mID; });
	} else if(input == '2') {
		sort(begin(members), end(members), [](const Member* x, const Member* y){ return x->mID > y->mID; });
	}
	
	ShowMemberList(members, true, true, false, false);
}


// 氏名で並び替え
void MemberSortByName(vector<const Member*>& members) {
	Selector sel;
	
	sel.AddItem('1', "昇順");
	sel.AddItem('2', "降順");
	
	cout << "\nどの順で並び替えますか?\n";
	char input = sel.Run();
	
	if(input == '1') {
		sort(begin(members), end(members), [](const Member* x, const Member* y){ return x->mName < y->mName; });
	} else if(input == '2') {
		sort(begin(members), end(members), [](const Member* x, const Member* y){ return x->mName > y->mName; });
	}
	
	ShowMemberList(members, true, true, false, false);
}


// 生年月日で並び替え
void MemberSortByBirthday(vector<const Member*>& members) {
	Selector sel;
	
	sel.AddItem('1', "昇順");
	sel.AddItem('2', "降順");
	
	cout << "\nどの順で並び替えますか?\n";
	char input = sel.Run();
	
	if(input == '1') {
		sort(begin(members), end(members), [](const Member* x, const Member* y){ return x->mBirthday < y->mBirthday; });
	} else if(input == '2') {
		sort(begin(members), end(members), [](const Member* x, const Member* y){ return x->mBirthday > y->mBirthday; });
	}
	
	ShowMemberList(members, true, true, false, true);
}


// リストを表示
void ShowMemberList(const vector<const Member*>& members) {
	Paginator p;
	
	for(auto member : members) {
		p.AddItem(Sprintf("%s | %s | %s | %04d/%02d/%02d", member->mID.c_str(), member->mName.c_str(), member->mAddress.c_str(),
						  member->mBirthday.mYear, member->mBirthday.mMonth, member->mBirthday.mDay));
	}
	
	p.SetHeaderText("ID | 氏名 | 住所 | 生年月日");
	p.SetReturnMessage("戻る");
	p.SetItemsPerPage(20);
	
	p.Run();
}


// リストを表示
void ShowMemberList(const vector<const Member*>& members, bool id, bool name, bool address, bool birthday) {
	Paginator p;
	
	// ヘッダ
	ostringstream header;
	if(id) {
		header << "ID |";
	}
	if(name) {
		header << "氏名 |";
	}
	if(address) {
		header << "住所 |";
	}
	if(birthday) {
		header << "生年月日";
	}
	p.SetHeaderText(header.str());
	
	// 行
	for(auto member : members) {
		ostringstream row;
		if(id) {
			row << member->mID << " | ";
		}
		if(name) {
			row << member->mName << " | ";
		}
		if(address) {
			row << member->mAddress << " | ";
 		}
		if(birthday) {
			row << member->mBirthday;
		}
		p.AddItem(row.str());
	}
	
	p.SetReturnMessage("戻る");
	p.SetItemsPerPage(20);
	
	p.Run();
}
