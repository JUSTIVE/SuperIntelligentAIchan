#include<iostream>
#include<vector>
#include<string>


using namespace std;

typedef struct size {
	int x;
	int y;
	size() {};
	size(int x, int y) { this->x = x; this->y = y; }
}Size;

class DynamicMatrix{
public:
	 Size size;
	 int** data;
	 vector<int>userHistory;
	 vector<int>enemyHistory;

	 vector<int>leftHand;
	 vector<int>rightHand;
	 DynamicMatrix* parent;
	 vector<DynamicMatrix*> childs;
	 DynamicMatrix(DynamicMatrix *parent,int myHis) {
		 this->parent = parent;
		 this->size = Size(parent->size.x-1,parent->size.x);
		 data = (int**)malloc(sizeof(int*)*size.x);
		 for (int i = 0; i < size.x; i++)
			 data[i] = (int *)malloc(sizeof(int)*size.y);

		 userHistory = parent->userHistory;
		 userHistory.push_back(myHis);

		 enemyHistory = parent->enemyHistory;


		 leftHand = handCreator(userHistory);
	 }
	 //only for roots
	 DynamicMatrix(int x, int y) { 
		 parent = NULL;
		 size = Size(x, y);	
		 data = (int**)malloc(sizeof(int*)*size.x);
		 for (int i = 0; i < size.x; i++)
			 data[i] = (int *)malloc(sizeof(int)*size.y);
		 leftHand = vector<int>();
		 for (size_t i = 0; i < x; i++)
			 leftHand.push_back(i);
		 rightHand = vector<int>();
		 for (size_t i = 0; i < y; i++)
			rightHand.push_back(i);
	 }
	 ~DynamicMatrix() {
		 for (int i = 0; i < size.x;i++) {
			 free(data[i]);
		}
		 free(data);
	 }
	 void calcultate() {
		 
		 for (size_t i = 0; i < size.x;i++) {
			 for (size_t j = 0; j < size.y; j++) {//각 칸에 대해
				 
				 enemyHistory.push_back((parent==NULL)?-1:j);
				 rightHand = handCreator(enemyHistory);//현재 인덱스를 포함하지 않은 rightHand 생성
				 data[i][j] = 0;
				 for (size_t k = 0; k < rightHand.size(); k++) {
					data[i][j] += evaluate(leftHand[i], rightHand[k]);
				 }
				 enemyHistory.pop_back();
			 }
		 }
	 }
	 void show() {
		 
		 for (size_t i = 0; i < size.x; i++)
		 {
			 string temp = "";
			 temp += (to_string(leftHand[i])+" - ");
			
			 for (size_t j = 0; j < size.y; j++)
			 {
				 temp += to_string(data[i][j]);
			 }
			 cout << temp << endl;
		 }
		 cout << endl;
	 }
	 void breed() {
		
	 }
	 static void treeBreed(DynamicMatrix* root) {
		 if (root->size.x == 0)
			 return;
		 for (size_t i = 0; i < root->size.x; i++) {
			 for (size_t j = 0; j < root->size.y; j++) {
				 DynamicMatrix* child = new DynamicMatrix(root, i);
				 root->childs.push_back(child);
				 treeBreed(child);
				 child->calcultate();
			 }
		 }
	 }
	 static void riot(DynamicMatrix* root) {
		 for each (DynamicMatrix* child in root->childs)
		 {
			 riot(child);
			 if (root->parent != NULL) {
				 for(size_t i=0;i<root->size.x;i++){
					 for (size_t j = 0; root->size.y; j++)
						 //root->parent->data[root->userHistory[root->userHistory.size()]][root->enemyHistory[root->enemyHistory.size()]] +=root->data[i][j];
						 printf("sth");
				 }
			 }
		 }
	 }
private:
	static int evaluate(int friendly, int enemy) { return friendly > enemy ? 1 : friendly == enemy ? 0 : -1; }

	static vector<int> handCreator(vector<int>prevHand) {//{1,2,3,4,5}에서 인풋 벡터를 제외한 서브셋 벡터를 반환하는 메소드(인풋은 히스토리에 한함)
		vector<int> returnVector;

		for (int i = 0; i < 5;i++) {
			for (int j = 0; j < prevHand.size(); j++) {
				if (i != prevHand[j]) {
					returnVector.push_back(i);
					break;
				}
			}
		}
		return returnVector;
	}
	
};

int main(int argc, char**argv) {
	DynamicMatrix root(5, 1);
	root.calcultate();
	root.show();
	DynamicMatrix::treeBreed(&root);
	//DynamicMatrix::riot(&root);
	for each (DynamicMatrix* var in root.childs[0]->childs)
	{
		var->show();
	}
	//root.childs[0]->show();
	printf("breeding done");
}