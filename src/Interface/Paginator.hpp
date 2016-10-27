//
//  Interface/Paginator.hpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/25.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#ifndef Included_Interface_Paginator_hpp
#define Included_Interface_Paginator_hpp

#include <functional>
#include <initializer_list>
#include <vector>
#include <string>


// リスト表示のページ分けを行う
class Paginator {
public:
	Paginator();
	explicit Paginator(const std::initializer_list<std::string>& items);
	template<typename InputIterator> Paginator(InputIterator begin, InputIterator end);
	~Paginator();
	
	void AddItem(const std::string& item);
	void SetHeaderText(const std::string& text);
	void SetItemsPerPage(int n);
	void SetSelectionHandler(const std::function<void(int)>& handler);
	void SetReturnMessage(const std::string& msg);
	
	void Run();
	
private:
	std::vector<std::string> mItems;
	std::function<void(int)> mHandler;
	
	int mPage;
	int mItemsPerPage;
	std::string mHeaderText;
	std::string mReturnMessage;
};


template<typename InputIterator> Paginator::Paginator(InputIterator begin, InputIterator end) : mPage(0), mItems(begin, end), mReturnMessage("戻る") {
	
}

#endif
