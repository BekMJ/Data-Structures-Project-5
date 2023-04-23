// Project 5
// CS 2413 Data Structures
// Spring 2023
// Bilguunzaya Mijiddorj


#include <iostream>
#include <string> // for the fields in the class
#include <vector> // for the flowchart structures
#include <stack>  // for conversion


using namespace std;

// class to store node information
class Node
{
private:
    int nodeNumber;    // to store the node number
    string type;       // can either be START, END, IF, BLOCK
    string textWithin; // can be expression or statement - for START and END this will be empty string
    int leftNode; // number of the node that this node points to, if the block is if block then leftnode is when the expression is true
    int rightNode; // if the node is IF block, then rightNode is when the expression is false
    bool isNodeElse; // whether this node is a negative path (if expression is false)
    int countNodes; // number of nodes pointing to this node


public:
    // TODO: construtors, getters, setters and other methods as needed
    Node() : nodeNumber(0), type(""), textWithin(""), leftNode(-1), rightNode(-1),
    isNodeElse(false), countNodes(0){} // default constructor
    Node(int n, string tempType, string textW){
        nodeNumber = n;
        type = tempType;
        textWithin = textW;
        leftNode = -1; rightNode = -1; isNodeElse = false; countNodes = 0;
    };
    // all the getters and setters
    int getcountNodes(){
        return countNodes;
    }
    int getisNodeElse(){
        return isNodeElse;
    }
    int getNumber(){
        return nodeNumber;
    }
    int getleftNode(){
        return leftNode;
    }
    int getrightNode(){
        return rightNode;
    }
    string getType(){
        return type;
    }
    string getText(){
        return textWithin;
    }
    void setleftNode(int x){
        leftNode = x;
    }
    void setrightNode(int x){
        rightNode = x;
    }
    void setisNodeElse(){
        isNodeElse = true;
    }
    void incrementCountNodes(){
        countNodes++;
    }
    void decrementCountNodes(){
        countNodes--;
    }
    void display(){
        if(textWithin.compare("") != 0){
            cout << nodeNumber << ": " << type << " node - " << textWithin << endl;
        }
        else {
            cout << nodeNumber << ": " << type << " node"<< endl;
        }

    } // print method
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// function to convert the given flowchart to generate code
void convertFlowChart(vector<Node> allNodes, vector<vector<int>> adjList)
{

    stack<int> nodeStack;
// Push the first node onto the stack
    nodeStack.push(0);

// While there are nodes to visit
    while (!nodeStack.empty()) {
        // Get the node at the top of the stack
        int currentNode = nodeStack.top();
        // Pop the node off the stack
        nodeStack.pop();

        // Get the type of the current node
        string nodeType = allNodes[currentNode].getType();

        // If the node is a START node
        if (nodeType == "START") {
            // Output the "start" statement
            cout << "start" << endl;
            // Push the next node onto the stack
            // Push the next node onto the stack (the "true" branch)

            if(allNodes[currentNode].getleftNode() != -1) {
                nodeStack.push(allNodes[currentNode].getleftNode());
            }
        }
        else if (nodeType == "IF") {
            //  go through the node iff the num of nodes pointing to this node is 1, if not decrement it
            if (allNodes[currentNode].getcountNodes() == 1){
                // Get the expression for the IF statement
                string expression = allNodes[currentNode].getText();
                // Output the "if" statement with the expression
                cout << "if (" << expression << ")" << endl;
                cout << "{" << endl;

                // Push the node after the "if" statement onto the stack (the "false" branch)
                if(allNodes[currentNode].getrightNode() != -1){
                    nodeStack.push(allNodes[currentNode].getrightNode());
                }

                // Push the next node onto the stack (the "true" branch)
                if(allNodes[currentNode].getleftNode() != -1) {
                    nodeStack.push(allNodes[currentNode].getleftNode());
                }
            }
            else { // decrement the num of nodes pointing to this node by 1
                allNodes[currentNode].decrementCountNodes();
            }

        }
            // If the node is a BLOCK node
        else if (nodeType == "BLOCK") {
            //  go through the node iff the num of nodes pointing to this node is 1, if not decrement it
            if (allNodes[currentNode].getcountNodes() == 1){
            // Get the statement for the BLOCK
            string statement = allNodes[currentNode].getText();

            if (allNodes[currentNode].getisNodeElse()){ // if the node is else node (it is the negative case of its parent if expression)
                cout << endl;
                cout << "}" << endl;
                cout << "else" << endl;
                cout << "{" << endl;
                // Output the statement
                cout << statement << endl;
                cout << endl;
                cout << "}" << endl;
            }
            else {
                cout << statement << endl;
            }


            if(allNodes[currentNode].getleftNode() != -1) {

                // Push the next node onto the stack (the "true" branch) which is the left node
                nodeStack.push(allNodes[currentNode].getleftNode());

            }
            }
            else { // decrement the num of nodes pointing to this node by 1
                allNodes[currentNode].decrementCountNodes();
            }
        }


    }
    cout << "end" << endl; // print end at the end
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main()
{
    int numNodesInFlowChart; // number of nodes in the flow chart

    cin >> numNodesInFlowChart;
    cout << "Number of nodes: " << numNodesInFlowChart << endl;

    // Node objects array to store all the information
    vector<Node> allNodes(numNodesInFlowChart);

    int nodeNumber = 0;    // to store the node number
    string type = "";       // can either be START, END, IF, BLOCK
    string textWithin; // can be expression or statement - for START and END this will be empty string

    for(int i =0; i < numNodesInFlowChart; i++)
    {
        cin >> nodeNumber >> type;
        textWithin = "";

        if (type.compare("START") != 0 && type.compare("END") != 0){ // start and end does not have any statements or expression
            cin >> textWithin;
        }
        allNodes[i] = Node(nodeNumber, type, textWithin);
    }


    // adjacency list to store the flow chart
    vector<vector<int>> adjList(numNodesInFlowChart);
    nodeNumber = 0;
    int flow1;
    int flow2;
    for(int i =0; i < numNodesInFlowChart; i++){
        cin >> nodeNumber;
        if (allNodes[nodeNumber].getType().compare("END") == 0){ // no need for any flows since end node won't point to anything
            adjList[i].push_back(nodeNumber);
        }
        else if (allNodes[nodeNumber].getType().compare("START") == 0 || allNodes[nodeNumber].getType().compare("BLOCK") == 0){ // if the node is either  block or start it is flowing into only one node afterwards
            adjList[i].push_back(nodeNumber);
            cin >> flow1;
            adjList[i].push_back(flow1);
            allNodes[nodeNumber].setleftNode(flow1);
            allNodes[flow1].incrementCountNodes(); // nodeNumber points to flow1, so the number of nodes pointing to flow1 is
            // incremented by 1

        }
        else { // if the block is if block
            adjList[i].push_back(nodeNumber);
            cin >> flow1; // positive node
            cin >> flow2; // negative node
            adjList[i].push_back(flow1);
            adjList[i].push_back(flow2);
            allNodes[nodeNumber].setleftNode(flow1); // flow1 is positive path of(left) of this if expression,
            // therefore it is the left child of the node
            allNodes[nodeNumber].setrightNode(flow2);// flow2 is negative path of(right) of this if expression,
            // therefore it is the right child of the node

            allNodes[flow2].setisNodeElse(); // flow2 is a negative case of nodeNumber node ( no need to do anything for flow1)
            allNodes[flow1].incrementCountNodes(); // nodeNumber points to flow1, so the number of nodes pointing to flow1 is
            // incremented by 1
            allNodes[flow2].incrementCountNodes(); // nodeNumber points to flow2, so the number of nodes pointing to flow2 is
            // incremented by 1

        }
    }

    for(int i =0; i < numNodesInFlowChart; i++){
        allNodes[i].display(); // display all the nodes and its type, and the textWithin if any
    }
    cout << "AdjList: " << endl;

    for (const auto& adj_list : adjList) { // display the adjacent list
        for (int i =0; i<adj_list.size(); i++) {
            if(i ==0){
                cout << adj_list[i] << ": ";


            }
            else {
                cout << adj_list[i] << " ";
            }


        }
        cout << endl;
    }

    convertFlowChart(allNodes, adjList); // call the convertFlowChart method to print the pseudo code

    return 0;
}
