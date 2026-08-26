#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

struct Song { 
    string title;
    int time; 
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

        //Convert underscores to spaces
        replace(songTitle.begin(), songTitle.end(), '_', ' ');
        replace(artistName.begin(), artistName.end(), '_', ' ');
        replace(albumName.begin(), albumName.end(), '_', ' ');

        //Convert time to seconds
        int min, sec;
        string minStr, secStr;
        stringstream ss2(songTime); 
        
           
           
        //Note: song map key is track number not title, helps when sorting numerically
        data[artistName].albums[albumName].songs[songNum].title = songTitle;
        data[artistName].albums[albumName].songs[songNum].time = songTime; 
        data[artistName].name = artistName; 
        data[artistName].albums[albumName].name = albumName;
        data[artistName].albums[albumName].songs[songNum].genre = songGenre;
        data[artistName].albums[albumName].songs[songNum].trackNum = songNum;

        //calc total time for album and artist
            
       }
            

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

