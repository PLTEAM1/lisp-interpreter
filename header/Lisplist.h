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
    public:
        List(){
            head = NULL;
            tail = NULL;
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
        }
        
        void addList(class List list){
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

        NODE* getHead(){
            return head;
        }
};

#endif