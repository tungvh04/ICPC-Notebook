/**
 * Author: FireGhost
 * Date: 2022-06-12
 * License: Unknown
 * Description: Builds suffix array for a string.
#pragma once

struct SuffixArray {
    int n;
    vector<int> p, rank, lcp;
    SuffixArray(string s, int lim = 256) {
        vector<int> p2, rank2, cnt;
        n = s.size();
        p = p2 = rank = rank2 = lcp = vector<int>(n + 1, 0);
        cnt = vector<int>(max(n, lim), 0);
        REP(i, 0, n) rank[i] = s[i], p[i] = i;

        for(int h = 0; h < n; h ? h <<= 1 : ++h) {
            fill(cnt.begin(), cnt.begin() + n, 0);
            REP(i, 0, n) ++cnt[rank[i]];
            REP(i, 1, cnt.size()) cnt[i] += cnt[i - 1];
            REPD(i, n, 0) {
                int j = (p[i] - h + n) % n;
                p2[--cnt[rank[j]]] = j;
            }
            swap(p, p2); rank2[p[0]] = 0;
            REP(i, 1, n) rank2[p[i]] = rank2[p[i - 1]] + (rank[p[i]] != rank[p[i-1]] || rank[(p[i] + h) % n] != rank[(p[i-1] + h) % n]);
            swap(rank, rank2);
        }
        /// LCP
        int d = 0;
        REP(i, 0, n) if (rank[i]) {
            int j = p[rank[i] - 1];
            while (s[i + d] == s[j + d]) ++d;
            lcp[rank[i]] = d;
            d -= bool(d);
        }
    }
};
