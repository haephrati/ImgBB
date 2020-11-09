#include "stdafx.h"
#include "../../JSON.h"
#include "../../JSONValue.h"
#include "../../StringProcess.h"

namespace
{
    int g_failed = 0;
    int g_passed = 0;

    void Expect(bool cond, const char* name)
    {
        if (cond)
        {
            ++g_passed;
            std::cout << "PASS " << name << std::endl;
        }
        else
        {
            ++g_failed;
            std::cout << "FAIL " << name << std::endl;
        }
    }
}

int main()
{
    Expect(Trim(L"  abc  ", L" ") == L"abc", "Trim strips spaces");
    Expect(ReplaceString(L"a-b-a", L"-", L"_") == L"a_b_a", "ReplaceString replaces all");
    Expect(StringToInteger(L"1,024") == 1024, "StringToInteger drops commas");
    Expect(FilterFileName(L"a/b:c*.png") == L"a_b_c_.png", "FilterFileName replaces reserved chars");
    Expect(GetHost(L"http://api.imgbb.com/1/upload") == L"api.imgbb.com", "GetHost from ImgBB API URL");

    JSONValue* ok = JSON::Parse(L"{\"success\":true,\"status\":200}");
    Expect(ok != nullptr && ok->IsObject(), "parse ImgBB-style object");
    if (ok)
    {
        JSONValue* success = ok->Child(L"success");
        JSONValue* status = ok->Child(L"status");
        Expect(success && success->IsBool() && success->AsBool(), "success is true");
        Expect(status && status->IsNumber() && status->AsNumber() == 200.0, "status is 200");
        delete ok;
    }

    JSONValue* bad = JSON::Parse(L"{not json");
    Expect(bad == nullptr, "invalid JSON returns null");

    std::cout << g_passed << " passed, " << g_failed << " failed" << std::endl;
    return g_failed == 0 ? 0 : 1;
}
