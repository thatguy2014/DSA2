#include <iostream>
#include <string>
#include <list>

using namespace std;

//function declarations
void printmatrix(int matrix[7][7], string names[7]);    
void printlinkedlist(linked_list City); 


//node structure for the linked list class
struct node
{
    int weight;
    string name;
    struct node *next;
};
// linked list class for the adjacency list
class linked_list {

private:
    node *head,*tail;
    int count = 0;
public:
    linked_list()                               //is a default constructor
    {
        head = NULL;
        tail = NULL;
    }

    void add_node(int weight, string name)      //adds a node 
    {
        count++;
        node *tmp = new node;
        tmp->weight = weight;
        tmp->name = name;
        tmp->next = NULL;

        if(head == NULL)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            tail->next = tmp;
            tail = tail->next;
        }
    }

    int get_count() {   //returns the count
        return count;
    }

    node* get_head() {  //returns a pointer to the head node
        return head;
    }
};


int main() {
    //creates the matrix with all the values
    int matrix[7][7] = {{0,200,900,0,0,0,780},
                        {200,0,0,160,0,0,0},
                        {0,0,0,0,0,0,1000},
                        {0,0,0,0,800,0,0},
                        {0,0,0,800,0,600,0},
                        {1300,0,0,0,600,0,0},
                        {0,0,1000,0,1400,0,0}};

    //creates the names array with all the names
    string names[7] = {"Dallas","Austin","Chicago","Houston","Atlanta","Wash.","Denver"};   

    printmatrix(matrix, names); //prints the matrix... duh

    // creates a linked list for every destination
    linked_list Dallas;
    linked_list Austin;
    linked_list Chicago;
    linked_list Houston;
    linked_list Atlanta;
    linked_list Washington;
    linked_list Denver;

    //set up linked lists
    Dallas.add_node(200, "Austin");
    Dallas.add_node(900, "Chicago");
    Dallas.add_node(780, "Denver");

    Austin.add_node(200, "Dallas");
    Austin.add_node(160, "Houston");

    Chicago.add_node(1000, "Denver");

    Houston.add_node(800, "Atlanta");

    Atlanta.add_node(800, "Houston");
    Atlanta.add_node(600, "Washington");

    Washington.add_node(600, "Atlanta");
    Washington.add_node(1300, "Dallas");

    Denver.add_node(1000, "Chicago");
    Denver.add_node(1400, "Atlanta");

    //prints out all of the linked lists
    cout << "Dallas: " << '\t';
    printlinkedlist(Dallas);

    cout << "Austin: " << '\t';
    printlinkedlist(Austin);

    cout << "Chicago: " << '\t';
    printlinkedlist(Chicago);

    cout << "Houston: " << '\t';
    printlinkedlist(Houston);

    cout << "Atlanta: " << '\t';
    printlinkedlist(Atlanta);

    cout << "Washington: " << '\t';
    printlinkedlist(Washington);

    cout << "Denver: " << '\t';
    printlinkedlist(Denver);
}

// will print out the matrix in a proper format
void printmatrix(int matrix[7][7], string names[7]) {


    cout << "note that every column points to the row" << endl;     //a little note for readability
    cout << '\t';
    for(int i = 0; i < 7; i++) {
        cout << names[i] << '\t';
    }
    cout << endl;
    for(int i = 0; i < 7; i++) {
        cout << names[i] << '\t';
        for (int j = 0; j < 7; j++) {
            cout <<  matrix[i][j] << '\t';
        }
        cout << endl;
    }
}

//will print out the given linked list in proper format
void printlinkedlist(linked_list City) {
    node* tmp = City.get_head();
    for (int i = 0; i < City.get_count(); i++) {
        cout << "| " << tmp->weight << " | " << tmp->name << " |" << " -> " << '\t';
        tmp = tmp->next;
    }
    cout << "null";
    cout << endl;
    delete tmp;
}