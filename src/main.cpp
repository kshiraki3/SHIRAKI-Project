//
//  main.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/09.
//	Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Sequences/StuffMainMenu.hpp"
#include "Utility.hpp"
#include <iostream>

using namespace std;


int main() {
	try {
		StuffMainMenu();
	} catch(const SPException& exception) {
		cerr << "!! エラー発生 !!\n";
		cerr << exception.what() << "\n";
	}
	
	return 0;
}
