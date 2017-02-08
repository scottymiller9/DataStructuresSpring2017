#include <iostream>

using namespace std;



typedef struct node {
    int data;
    node *next;
};

void printList(node *head, int &n) {
    node *t = head;
    for (int i = 0; i < n; i++) {
        t = t->next;

        cout << t->data << ' ';
    }
}

bool check(int a, int b, node *head, int &num) {
    node *temp = head->next;
    bool A = false;
    bool B = false;
    for (int i = 0; i < num; i++) {
        if (temp->data == a || temp->next->data == a) {
            A = true;
        } else if (temp->data == b || temp->next->data == b) {
            B = true;
        }
        temp = temp->next;
    }
    if (A && B) {
        return true;
    } else return false;
}

void editList(int a, int b, int s, node *head, int &num) {
    bool bInst = false;
    node *temp = head;
    node *prev = temp;
    if (!check(a, b, head, num)) {
        return;
    }
    while (temp->data != a) {
        prev = temp;
        temp = temp->next;
    }
    //adds node to know when to stop
    node *loopEnd = new node;
    loopEnd->data = NULL;
    prev->next = loopEnd;
    loopEnd->next = temp;
    while (temp != loopEnd) {
        //       printList(head,num);
        //     cout << endl;
        int i = 0;
        while (i < s - 1) {
            if (temp->data == b) {
                bInst = true;
            }
            prev = temp;
            temp = temp->next;
            i++;
        }
        int value = temp->data;
        if (temp->data == head->next->data) {
            head->next = temp->next;
        }
        if (temp->next != NULL && !bInst) {
            if (prev->next == loopEnd) {
                loopEnd->next = temp->next;
                temp = temp->next;
                num--;
            } else {
                prev->next = temp->next;
                temp = temp->next;
                num--;
            }
        }
        if (value == b || bInst) {
            int k = 0;
            while (temp->next != loopEnd) {
                temp = temp->next;
                if(k > num + 1){
                    return;
                }
                k++;
            }
            temp->next = loopEnd->next;
            return;
        }
    }
}

int main() {
    int n;
    cin >> n;
    int &num = n;
    node *head = new node;
    node *temp = head;
    head->next = temp;
    for (int i = 0; i < n; i++) {
        node *newNode = new node;
        int input = 0;
        cin >> input;
        newNode->data = (input);
        newNode->next = NULL;
        temp->next = newNode;
        temp = temp->next;
    }
    temp->next = head->next;
    int m;
    int a, b, s;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> a;
        cin >> b;
        cin >> s;
        editList(a, b, s, head, num);
    }

    printList(head, num);

    return 0;
}