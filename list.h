#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "node.h"
#include "iterator.h"

using namespace std;

template <typename T>
class List {
    private:
        Node<T>* start;
        int nodes;

    public:
        List(): start(nullptr), nodes(0) {};
        T front(){
          if (start) return start->data;
          throw "No element in empty list";
        };
        T back(){
          if (start) return start->prev->data;
          throw "No element in empty list";
        };
        void push_front(T value){
          //Create new node
          Node<T>* newnode = new Node<T>;
          newnode->data = value;

          if (empty()) newnode->prev = newnode->next = newnode;
          else{
            //Link final and new node
            newnode->prev=start->prev;
            start->prev->next=newnode;
            //Link start node to new node
            start->prev=newnode;
            newnode->next=start;
          }
          //Change start for new node
          start=newnode;

          //List size increases by 1
          nodes++;
        };
        void push_back(T value){
          /* Note: push_back is exactly as push_front except
          for the 'Change start for new node' part. */
          //Create new node
          Node<T>* newnode = new Node<T>;
          newnode->data = value;

          if (empty()){
            newnode->prev = newnode->next = newnode;
            start=newnode;
          }
          else{
            //Link final and new node
            newnode->prev=start->prev;
            start->prev->next=newnode;
            //Link start node to new node
            start->prev=newnode;
            newnode->next=start;
          }
          //List size increases by 1
          nodes++;
        };
        void pop_front(){
          if (empty()) throw "Can not delete element in empty list";
          Node<T>* secondnode = start->next;
          //Link final and second node
          secondnode->prev=start->prev;
          start->prev->next=secondnode;
          //Erase previous start node
          start->next=start->prev=nullptr;
          delete start;
          //Change start node for second node
          start=secondnode;

          //List size decreases by 1
          nodes--;
        };
        void pop_back(){
          if (empty()) throw "Can not delete element in empty list";
          Node<T>* secondlastnode = start->prev->prev;
          //Erase content of previous final node
          delete start->prev;
          //Link second last node to start
          secondlastnode->next=start;
          start->prev=secondlastnode;

          //List size decreases by 1
          nodes--;
        };
        T get(int position){
          if (this->empty() || 0 > position) throw "No element in empty list";
          Node<T>* temporalnode = this->start;
          for (int i=0; i<position%nodes; i++) temporalnode = temporalnode->next;
          return temporalnode->data;
        };
        void concat(List<T> &other);
        bool empty(){ return !start; };
        int size(){ return nodes; };
        void clear();
        Iterator<T> begin(){};
        Iterator<T> end(){};

        ~List(){};
};

#endif
