/**
 * Author: Monarchuwu
 * Date: 2023-11-30
 * Description: read the comments
 * Time: $\mathcal{O}(Q\times\log^2 N)$
 */
// only Segment Tree 2D update + query when:
// update 1 cell -> query range
// update range -> query 1 cell
// update range max_value -> query range max_value
// update range add_value -> query range sum_value
struct SegmentTree2D {
  int nx, ny;
  vector<vector<long long>> isum, lazy, lazyx, lazyy;
  vector<int> Ux, Uy;
  vector<int> leftx, rightx, lefty, righty;
  void init(int _nx, int _ny) {
    nx = _nx; ny = _ny;
    int sz_x = 1 << (33 - __builtin_clz(nx)), sz_y = 1 << (33 - __builtin_clz(ny));
    isum = lazy = lazyx = lazyy = vector<vector<long long>>(sz_x, vector<long long>(sz_y));
    leftx = rightx = vector<int>(sz_x);
    lefty = righty = vector<int>(sz_y);
    buildlr(leftx, rightx, 0, nx - 1);
    buildlr(lefty, righty, 0, ny - 1);
  }
  void buildlr(vector<int> &left, vector<int> &right, int l, int r, int pos = 1) {
    left[pos] = l; right[pos] = r;
    if (l == r) return;
    int mid = (l + r) / 2;
    buildlr(left, right, l, mid, pos * 2);
    buildlr(left, right, mid + 1, r, pos * 2 + 1);
  }
  void getrange(vector<int> &List, int x, int y, int l, int r, int pos = 1) {
    if (x > r || y < l) return;
    if (x <= l && r <= y) return void(List.push_back(pos));
    int mid = (l + r) / 2;
    getrange(List, x, y, l, mid, pos * 2);
    getrange(List, x, y, mid + 1, r, pos * 2 + 1);
    List.push_back(pos);
  }
  void add(int xl, int xr, int yl, int yr, long long val) {
    Ux.clear();
    Uy.clear();
    getrange(Ux, xl, xr, 0, nx - 1);
    getrange(Uy, yl, yr, 0, ny - 1);
    for(int px : Ux) {
      bool inx = (xl <= leftx[px] && rightx[px] <= xr);
      int rangex = min(xr, rightx[px]) - max(xl, leftx[px]) + 1;
      for(int py : Uy) {
        bool iny = (yl <= lefty[py] && righty[py] <= yr);
        int rangey = min(yr, righty[py]) - max(yl, lefty[py]) + 1;
        isum[px][py] += val * rangex * rangey;
        if (inx == 1 && iny == 1) lazy[px][py] += val;
        else if (inx == 0 && iny == 1) lazyx[px][py] += val * rangex;
        else if (inx == 1 && iny == 0) lazyy[px][py] += val * rangey;
      }
    }
  }
  long long querysum(int xl, int xr, int yl, int yr) {
    Ux.clear();
    Uy.clear();
    getrange(Ux, xl, xr, 0, nx - 1);
    getrange(Uy, yl, yr, 0, ny - 1);
    long long tmp_sum = 0;
    for(int px : Ux) {
      bool inx = (xl <= leftx[px] && rightx[px] <= xr);
      int rangex = min(xr, rightx[px]) - max(xl, leftx[px]) + 1;
      for(int py : Uy) {
        bool iny = (yl <= lefty[py] && righty[py] <= yr);
        int rangey = min(yr, righty[py]) - max(yl, lefty[py]) + 1;
        if (inx == 1 && iny == 1) tmp_sum += isum[px][py];
        else {
          if (inx == 0 && iny == 1) tmp_sum += lazyy[px][py] * rangex;
          else if (inx == 1 && iny == 0) tmp_sum += lazyx[px][py] * rangey;
          tmp_sum += lazy[px][py] * rangex * rangey;
        }
      }
    }
    return tmp_sum;
  }
};
