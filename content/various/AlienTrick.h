/**
 * Author: FireGhost
 * Date: 2022-11-08
 * Description: ez pz
 */

long long l = 0, r = INF, ans = r, mid;
while (l <= r) {
  mid = (l + r) >> 1;
  pair<long long, int> tmp = calc(mid);
  if (tmp.second <= m) {
    ans = tmp.first - mid * m;
    r = mid - 1;
  }
  else {
    l = mid + 1;
  }
}
