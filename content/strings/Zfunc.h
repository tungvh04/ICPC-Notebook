/**
 * Author: chilli
 * License: CC0
 * Description: z[x] computes the length of the longest common prefix of s[i:] and s, except z[0] = 0. (abacaba -> 0010301)
 * Time: O(n)
 * Status: stress-tested
 */
int L = 0, R = 0;
Z[0] = n;
for (int i = 1; i < n; i++) {
   if (i > R)
   {
      L = R = i;
      while (R < n && S[R] == S[R - L]) R++;
      Z[i] = R - L; R--;
   }
   else
   {
      int k = i - L;
      if (Z[k] < R - i + 1) Z[i] = Z[k];
      else
      {
          L = i;
          while (R < n && S[R] == S[R - L]) R++;
          Z[i] = R - L; R--;
      }
   }
}
