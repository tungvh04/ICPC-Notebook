/**
 * Author: FireGhost
 * Date: 2022-11-08
 * Description: ez pz
 */

// task : given a bipartite graph
// ask : color the edges so that no 2 edges that share a vertex have the same color
int m, n, p, deg[N];
char c[N][N];
int match[N][N];
void add(int x, int y, int cx, int cy) {
    // cạnh (x, y) tô màu cx
    // cạnh (y, w) tô màu cy
    int w = match[y][cx];
    match[x][cx] = y;
    match[y][cx] = x;

    if (w == 0) match[y][cy] = 0;
    else add(y, w, cy, cx);
}

void add(int x, int y) {
    int cx = find(match[x] + 1, match[x] + p + 1, 0) - match[x];
    int cy = find(match[y] + 1, match[y] + p + 1, 0) - match[y];
    if (cx == cy) {
        match[x][cx] = y;
        match[y][cx] = x;
    }
    else add(x, y, cx, cy);
}

int a[N][N];
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> m >> n;
    for (int i = 1; i <= m; ++i) {
        cin >> (c[i] + 1);
        for (int j = 1; j <= n; ++j)
            if (c[i][j] == '1') {
                ++deg[i], ++deg[j + m];
            }
    }

    p = *max_element(deg + 1, deg + m + n + 1);
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            if (c[i][j] == '1') {
                add(i, j + m);
            }

    for (int u = 1, v; u <= m; ++u)
        for (int color = 1; color <= p; ++color)
            if (v = match[u][color])
                a[u][v - m] = color;

    cout << p << '\n';
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            cout << a[i][j] << " \n"[j == n];
}
