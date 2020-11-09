#include "imgbb.h"

#include "WinHTTPClient.h"

#include <Wincrypt.h>
#pragma comment (lib, "Crypt32.lib")

#include "JSON.h"

bool EmptyProgressProc(double percent)
{
	return true;
}

std::wstring ImgBBUpload(std::wstring imagepath, std::wstring apikey)
{
	std::wstring returnUrl = L"";
	std::wstring duration = L"600";
	std::wstring boundary = L"------------ImgBB_Uploader_28083191_Code_";
	for (int i = 1; i < 20; i++)
		boundary += L'A' + rand() % 26;

	const std::string bound(boundary.begin(), boundary.end());

	DWORD dwBytesRead;
	HANDLE hFile = CreateFile(imagepath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwFileSize = GetFileSize(hFile, &dwFileSize);
		BYTE *imageContent = new BYTE[dwFileSize];
		ReadFile(hFile, imageContent, dwFileSize, &dwBytesRead, NULL);
		CloseHandle(hFile);

		DWORD nLenOut = dwFileSize * 2;
		char* pDst = new char[nLenOut];
		CryptBinaryToStringA((const BYTE*)imageContent, dwFileSize, CRYPT_STRING_BASE64, pDst, &nLenOut);

		std::string body = "";
		body = "--" + bound + "\r\n";
		body += "Content-Disposition: form-data; name=\"image\"\r\n\r\n";
		body += pDst;

		delete pDst;
		body += "--" + bound + "--\r\n";

		std::wstring url = L"https://api.imgbb.com/1/upload?expiration=" + duration + L"&key=" + apikey;
		WinHttpClient client(url, &EmptyProgressProc);
		client.SetUserClient(L"ImgBB Uploader 28083191 v.1");
		client.SetAdditionalRequestHeaders(L"Content-Type: multipart/form-data; boundary=" + boundary);
		client.SetAdditionalDataToSend((BYTE*)body.c_str(), body.size());
		client.SendHttpRequest(L"POST");
		delete imageContent;
		std::wstring response = client.GetResponseContent();

		JSONValue* pValue = JSON::Parse(response.c_str());
		if (pValue)
		{
			returnUrl = L"JSON ERROR: Not found data in response";

			JSONValue* data = pValue->Child(L"data");
			if (data)
			{
				if (data->Child(L"url"))
					returnUrl = data->Child(L"url")->AsString();
			}
			else
			{
				JSONValue* error = pValue->Child(L"error");
				if (error)
				{
					if (error->Child(L"message"))
						returnUrl = L"API ERROR: " + error->Child(L"message")->AsString();
				}
			}
			delete pValue;
		}
		else
		{
			returnUrl = L"JSON ERROR: Malformed response form server";
		}

		return returnUrl;
	}
	else
	{
		return L"FILE ERROR: Cannot open file";
	}
}