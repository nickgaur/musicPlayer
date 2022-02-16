#include <iostream>
#include <list>
#include <string>
#include <cctype>
#include <iomanip>
#include <limits>

using namespace std;

class Song{
        friend ostream &operator<<(ostream &os, const Song &rhs);
        string name;
        string artist;
        int rating;
public:
        Song(string name, string artist, int rating)
                :name{name}, artist{artist}, rating{rating}{}
                
         string get_name() const {
                return name;
        }
        string get_artist() const {
                return artist;
        }
        int get_rating() const {
                return rating;
        }
    
    bool operator<(const Song &rhs) const {
                return this->name < rhs.name;
        }
        bool operator==(const Song &rhs) const {
                return this->name == rhs.name;
        }
};

ostream &operator<<(ostream &os, const Song &s) {
    os << setw(20) << left << s.name
       << setw(30) << left << s.artist
       << setw(2) << left << s.rating;
       return os;
}

void displayMenu(){
        cout << "F - Play First song" << endl;
        cout << "N - Play Next song" << endl;
        cout << "P - Play Prev song" << endl;
        cout << "A - Add New song" << endl;
        cout << "L - List the current playlist" << endl;
        cout << "========================" << endl;
        cout << "Enter a selection (Q to quit): ";
}

void play_current_song(const Song &song) {
    cout << "Playing:"<< endl;
    cout << song << "\n" << endl;
}

void display_playlist(const list<Song> &playlist, const Song &current_song) {
    for(auto song: playlist){
            cout << song << endl;
    }
    cout << "Current Song:" << endl;
    cout << current_song << endl;
}

int main()
{
	list <Song> playlist{
            {"God's Plan",        "Drake",                     5},
            {"Never Be The Same", "Camila Cabello",            5},
            {"Pray For Me",       "The Weekend and K. Lamar",  4},
            {"The Middle",        "Zedd, Maren Morris & Grey", 5},
            {"Wait",              "Maroone 5",                 4},
            {"Whatever It Takes", "Imagine Dragons",           3}    
        };
        auto currentSong = playlist.begin();
        char choice;
        do{
                displayMenu();
                cin >> choice;
                choice = toupper(choice);
                if(choice == 'F'){
                        cout << "Playing First Song:" << endl;
                        currentSong = playlist.begin();
                        play_current_song(*currentSong);
                }
                else if(choice == 'N'){
                        cout << "Playing Next Song:" << endl;
                        currentSong++;
                        if(currentSong == playlist.end()){
                                cout << "Wrapping to start of playlist" << endl;
                                currentSong = playlist.begin();
                        }
                        play_current_song(*currentSong);
                }
                else if(choice == 'P'){
                        cout << "Playing Previous Song:" << endl;
                        if(currentSong == playlist.begin()){
                                cout << "Wrapping to end of playlist" << endl;
                                currentSong = playlist.end();
                        }
                        currentSong--;
                        play_current_song(*currentSong);
                }
                else if(choice == 'A'){
                        cout << "Adding and playing new song" << endl;
                        string songName{""};
                        cout << "Enter song name: ";
                        getline(cin, songName);
                        cout << "Enter artist name: ";
                        string artist{""};
                        getline(cin, artist);
                        cout << "Enter rating: ";
                        int rating{0};
                        cin >> rating;
                        playlist.insert(currentSong, Song{songName, artist, rating});
                        cout << "New Song Added" << endl;
                }
                else if(choice == 'L'){
                        display_playlist(playlist, *currentSong);
                }
                else
                        cout << "Illegal choice, try again...";
        }while(choice != 'Q');
        
	return 0;
}
