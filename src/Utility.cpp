//
//  Utility.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/27.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Utility.hpp"


SPException::SPException(const std::string& what) : std::runtime_error(what) {
	
}

SPException::~SPException() {
	
}
