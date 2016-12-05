//
//  Sequences/Goods/GoodsList.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/27.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Sequences/Goods/GoodsList.hpp"
#include "Utility.hpp"
#include "Record/Database.hpp"
#include "Interface/Menu.hpp"
#include "Interface/Paginator.hpp"
#include "Interface/Selector.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;


void GoodsSortByID(std::vector<const DVD*>& dvds);
void GoodsSortByTitle(std::vector<const DVD*>& dvds);
void GoodsSortByGenre(std::vector<const DVD*>& dvds);
void GoodsSortByReleaseDate(std::vector<const DVD*>& dvds);
void ShowGoodsList(const vector<const DVD*>& dvds, bool id, bool title, bool genre, bool releaseDate);

void GoodsList() {
	std::vector<const DVD*> dvds;
	dvds.reserve(gDB.DVDs().size());
	for(const DVD& dvd : gDB.DVDs()) {
		dvds.push_back(&dvd);
	}
	
	// メニュー
	Menu menu;
	menu.SetTitle("商品一覧表示");
	menu.SetSingle(true);
	menu.AddItem('1', "IDで並び替え", bind(GoodsSortByID, dvds));
	menu.AddItem('2', "タイトルで並び替え", bind(GoodsSortByTitle, dvds));
	menu.AddItem('3', "ジャンルで並び替え", bind(GoodsSortByGenre, dvds));
	menu.AddItem('4', "発売日で並び替え", bind(GoodsSortByReleaseDate, dvds));
	menu.AddItem('0', "商品情報管理メニューに戻る", bind(&Menu::Quit, &menu));
	
	menu.Run();
}


void GoodsSortByID(std::vector<const DVD*>& dvds) {
	Selector sel;
	
	sel.AddItem('1', "昇順");
	sel.AddItem('2', "降順");
	
	cout << "\nどの順で並び替えますか?\n";
	char input = sel.Run();
	
	if(input == '1') {
		sort(begin(dvds), end(dvds), [](const DVD* x, const DVD* y){ return x->mID < y->mID; });
	} else if(input == '2') {
		sort(begin(dvds), end(dvds), [](const DVD* x, const DVD* y){ return x->mID > y->mID; });
	}
	
	ShowGoodsList(dvds, true, true, false, false);
}

void GoodsSortByTitle(std::vector<const DVD*>& dvds) {
	Selector sel;
	
	sel.AddItem('1', "昇順");
	sel.AddItem('2', "降順");
	
	cout << "\nどの順で並び替えますか?\n";
	char input = sel.Run();
	
	if(input == '1') {
		sort(begin(dvds), end(dvds), [](const DVD* x, const DVD* y){ return x->mTitle < y->mTitle; });
	} else if(input == '2') {
		sort(begin(dvds), end(dvds), [](const DVD* x, const DVD* y){ return x->mTitle > y->mTitle; });
	}
	
	ShowGoodsList(dvds, true, true, false, false);
}

void GoodsSortByGenre(std::vector<const DVD*>& dvds) {
	Selector sel;
	
	sel.AddItem('1', "昇順");
	sel.AddItem('2', "降順");
	
	cout << "\nどの順で並び替えますか?\n";
	char input = sel.Run();
	
	if(input == '1') {
		sort(begin(dvds), end(dvds), [](const DVD* x, const DVD* y){ return x->mGenre < y->mGenre; });
	} else if(input == '2') {
		sort(begin(dvds), end(dvds), [](const DVD* x, const DVD* y){ return x->mGenre > y->mGenre; });
	}
	
	ShowGoodsList(dvds, true, true, true, false);
}

void GoodsSortByReleaseDate(std::vector<const DVD*>& dvds) {
	Selector sel;
	
	sel.AddItem('1', "昇順");
	sel.AddItem('2', "降順");
	
	cout << "\nどの順で並び替えますか?\n";
	char input = sel.Run();
	
	if(input == '1') {
		sort(begin(dvds), end(dvds), [](const DVD* x, const DVD* y){ return x->mReleaseDate < y->mReleaseDate; });
	} else if(input == '2') {
		sort(begin(dvds), end(dvds), [](const DVD* x, const DVD* y){ return x->mReleaseDate > y->mReleaseDate; });
	}
	
	ShowGoodsList(dvds, true, true, false, true);
}

// リスト表示
void ShowGoodsList(const vector<const DVD*>& dvds, bool id, bool title, bool genre, bool releaseDate) {
	vector<string> items;
	
	Paginator p;
	
	// ヘッダ
	ostringstream header;
	
	if(id) {
		header << "商品ID | ";
	}
	if(title) {
		header << "タイトル | ";
	}
	if(genre) {
		header << "ジャンル | ";
	}
	if(releaseDate) {
		header << "発売日";
	}
	p.SetHeaderText(header.str());
	
	// 各行
	for(auto dvd : dvds) {
		ostringstream row;
		
		if(id) {
			row << dvd->mID << " | ";
		}
		if(title) {
			row << dvd->mTitle << " | ";
		}
		if(genre) {
			row << dvd->mGenre << " | ";
		}
		if(releaseDate) {
			row << dvd->mReleaseDate;
		}
		
		p.AddItem(row.str());
	}
	
	p.SetReturnMessage("戻る");
	p.SetItemsPerPage(20);
	
	p.Run();
}
