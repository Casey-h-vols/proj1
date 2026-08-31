#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <vector>

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


string convert_time(int a){
	int sec,min;

	if ((a / 60)>0){
		sec = a%60;
		min = a/60;
		if (sec < 10){
			return to_string(min)+":0"+to_string(sec);
		} else return to_string(min)+":"+to_string(sec);
	}
	sec = a%60;
	return "0:"+to_string(sec);
	 
}


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
		
		// Debug string for file ingestion
		//cout << "Title: " << songTitle << "\n";
		//cout << "Time: " << songTime << "\n";


        //Convert underscores to spaces
        replace(songTitle.begin(), songTitle.end(), '_', ' ');
        replace(artistName.begin(), artistName.end(), '_', ' ');
        replace(albumName.begin(), albumName.end(), '_', ' ');

        //Convert time to seconds
        int min, sec;
        string minStr, secStr;
		vector<int> timeVec;
        stringstream ss2(songTime); 
		while (getline(ss2,minStr,':')) {
			//cout << "time check:  " <<minStr << "\n";
			timeVec.push_back(stoi(minStr));
		}
		sec = (timeVec[0]*60) + timeVec[1];
		//cout << "TIME: " << sec << "\n";
           
           
        //Note: song map key is track number not title, helps when sorting numerically
        data[artistName].albums[albumName].songs[songNum].title = songTitle;		
        data[artistName].albums[albumName].songs[songNum].time = sec;
		data[artistName].albums[albumName].totalTime += sec;
		data[artistName].totalTime += sec;
		data[artistName].nsongs++;
		data[artistName].albums[albumName].nsongs++;
		data[artistName].name = artistName; 
        data[artistName].albums[albumName].name = albumName;
        data[artistName].albums[albumName].songs[songNum].genre = songGenre;
        data[artistName].albums[albumName].songs[songNum].trackNum = songNum;

        //calc total time for album and artist
            
       }
            

    } 
    
    inputFile.close();

    //Print data 
	
	map<string, Artist>::iterator itr1;
	map<string, Album>::iterator itr2;
	map<int, Song>::iterator itr3;

	for (itr1 = data.begin(); itr1 != data.end(); ++itr1) {
		cout << itr1->first <<": " << itr1->second.nsongs << ", " << convert_time(itr1->second.totalTime) <<endl;
	
		for (itr2 = itr1->second.albums.begin(); itr2 != itr1->second.albums.end(); ++itr2){
			cout <<"        " << itr2->first << ": "<< itr2->second.nsongs << ", " << convert_time(itr2->second.totalTime) << endl;

			for (itr3 = itr2->second.songs.begin(); itr3 != itr2->second.songs.end(); ++itr3){
				cout << "                "  << itr3->first << ". " << itr3->second.title << ": " << convert_time(itr3->second.time) << endl;
			}
		}
	}

    return 0; 
}

 

//	- apply data where it needs to go 
//		- insert song -> data[artist][album][track]
//		- insert album total -> albumLengthData[Artist][Album] += time;
//	
//  - print entire library using nested iterators
