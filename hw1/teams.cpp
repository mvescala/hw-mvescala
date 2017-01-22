#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

// *You* are not allowed to use global variables
//  but for just the output portion *we* will. ;>
int combo = 1;

// @brief Prints a single combination of teams
//
// @param[in] team1 Array containing the names of team 1
// @param[in] team2 Array containing the names of team 2
// @param[in] len Size of each array
void printSolution(const string* team1, 
		   const string* team2,
		   int len)
{
  cout << "\nCombination " << combo++ << endl;
  cout << "T1: ";
  for(int i=0; i < len; i++){
    cout << team1[i] << " ";
  }
  cout << endl;
  cout << "T2: ";
  for(int i=0; i < len; i++){
    cout << team2[i] << " ";
  }
  cout << endl;
}

// You may add additional functions here
int setTeams(const string* names,  string* team1, 
		   string* team2,
		   int num, int dex, int i)
{
   //Run function until our position reaches the the end of a team size
   if(dex == num/2){
      return 1;
   }
   //For one index less, add the appropriate name to the array
   //for both teams based on a moving index
   if(dex <num/2-1){
               team1[dex+1] = names[(dex+i)%(num-1)+1];
            }
    team2[dex] = names[(dex+i-1+num/2)%(num-1)+1]; 
    //run again for the next name
    return setTeams(names, team1, team2, num, dex+1, i);   
}



int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please provide a file of names" << endl;
    return 1;
  }
  // Complete the rest of main
   int num;
   ifstream ifile(argv[1]);
   
   if(ifile.fail()){
    cerr << "error" << endl;
    return 1;
  }
   
   string x;
   ifile >> num;
   //check for even amount of names
   if (num%2 != 0){
         cout << "error" <<endl;
         return 1;
      }
   //dynamically allocate 3 arrays of strings
   string *names = new string[num];
   string *team1 = new string[num/2];
   string *team2 = new string[num/2];
   int v = 0;
   while( 1 ){
   //add names from file to array
   //until failure, or end if number of names
   //is not the same as given number
      ifile >> x;
      if(ifile.fail()) break;
      if (v >= num){
         cout << "error" <<endl;
         return 1;
      }
      names[v] = x;
      ++v;
   }
   if (v != num){
         cout << "error" <<endl;
         return 1;
      }
   //process all different types of set
   for(int i=0; i<(num*2-2)/2; i++){
      team1[0] = names[0];
      //run recursive function for each team 
      setTeams(names, team1, team2, num, 0, i);
   printSolution(team1, team2, num/2);
   printSolution(team2, team1, num/2);
   }
   //free up the space
   delete [] names;
   delete [] team1;
   delete [] team2;

  return 0;
}
