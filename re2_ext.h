#ifndef __RE2_EXTENSION_H__
#define __RE2_EXTENSION_H__

#include <string>
#include <functional>
#include <vector>
#include <re2/re2.h>
#include "matchobject.h"

MatchObject match(const std::string &string, re2::RE2 &pattern, bool detail=false);

MatchObject search(const std::string &string, re2::RE2 &pattern, bool detail=false);

std::vector<std::string> findall(const std::string &string, re2::RE2 &pattern);

std::string sub(const std::string &string, re2::RE2 &pattern, const std::string repl);

std::string sub(const std::string &string, re2::RE2 &pattern, std::function<std::string(MatchObject&)> repl);


#endif // __RE2_EXTENSION_H__
