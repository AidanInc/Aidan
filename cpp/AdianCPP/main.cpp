// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>c
#include "Reader.h"
int main()
{
    BinaryReader* r = new BinaryReader("./model.ALI");

    while (!r->endOfFile()) {
        std::cout << "Read Int: " << r->readInt() << std::endl;
		std::cout << "peek: " << r->peekNext() << std::endl;


    }

    system("PAUSE");
}
