//DateTime : 2014. 10. 12

#include "iostream"
#include "cstring"
#define MAXLEN 256
using namespace std;
unsigned char s[MAXLEN], k[MAXLEN];
void swap(unsigned char *a, unsigned char *b) {
	char tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
int mystrlen(unsigned char *str) {
	int cnt = 0;
	while (str[cnt++]);
	return cnt;
}
void mystrcpy(unsigned char* str1, char* str2){
	int cnt = 0;
	while (str2[cnt]){
		str1[cnt] = str2[cnt++];
	}
}
void init_rc4(unsigned char *key) {
	int i, j = 0;
	for (i = 0; i < MAXLEN; i++) {
		s[i] = i;
		k[i] = key[i % mystrlen(key)];
	}
	for (i = 0; i< MAXLEN; i++) {
		j = (j + s[i] + k[i]) % MAXLEN;
		swap(&s[i], &s[j]);
	}
}
void make_rc4(unsigned char *str, unsigned char *key, int len) {
	int cnt;
	int i = 0, j = 0;
	char XOR, t;
	for (cnt = 0; cnt < len; cnt++) {
		i = (i + 1) % MAXLEN;
		j = (j + s[i]) % MAXLEN;
		swap(&s[i], &s[j]);
		t = (s[i] + s[j]) % MAXLEN;
		XOR = s[t];
		str[cnt] ^= XOR;
	}
}
int main(int argc, char *argv[]) {
	if (argc != 3) {
		cout << "usage : myrc4 [String] [key]" << endl;
		return 1;
	}
	unsigned char string[MAXLEN];
	mystrcpy(string, argv[1]);
	unsigned char key[MAXLEN];
	mystrcpy(key, argv[2]);
	int length = mystrlen(string);
	init_rc4(key);
	make_rc4(string, key, length);
	cout << "key 로 암호화 :" << string << endl;
	init_rc4(key);
	make_rc4(string, key, length);
	cout << "한번더 :" << string << endl;
	return 0;
}
