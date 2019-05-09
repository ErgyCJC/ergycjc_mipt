#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <queue>

// Элемент декартова дерева по неявному ключу
struct TreapNode {
    TreapNode* left;
    TreapNode* right;
    
    std::string line;
    int sub_tree_height;

    TreapNode(const std::string& value) : line(value),
                                            sub_tree_height(1),
                                            left(nullptr),
                                            right(nullptr) {}

    int RecalcSubHeight() {
        sub_tree_height = 1;

        if (left != nullptr) {
            sub_tree_height += left->sub_tree_height;
        }
        if (right != nullptr) {
            sub_tree_height += right->sub_tree_height;
        }

        return sub_tree_height;
    }
};

// Treap-with-implicit-key-based
class StringArray {
public:
    StringArray() {
        tree_root = nullptr;
    }

    ~StringArray() {
        DeleteSubTree(tree_root);
    }

    StringArray(const StringArray& original_array) {
        DeepCopy(original_array);
    }

    StringArray& operator=(const StringArray& original_array) {
        DeepCopy(original_array);
        return *this;
    }

    StringArray(StringArray&& original_array) {
        tree_root = original_array.tree_root;
    }

    StringArray& operator=(StringArray&& original_array) {
        tree_root = original_array.tree_root;
        return *this;
    }

    void InsertAt(int position, std::string& value) {
        TreapNode* insertion_node = new TreapNode(value);

        std::pair<TreapNode*, TreapNode*> splitted = Split(position, tree_root);
        splitted.second = Merge(insertion_node, splitted.second);
        
        tree_root = Merge(splitted.first, splitted.second);
    }

    void DeleteAt(int position) {
        std::pair<TreapNode*, TreapNode*> splitted_1 = Split(position, tree_root);
        std::pair<TreapNode*, TreapNode*> splitted_2 = Split(1, splitted_1.second);

        DeleteSubTree(splitted_2.first);

        tree_root = Merge(splitted_1.first, splitted_2.second);
    }

    void DeleteRange(int from_index, int to_index) {
        std::pair<TreapNode*, TreapNode*> splitted_1 = Split(from_index, tree_root);
        std::pair<TreapNode*, TreapNode*> splitted_2 = Split(to_index - from_index, splitted_1.second);

        if (splitted_1.second == splitted_2.first) {
            DeleteSubTree(splitted_1.second);
        }
        else {
            DeleteSubTree(splitted_1.second);
            DeleteSubTree(splitted_2.first);
        }

        tree_root = Merge(splitted_1.first, splitted_2.second);
    }

    std::string GetAt(int position) {
        int left_sub_height = 0;
        TreapNode* current_node = tree_root;
        
        do {
            left_sub_height = 0;
            if (current_node->left != nullptr) {
                left_sub_height = current_node->left->sub_tree_height;
            }

            if (position == left_sub_height) {
                break;
            }
            else if (position < left_sub_height) {
                current_node = current_node->left;
            }
            else {
                position -= left_sub_height + 1;
                current_node = current_node->right;
            }
        } while (true);

        return current_node->line;
    }

private:
    TreapNode* tree_root;

    TreapNode* Merge(TreapNode* node1, TreapNode* node2) {
        if (node2 == nullptr) {
            return node1;
        }
        if (node1 == nullptr) {
            return node2;
        }

        if (node1->sub_tree_height > node2->sub_tree_height) {
            node1->right = Merge(node1->right, node2);

            node1->RecalcSubHeight();
            return node1;
        }
        else {
            node2->left = Merge(node1, node2->left);

            node2->RecalcSubHeight();
            return node2;
        }
    }

    std::pair<TreapNode*, TreapNode*> Split(int position, TreapNode* current_node) {
        if (current_node == nullptr) {
            return std::make_pair(nullptr, nullptr);
        }

        int left_sub_height = 0;
        if (current_node->left != nullptr) {
            left_sub_height = current_node->left->sub_tree_height;
        }

        if (left_sub_height >= position) {
            std::pair<TreapNode*, TreapNode*> splitted = Split(position, current_node->left);
            current_node->left = splitted.second;

            current_node->RecalcSubHeight();
            return std::make_pair(splitted.first, current_node);
        }
        else {
            std::pair<TreapNode*, TreapNode*> splitted = Split(position - (left_sub_height + 1), current_node->right);
            current_node->right = splitted.first;

            current_node->RecalcSubHeight();
            return std::make_pair(current_node, splitted.second);
        }
    }

    void DeleteSubTree(TreapNode* current_node) {
        if (current_node == nullptr) {
            return;
        }

        std::queue<TreapNode*> nodes;
        nodes.push(current_node);

        while (!nodes.empty()) {
            current_node = nodes.front();
            nodes.pop();

            if (current_node->left != nullptr) {
                nodes.push(current_node->left);
            }
            if (current_node->right != nullptr) {
                nodes.push(current_node->right);
            }

            delete current_node;
        }
    }

    void DeepCopy(const StringArray& original_array) {
        
    }
};

int main(int argc, char** argv) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    int commands_count;
    std::cin >> commands_count;

    StringArray lines;

    char cmd;
    char symb;
    int position, position2;
    bool non_input_flag = false;

    // Такая запутанная система ввода из-за команды '-',
    // которая может принимать как 2, так и 1 аргумент
    while (non_input_flag || std::cin >> cmd) {
        non_input_flag = false;

        if (cmd == '+') {
            std::string line;
            std::cin >> position >> line;

            lines.InsertAt(position, line);
        }
        else if (cmd == '?') {
            std::cin >> position;
            std::cout << lines.GetAt(position) << "\n";
        }
        else if (cmd == '-') {
            std::cin >> position;

            if (std::cin >> symb) {
                if (symb == ' ') {
                    std::cin >> position2;
                    lines.DeleteRange(position, position2 + 1);
                }
                else {
                    non_input_flag = true;
                    cmd = symb;

                    lines.DeleteAt(position);
                }
            }
            else {
                lines.DeleteAt(position);
            }
        }
    }
    return 0;
}