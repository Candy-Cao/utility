#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// 找出所有入度为0的点
int* findSmallestSetOfVertices(int n, int** edges, int edgesSize, int* edgesColSize, int* returnSize){
    int *inDeg = (int*)calloc(n, sizeof(int));
    int *retArr = (int*)calloc(n, sizeof(int));
    *returnSize = 0;
    for (int i = 0; i < edgesSize; i++) {
        inDeg[edges[i][1]]++;
    }
    for (int i = 0; i < n; i++) {
        if (inDeg[i] == 0) {
            retArr[*returnSize] = i;
            (*returnSize)++;
        }
    }
    return retArr;
}
// dfs
#define MAXN 1000
bool book[MAXN];
void dfs(int** rooms, int roomsSize, int* roomsColSize, int cur) {
    if (book[cur]) {
        return ;
    }
    book[cur] = true;
    for (int i = 0; i < roomsColSize[cur]; i++) {
        dfs(rooms, roomsSize, roomsColSize, rooms[cur][i]);
    }
    return ;
}
bool canVisitAllRooms(int** rooms, int roomsSize, int* roomsColSize){
    dfs(rooms, roomsSize, roomsColSize, 0);
    for (int i = 0; i < roomsSize; i++) {
        if (!book[i]) {
            return false;
        }
    }
    memset(book, 0, sizeof(book));
    return true;
}
int main() {
    
    return 0;
}