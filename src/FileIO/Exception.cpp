//
//  FileIO/Exception.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/22.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "FileIO/Exception.hpp"


FileOpenException::FileOpenException() : std::runtime_error("ファイルのオープンに失敗しました。") {
	
}
