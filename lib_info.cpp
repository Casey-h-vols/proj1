#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

struct Song { 
    string title;
    string time; 
    string genre;
    int trackNum;
};

struct Album {
    map <int, Song > songs;
    string name;
    int totalTime;
    int nsongs;  // optional variable but makes it easier
};

struct Artist {
    map <string, Album > albums;
    string name;
    int totalTime;
    int nsongs;
};


// Main func needs to 
int main (int argc, char* argv[]) { 

    //Create 3D Map
    map <string, Artist> data; 
    
    //Open and read file contents
    ifstream inputFile(argv[1]); 

    if (!inputFile.is_open()) { 
        cerr << "Failed to open file" << endl; 
        return -1; 
    }

    string line;
    string artistKey, albumKey, songTitle, songTime, songName, artistName, albumName, songGenre;
    int songNum;

    //Extract and store data from each line
    while (getline(inputFile, line)) {
        stringstream ss(line); 

       if (ss >> songTitle >> songTime >> artistName >> albumName >> songGenre >> songNum) {
           
        data[artistName].albums[albumName].songs[songTitle].title = songTitle;

            
       }

         //convert underscores to spaces
            //time -> int -> seconds
            //calc total time for album and artist 
            

    } 
    
    inputFile.close();

    //Print data 
    
    return 0; 
}

//	- create 3-d maps 
//	- open/ read file contents
//	- apply data where it needs to go 
//		- insert song -> data[artist][album][track]
//		- insert album total -> albumLengthData[Artist][Album] += time;
//	

