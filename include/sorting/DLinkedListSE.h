/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   DLinkedListSE.h
 * Author: LTSACH
 *
 * Created on 31 August 2020, 14:13
 */

#ifndef DLINKEDLISTSE_H
#define DLINKEDLISTSE_H
#include "list/DLinkedList.h"
#include "sorting/ISort.h"

template <class T>
class DLinkedListSE : public DLinkedList<T>
{
public:
    DLinkedListSE(
        void (*removeData)(DLinkedList<T> *) = 0,
        bool (*itemEQ)(T &, T &) = 0) : DLinkedList<T>(removeData, itemEQ) {

                                        };

    DLinkedListSE(const DLinkedList<T> &list)
    {
        this->copyFrom(list);
    }

    void sort(int (*comparator)(T &, T &) = 0)
    {
        if (this->count <= 1) return;

        // Perform merge sort on the list
        this->head->next = mergeSort(this->head->next, comparator);

        // Update tail pointer
        typename DLinkedList<T>::Node* temp = this->head;
        while (temp->next != this->tail) {
            temp = temp->next;
        }
        temp->next = this->tail;
        this->tail->prev = temp;
    }

    private:
    typename DLinkedList<T>::Node* mergeSort(typename DLinkedList<T>::Node* start, int (*comparator)(T&, T&) = 0) {
        if (start == this->tail || start->next == this->tail) {
            return start;
        }

        // Split the list into halves
        typename DLinkedList<T>::Node* middle = getMiddle(start);
        typename DLinkedList<T>::Node* nextOfMiddle = middle->next;

        // Disconnect the left half from the right half
        middle->next = this->tail;
        this->tail->prev = middle;

        // Recursively sort the sublists
        typename DLinkedList<T>::Node* left = mergeSort(start, comparator);
        typename DLinkedList<T>::Node* right = mergeSort(nextOfMiddle, comparator);

        // Merge the sorted sublists
        return merge(left, right, comparator);
    }

    typename DLinkedList<T>::Node* getMiddle(typename DLinkedList<T>::Node* start) {
        if (start == this->tail) return start;

        typename DLinkedList<T>::Node* slow = start;
        typename DLinkedList<T>::Node* fast = start->next;

        while (fast != this->tail && fast->next != this->tail) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    typename DLinkedList<T>::Node* merge(typename DLinkedList<T>::Node* left, typename DLinkedList<T>::Node* right, int (*comparator)(T&, T&) = 0) {
        typename DLinkedList<T>::Node dummy;
        typename DLinkedList<T>::Node* tail = &dummy;

        while (left != this->tail && right != this->tail) {
            if (compare(left->data, right->data, comparator) <= 0) {
                tail->next = left;
                left->prev = tail;
                left = left->next;
            } else {
                tail->next = right;
                right->prev = tail;
                right = right->next;
            }
            tail = tail->next;
        }

        tail->next = (left != this->tail) ? left : right;
        if (tail->next != this->tail) {
            tail->next->prev = tail;
        } else {
            this->tail->prev = tail;
        }

        return dummy.next;
    }
    
protected:
    static int compare(T &lhs, T &rhs, int (*comparator)(T &, T &) = 0)
    {
        if (comparator != 0)
            return comparator(lhs, rhs);
        else
        {
            if (lhs < rhs)
                return -1;
            else if (lhs > rhs)
                return +1;
            else
                return 0;
        }
    }
};

#endif /* DLINKEDLISTSE_H */
