/**
 * Author: FireGhost
 * Date: 2022-06-12
 * Description: ez pz
 */
int nxt[N][10], suf[N], tme;
void add(const vector<int> &vec) {
	int u(0);
	for (int c : vec) {
		if (!nxt[u][c]) nxt[u][c] = ++tme;
		u = nxt[u][c];
	}
}
void build_automaton() {
	queue<int> q;
	q.push(0);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int c = 0, v; c < 10; ++c) {
			v = nxt[u][c];
			if (v) {
				suf[v] = u ? nxt[suf[u]][c] : 0;
				q.push(v);
			}
			else nxt[u][c] = nxt[suf[u]][c];
		}
	}
}
