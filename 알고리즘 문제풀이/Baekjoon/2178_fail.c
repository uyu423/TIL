/* not shortest path */
#include <stdio.h>

typedef enum { false, true } bool;
typedef enum {R, D, L ,U} positon;
typedef struct {
	int h;
	int w;
}GO;
char maze[102][102];
bool mark[102][102] = { false, };
GO go[4];
int w, h;

void initMaze() {
	int i, j;
	go[U].h = -1; go[U].w = 0;
	go[R].h = 0; go[R].w = 1;
	go[L].h = 0; go[L].w = -1;
	go[D].h = 1; go[D].w = 0;
	for (i = 0; i < h + 1; i++) {
		for (j = 0; j < w + 1; j++) {
			maze[i][j] = '0';
		}
	}
}

void solve(int cnt, int nowH, int nowW) {
	int i;
	int nextH, nextW;
	mark[nowH][nowW] = true;
	printf("[%d, %d] -> ", nowH, nowW);
	if (nowH == h && nowW == w) {
		printf("%d\n", cnt);
		return;
	}
	else {
		for (i = 0; i < 4; i++) {
			nextH = nowH + go[i].h;
			nextW = nowW + go[i].w;
			if (maze[nextH][nextW] == '1' && mark[nextH][nextW] == false) {
				solve(cnt + 1, nowH + go[i].h, nowW + go[i].w);
			}
			else {
				continue;
			}
		}
	}
}

int main(void) {
	int i, j;
	char tmp;
	scanf("%d %d", &h, &w);
	initMaze();
	for (i = 1; i <= h; i++) {
		for (j = 1; j <= w; j++) {
			scanf("%c", &tmp);
			if (tmp == '\n') {
				j--;
				continue;
			}
			maze[i][j] = tmp;
		}
		getchar();
	}
	solve(1, 1, 1);
}
