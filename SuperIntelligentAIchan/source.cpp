#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

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
	 vector<int>leftHand;
	 vector<int>rightHand;
	 DynamicMatrix* parent;
	 DynamicMatrix(DynamicMatrix *parent) {
		 this->parent = parent;
		 this->size = Size(parent->size.x-1,parent->size.x);
		 data = (int**)malloc(sizeof(int*)*size.x);
		 for (int i = 0; i < size.x; i++)
			 data[i] = (int *)malloc(sizeof(int)*size.y);

		 leftHand = handCreator(parent->leftHand,-1);
	 }
	 //only for roots
	 DynamicMatrix(int x, int y) { 
		 parent == NULL;
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
			 rightHand = handCreator(parent->rightHand, i);
		 }
	 }
	 void show() {
		 
		 for (size_t i = 0; i < size.x; i++)
		 {
			 string temp = "";
			 temp += (to_string(leftHand[i])+" - ");
			
			 for (size_t j = 0; j < size.y; j++)
			 {
				 temp += data[i][j];
			 }
			 cout << temp << endl;
		 }
	 }
private:
	static vector<int> handCreator(vector<int>prevHand,int current) {		
		vector<int> returnVector;
		for (int i = 0; i < 5;i++) {
			for (int j = 0; j < prevHand.size(); j++) {
				if (i != prevHand[j]&&(i!=current)) {
					returnVector.push_back(i);
					break;
				}
			}
		}
	}
};

int main(int argc, char**argv) {
	DynamicMatrix root(5, 1);
	root.show();
}