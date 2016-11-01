//
//  Sequences/Members/Input.hpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/27.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#ifndef Included_Sequences_Members_Input_hpp
#define Included_Sequences_Members_Input_hpp

#include "Record/Member.hpp"

std::string InputMemberID(const std::string& msg, Member* member, bool allowCancel = false);
std::string InputMemberName(const std::string& msg, Member* member);
std::string InputMemberAddress(const std::string& msg, Member* member);
std::string InputMemberPhoneNumber(const std::string& msg, Member* member);
Date InputMemberBirthday(const std::string& msg, Member* member);

#endif
