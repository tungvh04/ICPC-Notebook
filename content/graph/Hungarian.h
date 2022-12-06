/**
 * Author: FireGhost
 * Date: 2022-11-08
 * Description: ez pz
 */

// Usage:
//   Hungarian hung(m, n);
//   - X[0..m-1] and Y[0..n-1]  // 0-based
//   mat.addEdge(u, v, cost)    // X[u] -> Y[v]
//   mat.solve()
//   --> sum of c[i][mX[i]] = minimum cost for assignment problem
//
//  Note:
//  - Only Bipartite Graph
struct Hungarian {
	typedef long long ll;
	const ll INF = 1e18;

	int n;
	vector<vector<ll>> c;
	vector<ll> fx, fy;
	vector<int> mX, mY;
	vector<int> trace, q, arg;
	vector<ll> d;
	int ql, qr, start, finish;
	Hungarian(int n = 0)
		: n(n), mX(n), mY(n), trace(n), q(n + 10), arg(n), c(n, vector<ll>(n, INF)), fx(n, 0), fy(n, 0), d(n) {}

	void addEdge(int u, int v, ll cost) { c[u][v] = min(c[u][v], cost); }
	ll solve() {
		for (int i = 0; i < n; ++i)
			fx[i] = *min_element(c[i].begin(), c[i].end());

		for (int j = 0; j < n; ++j) {
			fy[j] = c[0][j] - fx[0];
			for (int i = 1; i < n; ++i)
				fy[j] = min(fy[j], c[i][j] - fx[i]);
		}

		fill(mX.begin(), mX.end(), -1);
		fill(mY.begin(), mY.end(), -1);
		for (int i = 0; i < n; ++i) {
			start = i;
			initBFS();
			while (finish == -1) {
				findAugPath();
				if (finish == -1) subx_addy();
			}
			enlarge();
		}

		ll sum(0);
		for (int i = 0; i < n; ++i)
			sum += c[i][mX[i]];
		return sum;
	}

private:
	ll getC(int i, int j) { return c[i][j] - fx[i] - fy[j]; }
	void initBFS() {
		fill(trace.begin(), trace.end(), -1);
		ql = qr = 0;
		q[qr++] = start;
		for (int j = 0; j < n; ++j) {
			d[j]   = getC(start, j);
			arg[j] = start;
		}
		finish = -1;
	}
	void findAugPath() {
		while (ql < qr) {
			int i = q[ql++];
			for (int j = 0; j < n; ++j)
				if (trace[j] == -1) {
					ll w = getC(i, j);
					if (!w) {
						trace[j] = i;
						if (mY[j] == -1) return void(finish = j);
						q[qr++] = mY[j];
					}
					else if (d[j] > w) {
						d[j]   = w;
						arg[j] = i;
					}
				}
		}
	}
	void subx_addy() {
		ll delta = INF;
		for (int j = 0; j < n; ++j)
			if (trace[j] == -1 && delta > d[j]) delta = d[j];

		fx[start] += delta;
		for (int j = 0; j < n; ++j)
			if (~trace[j]) {
				fy[j] -= delta;
				fx[mY[j]] += delta;
			}
			else d[j] -= delta;

		for (int j = 0; j < n; ++j)
			if (trace[j] == -1 && !d[j]) {
				trace[j] = arg[j];
				if (mY[j] == -1) return void(finish = j);
				q[qr++] = mY[j];
			}
	}
	void enlarge() {
		do {
			int i = trace[finish], nxt = mX[i];
			mX[i] = finish, mY[finish] = i;
			finish = nxt;
		} while (~finish);
	}
};
