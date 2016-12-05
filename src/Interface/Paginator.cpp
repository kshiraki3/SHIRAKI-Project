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
	mItems.push_back(item);
}

unsigned Paginator::ItemCount() const {
	return static_cast<unsigned>(mItems.size());
}

void Paginator::SetHeaderText(const std::string& text) {
	mHeaderText = text;
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
	mQuit = false;
	
	while(!mQuit) {
		if(!mHeaderText.empty()) {
			cout << mHeaderText << "\n";
		}
		
		for(int i = mPage * mItemsPerPage; i < mItems.size() && i < (mPage + 1) * mItemsPerPage; ++i) {
			if(mHandler) {
				cout << static_cast<char>('1' + (i - mPage * mItemsPerPage)) << ". ";
			}
			cout << mItems[i] << "\n";
		}
		
		cout << "\n";
		
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
				if((input - '1' + mPage * mItemsPerPage < mItems.size()) && mHandler) {
					mHandler(input - '1' + mPage * mItemsPerPage);
				} else {
					cout << "入力が間違っています。\n";
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
				this->Quit();
				break;
		}
	}
}

void Paginator::Quit() {
	mQuit = true;
}
