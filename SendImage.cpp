// SendImage.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <iostream>

#include <string>
#include "imgbb.h"

#define API_KEY L"<PLACE HERE YOUR API KEY>"

int main()
{
    std::cout << "Demo of uploading an image to ImgBB\n";
	std::wstring imagePath = L"107705921_988368374919704_2553169134592330136_n.jpg";
	std::wstring url = ImgBBUpload(imagePath, API_KEY);
	MessageBox(NULL, url.c_str(), L"", MB_OK);
}

