//
//  Utility.hpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/27.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#ifndef Included_Utility_hpp
#define Included_Utility_hpp

#include <cstdio>
#include <string>

template<typename... Args> std::string Sprintf(const std::string& fmt, Args... args) {
	char buf[256];
	snprintf(buf, 256, fmt.c_str(), args...);
	return std::string(buf);
}

#endif /* Utility_hpp */
