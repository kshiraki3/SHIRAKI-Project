//
//  Interface/Menu.hpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/20.
//	Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#ifndef Included_Interface_Menu_hpp
#define Included_Interface_Menu_hpp

#include <functional>
#include <initializer_list>
#include <string>
#include <vector>

// メニューアクション
typedef std::function<void()> MenuAction;

// メニュー項目
struct MenuItem {
	char mCommand;	// 入力コマンド
	std::string mText;	// 表示テキスト
	MenuAction mAction;	// アクション
};

// メニュー
class Menu {
public:
	Menu();
	Menu(const std::string& title, const std::initializer_list<MenuItem>& items);
	~Menu();
	
	// 制御
	void Run();
	void Quit();
	
	// 設定
	void SetTitle(const std::string& title);
	void SetCustomText(const std::function<void()>& showText);
	
	void AddItem(const MenuItem& items);
	void AddItem(char command, const std::string& text, const MenuAction& action);
	
private:
	bool mQuit;
	std::string mTitle;
	std::function<void()> mShowText;
	std::vector<MenuItem> mItems;
};

#endif
