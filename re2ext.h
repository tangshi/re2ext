#ifndef RE2_EXTENSION_H_
#define RE2_EXTENSION_H_

#include <string>
#include <functional>
#include <vector>
#include <re2/re2.h>
#include "matchobject.h"

namespace re2 {

/** match `text` at beginning against `pattern`
 *
 * @param detail specify weather the returned MatchObject should store detail info or not, if true
 *        you can get the detail info of the match result by invoking MatchObject methods like
 *        MatchObject::group MatchObject::string MatchObject::start MatchObject::end etc.
 * @param offset specify the beginning of the `text` to be matched. usually it's **0**
 */
MatchObject match(const std::string &text, re2::RE2 &pattern, bool detail=false, size_t offset=0);

MatchObject search(const std::string &text, re2::RE2 &pattern, bool detail=false, size_t offset=0);

/** find all non-overlapping substrings in the `text` that match the `pattern`
 *
 * @return a vector of matched substrings
 */
std::vector<std::string> findall(const std::string &text, re2::RE2 &pattern, size_t offset=0);

/** replacing the leftmost non-overlapping occurrences
 *  of the pattern in `text` by the replacement string `repl`
 *
 * @return the string obtained after replacing
 */
std::string sub(const std::string &text, re2::RE2 &pattern, const std::string repl);

/** overload of sub function, except replacing occurrences of the pattern
 *  by the the result of the callable function parameter `repl`
 */
std::string sub(const std::string &text, re2::RE2 &pattern, std::function<std::string(MatchObject&)> repl);

}


#endif // RE2_EXTENSION_H_
