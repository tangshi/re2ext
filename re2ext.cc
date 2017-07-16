#include "re2ext.h"
#include "utf.h"

using namespace std;

namespace re2
{

MatchObject apply(StringPiece text, re2::RE2 &pattern, re2::RE2::Anchor anchor, int n_groups=-1, size_t offset=0);


MatchObject match(const std::string &text, re2::RE2 &pattern, bool detail, size_t offset)
{
    int n_groups = detail ? -1 : 0;
    return apply(text, pattern, re2::RE2::ANCHOR_START, n_groups, offset);
}

MatchObject search(const std::string &text, re2::RE2 &pattern, bool detail, size_t offset)
{
    int n_groups = detail ? -1 : 0;
    return apply(text, pattern, RE2::UNANCHORED, n_groups, offset);
}

std::vector<std::string> findall(const std::string &text, re2::RE2 &pattern, size_t offset)
{
    std::vector<std::string> vec;
    StringPiece sp(text);

    while(true)
    {
        MatchObject mb = apply(sp, pattern, re2::RE2::UNANCHORED, 1, offset);
        if (!mb.has_matched())
        {
            break;
        }

        std::string found = mb.group().as_string();
        vec.push_back(found);

        sp.remove_prefix(mb.end());
    }

    return vec;
}

std::string sub(const std::string &text, re2::RE2 &pattern, const std::string repl)
{
    std::string out_string(text);

    re2::RE2::GlobalReplace(&out_string, pattern, repl);

    return out_string;
}

std::string sub(const std::string &text, re2::RE2 &pattern, std::function<std::string(MatchObject&)> repl)
{
    const char* p = text.data();
    const char* ep = p + text.size();
    const char* lastend = NULL;
    std::string out;

    while (p <= ep)
    {
        MatchObject mb = apply(p, pattern, re2::RE2::UNANCHORED);
        if (!mb.has_matched())
        {
            break;
        }

        size_t start = mb.start();
        if (start > 0)
        {
            out.append(p, mb.start());
        }

        StringPiece matched = mb.group(0);
        if (matched.begin() == lastend && matched.size() == 0)
        {
            // Disallow empty match at end of last match: skip ahead.
            //
            // fullrune() takes int, not size_t. However, it just looks
            // at the leading byte and treats any length >= 4 the same.
            if (pattern.options().encoding() == re2::RE2::Options::EncodingUTF8 &&
                fullrune(p, static_cast<int>(std::min(static_cast<ptrdiff_t>(4), ep - p))))
            {
                // re is in UTF-8 mode and there is enough left of str
                // to allow us to advance by up to UTFmax bytes.
                Rune r;
                int n = chartorune(&r, p);
                // Some copies of chartorune have a bug that accepts
                // encodings of values in (10FFFF, 1FFFFF] as valid.
                if (r > Runemax)
                {
                    n = 1;
                    r = Runeerror;
                }
                if (!(n == 1 && r == Runeerror))
                {  // no decoding error
                    out.append(p, n);
                    p += n;
                    continue;
                }
            }
            // Most likely, pattern is in Latin-1 mode. If it is in UTF-8 mode,
            // we fell through from above and the GIGO principle applies.
            if (p < ep)
            {
                out.append(p, 1);
            }
            p++;
            continue;
        }

        out.append(repl(mb));
        p = matched.end();
        lastend = p;
    }

    if (p < ep)
    {
        out.append(p, ep - p);
    }

    return out;
}

MatchObject apply(StringPiece text, re2::RE2 &pattern, re2::RE2::Anchor anchor, int n_groups, size_t offset)
{
    StringPiece *groups = nullptr;

    if (n_groups < 0)
    {
        n_groups = pattern.NumberOfCapturingGroups() + 1;
    }

    if (n_groups > 0)
    {
        groups = new StringPiece[n_groups];
    }

    bool matched = pattern.Match(
                text,
                offset,
                text.size(),
                anchor,
                groups,
                n_groups);

    if (groups == nullptr)
    {
        return MatchObject(matched);
    }
    else
    {
        if (!matched)
        {
            MatchObject match_obj = MatchObject(false);
            delete[] groups;
            return match_obj;
        }
        else
        {
            MatchObject match_obj = MatchObject(&pattern, text, groups, n_groups);
            delete[] groups;
            return match_obj;
        }
    }
}

} // namespace re2
