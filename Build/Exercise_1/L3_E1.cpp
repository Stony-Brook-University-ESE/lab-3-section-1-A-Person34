#include <iostream>
#include <string>


using namespace std;


// Create a struct for the songs and all information about the song
struct song
{
    string name;
    string artist;
    int year;
    song* next;


    song(string n, string a, int y) : name(n), artist(a), year(y), next(nullptr) {}
};


// Create our class for the list of songs
class songList
{
    private:
        song* head;


    public:
        // Constructor
        songList() : head(nullptr) {}


        // Destructor
        ~songList()
        {
            while(!empty())
            {
                removeFront();
            }
        }

        // Function to remove the front element
        void removeFront() {
            if (!empty()) {
                song* temp = head;
                head = head->next;
                delete temp;
            }
        }

        // Function to detect if the string is empty or not
        bool empty() const
        {
            if(head == nullptr)
            {
                return true;
            }


            else
            {
                return false;
            }
        }

        song* getHead() const
        {
            return head;
        }

        // Function to add an element to the list in order
        void addSong(string name, string artist, int year)
        {
            song* newSong = new song(name, artist, year);
            
            // If the list is empty of a new song is to be put in front
            if(!head || head->name > name)
            {
                newSong->next = head;
                head = newSong;
                return;
            }

            // Place in the correct position in the list
            song* current = head;
            while(current->next && current->next->name < name)
            {
                current = current->next;
            }

            newSong->next = current->next;
            current->next = newSong;
        }

        // Function to delete the three requeseted songs from the list
        void deleteThree()
        {
            // First, make sure there are at least 3 songs to delete
            if(!head || !head->next || ! head->next->next)
            {
                cout << "ERROR: Not enough songs to remove.\n";
                return;
            }

            // Delete 3 songs from the list
            for(int i = 0; i < 3; i++)
            {
                string deleteSong;
                cout << "\nEnter song name to delete: ";
                getline(cin, deleteSong);

                song* current = head;
                song* prev = nullptr;

                while(current)
                {
                    if(current->name == deleteSong)
                    {
                        if(prev)
                        {
                            prev->next = current->next;
                        }

                        else
                        {
                            head = current->next;
                        }

                        // Now we delete the song that we found in the list
                        delete current;
                        cout << "Deleted: " << deleteSong << "\n\n";
                        break;
                    }

                    prev = current;
                    current = current->next;
                }

                // If the song inputted is not in there, let the user know
                if(!current)
                {
                    cout << "The song '" << deleteSong << "' was not found in the list.\n";
                }
            }
        }

        void display() const
        {
            song* current = head;
            while(current)
            {
                cout << "'" << current->name << "' by " << current->artist << " (released in " << current->year << ")\n";
                current = current->next;
            }
        }
};


int main()
{
    songList mainList;
    songList sortedList;
    string name, artist;
    int year;
    int songCount = 0;


    // Prompt the user to enter in a song, the artist, and release year
    cout << "\n\nEnter song name, artist, and release year:";

    // Get the data from what the user inputs
    while(true)
    {
        // Get the song name
        cout << "\nSong name: ";
        getline(cin, name);

        // If there is nothing inputted in for the name, we break out of the loop
        if(name.empty())
        {
            break;
        }

        // Get the artist's name
        cout << "Artist: ";
        getline(cin, artist);

        // Get the release year
        cout << "Release Year: ";
        cin >> year;

        // Ignore anything that is leftover and store everything else
        cin.ignore();
        mainList.addSong(name, artist, year);
    }

    // Display the list
    cout << "\nSongs in alphabetical order: \n";
    mainList.display();

    cout << "\n" << "\n";

    // Prompt the user to delete 3 songs at their request
    cout << "\nEnter 3 songs to delete: ";

    song* current = mainList.getHead();

    // Count how many songs are in the list
    while(current)
    {
        songCount++;
        current = current->next;
    }
    

    // Make sure there are at least 3 songs are inputted into the list
    if(songCount < 3)
    {
        cout << "ERROR: Not enough songs to remove.";
        return 0;
    }

    // Have the user input the 3 songs to delete and show the new list
    mainList.deleteThree();
    cout << "\n\nNew Song List:\n";
    mainList.display();

    cout << "\n\n";

    return 0;
}