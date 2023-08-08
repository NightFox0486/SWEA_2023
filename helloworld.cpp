#include <iostream>

struct Node{
    int data;
    Node* next;
    Node* previous;
};

constexpr size_t MAX_NODE = 10000;

int node_count = 0;
Node node_pool[MAX_NODE];

Node* new_node(int data) {
    node_pool[node_count].data = data;
    node_pool[node_count].next = nullptr;
    node_pool[node_count].previous = nullptr;

    return &node_pool[node_count++];
}

class LinkedList{
    private:
        Node* head;
        Node* tail;
        int size;

    public:
        LinkedList(){
            head = nullptr;
            tail = nullptr;
            size = 0;
        }
        void add_first(int data) {
            Node* node = new_node(data);
            if(size == 0) {
                head = node;
                tail = node;
            }else{
                node->next = head;
                head->previous = node;
                head = node;
            }
            size++;
        }
        void add_last(int data) {
            Node* node = new_node(data);
            if(size == 0){
                head = node;
                tail = node;
            }else{
                tail->next = node;
                node->previous = tail;
                tail = node;
            }
            size++;
        }
        void add_index(int index, int data){
            Node* node = new_node(data);
            if(index == 0){
                add_first(data);
            }else if(index == size-1){
                add_last(data);
            }else{
                if(index < size){
                    Node* current = head;
                    for(int i = 0; i < index; i++){
                        current = current->next;
                    }
                    current->previous->next = node;
                    node->previous = current->previous;
                    current->previous = node;
                    node->next = current;
                    size++;
                }else{
                    throw std::out_of_range("Index out of range");
                }
            }
        }
        void remove_first(){
            if(size == 1){
                head = nullptr;
                tail = nullptr;
                size--;
            }else if(size > 1){
                head->next->previous = nullptr;
                head = head->next;
                size--;
            }else{
                throw std::out_of_range("list is empty");
            }
        }
        void remove_last(){
            if(size == 1){
                head = nullptr;
                tail = nullptr;
                size--;
            }else if(size > 1){
                tail->previous->next = nullptr;
                tail = tail->previous;
                size--;
            }else{
                throw std::out_of_range("list is empty");
            }
        }
        void remove_index(int index){
            if(index == 0){
                remove_first();
            }else if(index == size-1){
                remove_last();
            }else{
                if(index < size){
                    Node* current = head;
                    for(int i = 0; i < index; i++){
                        current = current->next;
                    }
                    current->previous->next = current->next;
                    current->next->previous = current->previous;
                    size--;
                }else{
                    throw std::out_of_range("Index out of range");
                }
            }
        }

};

int main(){
    LinkedList *list = new LinkedList();
    list->add_first(3);
    list->add_first(1);
    list->add_last(4);
    list->add_index(1, 2);
    list->remove_first();
    list->remove_last();
    list->remove_index(1);
    std::cout << "test" << std::endl;
    return 0;
}