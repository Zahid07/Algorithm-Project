#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
using namespace std;
// Node and Node Data
struct node {
    int node_no;
    float weight;
    int load_demand;
    int priority;
    int DG_Effective_Power = 0;
    int impedence;
    node* adjacent;
    node* next;
};

// Linked list Class
class LinkedList {
public:
    node* head;

    LinkedList() {
        head = nullptr;
    }

    // Function to insert a node along with its information
    void insert_node(int no, int L_Demand = 0, int Priority = 0, int DG_POW = 0, float Weight = 99) {
        node* temp = head;
        if (temp == nullptr) {
            temp = new node;
            temp->next = nullptr;
            temp->adjacent = nullptr;
            temp->node_no = no;
            temp->weight = Weight;
            temp->load_demand = L_Demand;
            temp->priority = Priority;
            temp->DG_Effective_Power = DG_POW;
            temp->impedence = 0;
            head = temp;
        }
        else {
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = new node;
            temp->next->next = nullptr;
            temp->next->adjacent = nullptr;
            temp->next->node_no = no;
            temp->next->weight = Weight;
            temp->next->load_demand = L_Demand;
            temp->next->priority = Priority;
            temp->next->DG_Effective_Power = DG_POW;
            temp->next->impedence = 0;
        }

    }

    // Inserting Adjacent and impedence from source to adjacent
    void insert_adjacent(int source, int adjacent, int Impedence = 0) {
        node* temp = head;;
        while (temp->node_no != source) {
            temp = temp->next;
        }
        node* temp1 = temp->adjacent;;
        if (temp1 == nullptr) {
            temp1 = new node;
            temp1->adjacent = nullptr;
            temp1->next = nullptr;
            temp1->node_no = adjacent;
            temp1->impedence = Impedence;
            temp->adjacent = temp1;
        }
        else {
            while (temp1->adjacent != nullptr) {
                temp1 = temp1->adjacent;
            }
            temp1->adjacent = new node;
            temp1->adjacent->adjacent = nullptr;
            temp1->adjacent->next = nullptr;
            temp1->adjacent->node_no = adjacent;
            temp1->adjacent->impedence = Impedence;
        }

    }

    // To display all the nodes which we have entered
    void display_heads() {
        node* temp = head;
        while (temp != nullptr) {
            //cout << temp->node_no <<"  -   "<<temp->weight<< endl;
            temp = temp->next;
        }

    }

    //Display all nodes and their adjacent nodes
    void display_adjacents() {
        node* temp = head;
        bool tempnull = true;
        while (temp != nullptr) {
            tempnull = true;
            node* temp1 = temp->adjacent;
            if (temp1 != nullptr) {
                tempnull = false;
                cout << temp->node_no << "  --->  ";
            }
            while (temp1 != nullptr) {
                cout << temp1->node_no << "  ";;
                temp1 = temp1->adjacent;
            }
            if (tempnull == false) {

                cout << endl;
            }
            temp = temp->next;
        }
    }

    // return impedence from source to brancn (i to j)
    int getImpedence(int source, int branch) {
        // cout << "SOURCE is = " << source << "  and BRANCH is = " << branch << endl;
        node* temp = head;
        while (temp != nullptr) {
            if (temp->node_no == source) {
                // cout << "found source is = " << source << endl;
                ::node* temp1 = temp->adjacent;
                while (temp1 != nullptr) {
                    if (temp1->node_no == branch) {
                        //cout << "found branch is = " << branch<< endl;
                       // cout << "impedence is = " << temp1->impedence << endl;
                        return temp1->impedence;
                    }
                    temp1 = temp1->adjacent;
                }
            }
            temp = temp->next;
        }

    }

    // Return loadDemand and priority of each node
    void getLoadDemand_Priority(int node, int& loadDemand, int& priority) {
        ::node* temp = head;
        while (1) {
            if (temp->node_no == node) {
                loadDemand = temp->load_demand;
                priority = temp->priority;
                return;
            }
            temp = temp->next;
        }
    }

    int getLoadDemand(int node) {
        ::node* temp = head;
        while (1) {
            if (temp->node_no == node) {
                return temp->load_demand;

            }
            temp = temp->next;
        }
    }

    // Check if the list is empty or not
    bool isEmpty() {
        if (head == nullptr) {
            return true;
        }
        return false;
    }

    //Remoce head from a given list
    void removeHead() {
        if (head->next == nullptr) {
            head = nullptr;
        }
        else {
            head = head->next;
        }
        return;
    }

    // Remove a node from the list
    bool removeNode(int node) {
        ::node* temp = head;
        
        if (temp->next == nullptr) {
            head = nullptr;
            return true;
        }
        else if (temp->node_no == node) {
            //::node* temp1 = temp;
            head = temp->next;
            // delete(temp1);
            return true;
        }
        else {
            while (temp->next != nullptr) {
                if (temp->next->node_no == node) {
                    ::node* temp1 = temp->next;
                    temp->next = temp->next->next;
                    delete(temp1);
                    return true;
                }
                temp = temp->next;
            }
        }
        return false;
    }

    //remove adjacent node from a branch
    bool removeAdjacentNode(int branch, int node) {
        ::node* temp = head;
        while (temp != nullptr) {

            if (temp->node_no == branch) {

                ::node* temp1 = temp->adjacent;
                if (temp1->adjacent == nullptr) {
                    temp1 = nullptr;
                    return true;
                }
                else if (temp1->node_no == node) {

                    //::node* temp2 = temp1;
                    temp->adjacent = temp1->adjacent;
                    //delete(temp2);
                    return true;
                }
                else {

                    while (1) {
                        if (temp1->adjacent->node_no == node) {
                            ::node* temp2 = temp1->adjacent;
                            temp1->adjacent = temp1->adjacent->adjacent;
                            delete(temp2);
                            return true;
                        }
                        temp1 = temp1->adjacent;
                    }

                }


            }
            temp = temp->next;
        }
    }

    // Check if 'node' is a DG or not
    bool isDG(int node) {
        ::node* temp = head;
        while (temp != nullptr) {
            if (temp->node_no == node) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    //reutrn the adjacent list of a 'node'
    node* getAdjacentList(int node) {
        ::node* temp = head;
        while (temp != nullptr) {
            if (temp->node_no == node) {
                //cout << "adjacent is = " << temp->adjacent->adjacent->node_no << endl;
                return temp->adjacent;
            }
            temp = temp->next;
        }
    }

    //return head of a given list
    node* getHead() {
        node* temp = head;
        return temp;
    }

    // return a particular node from our list
    node* getNode(int node) {
        ::node* temp = head;
        while (temp != nullptr) {
            if (temp->node_no == node) {
                return temp;
            }
            temp = temp->next;
        }
    }

    // return the node with the least weight
    node* leastWeight() {
        node* temp = head;
        node* temp1 = nullptr;
        float weight = 9999999;
        if (temp->next == nullptr) {
            return temp;
        }
        while (temp != nullptr) {

            if (temp->weight < weight) {
                weight = temp->weight;
                temp1 = temp;
            }
            temp = temp->next;
        }
        return temp1;
    }

    // return max weight node
    node* mstMostWeight(LinkedList DG) {
        node* temp = head;
        node* temp1 = nullptr;
        node* temp2 = nullptr;
        float weight = -1;
        while (temp != nullptr) {
            temp1 = temp->adjacent;
            while (temp1 != nullptr)
            {
                //cout<<"node is = "<<temp1->node_no <<"  and their weight is = "<<temp1->weight<< endl;
                if (temp1->weight > weight) {
                    temp2 = temp1;
                }
                temp1 = temp1->adjacent;
            }
            temp = temp->next;
        }
        return temp2;
    }

    // Insert weight of a node calculated through given formula
    void insertWeight(int node, float weight) {
        ::node* temp = head;
        while (1) {
            if (temp->node_no == node) {
                temp->weight = weight;
                break;
            }
            temp = temp->next;
        }
    }

    // Inserting weight in an adjacent node
    void insertAdjacentWeight(int node, int adjac, float weight) {
        ::node* temp = head;
        while (1) {
            if (temp->node_no == node) {
                ::node* temp1 = temp->adjacent;
                while (temp1 != nullptr) {
                    if (temp1->node_no == adjac) {
                        temp1->weight = weight;
                        break;
                    }
                    temp1 = temp1->adjacent;
                }
                break;
            }
            temp = temp->next;
        }
    }

    // searching a 'node' ina particular linked list
    bool search(int node) {
        if (head == nullptr) {
            return false;
        }
        else {
            ::node* temp = head;
            while (temp != nullptr) {
                if (temp->node_no == node) {
                    return true;
                }
                ::node* temp2 = temp->adjacent;
                while (temp2 != nullptr) {
                    if (temp2->node_no == node) {
                        return true;
                    }
                    temp2 = temp2->adjacent;
                }
                temp = temp->next;
            }
        }
        return false;
    }

    //return power of a node
    int getPower(int node) {
        ::node* temp = head;
        while (temp != nullptr)
        {
            if (temp->node_no == node) {
                return temp->DG_Effective_Power;
            }
            temp = temp->next;

        }
    }

    // return priority of a node
    int getPriority(int node) {
        ::node* temp = head;
        while (temp != nullptr) {
            if (temp->node_no == node) {
                return temp->priority;
            }
            temp = temp->next;
        }
    }

    //return weight of a node
    float getWeight(int node) {
        ::node* temp = head;
        while (temp != nullptr) {
            if (temp->node_no == node) {
                return temp->weight;
            }
            temp = temp->next;
        }
    }

    //display weights of a node
    void displayWeights() {
        node* temp = head;
        while (temp != nullptr) {
            temp = temp->next;
        }
    }

    //search a node
    bool searchHead(int node) {
        ::node* temp = head;
        while (temp != nullptr) {
            if (temp->node_no == node) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    // calculate ttal nodes
    int calculateTotalNodes() {
        node* temp = head;
        int n = 0;
        while (temp != nullptr) {
            n += 1;
            temp = temp->next;
        }
        return n;
    }

    // return priority of a node
    int returnPriority(int priority) {
        node* temp = head;
        int weight = 0;
        while (temp != nullptr) {
            if (temp->priority == priority) {
                weight += temp->load_demand;
            }
            temp = temp->next;
        }
        return weight;
    }

    //write output to a file
    void writeFile() {
        ofstream myfile("input1.txt");
        if (myfile.is_open())
        {
            node* temp = head;
            bool tempnull = true;
            while (temp != nullptr) {
                tempnull = true;
                node* temp1 = temp->adjacent;
                if (temp1 != nullptr) {
                    tempnull = false;
                   myfile<< temp->node_no << "  --->  ";
                }
                while (temp1 != nullptr) {
                    myfile << temp1->node_no << "  ";;
                    temp1 = temp1->adjacent;
                }
                if (tempnull == false) {

                    myfile << endl;
                }
                temp = temp->next;
            }

            myfile.close();
        }
    }

};

LinkedList adjacencyList;


void insert_nodes() {


    // insert_node(int no, int L_Demand = 0, int Priority = 0, int DG_POW = 0, float Weight = 99)
    int i = 0;
    string line;
    ifstream myfile("facebook_combined.txt");
    if (myfile.is_open())
    {
        std::getline(myfile, line);
        //string ans = "";
        //ans+=line[0];
        //ans += ' ';
        //ans += line[line.length()-1];
       //cout << ans << endl;
        stringstream ss(line);
        string token;
        bool done = false;
        int curnode = -1;
        while (std::getline(ss, token, ' ')) {

            if (done == false) {
                if (adjacencyList.search(stoi(token)) == false) {
                    curnode = stoi(token);
                    int result = 1 + (rand() % 2);
                    adjacencyList.insert_node(stoi(token), 10, result, 0, 0);
                }
                done = true;
            }
            else {

                adjacencyList.insert_adjacent(curnode, stoi(token), 1);
            }

        }

        while (std::getline(myfile, line))
        {
            //cout << "here" << endl;
            i += 1;
            done = false;

            string ans = "";
            ans += line[0];
            ans += ' ';
            ans += line[line.length() - 1];
            stringstream ss1(line);
            string token1 = "";
            while (std::getline(ss1, token1, ' ')) {

                if (done == false) {
                    //stoi(token1) != curnode
                    if (adjacencyList.searchHead(stoi(token1)) == false) {
                        curnode = stoi(token1);
                        int result = 1 + (rand() % 2);
                       // cout << "here" << token1<<endl;
                        adjacencyList.insert_node(stoi(token1), 10, result, 0, 0);
                    }
                    done = true;
                }
                else {

                    adjacencyList.insert_adjacent(curnode, stoi(token1), 1);
                }

            }
            if (i == 70000) {
                break;
            }
            //cout << endl;


        }
    }

    //adjacencyList.display_adjacents();
    myfile.close();
    node* temp = adjacencyList.getHead();;
    while (temp != nullptr) {
        node* temp1 = adjacencyList.getAdjacentList(temp->node_no);
        while (temp1 != nullptr) {
            if (adjacencyList.searchHead(temp1->node_no) == false) {

                int result = 1 + (rand() % 2);
                adjacencyList.insert_node(temp1->node_no, 10, result, 0, 0);
                adjacencyList.insert_adjacent(temp1->node_no, temp->node_no, 1);
            }
            temp1 = temp1->adjacent;
        }
        temp = temp->next;
    }

   

}

// Function to calculate the weight from i to j
float weight_calculate(int i, int j, int Impedence, int load_demand, int priority) {
    float ans = (Impedence / (float(load_demand) * float(priority)));
    return ans;
}

int main()
{
    //insert_node(int no, int L_Demand = 0, int Priority = 0, int DG_POW = 0, float Weight = 99)
    insert_nodes();
    cout << "Total nodes are = " << adjacencyList.calculateTotalNodes(); cout << endl;

    


    /*

          6
          |
    0--1--2--3
          |  |
          4  5


    */
    //LinkedList adjacencyList;

    /// Input 1
   /* adjacencyList.insert_node(0,10,2); // to adjacent from node 0 to node 1 as there is a break
    adjacencyList.insert_adjacent(0, 1, 1);
    adjacencyList.insert_node(1);

    adjacencyList.insert_adjacent(1, 2,1);
    adjacencyList.insert_adjacent(1, 0, 1);

    adjacencyList.insert_node(2,10,1);
    adjacencyList.insert_adjacent(2, 1,1);
    adjacencyList.insert_adjacent(2, 3,1);
    adjacencyList.insert_adjacent(2, 4,1);
    adjacencyList.insert_adjacent(2, 6,1);

    adjacencyList.insert_node(3,10,1);
    adjacencyList.insert_adjacent(3, 2,1);
    adjacencyList.insert_adjacent(3, 5,1);

    adjacencyList.insert_node(4,10,1);
    adjacencyList.insert_adjacent(4, 2,1);

    adjacencyList.insert_node(5,10,1);
    adjacencyList.insert_adjacent(5, 3,1);

    adjacencyList.insert_node(6,10,1);
    adjacencyList.insert_adjacent(6, 2,1);
    adjacencyList.display_adjacents();

    LinkedList DG;
    DG.insert_node(1, 0, -1, 20, 0);*/

    //// INPUT 3
    /*adjacencyList.insert_node(0, 10, 2);
    adjacencyList.insert_node(1, 10, 2);
    adjacencyList.insert_node(2, 10, 1);
    adjacencyList.insert_node(3, 10, 1);
    adjacencyList.insert_node(4, 10, 1);
    adjacencyList.insert_node(5, 10, 2);
    adjacencyList.insert_node(6, 10, 2);
    adjacencyList.insert_node(7, 10, 1);
    adjacencyList.insert_node(8, 10, 2);
    adjacencyList.insert_node(9, 10, 2);
    adjacencyList.insert_node(10, 10, 2);
    adjacencyList.insert_node(11, 10, 2);
    adjacencyList.insert_node(12, 10, 2);
    adjacencyList.insert_node(13, 10, 2);
    adjacencyList.insert_node(14, 10, 2);
    adjacencyList.insert_node(15, 10, 2);


    adjacencyList.insert_adjacent(0, 1, 1);
    adjacencyList.insert_adjacent(0, 6, 3);
    adjacencyList.insert_adjacent(0, 8, 5);
    adjacencyList.insert_adjacent(0, 12, 2);

    adjacencyList.insert_adjacent(1, 0, 1);
    adjacencyList.insert_adjacent(1, 7, 3);
    adjacencyList.insert_adjacent(1, 2, 5);
    adjacencyList.insert_adjacent(1, 4, 2);

    adjacencyList.insert_adjacent(2, 3, 1);
    adjacencyList.insert_adjacent(2, 4, 3);

    adjacencyList.insert_adjacent(3, 2, 1);
    adjacencyList.insert_adjacent(3, 5, 3);

    adjacencyList.insert_adjacent(4, 1, 1);
    adjacencyList.insert_adjacent(4, 11, 3);

    adjacencyList.insert_adjacent(5, 3, 1);

    adjacencyList.insert_adjacent(6, 0, 1);
    adjacencyList.insert_adjacent(6, 7, 3);

    adjacencyList.insert_adjacent(7, 6, 1);
    adjacencyList.insert_adjacent(7, 1, 3);
    adjacencyList.insert_adjacent(7, 9, 1);

    adjacencyList.insert_adjacent(8, 0, 1);
    adjacencyList.insert_adjacent(8, 10, 3);

    adjacencyList.insert_adjacent(9, 7, 1);

    adjacencyList.insert_adjacent(10, 8, 1);
    adjacencyList.insert_adjacent(10, 11, 3);

    adjacencyList.insert_adjacent(11, 10, 1);
    adjacencyList.insert_adjacent(11, 4, 3);

    adjacencyList.insert_adjacent(12, 0, 1);
    adjacencyList.insert_adjacent(12, 13, 3);

    adjacencyList.insert_adjacent(13, 12, 1);
    adjacencyList.insert_adjacent(13, 14, 3);

    adjacencyList.insert_adjacent(14, 13, 1);
    adjacencyList.insert_adjacent(14, 15, 3);

    adjacencyList.insert_adjacent(15, 14, 1);




    LinkedList DG;
    DG.insert_node(0, 0, -1, 20, 0);
    DG.insert_node(4, 0, -1, 20, 0);
    DG.insert_node(11, 0, -1, 20, 0);
    DG.insert_node(8, 0, -1, 20, 0);
    */

    //input 2
    /*
        1
        |
     3--0--2
        |
        4--5--6--9
           |
           7--8--10
    */

    /*adjacencyList.insert_node(0);
    adjacencyList.insert_node(1, 10, 2);
    adjacencyList.insert_node(2, 10, 1);
    adjacencyList.insert_node(3, 10, 1);
    adjacencyList.insert_node(4,10,2);
    adjacencyList.insert_node(5,10,2);
    adjacencyList.insert_node(6, 10, 2);
    adjacencyList.insert_node(7, 10, 2);
    adjacencyList.insert_node(8);
    adjacencyList.insert_node(9, 10, 1);
    adjacencyList.insert_node(10, 10, 2);


    adjacencyList.insert_adjacent(0, 1, 1);
    adjacencyList.insert_adjacent(0, 2, 3);
    adjacencyList.insert_adjacent(0, 3, 5);
    adjacencyList.insert_adjacent(0, 4, 2);

    adjacencyList.insert_adjacent(1, 0, 1);

    adjacencyList.insert_adjacent(2, 0, 1);

    adjacencyList.insert_adjacent(3, 0, 1);

    adjacencyList.insert_adjacent(4, 0, 1);
    adjacencyList.insert_adjacent(4, 5, 1);

    adjacencyList.insert_adjacent(5, 6, 1);
    adjacencyList.insert_adjacent(5, 7, 1);

    adjacencyList.insert_adjacent(6, 5, 1);
    adjacencyList.insert_adjacent(6, 9, 1);

    adjacencyList.insert_adjacent(9, 6, 1);

    adjacencyList.insert_adjacent(7, 5, 1);
    adjacencyList.insert_adjacent(7, 8, 1);

    adjacencyList.insert_adjacent(8, 7, 1);
    adjacencyList.insert_adjacent(8, 10, 1);

    adjacencyList.insert_adjacent(10, 8, 1);

    LinkedList DG;
    DG.insert_node(0, 0, -1, 20, 0);
    DG.insert_node(8, 0, -1, 20, 0);
    */
    
    
    LinkedList DG;
    DG.insert_node(0, 0, -1, 20, 0);
    int start = clock();
    int priority_one_nodes = adjacencyList.returnPriority(2);

    //cout << "priority is = " << priority_one_nodes << endl;
    int priority_two_nodes = adjacencyList.returnPriority(1);

    LinkedList MST;  // LINKED LIST for MST
    LinkedList notVisited;


    node* cur_DG = DG.getHead();  // GETTNG the First DG
    MST.insert_node(cur_DG->node_no);  // INSERTING our DG in the MST
    node* adjacencylist = adjacencyList.getAdjacentList(cur_DG->node_no); // GETTING adjacency List of our DG


    int dgPoint = cur_DG->node_no; // Saving the DG node no
    while (1) {
        float weight = 999999;
        int node = -1;
        // applying Prims MST
        while (adjacencylist != nullptr) {
            if (MST.search(adjacencylist->node_no) == false && notVisited.search(adjacencylist->node_no) == false) {
                float calc_weight = weight_calculate(cur_DG->node_no, adjacencylist->node_no, adjacencyList.getImpedence(cur_DG->node_no, adjacencylist->node_no), adjacencyList.getLoadDemand(adjacencylist->node_no), adjacencyList.getPriority((adjacencylist->node_no)));

                adjacencyList.insertWeight(adjacencylist->node_no, calc_weight);
                notVisited.insert_node(adjacencylist->node_no);
                notVisited.insertWeight(adjacencylist->node_no, calc_weight);

            }
            adjacencylist = adjacencylist->adjacent;
        }
        //notVisited.display_heads();
        if (node == -1) {
            if (notVisited.isEmpty() == false) {
                ::node* temp = notVisited.leastWeight();
                node = temp->node_no;
            }
            else {
                break;
            }

        }

        int LD = adjacencyList.getLoadDemand(node);
        if (cur_DG->DG_Effective_Power >= LD) {
            notVisited.removeNode(node);
            if (adjacencyList.getPriority(node) == 2) {
                priority_one_nodes -= LD;
            }
            else {
                priority_two_nodes -= LD;
            }
            cur_DG->DG_Effective_Power -= LD; // removing load power from DG effective power
            int effective_power = cur_DG->DG_Effective_Power; // saving effective power
            MST.insert_adjacent(dgPoint, node); // Inserting our least node in adjacency list of our DG
            MST.insertAdjacentWeight(dgPoint, node, adjacencyList.getWeight(node));
            cur_DG = adjacencyList.getNode(node); // Now moving towards the least weight node
           // cout << "Cur DG effective power is = " << cur_DG->DG_Effective_Power << endl;
            adjacencylist = adjacencyList.getAdjacentList(node); // getting the adjacency list of our node with least weight
            if (DG.search(node) == true) { //checking if our node is a DG or not
                cur_DG->DG_Effective_Power = DG.getPower(node);
                DG.removeNode(node);// If DG then remove from the DG list as we now combine its power with our current DG
            }
            cur_DG->DG_Effective_Power += effective_power; // Combining DG Power with current node DG_power, this value will only increase if our cur node is a DG         
           
        }
        else {  // OUR DG can no longer provide power to the nodes
            if (priority_one_nodes <= 0 && cur_DG->DG_Effective_Power<priority_two_nodes ) {
                
                DG.removeHead();// remving DG from list

                if (DG.isEmpty()) { // Checking if there are any DG left or not, IF no DG then we exit
                    break;
                }
                notVisited.insert_node(node); // Inserting the node where out DG got exhausted
                DG.display_heads(); cout << endl;
                // If there is DG we get new DG and the above process repeats.
                cur_DG = DG.getHead();
                MST.insert_node(cur_DG->node_no);
                dgPoint = cur_DG->node_no;
                adjacencylist = adjacencyList.getAdjacentList(cur_DG->node_no);
            }
            else {
                ::node* temp = MST.mstMostWeight(DG);
                    cur_DG->DG_Effective_Power += adjacencyList.getLoadDemand(temp->node_no);
                    notVisited.insert_node(temp->node_no);
                    notVisited.insertWeight(temp->node_no, temp->weight);
                MST.removeAdjacentNode(dgPoint, temp->node_no);

            }
        }
    }
    int end = clock();

    cout << "Execution time: " << (double(end) - double(start)) / double(CLOCKS_PER_SEC) << endl;
    cout << "MST is ";    MST.display_adjacents();
    MST.writeFile();

}

