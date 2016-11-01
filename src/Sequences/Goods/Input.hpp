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
std::string InputGoodsTitle(const std::string& msg, DVD* dvd);
std::string InputGoodsGenre(const std::string& msg, DVD* dvd);
Date InputGoodsReleaseDate(const std::string& msg, DVD* dvd);
unsigned InputGoodsLendTime(const std::string& msg, DVD* dvd);
bool InputGoodsLendableFlag(const std::string& msg, DVD* dvd);
int InputGoodsPlace(const std::string& msg, DVD* dvd);

#endif
