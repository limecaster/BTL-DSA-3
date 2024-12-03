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
        if (this->count <= 1)
            return;

        int n = this->count;
        for (int step = 1; step < n; step *= 2)
        {
            Node *current = this->head;
            Node *newHead = nullptr;
            Node *tail = nullptr;

            while (current != nullptr)
            {
                Node *left = current;
                Node *right = split(left, step);
                current = split(right, step);

                Node *mergedHead = nullptr;
                Node *mergedTail = nullptr;
                merge(left, right, comparator, mergedHead, mergedTail);

                if (newHead == nullptr)
                {
                    newHead = mergedHead;
                }
                else
                {
                    tail->next = mergedHead;
                    mergedHead->prev = tail;
                }
                tail = mergedTail;
            }

            this->head = newHead;
            this->tail = tail;
        }
    }

    Node *split(Node *head, int n)
    {
        for (int i = 1; head != nullptr && i < n; i++)
        {
            head = head->next;
        }

        if (head == nullptr)
            return nullptr;

        Node *second = head->next;
        if (second != nullptr)
            second->prev = nullptr;
        head->next = nullptr;
        return second;
    }

    void merge(Node *left, Node *right, int (*comparator)(T &, T &), Node *&mergedHead, Node *&mergedTail)
    {
        Node dummy;
        Node *current = &dummy;

        while (left != nullptr && right != nullptr)
        {
            if (compare(left->data, right->data, comparator) <= 0)
            {
                current->next = left;
                left->prev = current;
                left = left->next;
            }
            else
            {
                current->next = right;
                right->prev = current;
                right = right->next;
            }
            current = current->next;
        }

        if (left != nullptr)
        {
            current->next = left;
            left->prev = current;
        }
        else if (right != nullptr)
        {
            current->next = right;
            right->prev = current;
        }

        while (current->next != nullptr)
        {
            current = current->next;
        }

        mergedHead = dummy.next;
        mergedHead->prev = nullptr;
        mergedTail = current;
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
