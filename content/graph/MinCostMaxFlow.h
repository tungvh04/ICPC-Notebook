/**
 * Author: FireGhost
 * Date: 2022-11-08
 * Description: ez pz
 */

// Usage:
//   MincostMaxflow flow(n); // 0-based and 1-based
//   flow.addEdge(u, v, cap, reverseCap)  // 1-direction and 2-direction
//   flow.getMinCostMaxFlow(s, t) --> pair(cost, flow)
struct MincostMaxflow {
	struct Edge {
		int to, cap, flw, cost;
		Edge(int to = 0, int cap = 0, int flw = 0, int cost = 0) : to(to), cap(cap), flw(flw), cost(cost) {}
		int residual() { return cap - flw; }
	};
	int n, s, t;
	vector<vector<int>> g;
	vector<Edge> edge;
	vector<int> dist;
	vector<int> trace;
	vector<bool> inQ;

	MincostMaxflow(int n = 0) : n(n), g(n + 1), dist(n + 1), trace(n + 1), inQ(n + 1) {}

	void addEdge(int u, int v, int cost, int cap, int reverseCap = 0) {
		g[u].push_back(edge.size());
		edge.emplace_back(v, cap, 0, cost);
		g[v].push_back(edge.size());
		edge.emplace_back(u, reverseCap, 0, cost);
	}
	pair<int, int> getMinCostMaxFlow(int _s, int _t) { // (cost, flow)
		s = _s, t = _t;
		int cost = 0, flw = 0;
		while (spfa()) {
			int delta = INT_MAX;
			for (int v = t, i; v != s; v = edge[i ^ 1].to) {
				i	  = trace[v];
				delta = min(delta, edge[i].flw >= 0 ? edge[i].residual() : -edge[i].flw);
			}
			for (int v = t, i; v != s; v = edge[i ^ 1].to) {
				i = trace[v];
				edge[i].flw += delta;
				edge[i ^ 1].flw -= delta;
			}
			cost += dist[t] * delta;
			flw += delta;
		}
		return pair<int, int>(cost, flw);
	}

private:
	bool spfa() {
		fill(dist.begin(), dist.end(), INT_MAX / 2); // must / 2 !!!
		fill(trace.begin(), trace.end(), 0);
		fill(inQ.begin(), inQ.end(), false);

		queue<int> q;
		q.push(s);
		dist[s] = 0;
		inQ[s]	= true;

		while (!q.empty()) {
			int u = q.front();
			q.pop();
			inQ[u] = false;

			for (int i : g[u]) {
				int v = edge[i].to;
				int c = (edge[i].flw < 0 ? -1 : 1) * edge[i].cost;
				if (edge[i].residual() && dist[v] > dist[u] + c) {
					dist[v]	 = dist[u] + c;
					trace[v] = i;
					if (!inQ[v]) {
						inQ[v] = true;
						q.push(v);
					}
				}
			}
		}
		return dist[t] != INT_MAX / 2; // must / 2 !!!
	}
};
