#include <bits/stdc++.h>
using namespace std;

class Node {
	public:
		int value;
		int	left;
		int right;
		
		Node(int vVal, int lLeft, int rRight) {
			value = vVal;
			left = lLeft;
			right = rRight;
		}
};

class BST {
	public:
		vector<Node> nodes;
		int root;
		BST(int value) {
			root = 0;
			nodes.push_back(Node(value,-1,-1));
		}
		
		void insert(int value) {
			nodes.push_back(Node(value,-1,-1));
			insertInternals(root);
		}
		
		void traverse(int nodeIndex,vector<char> &traversal) { //postorder to check shape.
			if (nodes[nodeIndex].left != -1) {
				traversal.push_back('L');
				traverse(nodes[nodeIndex].left,traversal);
			}
			if (nodes[nodeIndex].right != -1) {
				traversal.push_back('R');
				traverse(nodes[nodeIndex].right,traversal);
			}
			traversal.push_back('B');			
		}
		
	private:
		void insertInternals(int current) {
			int toInsert = nodes[nodes.size()-1].value;
			if (toInsert > nodes[current].value) {
				if (nodes[current].right == -1) {
					nodes[current].right = nodes.size()-1;
				} else {
					insertInternals(nodes[current].right);
				}
			} else {
				if (nodes[current].left == -1) {
					nodes[current].left = nodes.size()-1;
				} else {
					insertInternals(nodes[current].left);
				}
			}
		}
};


int main() {
	int n,k;
	scanf("%d %d",&n,&k);
	//while ( != EOF) {
	set<vector<char>> options; 
	for (int i=0;i<n;++i) {
		int v; cin >> v;
		BST myBST(v);
		for (int j=1;j<k;++j) {
			cin >> v;
			myBST.insert(v);
		}
		vector<char> traversal;
		myBST.traverse(myBST.root,traversal);
		options.insert(traversal);
	}
	cout << options.size() << endl;
	//}

}
