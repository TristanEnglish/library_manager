#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

string const FILENAME = "Desktop/PL/POWERS_INVENTORY.csv";

// Book structure
struct Book
{
    string inventory_number_string;
    string title;
    string author;
    string description;
    string additional_contents;
    string artist;
    string shelf_number;
};

// This function takes a book and outputs it's information to the user
void outputBook(Book book)
{
    // Output inventory number, title, author, artist, writing, and additional contents
    cout << "Inventory Number: " << book.inventory_number_string << endl;
    cout << "Title: " << book.title << endl;
    cout << "Author: " << book.author << endl;
    cout << "Artist: " << book.artist << endl;
    cout << "Writing Inside?: ";
    // If there is no description, tell the user
    if (book.description == "")
    {
        cout << "No" << endl;
    }
    // Otherwise, output the description
    else
    {
        cout << book.description << endl;
    }

    cout << "Additional Contents: ";
    // If there are no additional contents, tell the user
    if (book.additional_contents == "")
    {
        cout << "N/A" << endl;
    }
    // Otherwise, output the additional contents
    else
    {
        cout << book.additional_contents << endl;
    }

    cout << "Stored on "; 
    cout << book.shelf_number << endl;
}

// This function outputs a menu of options to the user
void displayMenu()
{
    cout << endl;
    cout << "Welcome to the Powers Library! What would you like to do?" << endl;
    cout << "1. Search by artist" << endl;
    cout << "2. Search by genre" << endl;
    cout << "3. Search by inventory number" << endl;
    cout << "4. (ADMIN ONLY) Edit a specific book" << endl;
    cout << "5. (ADMIN ONLY) Add a new book" << endl;
    cout << "6. Exit" << endl;
    cout << "#> ";
}

// This function opens a .csv file and reads the information into a vector of books, which it returns
vector<Book> readBooks()
{
    ifstream myFile;
    string line;
    string newInput;
    vector <Book> books;
    int inputCount = 0;

    // Open the spreadsheet
    myFile.open(FILENAME);

    // If the file opened correctly,
    if (myFile.is_open())
    {
        // For every line of the file:
        while (getline(myFile, line))
        {
            Book newBook;
            vector <string> inputs;
            stringstream ss(line);
            // Separate the line into inputs
            while (getline(ss, newInput, ','))
            {
                inputs.push_back(newInput);
                inputCount++;
            }
            // Fill in the information into a new book
            newBook.shelf_number = inputs[0];
            newBook.inventory_number_string = inputs[1];
            newBook.title = inputs[2];
            newBook.author = inputs[3];
            newBook.artist = inputs[4];
            // If we have a description but no additional contents, fill in the description only
            if (inputCount == 6)
            {
                newBook.description = inputs[5];
            }
            // If we have both a description and additional contents, fill in both
            if (inputCount == 7)
            {
                newBook.description = inputs[5];
                newBook.additional_contents = inputs[6];
            }

        // Add the books to the books vector
        books.push_back(newBook);
        inputCount = 0;
        newInput = "";
        }
    }
    else
    {
        // If we couldn't open the file, tell the user w/ an error
        cout << endl;
        cout << "Error: Cannot find spreadsheet data" << endl;
    }
    // Close the file and return our read vector when we're done
    myFile.close();
    return books;
}

// This function takes in two strings and checks if they are equivelant while being case insensitive
// Returns: false if not equivelant, true if equivelant
bool isEqual(string s, string a)
{
    // If the lengths don't match, we know they aren't equal
    if (s.length() != a.length())
    {
        return false;
    }

    // If the lenghths match, convert every letter to lowercase so it's case insensitive
    for (int i = 0; i < s.length(); i++)
    {
        s[i] = tolower(s[i]);
        a[i] = tolower(a[i]);
    }

    // Now, if they are the same, return true
    if (s == a)
    {
        return true;
    }
    // Otherwise, return false
    else
    {
        return false;
    }
}

// This function takes a vector of books and writes it to the existing spreadsheet so changes can persist
void newWrite(vector <Book> books)
{
    // Open the inventory spreadsheet
    ofstream writeFile;
    writeFile.open(FILENAME);

    // Go through the books vector
    for (int i = 0; i < books.size(); i++)
    {
        // Write all the information of each book to the spreadsheet
        writeFile << books[i].shelf_number << "," << books[i].inventory_number_string << "," << books[i].title << ",";
        writeFile << books[i].author << "," << books[i].artist << "," << books[i].description << "," << books[i].additional_contents;
        writeFile << endl;
    }
    // Close the file
    writeFile.close();
}

// This function takes in a string and checks to see if it is a number
// Returns: true if number, false if not
bool isNum(string s)
{
    // Go through the string character by character
    for (int i = 0; i < s.length(); i++)
    {
        // If we find any character that is not a digit, return false
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    // Otherwise, it's a number! Return true
    return true;
}

int main()
{
    vector<Book> books = readBooks();
    string strinput;
    int input;
    string password;
    if (true)
    {
        password = "password";
    }

    // Display the menu to the user
    cout << endl << endl;
    displayMenu();
    cin >> strinput;
    // Keep asking the user to input an option until they enter a number
    while (!isNum(strinput))
    {
        cout << "Invalid input. Please enter the NUMBER of the option you choose." << endl;
        cout << "#> ";
        cin >> strinput;
    }
    
    input = stoi(strinput);
    int number;
    string strnumber;

    // Repeat the following until the user presses Quit
    while (input != 6)
    {
        switch(input)
        {
            // If the user selects "search by artist"
            case 1:
            {
                string artist;
                bool found = false;
                // Ask the user to enter the artist's last name
                cout << "Please enter the LAST NAME of the artist you're looking for." << endl;
                cout << "#> "; 
                cin.ignore();
                getline(cin, artist);
                cout << endl;
                cout << "----------Showing all results for " << artist << "...----------" << endl;
                cout << endl;

                // Go through every book, output ones with matching artists
                for(int i = 0; i < books.size(); i++)
                {
                    // If we find a matching book
                    if (isEqual(books[i].artist, artist))
                    {
                        // Output the title and shelf number
                        found = true;
                        cout << "Title: " << books[i].title << endl;
                        cout << "Shelf Number: " << books[i].shelf_number << endl;
                        cout << endl;
                    }
                }
                // If we didn't find a matching book, tell the user
                if (!found)
                {
                    cout << "No results found for " << artist << ". Make sure you are typing the LAST NAME of the artist you're looking for. " << endl;
                }
                break;
            }
            // If the user selects "search by genre"
            case 2:
            {
                string genre;
                bool found = false;
                // Ask the user to enter the genre, and provide them with current genres to choose from
                cout << "Please enter the GENRE you're looking for." << endl;
                cout << "Our current selection of genres includes:" << endl;
                cout << "Old Masters, Art Around the World, American Art, Modern Art" << endl;
                cout << "#> "; 
                cin.ignore();
                getline(cin, genre);
                cout << endl;
                cout << "----------Showing all results for " << genre << "...----------" << endl;
                cout << endl;

                // Go through every book, output the ones with matching genre
                for(int i = 0; i < books.size(); i++)
                {
                    if (isEqual(books[i].artist, genre))
                    {
                        found = true;
                        // Output the title and shelf number
                        cout << "Title: " << books[i].title << endl;
                        cout << "Shelf Number: " << books[i].shelf_number << endl;
                        cout << endl;
                    }
                }
                // If we never found a matching book, tell the user
                if (!found)
                {
                    cout << "No results found for " << genre << ". Make sure you are typing the LAST NAME of the artist you're looking for. " << endl;
                }
                break;
            }
            // If the user selects "search by inventory number"
            case 3:
            {
                // Ask the user to enter the number of the book they're looking for
                cout << "Please enter the NUMBER of the book you are looking for." << endl;
                cout << "(For example, if the inventory number is PL25, only enter 25):" << endl;
                cout << "#> ";
                cin >> strnumber;
                // Continue asking for input until the user enters a number
                while (!isNum(strnumber))
                {
                    cout << "Invalid input. Please enter the NUMBER of the book you are looking for." << endl;
                    cout << "(For example, if the inventory number is PL25, only enter 25):" << endl;
                    cout << "#> ";
                    cin >> strnumber;
                }
                number = stoi(strnumber);
                cout << endl;
                // If the book number is outside the scope of our current books, tell the user
                if (number > books.size() || number == 0)
                {
                    cout << "Error. The number you inputted is outside the current number of books in the library." << endl;
                    break;
                }
                // Otherwise, output that particular book to the user
                outputBook(books[number - 1]);
                cout << endl;
                break;
            }
            // If the user selects "edit a specific book"
            case 4:
            {
                string pass;
                // Ask the user for a password to continue
                cout << "This option is for employees only. Please enter the password: ";
                cin >> pass;
                // If they got the password correct, continue
                if (pass == password)
                {
                    int option;
                    string stroption;
                    // Ask the user for the number of the book they're looking for
                    cout << "Please enter the NUMBER of the book you are looking to edit." << endl;
                    cout << "(For example, if the inventory number is PL25, only enter 25):" << endl;
                    cout << "#> ";
                    cin >> strnumber;
                    // Continue asking until they enter a number
                    while (!isNum(strnumber))
                    {
                        cout << "Invalid input. Please enter the NUMBER of the book you are looking for." << endl;
                        cout << "(For example, if the inventory number is PL25, only enter 25):" << endl;
                        cout << "#> ";
                        cin >> strnumber;
                    }
                    number = stoi(strnumber);
                    // If the book number is outside the scope of our current books, tell the user
                    if (number > books.size() || number == 0)
                    {
                        cout << "Error. The number you inputted is outside the current number of books in the library." << endl;
                        break;
                    }
                    // Otherwise, output that particular book
                    cout << endl;
                    outputBook(books[number - 1]);
                    cout << endl;
                    string stryn;
                    // Ask the user what they'd like to edit
                    cout << "What would you like to edit?" << endl;
                    cout << "1. Title" << endl;
                    cout << "2. Author" << endl;
                    cout << "3. Artist" << endl;
                    cout << "4. Writing Inside" << endl;
                    cout << "5. Additional Contents" << endl;
                    cout << "6. Shelf Number" << endl;
                    cout << "7. Exit" << endl;
                    cout << "#> ";
                    cin >> stroption;

                    // Continue asking until they enter a numerical option
                    while (!isNum(stroption))
                    {
                        cout << "we back" << endl;
                        cout << "Invalid input. Please enter the NUMBER of the option you choose." << endl;
                        cin >> stroption;
                    }
                    
                    option = stoi(stroption);
                    
                    switch(option)
                    {
                        // Title
                        case 1:
                        {
                            // Ask the user for the new title
                            string newTitle;
                            cout << "What would you like the new title to be?" << endl;
                            cout << "#> ";
                            cin.ignore();
                            getline(cin, newTitle);
                            // If there are any commas in the submission, change them to '-' since we use commas as delimeters
                            for (int i = 0; i < newTitle.length(); i++)
                            {
                                if (newTitle[i] == ',')
                                {
                                    newTitle[i] = '-';
                                }
                            }
                            // Check if the user is sure
                            cout << "Are you sure you want the new title for PL" << number << " to be " << newTitle << "? (y/n): ";
                            cout << "#> ";
                            cin >> stryn;

                            // Continue asking the user for input until they input a 'y' or 'n'
                            while (stryn[0] != 'n' && stryn[0] != 'N' && stryn[0] != 'y' && stryn[0] != 'Y')
                            {
                                cout << "Please enter your answer as one letter. Y for yes, N for no" << endl;
                                cout << "#> ";
                                cin >> stryn;
                            }
                            // If the user says yes
                            if (stryn[0] == 'Y' || stryn[0] == 'y')
                            {
                                // Change the title and write it to the spreadsheet
                                cout << "Changing title..." << endl;
                                books[number-1].title = newTitle;
                                newWrite(books);
                                books = readBooks();
                                cout << "Title changed successfully" << endl;
                            }
                            break;
                        }
                        // Author
                        case 2:
                        {
                            string newAuthor;
                            // Ask the user for the new author
                            cout << "What would you like the new author to be?" << endl;
                            cout << "#> ";
                            cin.ignore();
                            getline(cin, newAuthor);
                            // If there are any commas in the submission, change them to '-' since we use commas as delimeters
                            for (int i = 0; i < newAuthor.length(); i++)
                            {
                                if (newAuthor[i] == ',')
                                {
                                    newAuthor[i] = '-';
                                }
                            }
                            // Check if the user is sure
                            cout << "Are you sure you want the new author for PL" << number << " to be " << newAuthor << "? (y/n): ";
                            cout << "#> ";
                            cin >> stryn;
                            // Continue asking until they enter a 'y' or 'n'
                            while (stryn[0] != 'n' && stryn[0] != 'N' && stryn[0] != 'y' && stryn[0] != 'Y')
                            {
                                cout << "Please enter your answer as one letter. Y for yes, N for no" << endl;
                                cout << "#> ";
                                cin >> stryn;
                            }
                            // If the user says yes
                            if (stryn[0] == 'Y' || stryn[0] == 'y')
                            {
                                // Change the author and write it to the spreadsheet
                                cout << "Changing author..." << endl;
                                books[number-1].author = newAuthor;
                                newWrite(books);
                                books = readBooks();
                                cout << "Author changed successfully" << endl;
                            }
                            break;
                        }
                        // Artist
                        case 3:
                        {
                            string newArtist;
                            // Ask the user for the new artist
                            cout << "What would you like the new artist/genre to be?" << endl;
                            cout << "#> ";
                            cin.ignore();
                            getline(cin, newArtist);
                            // If there are any commas in the submission, change them to '-' since we use commas as delimeters
                            for (int i = 0; i < newArtist.length(); i++)
                            {
                                if (newArtist[i] == ',')
                                {
                                    newArtist[i] = '-';
                                }
                            }
                            // Check if they are sure
                            cout << "Are you sure you want the new artist/genre for PL" << number << " to be " << newArtist << "? (y/n): ";
                            cout << "#> ";
                            cin >> stryn;
                            // Continue asking until they enter a 'y' or 'n'
                            while (stryn[0] != 'n' && stryn[0] != 'N' && stryn[0] != 'y' && stryn[0] != 'Y')
                            {
                                cout << "Please enter your answer as one letter. Y for yes, N for no" << endl;
                                cout << "#> ";
                                cin >> stryn;
                            }
                            // If the user says yes
                            if (stryn[0] == 'Y' || stryn[0] == 'y')
                            {
                                // Change the artist and write to the spreadsheet
                                cout << "Changing artist/genre..." << endl;
                                books[number-1].artist = newArtist;
                                newWrite(books);
                                books = readBooks();
                                cout << "Artist/genre changed successfully" << endl;
                            }
                            break;
                        }
                        // Description
                        case 4:
                        {
                            string newDescription;
                            // Ask the user for the new description
                            cout << "What would you like the new writing description to be?" << endl;
                            cout << "#> ";
                            cin.ignore();
                            getline(cin, newDescription);
                            // If there are any commas in the submission, change them to '-' since we use commas as delimeters
                            for (int i = 0; i < newDescription.length(); i++)
                            {
                                if (newDescription[i] == ',')
                                {
                                    newDescription[i] = '-';
                                }
                            }
                            // Check if the user is sure
                            cout << "Are you sure you want the new writing description for PL" << number << " to be " << newDescription << "? (y/n): ";
                            cin >> stryn;
                            // Continue asking until they enter a 'y' or 'n'
                            while (stryn[0] != 'n' && stryn[0] != 'N' && stryn[0] != 'y' && stryn[0] != 'Y')
                            {
                                cout << "Please enter your answer as one letter. Y for yes, N for no" << endl;
                                cout << "#> ";
                                cin >> stryn;
                            }
                            // If they say yes
                            if (stryn[0] == 'Y' || stryn[0] == 'y')
                            {
                                // Change the description and write to the spreadsheet
                                cout << "Changing writing description..." << endl;
                                books[number-1].description = newDescription;
                                newWrite(books);
                                books = readBooks();
                                cout << "Writing description changed successfully" << endl;
                            }
                            break;
                        }
                        // Additional Contents
                        case 5:
                        {
                            string newContents;
                            // Ask for the new additional contents
                            cout << "What would you like the new additional contents to be?" << endl;
                            cin.ignore();
                            getline(cin, newContents);
                            // If there are any commas in the submission, change them to '-' since we use commas as delimeters
                            for (int i = 0; i < newContents.length(); i++)
                            {
                                if (newContents[i] == ',')
                                {
                                    newContents[i] = '-';
                                }
                            }
                            // Check if the user is sure
                            cout << "Are you sure you want the new additional contents for PL" << number << " to be " << newContents << "? (y/n): ";
                            cout << "#> ";
                            cin >> stryn;
                            // Continue asking until they enter a 'y' or 'n'
                            while (stryn[0] != 'n' && stryn[0] != 'N' && stryn[0] != 'y' && stryn[0] != 'Y')
                            {
                                cout << "Please enter your answer as one letter. Y for yes, N for no" << endl;
                                cout << "#> ";
                                cin >> stryn;
                            }
                            // If yes,
                            if (stryn[0] == 'Y' || stryn[0] == 'y')
                            {
                                // Change the additional contents and write to the spreadsheet
                                cout << "Changing additional contents..." << endl;
                                books[number-1].additional_contents = newContents;
                                newWrite(books);
                                books = readBooks();
                                cout << "Additional contents changed successfully" << endl;
                            }
                            break;
                        }
                        // Shelf Number
                        case 6:
                        {
                            string newShelfNumber;
                            // Ask the user for the new shelf number
                            cout << "What would you like the new shelf number to be?" << endl;
                            cout << "#> ";
                            cin.ignore();
                            getline(cin, newShelfNumber);
                            // If there are any commas in the submission, change them to '-' since we use commas as delimeters
                            for (int i = 0; i < newShelfNumber.length(); i++)
                            {
                                if (newShelfNumber[i] == ',')
                                {
                                    newShelfNumber[i] = '-';
                                }
                            }
                            // Check if they are sure
                            cout << "Are you sure you want the new shelf number for PL" << number << " to be " << newShelfNumber << "? (y/n): ";
                            cout << "#> ";
                            cin >> stryn;
                            // Continue asking until they enter a 'y' or 'n'
                            while (stryn[0] != 'n' && stryn[0] != 'N' && stryn[0] != 'y' && stryn[0] != 'Y')
                            {
                                cout << "Please enter your answer as one letter. Y for yes, N for no" << endl;
                                cout << "#> ";
                                cin >> stryn;
                            }
                            // If yes
                            if (stryn[0] == 'Y' || stryn[0] == 'y')
                            {
                                // Change the shelf number and write to the spreadsheet
                                cout << "Changing shelf number..." << endl;
                                books[number-1].shelf_number = newShelfNumber;
                                newWrite(books);
                                books = readBooks();
                                cout << "Shelf number changed successfully" << endl;
                            }
                            break;
                        }
                        // Exit
                        case 7:
                        {
                            break;
                        }
                        default:
                        {  
                            cout << "Invalid input. Please try again." << endl;
                        }
                    }
                }
                // If the user didn't get the password right, tell them and exit
                else
                {
                    cout << "INVALID PASSWORD" << endl;
                }
                break;
            }
            // If the user chooses "add a new book"
            case 5:
            {
                string pass;
                // Ask the user for the password
                cout << "This option is for employees only. Please enter the password: ";
                cin >> pass;
                // If they got the password right
                if (pass == password)
                {
                    string stryn;
                    string stryesno;
                    string title;
                    string author;
                    string artist;
                    string description;
                    string contents;
                    string shelf_num;
                    // Tell the user the next available inventory number they can fill
                    cout << "You can only make a new book at the next available inventory number" << endl;
                    cout << "As of now, that will be PL" << books.size()+1 << "." << endl;
                    cout << "Would you like to continue with this inventory number? (y/n)" << endl;
                    cout << "#> ";
                    cin >> stryesno;
                    // Continue asking until they enter a 'y' or 'n' if they'd like to continue
                    while (stryesno[0] != 'y' && stryesno[0] != 'Y' && stryesno[0] != 'n' && stryesno[0] != 'N')
                    {
                        cout << "Please enter your answer as one letter. Y for yes, N for no" << endl;
                        cout << "#> ";
                        cin >> stryesno;
                    }
                    // If yes, we will add a new book
                    if (stryesno[0] == 'y' || stryesno[0] == 'Y')
                    {
                        Book newBook;
                        newBook.inventory_number_string = "PL" + to_string(books.size()+1);

                        // Ask for the book's title
                        cout << "Please enter the book's title" << endl;
                        cout << "#> ";
                        cin.ignore();
                        getline(cin, title);

                        // If there are any commas in the submission, change them to '-' since we use commas as delimeters
                        for (int i = 0; i < title.length(); i++)
                        {
                            if (title[i] == ',')
                            {
                                title[i] = '-';
                            }
                        }
                        // Set the title
                        newBook.title = title;

                        // Ask for the author
                        cout << "Please enter the book's author" << endl;
                        cout << "#> ";
                        getline(cin, author);
                        // If there are any commas in the submission, change them to '-' since we use commas as delimeters
                        for (int i = 0; i < author.length(); i++)
                        {
                            if (author[i] == ',')
                            {
                                author[i] = '-';
                            }
                        }
                        // Set the author
                        newBook.author = author;

                        // Ask for the artist
                        cout << "Please enter the LAST NAME of the artist or the GENRE of the book:" << endl;
                        cout << "(Artists would be Johns, Warhol, Rauschenberg, etc.)" << endl;
                        cout << "(Genres would be Modern Art, Old Masters, Galleries and Auction Houses, etc.)" << endl;
                        cout << "#> ";
                        getline(cin, artist);
                        // If there are any commas in the submission, change them to '-' since we use commas as delimeters
                        for (int i = 0; i < artist.length(); i++)
                        {
                            if (artist[i] == ',')
                            {
                                artist[i] = '-';
                            }
                        }
                        // Set the artist
                        newBook.artist = artist;

                        // Ask if there is any writing
                        cout << "Is there any writing inside the book? (signatures, notes, etc.) (y/n)" << endl;
                        cout << "#> ";
                        cin >> stryn;
                        // Continue asking until the user inputs 'y' or 'n'
                        while (stryn[0] != 'n' && stryn[0] != 'N' && stryn[0] != 'y' && stryn[0] != 'Y')
                        {
                            cout << "Please enter your answer as one letter. Y for yes, N for no" << endl;
                            cout << "#> ";
                            cin >> stryn;
                        }
                        // If yes
                        if (stryn[0] == 'y' || stryn[0] == 'Y')
                        {
                            // Ask the user for the description
                            cout << "Please enter a description of any writing inside the book" << endl;
                            cout << "#> ";
                            cin.ignore();
                            getline(cin, description);
                            // If there are any commas in the submission, change them to '-' since we use commas as delimeters
                            for (int i = 0; i < description.length(); i++)
                            {
                                if (description[i] == ',')
                                {
                                    description[i] = '-';
                                }
                            }
                            // Set the description
                            newBook.description = description;
                        }
                        
                        // Ask if there are any additional contents
                        cout << "Are there any additional contents inside the book? (letters, notes, etc.) (y/n)" << endl;
                        cout << "#> ";
                        cin >> stryn;
                        // Continue asking until they input 'y' or 'n'
                        while (stryn[0] != 'n' && stryn[0] != 'N' && stryn[0] != 'y' && stryn[0] != 'Y')
                        {
                            cout << "Please enter your answer as one letter. Y for yes, N for no" << endl;
                            cout << "#> ";
                            cin >> stryn;
                        }
                        // If yes
                        if (stryn[0] == 'y' || stryn[0] == 'Y')
                        {
                            // Ask for a description of the additional contents
                            cout << "Please enter a description of any additional contents inside the book" << endl;
                            cout << "#> ";
                            cin.ignore();
                            getline(cin, contents);
                            // If there are any commas in the submission, change them to '-' since we use commas as delimeters
                            for (int i = 0; i < contents.length(); i++)
                            {
                                if (contents[i] == ',')
                                {
                                    contents[i] = '-';
                                }
                            }
                            // Set the additional contents
                            newBook.additional_contents = contents;
                        }

                        // Ask for the shelf number
                        cout << "Please enter the book's shelf number" << endl;
                        cout << "#> ";
                        cin.ignore();
                        getline(cin, shelf_num);
                        // If there are any commas in the submission, change them to '-' since we use commas as delimeters
                        for (int i = 0; i < shelf_num.length(); i++)
                        {
                            if (shelf_num[i] == ',')
                            {
                                shelf_num[i] = '-';
                            }
                        }
                        // Set the shelf number
                        newBook.shelf_number = shelf_num;

                        // Add the book to the vector
                        books.push_back(newBook);

                        // Write the new changes to the spreadsheet
                        newWrite(books);
                        // Load in the new books so we can use them in the program
                        books = readBooks();
                        cout << "Book added successfully" << endl;
                        cout << endl;
                        // Output the book to the user
                        outputBook(books[books.size()-1]);
                    }
                }
                // If they got the password wrong ,tell them and exit
                else
                {
                    cout << "INVALID PASSWORD" << endl;
                }
                break;
            }
            // If the user inputs any other number, tell them to try again
            default:
            {
                cout << "Invalid input. Please try again." << endl;
            }
        }
        // Display the menu again, this time within the loop
        displayMenu();
        cin >> strinput;
        // Continue asking until they enter a numerical option
        while (!isNum(strinput))
        {
            cout << "Invalid input. Please enter the NUMBER of the option you choose." << endl;
            cout << "#> ";
            cin >> strinput;
        }
        
        input = stoi(strinput);
    }
    return 0;
}