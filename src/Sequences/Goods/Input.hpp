//
//  Sequences/Goods/Input.hpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/27.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#ifndef Included_Sequences_Goods_Input_hpp
#define Included_Sequences_Goods_Input_hpp

#include "Record/DVD.hpp"


std::string InputGoodsID(const std::string& msg, DVD* dvd, bool allowCancel = false);

#endif
