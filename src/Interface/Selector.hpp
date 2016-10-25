//
//  Interface/Selector.hpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/20.
//	Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#ifndef Included_Interface_Selector_hpp
#define Included_Interface_Selector_hpp

#include <initializer_list>
#include <string>
#include <vector>


// 選択項目
struct SelectItem {
	char mCommand;	// 入力コマンド
	std::string mText;	// 表示テキスト
};


// 選択メニュー
class Selector {
public:
	Selector();
	Selector(const std::initializer_list<SelectItem>& items);
	~Selector();
	
	char Run();
	
	void AddItem(const SelectItem& item);
	void AddItem(char command, const std::string& text);
	
private:
	std::vector<SelectItem> mItems;
};

#endif
