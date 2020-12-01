#ifndef _LISPLIST_H
#define _LISPLIST_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>

using namespace std;

typedef struct NODE{
    string data;
    struct NODE* next;
    struct NODE* list;
}NODE;

class List{
    private:
        NODE *head, *tail;
        int size;
        int flag; // 0 : symbol, 1 : List, 2 : array
        string list_Check;
        string array_Check;
        
    public:
        List(){
            head = NULL;
            tail = NULL;
            flag = 0;
            size = 0;

            hash<string> hasher;
            stringstream ss;

            size_t hash = hasher("listdummy");
            ss << hash;

            list_Check = ss.str();

            hash = hasher("arraydummy");
            ss << hash;

            array_Check = ss.str();
        }

        void add(string data){
            NODE* temp = new NODE;
            temp->data = data;
            temp->next = NULL;
            temp->list = NULL;

            if(head == NULL){
                head = temp;
                tail = temp;
            }else{
                tail->next = temp;
                tail = tail->next;
            }
            size++;
        }
        
        void addList(class List list){
            if(list.getFlag() == 1){
                add(list_Check);
            }else{
                add(array_Check);
            }

            NODE* temp = list.head;
            if(head == NULL){
                head = temp;
                tail = temp;
            }else{
                tail->list = temp;
            }

            size++;
        }

        void addNode(NODE* node){
            NODE* temp = new NODE;
            temp->data = node->data;
            temp->next = NULL;
            temp->list = node->list;

            if(head == NULL){
                head = temp;
                tail = temp;
            }else{
                tail->next = temp;
                tail = tail->next;
            }
            size++;
        }

        void traverse(NODE* head){
            NODE* temp = head;

            if(this->flag == 1){
                cout << "(";
            }else if(this->flag == 2){
                cout << "#(";
            }

            while(temp != NULL){
                if(temp->data == list_Check){
                    List newList;
                    newList.setHead(temp->list);
                    newList.setFlag(1);
                    newList.traverse(newList.getHead());
                }else if(temp->data == array_Check){
                    List newList;
                    newList.setHead(temp->list);
                    newList.setFlag(2);
                    newList.traverse(newList.getHead());
                }else{
                    cout << temp->data << " ";
                }

                temp = temp->next;
            }

            cout << ") ";
        }

        void insertValue(string data, int index){ // 값 하나 , 인덱스에 (사이에) 넣기
            NODE* node = new NODE;
            node->data = data;
            node->next = NULL;
            node->list = NULL;

            if(index == 0){
                node->next = head;
                head = node;

                size++;

                return;
            }

            NODE* previous = head;
            NODE* after = head;

            for(int i=0;i<index;i++){
                previous = after;
                after = after->next;
            }
            previous->next = node;
            node->next = after;
            size++;
        }

        void insertList(class List list, int index){ // 사이에 리ㅡㅅ트넣기
            NODE* node = new NODE; 
            node->data = "dummy";
            node->next = NULL;
            node->list = list.head;

            if(index == 0){
                node->next = head;
                head = node;

                size++;

                return;
            }

            NODE* previous = head;
            NODE* after = head;

            for(int i=0;i<index;i++){
                previous = after;
                after = after->next;
            }

            previous->next = node;
            node->next = after;
            size++;
        }

        void reverse(List& reverse_list, NODE* head){
            if(head->next == NULL){
                reverse_list.addNode(head);
            }else{
                reverse(reverse_list, head->next);

                reverse_list.addNode(head);
            }
        }

        string back(){
            return tail->data;
        }

        string front(){ // 리스트 맨 앞 데이터
            return head->data;
        }

        NODE* getHead(){ // private head 구하기
            return head;
        }

        void setHead(NODE *head){
            this->head = head;
        }

        int getSize(){
            return size;
        }

        void setFlag(int flag){
            this->flag = flag;
        }

        int getFlag(){
            return flag;
        }
};

#endif