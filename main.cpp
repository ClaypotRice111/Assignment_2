//============================================================================
// Description
//============================================================================
// File Name	: Assigment_2
// Author		: Weihao Huang
// Goal			: Develop an inventory management system for an electronics store. 
//                Implement a two-dimensional array that contains objects inherited 
//				  from a base class, utilizing static_cast for type conversion.
//============================================================================
/*Copyright (c) 2024 Weihao Huang

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files (the "Software"), to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and
to permit persons to whom the Software is furnished to do so, subject to the following conditions:

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/
//==========================================================================



/*
Can't use visual studio 2022. Always glitching.
https://github.com/ClaypotRice111/Assignment_2.git

folder tree
──assigment_2
	├── main.cpp
	└── includes
		├── product.h
		├── product.cpp
		├── system.h
		└── system.cpp

your building path
	├── main.exe
	└── defualt.txt
*/



#include <iostream>
#include "includes/system.h"

using namespace std;




int main(int argc, char* argv[]) {

    InventorySystem ManagementSystem("Seven");
	ManagementSystem.Run();

	return 0;
}


