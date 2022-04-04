#include <iostream>
#include <fstream>

using namespace std;

struct Player {
	Player *parent; 
	Player *left; 
	Player *right;
    string key; // holds Player Name as key
	int color; // 0 for BLACK, 1 for RED
    int rebound;
    int asist;
    int point;
    string team;
};

class RedBlackTree {
private:
	Player* root;
    
	void fixTree(Player* k){
        
		if (k->parent == nullptr){
			k->color = 0;
			return;
		}else if (k->parent->parent == nullptr) {
			return;
		}

		Player* u;
		while (k->parent->color == 1) {
			if (k->parent == k->parent->parent->right) {
				if(k->parent->parent->left !=nullptr){
                    u = k->parent->parent->left ;
                }else{
                    u = nullptr;
                }
                if(u != nullptr){
                    if (u->color == 1) {
                        u->color = 0;
                        k->parent->color = 0;
                        k->parent->parent->color = 1;
                        k = k->parent->parent;
                    }else{
                        if (k == k->parent->left) {
                            k = k->parent;
                            rightRotate(k);
                            }
                            k->parent->color = 0;
                            k->parent->parent->color = 1;
                            leftRotate(k->parent->parent);
                    }
                
                }else{
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    leftRotate(k->parent->parent);
                }
        } else {
            if(k->parent->parent->right !=nullptr){
                    u = k->parent->parent->right ;
                }else{
                    u = nullptr;
                }
           
            if(u != nullptr){
				if (u->color == 1) {
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;	
				} else {
					if (k == k->parent->right) {
						k = k->parent;
						leftRotate(k);
					}
					k->parent->color = 0;
					k->parent->parent->color = 1;
					rightRotate(k->parent->parent);
				}
			}else{
               if (k == k->parent->right) {
						k = k->parent;
						leftRotate(k);
					}
					k->parent->color = 0;
					k->parent->parent->color = 1;
					rightRotate(k->parent->parent);
            }
        }
			if (k == root) {
				break;
			}
            
		}
        root->color = 0;
    }

public:
	RedBlackTree() {
		root = nullptr;
	}
    void maxfinder(Player* Player, int &a, int &b,int &c, string &an, string &bn, string &cn) {
		if (Player != nullptr) {
            if(Player->asist > a){
                a= Player->asist;
                an = Player->key;
            }
            if(Player->point > b){
                b= Player->point;
                bn= Player->key;
            }
            if(Player->rebound > c){
                c= Player->rebound;
                cn= Player->key;
            }
			maxfinder(Player->left,a,b,c,an,bn,cn);
			maxfinder(Player->right,a,b,c,an,bn,cn);
		} 
	}
    
    void preOrderOut(Player* Player, int &depth) {
		if (Player != nullptr) {
            for(int i=0; i<depth; i++){
                cout << "-";
            }
            depth++;
            if(Player->color == 0){
                cout << "(BLACK) ";
            }else{
                cout << "(RED) ";
            }
			cout<<Player->key<<" " << Player->color << " " << Player->asist << endl;
			preOrderOut(Player->left, depth);
			preOrderOut(Player->right, depth);
            depth--;
		} 
    }

	void leftRotate(Player* x) {
		Player* y = x->right;
		x->right = y->left;
		if (y->left != nullptr) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->left) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void rightRotate(Player* x) {
		Player* y = x->left;
		x->left = y->right;
		if (y->right != nullptr) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->right) {
			x->parent->right = y;
		} else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}
    
    Player* search(Player* root,Player* n) {
		if (root == nullptr) {
			return nullptr;
		}else if( n->key == root->key){
            return root;
        }
		if (n->key < root->key) {
            return search(root->left, n);
		} 
        return search(root->right, n);
    }

	void insert(Player *newPlayer) {                    //BST ınsert to leaf
		newPlayer->color = 1; // new Player is red
        Player* x;
		Player* y = nullptr;
        if(this->root != nullptr){
            x = this->root;
        }else{
            x = nullptr;
        }

		while (x != nullptr) {
			y = x;
			if (newPlayer->key < x->key) {
				x = x->left;
			} else {
				x = x->right;
			}
		}

		newPlayer->parent = y;
		if (y == nullptr) {
			root = newPlayer;
		} else if (newPlayer->key < y->key) {
			y->left = newPlayer;
		} else if(newPlayer->key > y->key) {
			y->right = newPlayer;
		}
		
		fixTree(newPlayer);
	}

	Player* GetterRoot(){
		return this->root;
	}
    
};

int main() {
	RedBlackTree bst;
    ifstream file;
    int count = 0;
    string an,bn,cn;
    int maxpoint = 0;
    int maxrebound =0;
    int maxasist= 0;
    int depth =0;
    string year1 ="2000-2001";
    string year2 = "";

	file.open("euroleague.csv");
    string line;
    getline(file, line); //this is the header line
    if (!file){
		cerr << "File cannot be opened!";
		exit(1);
    }
    while(true){
        year2 = year1;
        Player *a = new Player;
        a->color = 0;
		a->left = nullptr;
		a->right = nullptr;
        a->parent = nullptr;
        Player* root = bst.GetterRoot();
        getline(file, line, ',');
        year1 = line;
        getline(file, line, ',');
        a->key = line;
        getline(file, line, ',');
        a->team = line;
        getline(file, line, ',');
        a->rebound = stoi(line);
        getline(file, line, ',');
        a->asist = stoi(line);
        getline(file, line, '\n');
        a->point = stoi(line);
        Player* find = bst.search(root,a);
         if(year1 != year2){
            if(count != 1){
                bst.preOrderOut(root, depth); 
                count =1;
            }
            bst.maxfinder(root,maxasist,maxpoint,maxrebound,an,bn,cn);
            cout << "End of the " << year2 << " Season" << endl;
            cout << "Max Points: " << maxpoint << "- Player Name: " << an << endl;
            cout << "Max Asist: " << maxasist << "- Player Name: " << bn << endl;
            cout << "Max Rebs: " << maxrebound << "- Player Name: " << cn << endl;
        }
    
        if(find == nullptr){
            bst.insert(a);
        }else{
            find->asist += a->asist;
            find->rebound += a->rebound;
            find->point += a->point;
        }
       
        if(file.eof()){
            bst.maxfinder(root,maxasist,maxpoint,maxrebound,an,bn,cn);
            cout << "End of the " << year2 << " Season" << endl;
            cout << "Max Points: " << maxpoint << "- Player Name: " << an << endl;
            cout << "Max Asist: " << maxasist << "- Player Name: " << bn << endl;
            cout << "Max Rebs: " << maxrebound << "- Player Name: " << cn << endl;
            break;
        }
    }

	return 0;
}