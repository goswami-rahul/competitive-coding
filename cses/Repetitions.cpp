#include <stdio.h>
#include <string.h>
int main() {
  char s[1000000];
  scanf(" %s", s);
  int cur = 1, ans = 1;
  for (int i = 1; i < strlen(s); ++i) 
    cur = s[i] == s[i - 1] ? ++cur: 1, ans = cur > ans ? cur : ans;
  printf("%d", ans);
}
