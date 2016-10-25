//
//  Interface/IDInputer.hpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/21.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#ifndef Included_Interface_IDInputer_hpp
#define Included_Interface_IDInputer_hpp

#include <string>


class Member;

class MemberIDInputer {
public:
	MemberIDInputer(const std::string& text, bool allowCencel);
	~MemberIDInputer();
	
	std::string Input();
	Member* Find();	// キャンセルされた場合nullptr
	
private:
	std::string mText;
	bool mAllowCancel;
};

#endif /* IDInputer_hpp */
