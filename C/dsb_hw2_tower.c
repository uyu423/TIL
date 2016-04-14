#include <stdio.h>
#include <stdlib.h>
#define INF 2100000000

/* define typedef enum && struct */
typedef enum { false, true } bool;
typedef struct __graphVertex { 
	int width; 
	int height; 
	int weight; 
	struct __graphVertex **conn; 
} graphVertex;
typedef struct __maxHeightTower{ 
	int value; 
	int list[100]; 
} maxHeightTower;

graphVertex node[100];
int graphVertexCnt;
maxHeightTower max;

bool initNodes() {
	int t, cnt = 0;
	FILE *fp;
	if(!(fp = fopen("input.txt", "r"))) {
		perror("input.txt FILE Open error : ");
		return false;
	}
	fscanf(fp, "%d", &t);
	graphVertexCnt = t;
	max.value = 0;
	while(cnt < t) {
		fscanf(fp, "%d %d %d", &node[cnt].width, &node[cnt].height, &node[cnt].weight);
		node[cnt].height = ~node[cnt].height + 1;
		node[cnt].conn = (graphVertex**)malloc(sizeof(graphVertex*));
		node[cnt].conn[0] = NULL;
		cnt++;
	}
	return true;
}

void printAllNodeInfo() {
	int i;
	for(i=0; i<graphVertexCnt; i++) {
		printf("Node[%d] : Width(%d), Height(%d), Weight(%d)\n", i, node[i].width, node[i].height, node[i].weight);
	}
	return;
}

bool solve() {
	if(!initNodes()) {
		printf("init fucntion occur error.\n");
		return false;		
	}
	printAllNodeInfo();
	return true;
}

int main(void) {
	if(!solve()) {
		printf("Application running failed,\n");
		return 1;
	}
	return 0;
}
