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
        for (const auto lines = splitLines(s); const auto& line : lines) {
            if (line.empty()) {
                continue;
            }
            if (line[0] != ' ') {
                continue;
            }
            if (line.find("<!--") != std::string::npos) {
                continue;
            }
            content.push_back(line);
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
