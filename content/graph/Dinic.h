/**
 * Author: FireGhost
 * Date: 2022-11-08
 * Description: ez pz
 */

// Usage:
//   Dinitz dinic(n); // 0-based and 1-based
//   dinic.addEdge(u, v, cap, reverseCap) // 1-direction and 2-direction
//   dinic.getFlow(s, t) --> maxflow s->t
// Time: O(V^2 E)
struct Dinitz {
	struct Edge {
		int to, cap;
		Edge(int to = 0, int cap = 0) : to(to), cap(cap) {}
	};
	int n, s, t;
	vector<vector<int>> g;
	vector<Edge> edge;
	vector<int> dist, q;
	vector<vector<int>::iterator> cur;

	Dinitz(int n = 0) : n(n), g(n + 1), dist(n + 1), q(n + 1), cur(n + 1) {}
	void addEdge(int u, int v, int cap, int reverseCap = 0) {
		g[u].push_back(edge.size());
		edge.emplace_back(v, cap);
		g[v].push_back(edge.size());
		edge.emplace_back(u, reverseCap);
	}
	int getFlow(int _s, int _t) {
		s = _s, t = _t;
		int flw = 0;
		while (bfs()) {
			for (int i = 0; i <= n; ++i)
				cur[i] = g[i].begin();
			flw += dfs(s, INT_MAX);
		}
		return flw;
	}

private:
	bool bfs() {
		int ql = 0, qr = 0;
		dist.assign(n + 1, -1);
		dist[s] = 0;
		q[qr++] = s;
		while (ql < qr && dist[t] == -1) {
			int u = q[ql++];
			for (int i : g[u]) {
				int v = edge[i].to;
				if (dist[v] == -1 && edge[i].cap) {
					dist[v] = dist[u] + 1;
					q[qr++] = v;
				}
			}
		}
		return dist[t] != -1;
	}
	int dfs(int u, int flowIn) {
		if (u == t || !flowIn) return flowIn;

		int flowOut = 0;
		for (; cur[u] != g[u].end(); ++cur[u]) {
			int i = *cur[u];
			if (dist[edge[i].to] == dist[u] + 1 && edge[i].cap) {
				int flw = dfs(edge[i].to, min(flowIn, edge[i].cap));
				flowOut += flw;
				flowIn -= flw;
				edge[i].cap -= flw;
				edge[i ^ 1].cap += flw;
				if (!flowIn) break;
			}
		}
		return flowOut;
	}
};
