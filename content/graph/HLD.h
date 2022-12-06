/**
 * Author: FireGhost
 * Date: 2022-11-08
 * Description: ez pz
 */

void DFS(int u) {
	sz[u] = 1; // size of subtree u
	for (auto v : adj[u]) {
		if (v == p[u]) continue; // p[u] = par[u]
		h[v] = h[u] + 1;
		p[v] = u;
		child[u].push_back(v);
		DFS(v);
		sz[u] += sz[v];
	}
}
void HLD(int u) {
	t_in[u]	 = ++timer;
	V[timer] = u; // V[timer] = u <=> t_in[u] = timer
	for (int i = 1; i < child[u].size(); ++i)
		if (sz[child[u][i]] > sz[child[u][0]])
			swap(child[u][i], child[u][0]);
	for (int i = 0; i < child[u].size(); ++i) {
		int v	= child[u][i];
		head[v] = (i == 0 ? head[u] : v); // head of chain
		HLD(v);
	}
	t_out[u] = timer;
}
void query(int a, int b) {
	for (; head[a] != head[b]; b = p[head[b]]) {
		if (h[head[a]] > h[head[b]])
			swap(a, b);
		// segment t_in[head[b]], t_in[b]
	}
	if (h[a] > h[b])
		swap(a, b);
	// segemnt t_in[a], t_in[b]
}
