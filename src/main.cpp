//
//  main.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/09.
//	Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include <iostream>
using namespace std;

#include "Interface/Paginator.hpp"


int main() {
	Paginator p({
		"item 01", "item 02", "item 03", "item 04", "item 05",
		"item 06", "item 07", "item 08", "item 09", "item 10",
		"item 11", "item 12", "item 13", "item 14", "item 15"
	});
	
	p.SetItemsPerPage(9);
	p.SetSelectionHandler([&](int select){
		cout << select << " selected\n";
	});
	
	p.Run();
	
	return 0;
}
