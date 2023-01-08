#pragma once

//i190663
//Abdul Samie
//The etwork emulator
#include <iostream>
#include <cstring>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <list>
#include <iterator>
#include <queue>
#include <sstream>
#include <Windows.h>
using namespace std;

int ST = -1;


template<typename T>
struct List
{
    T _data;
    struct List<T>* _next;

    List()
    {
        _next = NULL;
    }

    template<typename T>
    void insert(T data)
    {
        List<T>* tempHead = this;
        List<T>* temp = new List<T>;
        temp->_data = data;
        temp->_next = NULL;

        if (tempHead == NULL)
        {
            tempHead = temp;
            return;
        }
        else
        {
            temp->_next = tempHead;
            tempHead = temp;
        }
    }


    template<typename T>
    void deleteValue(T data)
    {
        List<T>* tempHead = this;
        if (tempHead == NULL)
        {
            cout << "Empty List\n";
        }
        else if (tempHead->_data == data)
        {
            *this = *tempHead->_next;
            delete tempHead;
        }
        else
        {
            while (tempHead->_next != NULL && tempHead->_next->_data != data)
            {
                tempHead = tempHead->_next;
            }
            if (tempHead->_next != NULL && tempHead->_next->_data == data)
            {
                List<T>* tempDelete = tempHead->_next;
                tempHead->_next = tempHead->_next->_next;
                delete tempDelete;
            }
            else
            {
                cout << "value not found\n";
            }
        }
    }


    template<typename T>
    void displayList()
    {
        List<T>* tempHead = this;
        while (tempHead != NULL)
        {
            cout << tempHead->_data << " -> ";
            tempHead = tempHead->_next;
        }

        if (tempHead == NULL)
            cout << "END\n";
    }
};





template<typename T>
struct QNode {
    T data;
    struct QNode* next;
    T getData() {
        // T value;
        // value = dequeue();
        return data;
    }
};










template<typename T>
class Queue {
public:
    struct QNode<T>* front = NULL;
    struct QNode<T>* rear = NULL;
    struct QNode<T>* temp;


    T dequeue() {
        temp = front;
        T tmp1;
        if (front == NULL) {
            cout << "Underflow" << endl;
            return 0;
        }
        else
            if (temp->next != NULL) {
                temp = temp->next;
                tmp1 = front->data;
                //cout << "Element deleted from queue is : " << front->data << endl;
                free(front);
                front = temp;
            }
            else {
                tmp1 = front->data;
                //cout << "Element deleted from queue is : " << front->data << endl;
                free(front);
                front = NULL;
                rear = NULL;
            }
        return tmp1;
    }
    ///public:

    bool isEmpty() {
        bool tmp1;
        if (front == NULL) {
            tmp1 = true;
        }
        else
            tmp1 = false;

        return tmp1;
    }

    void enqueue(T val) {

        if (rear == NULL) {
            rear = new QNode<T>;
            rear->next = NULL;
            rear->data = val;
            front = rear;
        }
        else {
            temp = new QNode<T>;
            rear->next = temp;
            temp->data = val;
            temp->next = NULL;
            rear = temp;
        }
    }



    T Front() {
        temp = front;
        T tmp1;
        if ((front == NULL) && (rear == NULL)) {
            cout << "Queue is empty" << endl;
            return 0;
        }
        else {
            tmp1 = temp->data;
        }
        return tmp1;

    }

    QNode<T>* getRear() {
        return rear;
    }

    void Display() {
        temp = front;
        if ((front == NULL) && (rear == NULL)) {
            cout << "Queue is empty" << endl;
            return;
        }
        cout << "Queue elements are: ";
        while (temp != NULL) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }


    int count() {
        int cn = 0;
        temp = front;
        if ((front == NULL) && (rear == NULL)) {
            cout << "Queue is empty" << endl;
            return 0;
        }
        //cout << "Queue elements are: ";
        while (temp != NULL) {
            cn++;
            temp = temp->next;
        }
        //cout << endl;
        return cn;
    }

    void queueConcat(string str) {
        int tmp1 = str.length();
        for (int i = 0; i < tmp1; i++) {
            if (str[i] != ' ') {
                enqueue(str[i]);
            }
        }
    }
};










template<typename T>
struct BST
{
    T data;
    BST<T>* left;
    BST<T>* right;

    BST();

    BST(T);

    BST* Insert(BST*, T);

    BST* Delete(BST*, T);
};

template<typename T>
BST<T>::BST()
    :left(NULL)
    , right(NULL)
{
}

template<typename T>
BST<T>::BST(T value)
{
    data = value;
    left = right = NULL;
}











template<typename T>
BST<T>* BST<T>::Insert(BST<T>* root, T value)
{
    if (!root)
    {
        return new BST(value);
    }

    if (value > root->data)
    {
        root->right = Insert(root->right, value);
    }
    else
    {
        root->left = Insert(root->left, value);
    }

    return root;
}

template<typename T>
BST<T>* leftRotate(BST<T>* x)
{
    BST<T>* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}















template<typename T>
BST<T>* rightRotate(BST<T>* x)
{
    BST<T>* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

template<typename T>
BST<T>* splay(BST<T>* root, T data)
{
    if (root == NULL || root->data == data)
        return root;

    if (root->data > data)
    {
        if (root->left == NULL) return root;

        if (root->left->data > data)
        {
            root->left->left = splay(root->left->left, data);

            root = rightRotate(root);
        }
        else if (root->left->data < data) // Zig-Zag (Left Right)
        {
            root->left->right = splay(root->left->right, data);

            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }

        return (root->left == NULL) ? root : rightRotate(root);
    }
    else // data lies in right subtree
    {
        if (root->right == NULL) return root;

        if (root->right->data > data)
        {
            root->right->left = splay(root->right->left, data);

            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }
        else if (root->right->data < data)// Zag-Zag (Right Right)
        {
            root->right->right = splay(root->right->right, data);
            root = leftRotate(root);
        }

        return (root->right == NULL) ? root : leftRotate(root);
    }
}

template<typename T>
BST<T>* BST<T>::Delete(BST<T>* root, T data)
{
    BST* temp;
    if (!root)
        return NULL;

    root = splay(root, data);

    if (data != root->data)
        return root;

    if (!root->left)
    {
        temp = root;
        root = root->right;
    }

    else
    {
        temp = root;

        root = splay(root->left, data);

        root->right = temp->right;
    }

    free(temp);

    return root;

}

template<typename T>
BST<T>* insert(BST<T>* root, T data)
{
    root = root->Insert(root, data);
    return splay(root, data);
}









template<typename T>
BST<T>* search(BST<T>* root, T data)
{
    return splay(root, data);
}








template<typename T>
void preOrder(BST<T>* root)
{
    if (root != NULL)
    {
        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

//function for printing the elements in a list
void showListStr(list<string> g)
{
    for (list<string>::iterator it = g.begin(); it != g.end(); ++it)
        cout << *it << '\n';
    cout << '\n';
}

// Print the queue
void showQStr(queue<string> gq)
{
    queue<string> g = gq;
    while (!g.empty()) {
        cout << '\t' << g.front();
        g.pop();
    }
    cout << '\n';
}

class Message {
public:
    int msgID;
    int priority;
    string sourceAddress;
    string destinationAddress;
    string payload;
    string trace;
    Message() {
        srand(time(NULL));
        msgID = rand();
        priority = rand() % 10;
    }
    Message(string sourceAdd, string destinationAdd, string pl) {
        srand(time(NULL));
        msgID = rand();
        priority = rand() % 10;
        sourceAddress = sourceAdd;
        destinationAddress = destinationAdd;
        payload = pl;
    }
};

//void Push(list<Node> neigh, Message* msg)
//{
//    Node* temp;
//    int i = 0;
//    for (list<Node>::iterator it = neigh.begin(); it != neigh.end(); ++it, i++)
//    {
//        //Node* temp = &*it;
//        
//    }
//}

class Node {
public:
    string name;
    list<Node> neighbours;
    list<int> weights;

    string getName()
    {
        return name;
    }

    void printNode()
    {
        cout << "Name: " << name << endl;
        cout << "Neighbours: ";
        for (list<Node>::iterator it = neighbours.begin(); it != neighbours.end(); ++it)
        {
            Node* Temp = &*it;
            cout << Temp->getName() << ", ";
        }
        cout << "\nWeights: ";
        for (list<int>::iterator it = weights.begin(); it != weights.end(); ++it)
        {
            int* Temp = &*it;
            cout << *Temp << ", ";
        }
        cout << endl;
    }
};






class Machine : public Node {
public:
    list<Message> sendbuf;
    list<Message> recievebuf;

    Machine()
    {

    }

    void insertMsg(Message* msg)
    {
        sendbuf.push_back(*msg);
    }

    void Print()
    {
        printNode();
    }
};

class Router : public Node {
public:
    list<Node> destinationNode;      //for Routing table using Splaay Trees or Linear lists
    list<Node> outgoingqueNode;      //for routing table using Splaay trees or Linear lists

    BST<Node> DesTree;
    BST<Node> OutTree;

    queue<Message> incoming;       //Min Heap sort according to priority of message------Pending
    list<queue<Message>> outqueue;   //FIFO with one second delay

    Router()
    {

    }

    void setDes()
    {

    }
};









class networks
{
public:
    list<Machine> maclist;
    list<Router> routlist;

    void printMacList()
    {
        for (list<Machine>::iterator it = maclist.begin(); it != maclist.end(); ++it)
        {
            Node* Temp = &*it;
            Temp->printNode();
        }
    }

    void printRoutList()
    {
        for (list<Router>::iterator it = routlist.begin(); it != routlist.end(); ++it)
        {
            Node* Temp = &*it;
            Temp->printNode();
        }
    }
};

Machine* getMacIdx(list<Machine>& _list, int& _i)
{
    list<Machine>::iterator it = _list.begin();
    for (int i = 0; i < _i; i++) {
        ++it;
    }
    return &*it;
}

Machine* getMacName(list<Machine>& _list, string& _i)
{
    for (list<Machine>::iterator it = _list.begin(); it != _list.end(); ++it)
    {
        string str = (*it).getName();
        if (_i == str)
            return &*it;
    }
}

Router* getRoutIdx(list<Router>& _list, int& _i)
{
    list<Router>::iterator it = _list.begin();
    for (int i = 0; i < _i; i++) {
        ++it;
    }
    return &*it;
}

Router* getRoutName(list<Router>& _list, string& _i)
{
    for (list<Router>::iterator it = _list.begin(); it != _list.end(); ++it)
    {
        string str = (*it).getName();
        if (_i == str)
            return &*it;
    }
}











void preprocessing(string filename, networks* net)
{
    //File Reading from filename
     //skip first line
     //tokenize file
            //{ After reading R value, add R to routers's list
            // Read next token-> if != ? -> go to machine's list index = token(index-1),add machine's neighbours' list R, add machine weightlist value....
            // in current router, add to router neighbour list machine index = token(index-1), add router weightlist value....
            // repeat for tokens = no. of  machines + 1 }
    fstream myFile;
    list<string> Lines;
    string strLine;
    cout << "Processing-----\n";

    myFile.open("network.csv", ios::in); //open a file to perform read operation using file object
    if (myFile.is_open())
    {   //checking whether the file is open
        while (getline(myFile, strLine))
        {
            //read data from file object and put it into string.
            //cout << strLine << "\n"; //print the data of the string
            Lines.push_back(strLine);
        }

        Lines.pop_front();
        showListStr(Lines);

        for (list<string>::iterator it = Lines.begin(); it != Lines.end(); ++it)
        {
            string temp = *it;

            if (temp[0] == 'M' || temp[0] == 'm')
            {
                stringstream ss(temp);

                vector<string> tokens;
                string temp_str;

                while (getline(ss, temp_str, ','))
                {
                    //use comma as delim for cutting string
                    tokens.push_back(temp_str);
                }

                //cout << "it is a machine ->" << tokens[0] << endl;
                Machine temp;
                temp.name = tokens[0];
                net->maclist.push_back(temp);
            }

            else if (temp[0] == 'R' || temp[0] == 'r')
            {
                stringstream ss(temp);

                vector<string> tokens;
                string temp_str;

                while (getline(ss, temp_str, ','))
                {
                    //use comma as delim for cutting string
                    tokens.push_back(temp_str);
                }

                //cout << "it is a Router ->" << tokens[0] << endl;
                Router temp;
                temp.name = tokens[0];
                net->routlist.push_back(temp);
            }
        }

        for (list<string>::iterator it = Lines.begin(); it != Lines.end(); ++it)
        {
            string temp = *it;
            stringstream ss(temp);

            vector<string> tokens;
            string temp_str;

            while (getline(ss, temp_str, ','))
            {
                //use comma as delim for cutting string
                tokens.push_back(temp_str);
                //cout << "temp_str: " << temp_str << endl;
            }

            int j = 0;
            Node* SouNode = NULL;
            Node* DesNode = NULL;

            for (auto i = tokens.begin(); i != tokens.end(); ++i, j++)
            {
                if (j == 0)
                {
                    if (temp[0] == 'M' || temp[0] == 'm')
                    {
                        SouNode = getMacName(net->maclist, *i);
                    }
                    else if (temp[0] == 'R' || temp[0] == 'r')
                    {
                        SouNode = getRoutName(net->routlist, *i);
                    }
                }
                else if (*i != "?")
                {
                    if (j > 0 && j < (net->maclist.size() + 1))
                    {
                        int tempi = (j - 1);
                        DesNode = getMacIdx(net->maclist, tempi);

                        SouNode->neighbours.push_back(*DesNode);
                        SouNode->weights.push_back(stoi(*i));
                    }
                    else if (j >= (net->maclist.size() + 1))
                    {
                        int tempi = (j - 1 - net->maclist.size());
                        DesNode = getRoutIdx(net->routlist, tempi);

                        SouNode->neighbours.push_back(*DesNode);
                        SouNode->weights.push_back(stoi(*i));
                    }
                }

            }

        }
        myFile.close(); //close the file object.
    }
    else
    {
        cout << "File Not Found." << endl;
    }
}









void print(std::vector <string> const& a) {
    cout << "Parameter: ";

    for (int i = 0; i < a.size(); i++)
        cout << a.at(i) << ' ';
    cout << endl;
}

string returnNei(list<Node> myList, string Des)
{
    Node* temp;
    for (list<Node>::iterator it = myList.begin(); it != myList.end(); ++it)
    {
        Node* temp = &*it;
        if (temp->name == Des)
            return temp->name;
    }
}

void sendMsg(networks* net, Message* msg)
{
    for (list<Machine>::iterator it = net->maclist.begin(); it != net->maclist.end(); ++it)
    {
        Node* temp = &*it;
        if (temp->name == msg->sourceAddress)
        {
            msg->trace += returnNei(temp->neighbours, msg->destinationAddress);
            Sleep(1000);
        }
    }

}






void setDes(networks* net)
{
    for (list<Router>::iterator it = net->routlist.begin(); it != net->routlist.end(); ++it)
    {
        Router* temp = &*it;
    }
}


int main(int argc, char** argv)
{


    networks* objNet = new networks;
    string filename = "Network1.txt";
    preprocessing(filename, objNet);
    //command tokenize after input------if else likhny hain

    //obj->printMacList();
    //obj->printRoutList();

    /*vector<string> argList;
    for (int i = 0; i < argc; i++)
        argList.push_back(argv[i]);

    print(argList);*/

    cout << "0 for Splays Tree\n";
    cout << "1 for linear List\n";
    int i = -1;
    cin >> i;
    if (i == 0)
        ST = 1;
    else
        ST = 0;

    cout << "1) Send Message" << endl;
    cout << "2) Add RT" << endl;
    cout << "3) Remove RT" << endl;
    cout << "4) Print Path" << endl;

    int input;
    cin >> input;

    Message* myMsg = NULL;

    if (input == 1)
    {
        int id = -1;
        int pri = -1;
        string souAdd = "";
        string desAdd = "";
        string payLoad = "";
        string trace = "";
        cout << "Message ID: ";
        cin >> id;
        cout << "Priority: ";
        cin >> pri;
        cout << "Source Address: ";
        getline(cin, souAdd);
        cout << "Destination Address: ";
        getline(cin, desAdd);
        cout << "Payload: ";
        getline(cin, payLoad);

        myMsg = new Message;
        myMsg->msgID = id;
        myMsg->priority = pri;
        myMsg->sourceAddress = souAdd;
        myMsg->destinationAddress = desAdd;
        myMsg->payload = payLoad;

        sendMsg(objNet, myMsg);
    }
    else if (input == 2)
    {
        string name;
        string nei;
        string wei;
        cout << "Router Name: ";
        getline(cin, name);
        cout << "Neighbours:";
        getline(cin, nei);
        cout << "Correspondig weights: ";
        getline(cin, wei);

        cin.ignore();

        Router* tempRout = new Router;
        tempRout->name = name;

        string temp = nei;
        stringstream ss(temp);

        vector<string> tokens;
        string temp_str;

        while (getline(ss, temp_str, ','))
        {
            //use comma as delim for cutting string
            //tokens.push_back(temp_str);
            //cout << "temp_str: " << temp_str << endl;
            for (list<Machine>::iterator it = objNet->maclist.begin(); it != objNet->maclist.end(); ++it)
            {
                tempRout->neighbours.push_back(*it);
            }

            for (list<Router>::iterator it = objNet->routlist.begin(); it != objNet->routlist.end(); ++it)
            {
                tempRout->neighbours.push_back(*it);
            }
        }

        temp = wei;
        stringstream sss(temp);

        vector<string> tokenss;
        string temp_strr;

        while (getline(sss, temp_strr, ','))
        {
            //use comma as delim for cutting string
            //tokens.push_back(temp_str);
            //cout << "temp_str: " << temp_str << endl;
            for (list<Machine>::iterator it = objNet->maclist.begin(); it != objNet->maclist.end(); ++it)
            {
                tempRout->neighbours.push_back(*it);
            }

            for (list<Router>::iterator it = objNet->routlist.begin(); it != objNet->routlist.end(); ++it)
            {
                tempRout->neighbours.push_back(*it);
            }
        }

        objNet->routlist.push_back(*tempRout);
    }
    else if (input == 4)
    {
        cout << "of: ";
        string c = "";
        getline(cin, c);
        cin.ignore();

        if (c[0] == 'm' || c[0] == 'M')
        {
            for (list<Machine>::iterator it = objNet->maclist.begin(); it != objNet->maclist.end(); ++it)
            {
                Node* temp = &*it;
                if (temp->name == c)
                {
                    if (ST == 0)
                    {
                        for (list<Node>::iterator it = temp->neighbours.begin(); it != temp->neighbours.end(); ++it)
                        {
                            Node* temp = &*it;
                            cout << temp->name << " ";
                        }
                        cout << "\n";
                        break;
                    }
                    else
                    {

                    }
                }
            }
        }
        else if (c[0] == 'r' || c[0] == 'R')
        {
            for (list<Router>::iterator it = objNet->routlist.begin(); it != objNet->routlist.end(); ++it)
            {
                Node* temp = &*it;
                if (temp->name == c)
                {
                    if (ST == 0)
                    {
                        for (list<Node>::iterator it = temp->neighbours.begin(); it != temp->neighbours.end(); ++it)
                        {
                            Node* temp = &*it;
                            cout << temp->name << " ";
                        }
                        cout << "\n";
                        break;
                    }
                    else
                    {
                        BST<string>* root = NULL;
                        for (list<Node>::iterator it = temp->neighbours.begin(); it != temp->neighbours.end(); ++it)
                        {
                            Node* temp = &*it;
                            root->Insert(root, temp->getName());
                        }
                        preOrder(root);
                    }
                }
            }
        }
    }

    return 0;
}
