#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
const int max_levels = 25;
std::ifstream fin("abce.in");
std::ofstream fout("abce.out");


class Node {
public:
    int data;
    std::vector<Node*> next;
    Node(int data, int Level): data(data), next(Level + 1, nullptr) {}

};

class SkipList {
private:
    Node *head;
    int Level;
public:
    SkipList() {
        head = new Node(0, max_levels);
        Level = 0;
    }
    void insert(int data) {
        int newLevel = 0;
        while (newLevel < max_levels and (rand()%2) == 1) {
            newLevel++;
        }
        if (Level < newLevel) {
            head -> next.resize(newLevel + 1, nullptr);
            Level = newLevel;
        }
        Node* current = head;
        std::vector<Node*>Update(Level+1, nullptr);

        for (int i = Level; i>=0; i--) {
            while (current -> next[i] and current->next[i]->data < data) {
                current = current->next[i];
            }
            Update[i] = current;
        }

        current = current->next[0];
        Node *newNode = new Node(data, Level);
        for (int i = 0; i <= newLevel; i++) {
            newNode->next[i] = Update[i]->next[i];
            Update[i]->next[i] = newNode;
        }


    }

    void remove(int data) {
        Node* current = head;
        std::vector<Node*>Update(Level+1, nullptr);

        for (int i = Level; i >= 0; i--) {
            while (current -> next[i] != nullptr and current->next[i]->data < data) {
                current = current->next[i];
            }
            Update[i] = current;
        }

        current = current->next[0];

        if (current != nullptr and current -> data == data) {
            for (int i = 0; i <= Level; i++) {
                if (Update[i]->next[i] != current) {
                    break;
                }
                else {
                    Update[i]->next[i] = current->next[i];
                }
            }
            delete current;
            while (Level > 0 and head->next[Level] == nullptr) {
                Level--;
            }
        }

    }

    bool search(int data) {
        Node* current = head;
        for (int i = Level; i >=0; i--) {
            while (current -> next[i] != nullptr and current->next[i]->data < data) {
                current = current->next[i];
            }
        }
        current = current->next[0];
        if (current != nullptr and current -> data == data) {
            return true;
        }
        else {
            return false;
        }
    }

    void after_data(int data) {
        Node* current = head;
        for (int i = Level; i >=0; i--) {
            while (current -> next[i] != nullptr and current->next[i]->data < data) {
                current = current->next[i];
            }
        }
        current = current->next[0];
        if (current != nullptr) {
            fout << current->data<<'\n';
        }

    }

    void before_data(int data) {
        Node* current = head;
        for (int i = Level; i >=0; i--) {
            while (current -> next[i] != nullptr and current->next[i]->data < data) {
                current = current->next[i];
            }
        }
        if (current->next[0] != nullptr and current->next[0]->data == data) {
            fout << current->next[0]->data<<"\n";
        }
        else if (current != nullptr) {
            fout << current->data<<"\n";
        }
    }

    void numbers_between(int x, int y) {
        Node* current = head;
        for (int i = Level; i >= 0; i--) {
            while (current -> next[i] != nullptr and current->next[i]->data < x) {
                current = current->next[i];
            }
        }
        while (current != nullptr and current->next[0] != nullptr and current->next[0]->data <= y) {
            fout << current->next[0]->data<<" ";
            current = current->next[0];
        }
        fout << std::endl;
    }


    void display() {
        for (int i = Level; i >= 0; i--) {
            Node* current = head->next[i];
            std::cout<<"Level "<<i<<": ";
            while (current != nullptr) {
                std::cout<<current->data<<" ";
                current = current->next[i];
            }
            std::cout<<std::endl;
        }
    }


};

int main() {

    int nr_op, op, data, x, y;
    SkipList s;
    /*std::cin>>nr_op;
    for (int i = 0; i < nr_op; i++) {
        std::cin >> op >> data;
        if (op == 0)
            s.insert(data);
        else if (op == 1)
            s.remove(data);
        else if (op == 2)
            s.search(data);


    }*/

    fin>>nr_op;
    for (int i = 0; i < nr_op; i++) {
        fin>>op;
        if (op == 1) {
            fin>>data;
            s.insert(data);
        }
        if (op == 2) {
            fin>>data;
            s.remove(data);
        }
        if (op == 3) {
            fin>>data;
            if (s.search(data)) {
                fout<<1<<"\n";
            }
            else fout<<0<<"\n";
        }
        if (op == 4) {
            fin>>data;
            s.before_data(data);
        }
        if (op == 5) {
            fin>>data;
            s.after_data(data);
        }
        if (op == 6) {
            fin>>x>>y;
            s.numbers_between(x,y);
        }

    }

    return 0;
}
