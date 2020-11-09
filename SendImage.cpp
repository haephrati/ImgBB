// SendImage.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <atlbase.h>
#include <iostream>

#include <string>
#include "imgbb.h"

#define API_KEY L"43d965d6bf63c2d0a78e09a83ccb19ff" // <PLACE HERE YOUR API KEY>

int main()
{
	wprintf(L"Demo of uploading an image to ImgBB\n");
	std::wstring imagePath = L"running.jpg";
	std::wstring url = ImgBBUpload(imagePath, API_KEY);
	ShellExecute(GetActiveWindow(), L"OPEN", url.c_str(), NULL, NULL, TRUE);
	MessageBox(NULL, url.c_str(), L"Opening image from ", MB_OK);
}

