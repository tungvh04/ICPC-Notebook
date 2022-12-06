/**
 * Author: FireGhost
 * Date: 2022-11-08
 * Description: ez pz
 */

// Usage:
//   HopcroftKarp mat(m, n);
//   - X[1..m] and Y[1..n]  // 1-based
//   mat.addEdge(u, v)      // X[u] -> Y[v]
//   mat.MaxMatching() --> maximum matching X and Y
//
//  Note:
//  - Only Bipartite Graph
//
// Time: O(sqrt(V) E)
struct HopcroftKarp {
	int m, n; // X : 1..m, Y : 1..n
	vector<vector<int>> g;
	vector<int> dist, mX, mY, q;
	vector<bool> Select[2]; // remove if not using Konig
	HopcroftKarp(int m = 0, int n = 0)
		: m(m), n(n), dist(m + 1), mX(m + 1, 0), mY(n + 1, 0), g(m + 1), q(m + 1) {}

	void addEdge(int u, int v) { g[u].push_back(v); }
	int MaxMatching() {
		int cnt = 0;
		while (bfs())
			for (int i = 1; i <= m; ++i)
				if (!mX[i] && dfs(i)) ++cnt;
		return cnt;
	}
	void Konig(); // remove if not using Konig

private:
	bool bfs() {
		int ql = 0, qr = 0;
		for (int i = 1; i <= m; ++i) {
			if (!mX[i]) {
				dist[i] = 0;
				q[qr++] = i;
			}
			else dist[i] = -1;
		}

		dist[0] = -1;
		while (ql < qr) {
			int u = q[ql++];
			for (int v : g[u]) {
				if (dist[mY[v]] == -1) {
					dist[mY[v]] = dist[u] + 1;
					q[qr++]		= mY[v];
				}
			}
		}
		return dist[0] != -1;
	}
	bool dfs(int u) {
		if (u == 0) return true;
		for (int v : g[u]) {
			if (dist[mY[v]] == dist[u] + 1 && dfs(mY[v])) {
				mX[u] = v, mY[v] = u;
				dist[u] = -1;
				return true;
			}
		}
		dist[u] = -1;
		return false;
	}
};
