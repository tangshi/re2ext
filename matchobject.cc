#include <string>
#include "matchobject.h"

using namespace std;
using namespace re2;

MatchObject::MatchObject(RE2 *re, StringPiece text, StringPiece *groups, size_t ngroups) :
    _matched(true),
    _re(re),
    _string(text)
{
    for (size_t i = 0; i < ngroups; ++i)
    {
        _groups.push_back(groups[i]);
    }
}

const re2::StringPiece MatchObject::group(std::string group_name)
{
    int group_index = _re->NamedCapturingGroups().at(group_name);
    return group(group_index);
}

size_t MatchObject::start(int group_index)
{
    StringPiece sp = group(group_index);
    return (sp.begin() - _string.begin());
}

size_t MatchObject::start(std::string group_name)
{
    int group_index = _re->NamedCapturingGroups().at(group_name);
    return start(group_index);
}

size_t MatchObject::end(int group_index)
{
    StringPiece sp = group(group_index);
    return (sp.end() - _string.begin());
}

size_t MatchObject::end(std::string group_name)
{
    int group_index = _re->NamedCapturingGroups().at(group_name);
    return end(group_index);
}