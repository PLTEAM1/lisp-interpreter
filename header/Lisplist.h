#ifndef _LISPLIST_H
#define _LISPLIST_H

#include <iostream>
#include <vector>

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
        //yae
        bool flag;
    public:
        List(){
            head = NULL;
            tail = NULL;
            //yae
            flag = false;
            size = 0;
        }
        //yae
        void setList(){
            flag = true;
        }
        bool isList(){
            return flag;
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
            add("dummy"); // yae, 특문으로 바꾸기

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

            while(temp!= NULL){
                if(temp->data != "dummy"){
                    cout << temp->data << " ";
                }else{
                    cout << "( ";
                    traverse(temp->list);
                    cout << ") ";
                }

                temp = temp->next;
            }
        }
        
        bool compare(NODE* pHead,NODE* qHead){
            NODE* origin = pHead;
            NODE* compared = qHead;

            while(origin != NULL){
                if(origin->data != compared->data) return false;
                else if(origin->data == "dummy"){
                    bool flag = compare(origin->list, compared->list);
                    if(flag == false) return false;
                }

                origin = origin->next;
                compared =compared->next;
            }

            return true;

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
};

#endif