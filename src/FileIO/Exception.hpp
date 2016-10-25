//
//  FileIO/Exception.hpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/22.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#ifndef Included_FileIO_Exception_hpp
#define Included_FileIO_Exception_hpp

#include <stdexcept>

class FileOpenException : std::runtime_error {
public:
	FileOpenException();
	
private:
};

#endif /* Exception_hpp */
