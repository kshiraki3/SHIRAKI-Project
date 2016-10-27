//
//  Sequences/Stores/Input.hpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/26.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#ifndef Included_Sequences_Stores_Input_hpp
#define Included_Sequences_Stores_Input_hpp

#include "Record/Store.hpp"
#include <string>

int InputStoreID(const std::string& msg, Store* store);
std::string InputStoreName(const std::string& msg, Store* store);

#endif
