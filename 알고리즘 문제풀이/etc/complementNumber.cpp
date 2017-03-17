#include <iostream>
#include <string>
using namespace std;

/*
 *
 * 50을 2진수로 바꾸면 110010 이다.
 * 110010의 보수를 취하면 001101 이다.
 * 이것의 10진수는 13이다.
 *
 * n 이 주어졌을 때 보수의 10진수를 리턴하는 complementNumber 함수를 구현하자
 * n의 범위는 0 ~ 10^5 다.
 *
 */

int complementNumber(int number) {
  string binaryString;
  int adder = 1;
  int answer = 0;
  while (number > 0) {
    binaryString = (number % 2 ? '0' : '1') + binaryString;
    number /= 2;
  }

  int binaryStringLength = binaryString.length();
  while(binaryStringLength--) {
    if (binaryString[binaryStringLength] == '1') answer += adder;
    adder *= 2;
  }

  return answer;
}

int main(void) {
  int n;
  cin >> n;
  cout << complementNumber(n) << endl;
  return 0;
}
