#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <bitset>
using namespace std;

struct StateNode{
	int convertInt;
	int step;
	int toy[8];
};

// 待插入树的数组编号
int insert_index;
// 是否复原
bool back;
// 检验是否已插入
# define MAXSIZE 40325
bitset<MAXSIZE> bit;

void whether_insert(StateNode* StateTree){
	if (bit[StateTree[insert_index].convertInt])
		return;
	bit.set(StateTree[insert_index].convertInt);
	insert_index = insert_index+1;
	return;
}

int convertToInt(StateNode* StateTree){
	int convertInt = 1;
	int factorial[8] = {5040,720,120,24,6,2,1,1};
	int count_small;
	// 第i位
	for (int i=0;i<7;i++){
		// 之前有多少位比这位小
		count_small = 0;
		for (int j=0;j<i;j++){
			if (StateTree[insert_index].toy[j]<StateTree[insert_index].toy[i])
				count_small += 1;
		}
		convertInt += factorial[i] * (StateTree[insert_index].toy[i] - 1 - count_small );
	}
	// cout<<convertInt<<endl;
	return convertInt;
}

StateNode* op_a(StateNode* StateTree,int check_index){
		StateTree[insert_index].step = StateTree[check_index].step + 1;
		for (int i = 0;i<8;i++){
			StateTree[insert_index].toy[i] = StateTree[check_index].toy[7-i];
		}
		StateTree[insert_index].convertInt = convertToInt(StateTree);
		if (StateTree[insert_index].convertInt==1){
			printf("%d\n",StateTree[insert_index].step);
			back = true;
		}
		whether_insert(StateTree);
	return StateTree;
}

StateNode* op_b(StateNode* StateTree,int check_index){
		StateTree[insert_index].step = StateTree[check_index].step + 1;
		for (int i=3;i>0;i--){
			StateTree[insert_index].toy[i] = StateTree[check_index].toy[i-1];
		}
		StateTree[insert_index].toy[0] = StateTree[check_index].toy[3];
		for (int i=4;i<7;i++){
			StateTree[insert_index].toy[i] = StateTree[check_index].toy[i+1];
		}
		StateTree[insert_index].toy[7] = StateTree[check_index].toy[4];
		StateTree[insert_index].convertInt = convertToInt(StateTree);
		if (StateTree[insert_index].convertInt==1){
			printf("%d\n",StateTree[insert_index].step);
			back = true;
		}
		whether_insert(StateTree);
	return StateTree;
}

StateNode* op_c(StateNode* StateTree,int check_index){
		StateTree[insert_index].step = StateTree[check_index].step + 1;
		StateTree[insert_index].toy[6] = StateTree[check_index].toy[5];
		StateTree[insert_index].toy[5] = StateTree[check_index].toy[2];
		StateTree[insert_index].toy[2] = StateTree[check_index].toy[1];
		StateTree[insert_index].toy[1] = StateTree[check_index].toy[6];
		StateTree[insert_index].toy[0] = StateTree[check_index].toy[0];
		StateTree[insert_index].toy[3] = StateTree[check_index].toy[3];
		StateTree[insert_index].toy[4] = StateTree[check_index].toy[4];
		StateTree[insert_index].toy[7] = StateTree[check_index].toy[7];
		StateTree[insert_index].convertInt = convertToInt(StateTree);
		if (StateTree[insert_index].convertInt==1){
			printf("%d\n",StateTree[insert_index].step);
			back = true;
		}
		whether_insert(StateTree);
	return StateTree;
}

void init_StateTree(StateNode* StateTree){
	back = false;
	// 初始化
	StateTree[0].step = 0;
	insert_index = 0;
	StateTree[0].convertInt = convertToInt(StateTree);
	bit.reset();
	bit.set(StateTree[0].convertInt);
	if (StateTree[0].convertInt == 1){
		printf("%d\n",StateTree[0].step);
		return;
	}

	// 待插入树的数组编号
	insert_index = 1;
	// 待检验的数组变化
	int check_index = 0;
	while(check_index!=insert_index){
		op_a(StateTree,check_index);
		if (back)
			break;
		op_b(StateTree,check_index);
		if (back)
			break;
		op_c(StateTree,check_index);
		if (back)
			break;
		check_index += 1;
	}
	if (!back)
		printf("-1\n");
	return;
}

int main()
{
    #ifndef _OJ_
          freopen("input.txt", "r", stdin);
          // freopen("output.txt", "w", stdout);
    #endif
	int N;
	scanf("%d",&N);

	StateNode* StateTree = new StateNode[MAXSIZE];

	for (int i=0;i<N;i++){
		for(int j=0;j<8;j++){
			scanf("%d",&StateTree[0].toy[j]);
		}
		init_StateTree(StateTree);
	}

	return 0;
}
