/**
 * Author: Monarchuwu
 * Date: 2023-11-30
 * License: CC0
 * Description: ez pz
 * Time: O(n)
 * Status: Tested on https://codeforces.com/contest/346/submission/235078151
 */
#pragma once

int p[N], nxt[N][26];
void buildKMPTable(string s) {
  for (int i = 1; i < s.size(); ++i) {
    p[i] = p[i - 1];
    while (p[i] > 0 && s[i] != s[p[i]]) p[i] = p[p[i] - 1];
    if (s[i] == s[p[i]]) ++p[i];
  }
}
void buildAutomaton(string s) {
  buildKMPTable(s);
  nxt[0][s[0] - 'A'] = 1;
  for (int i = 1; i < s.size(); ++i)
    for (int c = 0; c < 26; ++c)
      nxt[i][c] = (s[i] == ('A' + c) ? i + 1 : nxt[p[i - 1]][c]);
}