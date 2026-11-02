// Reservation System Tree
#ifndef AVL_TREE_H
#define AVL_TREE_H
#include<iostream>
#include<string>
#include<algorithm>
#include<fstream>

struct TreeNode {
    int res_id;
    std::string driver_name;
    std::string time_slot;
    int height;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int id, const std::string& name, const std::string& slot) {
        res_id = id;
        driver_name = name;
        time_slot = slot;
        height = 1;
        left = nullptr;
		right = nullptr;
    }
};

class AVLTree{
	private:
	    int height(TreeNode* n){
	        if (!n) return 0;
	        return n->height;
	    }
	
	    int getBalance(TreeNode* n){
	        if (!n) return 0;
	        return height(n->left) - height(n->right);
	    }
	
	    TreeNode* rightRotate(TreeNode* y) {
	        TreeNode* x = y->left;
	        TreeNode* a = x->right;
	        x->right = y;
	        y->left = a;
	        y->height = std::max(height(y->left), height(y->right)) + 1;
	        x->height = std::max(height(x->left), height(x->right)) + 1;
	        return x;
	    }
	
	    TreeNode* leftRotate(TreeNode* x) {
	        TreeNode* y = x->right;
	        TreeNode* a = y->left;
	        y->left = x;
	        x->right = a;
	        x->height = std::max(height(x->left), height(x->right)) + 1;
	        y->height = std::max(height(y->left), height(y->right)) + 1;
	        return y;
	    }
	
	    TreeNode* insert(TreeNode* node, int id, const std::string& name, const std::string& slot){
	        if (!node){
				return new TreeNode(id, name, slot);
			}	
	        if (id < node->res_id){
	            node->left = insert(node->left, id, name, slot);
	        }
	        else if (id > node->res_id){
	            node->right = insert(node->right, id, name, slot);
	        }
	        else{
	            return node; 
	        }
	
	        node->height = 1 + std::max(height(node->left), height(node->right));
	        int balance = getBalance(node);
	
	        // Left Left Case
	        if (balance > 1 && id < node->left->res_id){
	            return rightRotate(node);
	        }
	
	        // Right Right Case
	        if (balance < -1 && id > node->right->res_id){
	            return leftRotate(node);
	        }
	
	        // Left Right Case
	        if (balance > 1 && id > node->left->res_id){
	            node->left = leftRotate(node->left);
	            return rightRotate(node);
	        }
	
	        // Right Left Case
	        if (balance < -1 && id < node->right->res_id){
	            node->right = rightRotate(node->right);
	            return leftRotate(node);
	        }
	        return node;
	    }
	
	    TreeNode* search(TreeNode* root, int id){
	        if (!root || root->res_id == id){
	            return root;
	        }
	        
	        if (root->res_id > id){
	            return search(root->left, id);
	        }
	        return search(root->right, id);
	    }
	
	    void inorder(TreeNode* root){
	        if (root){
	            inorder(root->left);
	            std::cout << "Reservation ID: " << root->res_id 
	                      << "Driver: " << root->driver_name 
	                      << "Time Slot: " << root->time_slot << "\n";
	            inorder(root->right);
	        }
	    }
	
	    void destroy(TreeNode* node){
	        if (node){
	            destroy(node->left);
	            destroy(node->right);
	            delete node;
	        }
	    }
	    TreeNode* root;
	    
	    void saveAVL(TreeNode* node, std::ofstream& file){
		    if(node == nullptr){
		        return;
		    }
		
		    saveAVL(node->left, file);
		    file << node->res_id << " " << node->driver_name << " " << node->time_slot << "\n";
		    saveAVL(node->right, file);
		}
		
		void loadAVL(){
		    std::ifstream file("data/reservations.txt");
		    if(!file.is_open()){
		        return;
		    }
		
		    int id;
		    std::string name, slot;
	
		    while(file >> id >> name >> slot){
		        root = insert(root, id, name, slot);
		    }
		    file.close();
		}
	
	public:
	    AVLTree(){
			root = nullptr;
			loadAVL();
		}
	    ~AVLTree(){
			destroy(root);
		}
	
	    void insertRes(int id, const std::string& name, const std::string& slot){
	        root = insert(root, id, name, slot);
	        saveRes();
	        std::cout << "Reservation ID " << id << " successfully booked.\n";
	    }
	    
	    bool searchRes(int id){
	        TreeNode* res = search(root, id);
	        if(res){
	            std::cout << "ID: " << res->res_id 
	                      << "Driver: " << res->driver_name 
	                      << "Time: " << res->time_slot << "\n";
	            return true;
	        }
	        std::cout << "Reservation ID " << id << " not found.\n";
	        return false;
	    }
	
	    void dispRes(){
	        std::cout << "\nReservations List:\n";
	        inorder(root);
	    }
	    
	    void saveRes(){
		    std::ofstream file("data/reservations.txt");
		
		    if(file.is_open()){
		        saveAVL(root, file);
		        file.close();
		        std::cout << "Reservations saved successfully.\n";
		    }
		    else{
		        std::cout << "Unable to save reservations.\n";
		    }
		}
	};
#endif
