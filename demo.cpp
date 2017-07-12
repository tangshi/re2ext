#include <iostream>
#include <re2/re2.h>
#include <vector>
#include <string>
#include "re2ext.h"

using namespace std;
using namespace re2;

int main(int argc, char *argv[])
{
    locale::global(locale(""));

    string str1 = u8"123 456 78 hello";
    RE2 re1("(\\d+\\s)+(?P<word>\\w+)");
    MatchObject mb1 = match(str1, re1, true);
    if (mb1.has_detail())
    {
        cout << "string: " << mb1.string() << endl;
        cout << "group: " << mb1.group().as_string() << endl;
        cout << "span: (" << mb1.start() << ", " << mb1.end() << ")" << endl;
        cout << "group(1): " << mb1.group(1).as_string() << endl;
        cout << "group(2): " << mb1.group(2).as_string() << endl;
        cout << "group('word'): " << mb1.group("word").as_string() << endl;
    }

    string str2 = u8"1991年7月1日香港回归！";
    RE2 re2("[\u4e00-\u9fa5]{2,}");
    MatchObject mb2 = search(str2, re2, true);
    cout << "string: " << mb2.string() << endl;
    cout << "group: " << mb2.group().as_string() << endl;
    cout << "span: (" << mb2.start() << ", " << mb2.end() << ")" << endl;

    string str3 = u8"1991年7月1日香港回归！";
    RE2 re3("\\d+");
    string out3 = sub(str3, re3, u8"数字");
    cout << out3 << endl;

    string str4 = u8"100 + 10";
    RE2 re4("\\d+");
    string out4 = sub(str4, re4, [](MatchObject &mb) -> std::string {
        StringPiece sp = mb.group();
        if (sp.size() == 3)
        {
            return u8"一百";
        }
        else
        {
            return u8"十";
        }
    });
    cout << out4 << endl;

    string str5 = u8"123abc45de6fg789h000ijk";
    RE2 re5("\\d+|[a-z]+");
    auto all = findall(str5, re5);

    for (auto &one : all) {
        cout << one << endl;
    }

    return 0;
}
