/**
 * Author: FireGhost
 * Date: 2022-11-08
 * Description: ez pz
 */

// Usage:
//  - Konig()
//    --> Select[0] : mX
//    --> Select[1] : mY
//    --> Select[k][vertex] = true : selected
//
// Note:
//  - Used together with HopcroftKarp.cpp
//  - Call HopcroftKarp::MaxMatching() before Konig()
//  - Only Bipartite Graph
void HopcroftKarp::Konig() {
	Select[0].resize(m + 1, false);
	Select[1].resize(n + 1, false);

	queue<int> q;
	for (int i = 1; i <= m; ++i) {
		if (mX[i]) Select[0][i] = true;
		else q.push(i);
	}
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int v : g[u])
			if (!Select[1][v]) {
				Select[1][v] = true;
				if (Select[0][mY[v]]) {
					Select[0][mY[v]] = false;
					q.push(mY[v]);
				}
			}
	}
}
