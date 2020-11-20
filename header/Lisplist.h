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
    public:
        List(){
            head = NULL;
            tail = NULL;
            size = 0;
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
            add("dummy");

            NODE* temp = list.head;
            if(head == NULL){
                head = temp;
                tail = temp;
            }else{
                tail->list = temp;
            }
        }

        void traverse(NODE* head){
            NODE* temp = head;

            while(temp!= NULL){
                if(temp->data != "dummy"){
                    cout << temp->data << " ";
                }else{
                    cout << "(";
                    traverse(temp->list);
                    cout << ")";
                }

                temp = temp->next;
            }
        }

        void insertValue(string data, int index){
            NODE* node = new NODE;
            node->data = data;
            node->next = NULL;
            node->list = NULL;

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

        void insertList(class List list, int index){
            NODE* node = new NODE;
            node->data = "dummy";
            node->next = NULL;
            node->list = list.head;

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

        string back(){
            return tail->data;
        }

        string front(){
            return head->data;
        }

        NODE* getHead(){
            return head;
        }

        int getSize(){
            return size;
        }
};

#endif