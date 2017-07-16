#ifndef __RE2_MATCH_OBJECT_H__
#define __RE2_MATCH_OBJECT_H__

#include <re2/re2.h>
#include <re2/stringpiece.h>
#include <vector>

namespace re2
{

class MatchObject
{
public:
    MatchObject(bool matched=false) : _matched(matched), _re(nullptr) {}

    MatchObject(re2::RE2 *re, re2::StringPiece text, re2::StringPiece *groups, size_t ngroups);

    bool has_matched() { return _matched; }

    bool has_detail() { return _matched && _re != nullptr && _groups.size() > 0;}

    const re2::StringPiece group(int group_index=0) {return _groups.at(group_index);}

    const re2::StringPiece group(std::string group_name);

    const std::string string() { return _string.as_string(); }

    size_t start(int group_index=0);

    size_t start(std::string group_name);

    size_t end(int group_index=0);

    size_t end(std::string group_name);

protected:

    bool _matched;
    re2::RE2 *_re;
    re2::StringPiece _string;
    std::vector<re2::StringPiece> _groups;
};

} // namespace re2

#endif  // __RE2_MATCH_OBJECT_H__
