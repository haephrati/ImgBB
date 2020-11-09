# ImgBB
Demonstration by Michael Haephrati showing the process of uploading an image to ImgBB from a C++ application.
The code uses https://api.imgbb.com/

`ImgBBUpload` in `imgbb.cpp` posts the file through WinHTTP. Helpers in `StringProcess.h` trim, replace, and parse host names; `JSON.cpp` / `JSONValue.cpp` decode the API response.

## Unit tests

`Tests/ImgBBTests` compiles production `JSON.cpp` and `JSONValue.cpp` and exercises `Trim`, `ReplaceString`, `StringToInteger`, `FilterFileName`, and `GetHost` from `StringProcess.h`, plus parsing of an ImgBB-style JSON object. Build **Release | x64** and run `ImgBBTests.exe`.
