#include <iostream>
#include <string>
using namespace std;

/*
 * aaa bbb 문자열이 주어졌을 때
 * ababab 로 출력되는 함수를 짜보자
 * aaaaa bbb 가 입력되면
 * abababaa 가 출력된다.
 */

string stringMerge(string a, string b){
  string ans;
  int alen = a.length();
  int blen = b.length();
  int longlen = alen > blen ? alen : blen;
  for(int i = 0; i < longlen; i++) {
    if (i < alen) ans += a[i];
    if (i < blen) ans += b[i];
  }
  return ans;
}

int main(void) {
  string a, b;
  cin >> a;
  cin >> b;
  cout << stringMerge(a, b) << endl;

  return 0;
}


