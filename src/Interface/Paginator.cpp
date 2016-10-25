//
//  Interface/Paginator.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/25.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Interface/Paginator.hpp"
#include <iostream>

using namespace std;


Paginator::Paginator() : mPage(0), mReturnMessage("戻る") {
	
}

Paginator::Paginator(const std::initializer_list<std::string>& items) : mPage(0), mItems(items), mReturnMessage("戻る") {
	
}

Paginator::~Paginator() {
	
}

void Paginator::AddItem(const std::string& item) {
	
}

void Paginator::SetItemsPerPage(int n) {
	mItemsPerPage = n;
}

void Paginator::SetSelectionHandler(const std::function<void(int)>& handler) {
	mHandler = handler;
}

void Paginator::SetReturnMessage(const std::string& msg) {
	mReturnMessage = msg;
}

void Paginator::Run() {
	bool quit = false;
	
	while(!quit) {
		for(int i = mPage * mItemsPerPage; i < mItems.size() && i < (mPage + 1) * mItemsPerPage; ++i) {
			if(mHandler) {
				cout << static_cast<char>('1' + (i - mPage * mItemsPerPage)) << ". ";
			}
			cout << mItems[i] << "\n";
		}
		
		if(mItems.size() > (mPage + 1) * mItemsPerPage) {
			cout << "n. 次のページへ\n";
		}
		if(mPage > 0) {
			cout << "p. 前のページへ\n";
		}
		
		cout << "0. " << mReturnMessage << "\n\n";
		
		// 入力
		char input;
		
		cout << "入力> ";
		cin >> input;
		
		// 処理
		switch(input) {
			case '1'...'9':
				if(mHandler) {
					mHandler(input - '1' + mPage * mItemsPerPage);
				}
				break;
				
			case 'p':
			case 'P':
				if(mPage > 0) {
					--mPage;
				}
				break;
				
			case 'n':
			case 'N':
				if(mItems.size() > (mPage + 1) * mItemsPerPage) {
					++mPage;
				}
				break;
				
			case '0':
				quit = true;
				break;
		}
	}
}
