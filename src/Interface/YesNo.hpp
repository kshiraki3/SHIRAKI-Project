//
//  Interface/YesNo.hpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/20.
//  Copyright (C) 2016 SHIRAKI System. All rights reserved.
//

#ifndef Included_Interface_YesNo_hpp
#define Included_Interface_YesNo_hpp

#include <string>


class YesNo {
public:
	YesNo();
	explicit YesNo(const std::string& text);
	~YesNo();
	
	bool Run();
	
	void SetText(const std::string& text);
	
private:
	std::string mText;
};

#endif /* YesNo_hpp */
