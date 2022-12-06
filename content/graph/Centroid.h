int get_sz(int u, int p) {
	sz[u] = 1;
	for (int v : g[u])
		if (v != p && !vst[v])
			sz[u] += get_sz(v, u);
	return sz[u];
}
int get_cen(int u, int p, int csz) {
	for (int v : g[u])
		if (v != p && !vst[v])
			if (sz[v] > csz / 2) return get_cen(v, u, csz);
	return u;
}
void build_cd(int u, int p) {
	u	  = get_cen(u, 0, get_sz(u, 0));
	pa[u] = p, vst[u] = true;
	for (int v : g[u])
		if (!vst[v])
			build_cd(v, u);
}
