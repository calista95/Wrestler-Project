//Program: wrestler.txt
//Name: Calista Wong

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
using namespace std;


struct Wrestler
{
        string name;
        int number;
        char type;
        string color;
};

struct Pair
{
        int w1;
        int w2;
};


void displayResult(bool result, vector<Wrestler> wrestler)
{
        if (result == true)
        {
                cout << "Yes" << endl;
                cout << "Babyfaces: " << endl;
                for (int i=0; i < wrestler.size(); i++)
                {
                        if (wrestler[i].type == 'b')
                        {
                                cout << wrestler[i].name << " ";
                        }
                }

                cout << endl;

                cout << "Heels: " << endl;
                for (int i=0; i<wrestler.size(); i++)
                {
                        if (wrestler[i].type == 'h')
                        {
                                cout << wrestler[i].name << " ";
                        }
                }
        }

        else
        {
                cout << "Impossible " << endl;
        }
}

bool whiteNode(vector<Wrestler> wrestler)
{
        for (int i=0; i<wrestler.size(); i++)
        {
                if (wrestler[i].color == "white" )
                        return true;
        }
        return false;
}

void Search(int **graph, vector<Wrestler> wrestler)
{

        bool rivalry = true; //indicates that the rivalries we have will work
        int size = wrestler.size();
        queue<Wrestler>myQueue; //this will be the wrestlers that we have not visited yet


        //initialize first wrestler as a babyface
        wrestler[0].type = 'b';
        wrestler[0].color = "gray";
 	//add the first wrestler to the queue
        myQueue.push(wrestler[0]);


        int iteration=1;
        //while (!myQueue.empty() && rivalry == true)
        while (whiteNode(wrestler) != false && rivalry == true)  //there exists white nodes and everything is compatible
        {
                //cout << "Iteration number: " << iteration << endl;
                iteration++;

                if (myQueue.empty()) //queue is empty
                {
                        //put a node that has not been explored yet
                        for (int i=0; i<size; i++)
                        {
                                if (wrestler[i].color == "white")
                                {
                                        //initialize type as babyface
                                        wrestler[i].type = 'b';
                                        wrestler[i].color = "gray";
                                        myQueue.push(wrestler[i]);
                                        break;
                                }
                        }
                }

                Wrestler parent = myQueue.front();
                //cout << "parent number: " << parent.number << endl;
                //cout << "Parent name: " << parent.name << endl;
                //cout << "Parent type: " << parent.type << endl;
                myQueue.pop();

                for (int i=1; i<size+1; i++) //find the edges
                {
                        //cout << graph[parent.number][i] << " ";

                        if (graph[parent.number][i] == 1 && wrestler[i-1].color != "black") //found a vertex that has not already been covered
                        {
                                //cout << "child node: " << i << " " << endl;
                                //cout << "Opponent name: " << wrestler[i-1].name << endl;
                                //cout << "Opponent color: " << wrestler[i-1].color << endl;
                                //if children color white, change to gray

                                if (wrestler[i-1].color == "white")
                                        {
                                                wrestler[i-1].color = "gray";
                                                //change the type if needed
                                                if (wrestler[i-1].type == '*') //not designated yet
                                                {
                                                        if (parent.type == 'b') //parent type is a babyface, so child must be heel
                                                                {
                                                                        wrestler[i-1].type = 'h';
                                                                }
                                                        else if (parent.type == 'h') //parent type is a heel, so child must be babyface
                                                                {
                                                                        wrestler[i-1].type = 'b';
                                                                }
                                                        //cout << "child new type: " << wrestler[i-1].type << endl;
                                                }
                                        }
                                else if (wrestler[i-1].color == "gray")
                                        {

                                                if (wrestler[i-1].type == 'b')
                                                {
                                                        //cout << "child already designated: " << wrestler[i-1].type << endl;
                                                        if (parent.type == 'b')
                                                                {
                                                                        //cout << "both are babyface " << endl;
                                                                        rivalry = false;
                                                                        break;
                                                                }
                                                }
                                                else if (wrestler[i-1].type == 'h')
                                                {
  							//cout << "child already designated: " << wrestler[i-1].type << endl;
                                                        if (parent.type == 'h')
                                                                {
                                                                        //cout << "both are heel " << endl;
                                                                        rivalry = false;
                                                                        break;
                                                                }
                                                }
                                        }
                                        //push to queue
                                        myQueue.push(wrestler[i-1]);
                                }
                        }

                        //cout << endl;
                        //change parent node color to black
                        wrestler[parent.number-1].color = "black";
                        parent.color = "black";

                }

                displayResult(rivalry, wrestler);
}


int main()
{
        string name;
        cout << "Enter your file name: " << endl;
        cin >> name;

        ifstream infile;
        infile.open(name.c_str());

        int numWrestlers;
        int numPairs;
        vector <Wrestler>myVector;
        vector <Pair> edges;

        string myString;
        int iter=1;
        int count=1;
        int number = 1;
        int wrestler1;
        int wrestler2;

        //pointer to matrix
        int**matrix;
        while (infile >> myString)
        {
                //cout << "Iteration: " << iter << endl;
                if (iter == 1)
                {
                        //convert from string to int
                        stringstream geek(myString);
                        int x = 0;
                        geek >> x;
                        numWrestlers = x;
                }
                if (iter >1 && iter < numWrestlers+2) //these are the fighters
                {
                        //store in a struct
                        Wrestler wrestler;
                        wrestler.name = myString;
                        //initialize number for adj matrix
                        wrestler.number = number;
                        //initialize type as blank
                        wrestler.type = '*';
                        //initialize color as white
                        wrestler.color = "white";
                        //then add to the vector
                        myVector.push_back(wrestler);
                        //increment number
                        number++;

                }
                if (iter == numWrestlers+2)
 		{
                        //convert from string to int
                        stringstream geek(myString);
                        int x = 0;
                        geek >> x;
                }
                //determine edges
                if (iter > numWrestlers+2)
                {

                        if (count ==1)
                        {
                                //search for the matching int
                                for (int i=0; i<numWrestlers; i++)
                                {
                                        if (myVector[i].name == myString)
                                        {
                                                wrestler1 = myVector[i].number;
                                        }
                                }
                                //cout << "wrestler name: " << myString << endl;
                                //cout << "wrestler 1: " << wrestler1 << endl;
                                count++;
                        }
                        else // (count ==2)
                        {
                                //search for the matching int
                                for (int i=0; i<numWrestlers; i++)
                                {
                                        if (myVector[i].name == myString)
                                        {
                                                wrestler2 = myVector[i].number;
                                        }
                                }
                                //cout << "wrestler name: " << myString << endl;

                                //cout << "wrestler 2: " << wrestler2 << endl;

                                //store in a struct
                                Pair pair;
                                pair.w1 = wrestler1;
                                pair.w2 = wrestler2;
                                //push into vector
                                edges.push_back(pair);

                                count =1; //reset count;
                        }

                        //cout << myString << endl;
                }

                iter++;
                //cout << myString << endl;
        }

        infile.close();


        //allocate space for adjacency matrix
        matrix = new int*[numWrestlers+1];
        for (int i=0; i<numWrestlers+1; i++)
                {
                        matrix[i] = new int[numWrestlers+1];
                }


        //initialize adjacency matrix
        for (int i=0; i<numWrestlers+1; i++)
        {
                for (int j=0; j<numWrestlers+1; j++)
                {
                        if (i ==0) //first row
                        {
 				matrix[i][j] = j;
                        }
                        else if (j==0)
                        {
                                matrix[i][j] = i;
                        }
                        else
                        {
                                matrix[i][j] = 0;
                        }
                }
        }

        //fill up adjacency matrix
        for (int i=0; i<numPairs; i++)
        {
                matrix[edges[i].w1][edges[i].w2] = 1;
                matrix[edges[i].w2][edges[i].w1] = 1;
        }

        //send to function
        Search(matrix, myVector);

	//clean up memory
	for (int i=0; i<numWrestlers+1; i++)
		{
			delete[] matrix[i];
		} 
	delete[] matrix;

        return 0;
        }


