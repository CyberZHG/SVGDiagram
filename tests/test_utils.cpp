#include "test_utils.h"

#include <regex>
#include <gtest/gtest.h>
using namespace std;

void compareSVGContent(const string& a, const string& b) {
    auto splitLines = [](const string& s) -> vector<string> {
        regex re("\r\n|\r|\n");
        sregex_token_iterator it(s.begin(), s.end(), re, -1);
        sregex_token_iterator end;
        return {it, end};
    };
    auto getContent = [splitLines](const string& s) -> vector<string> {
        vector<string> content;
        const auto lines = splitLines(s);
        for (const auto& line : lines) {
            if (!line.empty() && line[0] == ' ') {
                content.push_back(line);
            }
        }
        return content;
    };
    const auto contentA = getContent(a);
    const auto contentB = getContent(b);
    EXPECT_EQ(contentA.size(), contentB.size());
    for (int i = 0; i < min(contentA.size(), contentB.size()); ++i) {
        EXPECT_EQ(contentA[i], contentB[i]);
    }
}
