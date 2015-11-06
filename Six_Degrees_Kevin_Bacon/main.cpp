#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <queue>

using namespace std;

class Actors; //declare class actors

class Movies //class movie
{
public:
    Movies(Actors *Tatum, Actors *endActor, char* movieTitles) //movies function takes in parameters
    {
        startPoint = Tatum; //start point of graph
        endPoint = endActor; //endpoint
        titles = movieTitles; //titles of movies
    }
    
    Actors* getOrigin() {return startPoint;} //returns the starting point
    Actors* getDestination() {return endPoint;} //returns the end point
    char* getDistance() {return titles;} //returns the movies leading up to actors
private: //declared variables
    Actors* startPoint;
    Actors* endPoint;
    char* titles;
};

class Actors //class actors
{
public:
    Actors(string id) //actor function
    {
        name = id;
        visited = false;
    }
    //add actors/movies to graph
    void addEdge(Actors *actor, char* movie)
    {
        Movies newEdge(this, actor, movie);
        edges.push_back(newEdge);
    }
    //print edges to make sure the movies connect to actors
    void printEdges()
    {
        cout << name << ":" << endl;
        for (int i = 0; i < edges.size(); i++)
        {
            Movies e = edges[i];
            cout << e.getDestination()->getName() <<
            " - " << e.getDistance() << endl;
        }
        cout << endl;
    }
    //gets the name of the actor
    string getName() {return name;}
    vector<Movies> getEdges() {return edges;} //get the edges for the movies
    bool visited;
private: //private variables
    string name;
    vector<Movies> edges;
};


class Graph //class graph
{
public:
    Graph() {}; //graph function
    int **A;
    //inserts actors as vertices
    void insert(Actors *v)
    {
        vertices.push_back(v);
    }
    //printsgraph function
    void printGraph()
    {
        for (int i = 0; i < vertices.size(); i++)
            vertices[i]->printEdges();
    }
    //traverse through graph if needed
    void BFS(string s);
    //search using breadth first search for the actor
    void BFSearch(string s);
    
private:
    //the vertices of the actors
    vector<Actors*> vertices;
};

// Traverse the graph using breadth first search algorithm
void Graph::BFS(string s)
{
    // Create a queue for BFS
    queue <Actors*> q;
    
    //Find and mark the current node as visited and enqueue it
    int c = 0;
    Actors *curr = vertices[c]; //get the first node of the graph. All nodes are in vector vertices
    string comp = curr->getName(); //get the actor's name from node
    while (s.compare(comp) != 0 && c < 15) //find the node that has the same name as the entered parameter
    {
        c++;
        curr = vertices[c];
        comp = curr->getName();
    }
    curr->visited = true; //mark node as visited
    q.push(curr); //enqueue node
    
    while(!q.empty())
    {
        // Dequeue a vertex from queue and print it
        curr = q.front();
        cout << curr->getName() << " ";
        q.pop();
        
        // Get all adjacent vertices of the dequeued vertex s
        // If a adjacent has not been visited, then mark it visited
        // and enqueue it
        vector<Movies> toNeighbors = curr->getEdges();
        for (int i = 0; i < toNeighbors.size(); i++)
        {
            Movies e = toNeighbors[i];
            Actors *neighbor = e.getDestination();
            if (!neighbor->visited)
            {
                neighbor->visited = true;
                q.push(neighbor);
            }
        }
    }
}

//Search for shortest path to Channing Tatum given an actor's name
//Since there is only one path to Channing Tatum from any actor,
//either the left neighbor nod path or the right neighbor node path will lead to him.
//Function looks for the path that leads to Channing Tatum and prints it
void Graph::BFSearch(string s)
{
    queue <Actors*> q1; //for the left neighbor node path
    queue <Actors*> q2; //for the right neighbor node path
    int count = 0;
    
    //Find and mark the current node as visited and enqueue it
    int c = 0;
    Actors *curr1 = vertices[c];
    string comp = curr1->getName();
    while (s.compare(comp) != 0 && c < 15)
    {
        c++;
        curr1 = vertices[c];
        comp = curr1->getName();
    }
    curr1->visited = true;
    Actors *curr2 = curr1;
    q1.push(curr1);
    q2.push(curr2);
    
    //Get path until there are no more nodes, or until it reaches Channing Tatum
    while(!q1.empty() && curr1->getName().compare("Channing Tatum") !=0)
    {
        // Dequeue a vertex from queue and print it
        curr1 = q1.front();
        if (curr1->getName().compare("Channing Tatum") ==0)
        {
            cout << curr1->getName();
        }
        else
        {
            cout << curr1->getName() << " -> ";
        }
        q1.pop();
        count++;
        
        // Get left vertice of the dequeued vertex s
        // If a adjacent has not been visited, then mark it visited
        // and enqueue it
        vector<Movies> toNeighbors = curr1->getEdges();
        Movies e = toNeighbors[0];
        if (curr1->getName().compare("Channing Tatum") !=0)
        {
            cout << e.getDistance() << " -> ";
        }
        {
            Actors *neighbor1 = e.getDestination();
            if (!neighbor1->visited)
            {
                neighbor1->visited = true;
                q1.push(neighbor1);
            }
        }
    }
    cout << endl;
    
    //If left neighbor node path did not find Channing Tatum, find path to him using right neighbor node
    if (curr1->getName().compare("Channing Tatum") !=0)
    {
        count = 1;
        while(!q2.empty() && curr2->getName().compare("Channing Tatum") !=0)
        {
            // Dequeue a vertex from queue and print it
            curr2 = q2.front();
            if (curr2->getName().compare("Channing Tatum") ==0)
            {
                cout << curr2->getName();
            }
            else
            {
                cout << curr2->getName() << " -> ";
            }
            q2.pop();
            
            // Get right vertice of the dequeued vertex s
            // If a adjacent has not been visited, then mark it visited
            // and enqueue it
            vector<Movies> toNeighbors2 = curr2->getEdges();
            if (toNeighbors2.size() > 1)
            {
                Movies e = toNeighbors2[1];
                Actors *neighbor2 = e.getDestination();
                if (curr2->getName().compare("Channing Tatum") !=0)
                {
                    cout << e.getDistance() << " -> ";
                }
                if (!neighbor2->visited)
                {
                    neighbor2->visited = true;
                    q2.push(neighbor2);
                }
            }
            count++;
        }
    }
    cout<<endl <<"His/her Tatum number is "<< count-1 <<endl;
}
//this function makes the graph so it can be used multiple times
//it takes an input to search
Graph makeGraph(string input){
    Graph g; //creates graph g
    //actor's initials
    Actors ct = Actors("Channing Tatum");
    Actors jh = Actors("Jonah Hill");
    Actors sr = Actors("Seth Rogen");
    Actors mm = Actors("Matthew McConaughey");
    Actors ld = Actors("Leonardo DiCaprio");
    Actors jgl = Actors("Joseph Gordon-Levit");
    Actors jf = Actors("Jamie Fox");
    Actors ja = Actors("Jennifer Aniston");
    Actors ze = Actors("Zac Efron");
    Actors ew = Actors("Emma Watson");
    Actors mt = Actors("Myles Teller");
    Actors jb = Actors("Jason Batemen");
    Actors melm = Actors("Melissa McCarthy");
    Actors sb = Actors("Sandra Bullock");
    Actors rr = Actors("Ryan Reynolds");
    //actor's pointers to point to a movie/actor
    Actors *ctP = &ct;
    Actors *jhP = &jh;
    Actors *srP = &sr;
    Actors *mmP = &mm;
    Actors *ldP = &ld;
    Actors *jglP = &jgl;
    Actors *jfP = &jf;
    Actors *jaP = &ja;
    Actors *zeP = &ze;
    Actors *ewP = &ew;
    Actors *mtP = &mt;
    Actors *jbP = &jb;
    Actors *melmP = &melm;
    Actors *sbP = &sb;
    Actors *rrP = &rr;
    //adds the edges, which are the movies using the pointers, connects actor to another actor's pointer and has the movie associated
    ct.addEdge(jhP, "Lego Movie");
    jh.addEdge(ctP, "Lego Movie");
    ct.addEdge(mmP, "Magic Mike");
    mm.addEdge(ctP, "Magic Mike");
    ct.addEdge(srP, "22 Jump Street");
    sr.addEdge(ctP, "22 Jump Street");
    sr.addEdge(zeP, "Neighbors");
    ze.addEdge(srP, "Neighbors");
    ze.addEdge(mtP, "The Awkward Moment");
    mt.addEdge(zeP, "The Awkward Moment");
    ew.addEdge(jhP, "This is the End");
    jh.addEdge(ewP, "This is the End");
    ct.addEdge(jfP, "White House Down");
    jf.addEdge(ctP, "White House Down");
    jf.addEdge(jaP, "Horrible Bosses 2");
    ja.addEdge(jfP, "Horrible Bosses 2");
    ja.addEdge(jbP, "The Switch");
    jb.addEdge(jaP, "The Switch");
    jb.addEdge(melmP, "Identity Thief");
    melm.addEdge(jbP, "Identity Thief");
    melm.addEdge(sbP, "The Heat");
    sb.addEdge(melmP, "The Heat");
    sb.addEdge(rrP, "The Proposal");
    rr.addEdge(sbP, "The Proposal");
    mm.addEdge(ldP, "The Wolf of Wall Street");
    ld.addEdge(mmP, "The Wolf of Wall Street");
    ld.addEdge(jglP, "Inception");
    jgl.addEdge(ldP, "Inception");
    //inserts the pointer into the graph, the pointer having all the movies connected to it and actors
    g.insert(ctP);
    g.insert(jhP);
    g.insert(srP);
    g.insert(mmP);
    g.insert(ldP);
    g.insert(jglP);
    g.insert(jfP);
    g.insert(jaP);
    g.insert(zeP);
    g.insert(ewP);
    g.insert(mtP);
    g.insert(jbP);
    g.insert(melmP);
    g.insert(sbP);
    g.insert(rrP);
    g.BFSearch(input); //searches using input for actor
    return g; //returns graph for use in main
}


int main()
{   Graph g; //declares graph
    
    char input[100]; //input from user
    char ans;
    
    cout<<"Six Degrees of Channing Tatum" <<endl << endl;
    cout<<"Here are the list of actors that will be within six degrees of Channing Tatum:" << endl;
    cout<<"Matthew McConaughey, Jonah Hill, Seth Rogen, Leonardo DiCaprio, Joseph Gordon-Levit, Jamie Fox, Jennifer Aniston, Zac Efron, Emma Watson, Myles Teller, Jason Batemen, Sandra Bullock, Melissa McCarthy, Ryan Reynolds"<<endl<<endl;
    cout<<"Please choose an actor: ";
    cin.getline(input, sizeof(input)); //gets input to be used in the function below
    cout<<endl;
    g = makeGraph(input); //takes input
    cin.clear(); //clears the cin so we can use it again
    
    cout<<endl<<"Do you want to pick another actor/actress? (y or n)"<<endl;
    cin>>ans;
    while(ans == 'y' || ans == 'Y') //while answer is y
    {
        char input2[100]; //new input
        cout<<endl<<"Please choose an actor: ";
        cin.clear(); //clears cin because it has "ans" in it
        cin.ignore(256, '\n'); //clears
        cin.getline(input2,sizeof(input2)); //takes input
        cout<< endl;
        g = makeGraph(input2); //uses input
        cout << endl<<"Do you want to pick another actor? (y or n)" << endl;
        cin>>ans; //loop back
    }
    
    cout<<"Thanks for using this program!"<<endl;
    return 1; //exit
}
