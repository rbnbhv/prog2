#include <iostream>
using namespace std;

class LinkedList {
    struct ListElem {
        int m_i;
        ListElem* m_pNext = nullptr;
        
        ListElem(int i, ListElem* next) : m_i(i), m_pNext(next) {
        }
        
        friend ostream& operator <<(ostream& os, const ListElem& crArg) {
            os << crArg.m_i << " ";
            if (crArg.m_pNext) {
                os << *crArg.m_pNext;
            }
            return os;
        }
    };
    
private:
    ListElem* m_pHead = nullptr;
    ListElem* m_pTail = nullptr;
    
public:
    LinkedList() {
    }
    
    LinkedList(const LinkedList& l) {
        copyHelper(l);
    }
    
    ~LinkedList() {
        destroy();
    }
    
    LinkedList& operator=(const LinkedList& l) {
        if (this == &l) {
            return *this;
        }
        destroy();
        copyHelper(l);
        return *this;
    }
    
    void copyHelper(const LinkedList& l) {
        ListElem *p = l.m_pHead;
        while (p) {
            this->push_back(p->m_i);
            p = p->m_pNext;
        }
    }
    
    void destroy() {
        ListElem* p = nullptr;
        while (m_pHead) {
            p = m_pHead->m_pNext;
            delete m_pHead;
            m_pHead = p;
        }
        m_pTail = nullptr;
    }
    
    void push_front(int elem) {
        m_pHead = new ListElem(elem, m_pHead);
        if (!m_pTail) {
            m_pTail = m_pHead;
        }
    }
    
    void push_back(int elem) {
        ListElem* node = new ListElem(elem, nullptr);
        if (!m_pHead) {
            m_pHead = m_pTail = node;
        } else {
            m_pTail->m_pNext = node;
            m_pTail = m_pTail->m_pNext;
        }
    }
    
    void pop_front() {
        if (m_pHead == m_pTail) {
            delete m_pHead;
            m_pHead = m_pTail = nullptr;
        }
        else {
            ListElem* p = m_pHead;
            m_pHead = m_pHead->m_pNext;
            delete p;
        }
    }
    
    void pop_back() {
        if (m_pHead == m_pTail) {
            delete m_pHead;
            m_pHead = m_pTail = nullptr;
        }
        else {
            ListElem* p = m_pHead;
            while (p->m_pNext != m_pTail) {
                p = p->m_pNext;
            }
            delete m_pTail;
            m_pTail = p;
            m_pTail->m_pNext = nullptr;
        }
    }
    
    int front() {
        return m_pHead->m_i;
    }
    
    int back() {
        return m_pTail->m_i;
    }
    
    friend ostream& operator <<(ostream& os, const LinkedList& l) {
        if (l.m_pHead) {
            os << *l.m_pHead;
        }
        return os;
    }
    
    void deleteIdx(int index) {
        ListElem** p = &m_pHead;
        for(int count = 0; count < index; ++count) {
            if (((*p)->m_pNext) == m_pTail) {
                m_pTail = *p;
            }
            p = &((*p)->m_pNext);
        }
        ListElem* pToDelete = *p;
        *p = (*p)->m_pNext;
        delete pToDelete;
    }
    
    void deleteEverySecond() {
        ListElem* prev = m_pHead;
        ListElem* node = m_pHead->m_pNext;
        while(prev && node) {
            prev->m_pNext = node->m_pNext;
            delete node;
            prev = prev->m_pNext;
            if(prev) {
                node = prev->m_pNext;
                m_pTail = prev;
            }
        }
    }
    
    void invert() {
        ListElem* p = m_pHead;
        ListElem* prev = nullptr;
        ListElem* next = nullptr;
        m_pTail = m_pHead;
        while(p) {
            next = p->m_pNext;
            p->m_pNext = prev;
            prev = p;
            p = next;
        }
        m_pHead = prev;
    }
};

int main() {
    LinkedList l1;
    LinkedList l2;
    LinkedList l3;
    l1.push_back(2);
    l1.push_back(3);
    l2.push_back(4);
    l2.push_back(4);
    l2.push_back(6);
    
    cout << l1.front() << " front()" << endl;
    cout << l1.back() << " back()" << endl;
    cout << l1 << endl;
    l2 = l1;
    cout << l2.back()  << endl;
}
