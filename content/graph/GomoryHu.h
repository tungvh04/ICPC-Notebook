/**
 * Author: FireGhost
 * Date: 2022-11-08
 * Description: ez pz
 */

// Usage:
//   GomoryHu g(n); // 0-based
//   g.addEdge(u, v, c)  // 1-direction, using cap[u][v] += c
//   g.calc()
//   --> g.minCut[i][j] = min cut i-j
//
// Note:
// - Used together with Dinic.h
struct GomoryHu { // 0-based
	vector<bool> ok;
	vector<int> parent;
	vector<vector<int>> cap, minCut;
	int n;
	Dinitz flow;

	GomoryHu(int n = 0)
		: n(n), flow(n), ok(n), parent(n, 0), cap(n, vector<int>(n, 0)), minCut(n, vector<int>(n, INT_MAX)) {}

	void addEdge(int u, int v, int c) { // 1-direction
		cap[u][v] += c;
	}
	void calc() {
		for (int i = 1; i < n; ++i) {
			flow = Dinitz(n); // reset Dinitz
			for (int u = 0; u < n; ++u)
				for (int v = 0; v < n; ++v)
					if (cap[u][v]) flow.addEdge(u, v, cap[u][v]);

			int mf = flow.getFlow(i, parent[i]);
			bfs(i);
			for (int j = i + 1; j < n; ++j)
				if (ok[j] && parent[j] == parent[i])
					parent[j] = i;

			minCut[i][parent[i]] = minCut[parent[i]][i] = mf;
			for (int j = 0; j < i; ++j)
				minCut[i][j] = minCut[j][i] = min(mf, minCut[parent[i]][j]);
		}
	}

private:
	void bfs(int start) {
		fill(ok.begin(), ok.end(), false);
		queue<int> q;
		q.push(start);
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			for (int id : flow.g[u]) {
				int v = flow.edge[id].to;
				if (!ok[v] && flow.edge[id].cap) {
					ok[v] = true;
					q.push(v);
				}
			}
		}
	}
};
