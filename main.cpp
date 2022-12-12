#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <cstring>
#include <regex>
#include <fstream>

using namespace std;

string generate_password(int pw_length, int character_count_uppercase, int character_count_lowercase, int digit_count, int special_character_count, string blacklist);


int main(){    
    string password = "";
    string tmp = "";

    int pw_length = 0;
    int character_count_uppercase = 0;
    int character_count_lowercase = 0;
    int digit_count = 0;
    int special_character_count = 0;

    int temp_pw_length = 0;

    string blacklist = "";
    string need_blacklist = "";

    string save_to_file = "";
    string file_name = "";

    cout << "Welcome to the c++-version of my password generator.\n\n";
    cout << "First type in the length of the password:\n";

    cin >> pw_length;
    temp_pw_length = pw_length;

    cout << "\n[" << temp_pw_length << " left]  Now enter the amount of uppercase letters(ABCDE) for your password:\n";

    cin >> character_count_uppercase;
    temp_pw_length -= character_count_uppercase;

    cout << "\n[" << temp_pw_length << " left]  And now the amount of lowercase(abcde) letters:\n";

    cin >> character_count_lowercase;
    temp_pw_length -= character_count_lowercase;

    cout << "\n[" << temp_pw_length << " left]  Soon there, now type in the amount of digits(1234) you need:\n";

    cin >> digit_count;
    temp_pw_length -= digit_count;

    cout << "\n[" << temp_pw_length << " left]  Now we need some special characters(%~_^). Also type the desired amount of these in:\n";

    cin >> special_character_count;
    temp_pw_length -= special_character_count;

    if(temp_pw_length < 0){
        cout << "You chose too many characters, please try it again!\n";

        this_thread::sleep_for(chrono::seconds(3));

        exit(1);
    } else if(temp_pw_length > 0){
        cout << "You didn't choose enough characters, please try again!\n";

        this_thread::sleep_for(chrono::seconds(3));

        exit(1);
    }

    cout << "For the last one you can type in all the characters which you don't want in your password. Do you want this? [y/n]\n";

    cin >> need_blacklist;

    if(need_blacklist.at(0) == 'y'){
        cout << "\nOk, just type them all in a row:\n";

        cin >> blacklist;
    }

    

    cout << "\n\nThank you, we will now generate your password!\n" << "--------------------------------------------------------------";

    password = generate_password(pw_length, character_count_uppercase, character_count_lowercase, digit_count, special_character_count, blacklist);

    cout << "\n\n\nYour Password is:\n" << password;


    this_thread::sleep_for(chrono::seconds(3));

    cout << "\n\nWant to save it to a file?[y/n]\n";


    cin >> save_to_file;

    if(save_to_file.at(0) == 'y'){
        cout << "\nOk, what's the the file's name?\n";
        cin >> file_name;

        ofstream pwf(file_name + ".txt");
        pwf << password;
        pwf.close();

        cout << "\nPassword saved to " << file_name << ".txt!\n";
    }

    cout << "\n\nPress any button and enter to exit!\n";

    cin >> tmp;

    return 0;

}

string generate_password(int pw_length, int character_count_uppercase, int character_count_lowercase, int digit_count, int special_character_count, string blacklist){
    srand(time(NULL));

    

    string char_list_uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string char_list_lowercase = "abcdefghijklmnopqrstuvwxyz";
    string digit_list = "1234567890";
    string special_character_list = "!*#,;?+-_.=~^%(){}[]|:/";

    for(int i = 0; i < char_list_uppercase.length(); i++){if(blacklist.find(char_list_uppercase.at(i)) != string::npos){char_list_uppercase.replace(i, 1, "");}}
    for(int i = 0; i < char_list_lowercase.length(); i++){if(blacklist.find(char_list_lowercase.at(i)) != string::npos){char_list_lowercase.replace(i, 1, "");}}
    for(int i = 0; i < digit_list.length(); i++){if(blacklist.find(digit_list.at(i)) != string::npos){digit_list.replace(i, 1, "");}}
    for(int i = 0; i < special_character_list.length(); i++){if(blacklist.find(special_character_list.at(i)) != string::npos){special_character_list.replace(i, 1, "");}}

    string final_password = "";
    while(final_password.length() != pw_length){
        switch(rand() % 4){
            case 0:
                if(character_count_uppercase > 0){
                    final_password += char_list_uppercase.at(rand()%char_list_uppercase.length());
                    character_count_uppercase--;
                } 
                break;
            case 1:
                if(character_count_lowercase > 0){
                    final_password += char_list_lowercase.at(rand()%char_list_lowercase.length());
                    character_count_lowercase--;
                }
                break;
            case 2:
                if(digit_count > 0){
                    final_password += digit_list.at(rand()%digit_list.length());
                    digit_count--;
                }
                break;
            case 3:
                if(special_character_count > 0){
                    final_password += special_character_list.at(rand()%special_character_list.length());
                    special_character_count--;
                }
                break;
        }
    }

    return final_password;
    
}