/*
 * NHN Intern Coding Test
 *
 * Corder : Yowu (Yu Yongwoo // uyu423@gmail.com)
 * Date : 160522
 * Env
 * 	- Ubuntu 16.04 LTS (Kernel 4.4.0-22)
 * 	- g++ 5.3.1 -std=c++11
 * Compile Usage : g++ -std=c++11 -o RecordMaker RecordMaker.cpp
 *
 */
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class Member {
	private:
		string idx;
		int score;
	public:
		void setMemIdx(string idx) { this->idx = idx; }
		void setMemScore(int score) { this->score = score; }
		string getMemIdx() { return this->idx; }
		int getMemScore() { return this->score; }
};

class memberManagementSystem {
	private:
		bool *idxChecker;
		int maxCnt;
		int maxIdxLimit;
		Member *member;
		string prefix; 

		string makeMemberIdxString() {
			int tmp, digits = 0, ranNum;
			string idx;
			srand((unsigned int)time(NULL));
			while(1) {
				ranNum = rand() % this->maxIdxLimit;
				if(this->idxChecker[ranNum] == false) {
					this->idxChecker[ranNum] = true;
					tmp = ranNum;
					break;
				}
			}
			do {
				digits++;
				tmp /= 10;	
			} while(tmp);
			idx = to_string(ranNum);	//is_string : STD C++11
			while(digits++) {
				if(digits > 5) break;
				idx = "0" + idx;
			}	
			return this->prefix + idx;
		}
	
		void setMemberInfo() {
			srand((unsigned int)time(NULL));
			for(int i=0; i<maxCnt; i++) {
				member[i].setMemScore(rand() % 100);
				member[i].setMemIdx(makeMemberIdxString());
			}
		}
	public:
		memberManagementSystem(int maxIdxLimit, string prefix, int maxCnt) {
			this->maxCnt = maxCnt;
			this->prefix = prefix;
			this->maxIdxLimit = maxIdxLimit;
			this->idxChecker = new bool[this->maxIdxLimit];
			initIdxChecker(this->idxChecker);
			this->member = new Member[this->maxCnt];
			this->setMemberInfo();
		}
		void printAllMemberInfos() {
			for(int i=0; i<this->maxCnt; i++) {
				cout << member[i].getMemIdx() << " " << member[i].getMemScore() << endl;
			}
		}
		static void initIdxChecker(bool *arr) {
			for(int i=0; i<sizeof(arr)/sizeof(*arr); i++) {
				arr[i] = false;
			}
		}
};

int main(int argc, char *argv[]) {
	if(argc != 2) {	//argc exception
		cout << "usage : ./RecordMaker [memberCount(int)]" << endl;
		return 1;
	}
	memberManagementSystem system(100000, "NT", atoi(argv[1])); //idxLimit, Prefix, MemberCount
	system.printAllMemberInfos();
	return 0;
}
