#ifndef _LISPLIST_H
#define _LISPLIST_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <string>

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

            if(this->flag != 0){
                cout << ") ";
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

        bool isListIn(){
            NODE* temp = head;

            while(temp != NULL){
                if(temp->data==list_Check) return true;
                temp =temp->next;
            }
            return false;
        }

        string getAssoc(string key){
            NODE* temp = head;
            NODE* ret;
            while(temp!= NULL){
                if(temp->data==list_Check){

                    ret = _getAssoc(key, temp->list);
                    if(ret != NULL){
                        NODE* listTemp = temp->list;
                        string result = "( ";
                        while(listTemp != NULL){
                            result.append(listTemp->data);
                            result.append(" ");
                            listTemp = listTemp->next;
                        }
                        result.append(")");
                        return result;
                    }
                }
                temp = temp->next;
            }
            
            return "NIL";
        }

        NODE* _getAssoc(string key, NODE* connected){
            if(connected->data == key){ 
                return connected;
            }
            else return NULL;
        }

        List getRemove(string key){
            List ret;
            NODE* temp = head;
            bool addFlag = false;

            if(this->flag == 1){
                ret.add("(");
                addFlag = true;
            }else if(this->flag == 2){
                ret.add("#(");
                addFlag = true;
            }

            while(temp != NULL){
                if(temp->data == list_Check){
                    List newList;
                    newList.setHead(temp->list);
                    newList.setFlag(1);
                    _getRemove(ret, newList);
                }else if(temp->data == array_Check){
                    List newList;
                    newList.setHead(temp->list);
                    newList.setFlag(2);
                    _getRemove(ret, newList);
                }else{
                    if(temp->data != key) ret.add(temp->data.append(" "));
                }

                temp = temp->next;
            }

            if(this->flag != 0){
                ret.add(") ");
            }
            return ret;
        }

        void _getRemove(List& ret, List input){
            NODE* temp = input.getHead();

            if(input.flag == 1){
                ret.add("(");
            }else if(input.flag == 2){
                ret.add("#(");
            }

            while(temp!=NULL){
                ret.add(temp->data.append(" "));
                temp = temp->next;
            }

            ret.add(")");
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

        string getListCheck(){
            return list_Check;
        }

        string getArrayCheck(){
            return array_Check;
        }
};

#endif