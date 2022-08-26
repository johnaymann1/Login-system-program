#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <regex>
#include <iomanip>
#include <conio.h>
#include "CS112-2022-2nd-s15s16-20210101-20210107-20210122-A4-FULL.h"

using namespace std;
fstream txtfile;

void get_user() {
    smatch sm;
    string u_name;
    cout << "please enter your username\n";
    cin >> u_name;
    regex regular_exp("[A-z]+_?[A-z]"); // regex exp of username to accept only letters or (_)
    if (regex_match(u_name, sm, regular_exp)) {
        while (not_valid_user(u_name)) { // if username is registered before
            cout << "this username is already taken please enter another username\n";
            cin >> u_name;
            while (!regex_match(u_name, sm, regular_exp)) { // if user typed digits for example in the username
                cout << "sorry invalid username you can try again your username can contain capital/small letters and (_)\n but cannot include digits or other spetial characters.\n";
                cout << "re-enter a new username ya user ya habebe\n";
                cin >> u_name;
            }
        }
        txtfile.open("users.txt", ios::app);// adding the username to the textfile
        txtfile << endl << u_name;
        txtfile.close();
        cout << "valid username and your username is added :)\n";
    }
    else {
        cout << "sorry invalid username you can try again your username can contain capital/small letters and (_)\n but cannot include digits or other spetial characters.\n";
        get_user(); // recursion
    }
}
//_______________________________________________________________________________________
void get_mail() {
    smatch sm2;
    string mail;
    cout << "please enter a valid email adress\n";
    cin >> mail;
    regex regular_exp2(R"([A-z0-9\.]+@[A-z]+\.(com|net|org))");// regex of valid email
    if (regex_match(mail, sm2, regular_exp2)) {
        while (not_valid_user(mail)) { // if email is registered before
            cout << "this email is registered before\nplease enter a new email adress\n";
            cin >> mail;
            while (!regex_match(mail, sm2, regular_exp2)) {// if user enetred invalid email
                cout << "sorry invalid email adress you can try again\n";
                cout << "re-enter a new mail ya user ya habebe\n";
                cin >> mail;
            }
        }
        txtfile.open("users.txt", ios::app); // adding the email to the file
        txtfile << setw(25) << mail;
        txtfile.close();
        cout << "valid email adress :)\n";
    }
    else {
        cout << "sorry invalid email adress you can try again\n";
        get_mail(); // recursion
    }
}
//_______________________________________________________________________________________________
bool not_valid_user(string x) { // pre-existing user
    string users;
    txtfile.open("users.txt", ios::in);
    while (txtfile >> users) {
        if (users == x) {
            txtfile.close();
            return true;
        }
    }
    txtfile.close();
    return false;
}
//__________________________________________________________________________________________
void get_pass() {
    string pass, verify_pass;
    cout << "please enter the password\nyour pass must contain at least 1 (uppercase letters/Lowercase letters/number/special character)\n";
    pass = hide_pass(); // hide pass with stars function is called
    while (not_valid_pass(pass)) { // make sure with regex exp
        cout << "\ninvalid password\ncheck that you meet all required conditions\n";
        pass = hide_pass();// hide pass with stars function is called
    }
    cout << "\nre-enter pass to verify it\n";
    verify_pass = hide_pass(); // hide pass with stars function is called if user re-entered wrong pass
    while (!(pass == verify_pass)) {
        cout << "\nyou re-entered a wrong pass please re-enter the password\n";
        verify_pass = hide_pass();// hide pass with stars function is called
    }
    txtfile.open("users.txt", ios::app);
    txtfile << setw(20) << pass; // add the pass
    txtfile.close();
}
//____________________________________________________________________________________________
void get_phone() {
    string phone_no;
    smatch sm3;
    cout << "\nplease enter your mobile number so that you can recover your account if lost or stolen\n";
    cin >> phone_no;
    regex regular_exp3("[0][1](0|1|2|5)[0-9]{8}"); // exp of the phone number
    while (!regex_match(phone_no, sm3, regular_exp3)) {
        cout << "invalid mobile number plese enter your phone number in form 01xxxxxxxxx\n";
        cin >> phone_no;
    }
    txtfile.open("users.txt", ios::app);
    txtfile << setw(20) << phone_no; // adding the phone number to the text folder
    txtfile.close();
}
//___________________________________________________________________________________
bool not_valid_pass(string pass) {
    smatch sm4;
    regex regular_exp4("^(?=.*?[A-Z])(?=.*?[a-z])(?=.*?[0-9])(?=.*?[#?!@$ %^&*-]).{8,}$"); // checking the strong pass
    if (!regex_match(pass, sm4, regular_exp4))
        return true;
    return false;
}
//___________________________________________________________________________________________
string hide_pass() {
    char ch;
    string value;
    ch = _getch();// taking  input from the keyboard and put in ch
    while (ch != 13) {
        if (ch == 8) { // if the user entered a backspace
            cout << "\b\b";
            value.erase(value.length() - 1); // erase the last value from the pass
        }
        else {
            cout << "*"; //convert it into *****
            value += ch; //pushback the input to the pass
        }
        ch = _getch();
    }
    return value;
}
//________________________________________________________________________________________________
void login() {
    string username, pass, user, passcode, email, phone;
    int count = 0, login_chances = 0;
    char ch;
    while (login_chances < 3) {
        cout << "welcome enter your username: " << endl;
        cin >> username;
        cout << "enter your password: \n";
        ch = _getch();// taking  input from the keyboard and put in ch
        while (ch != 13) { //while th user not click enter which is 13 in  ascii
            if (ch == 8) { // if the user entered a backspace
                cout << "\b\b";
                pass.erase(pass.length() - 1);
            }
            else {
                pass.push_back(ch);//pushback the input to the pass
                cout << '*';//convert it into *****
            }
            ch = _getch();//taking another input and so on
        }
        txtfile.open("users.txt", ios::in);
        while (txtfile.peek() != EOF) {
            txtfile >> user;//taking the user name from the first line in the file and store it
            txtfile >> email;//taking the email  from the second line in the file and store it
            txtfile >> passcode;//taking the passcode from the third in the file and store it
            txtfile >> phone; // taking the phone number in the fourth variable
            if (username == user && pass == passcode)//checking if the user enter the correct user name and passcode
                count = 1;
        }
        txtfile.close();
        if (count == 1) { // checking if true to login
            cout << "\nwelcome " << username << " you are permitted to login\n";
            break;
        }
        else {
            cout << "\nlogin failed try again\n" << endl;
            login_chances++;// giving the user 3 chances

        }
        if (login_chances == 3) {
            cout << "\nyou are denied to access your account\n";// if the user enter three chances wrong thn he denied to access his account
        }
    }
}
//_______________________________________________________________________________________________-
void change_password() {
    string line, data, old_pass, new_pass, user_n;
    int n = 0;
    cout << "please enter you username\n";
    cin >> user_n;
    while (!not_valid_user(user_n)) {
        cout << "user was not found\nplease enter valid user\n";
        cin >> user_n;
    }
    cout << "enter your old password\n";//taking info from user
    old_pass = hide_pass();
    cout << "\nenter your new password\n";
    new_pass = hide_pass();
    while (not_valid_pass(new_pass)) {
        cout << "\nMake sure you meet all requirements of strong pass\nyour pass must contain at least 1 (uppercase letters/Lowercase letters/number/special character)\n";
        cout << "\nEnter your new pass\n";
        new_pass = hide_pass();
    }
    txtfile.open("users.txt", ios::in);
    while (txtfile.peek() != EOF)//taking every word in the file
    {
        txtfile >> line;//storing th info of the file in line variable

        if (line == old_pass) {//if the line == old password
            data += new_pass;//we will add the new pass to temp variable called data
            cout << "\nyour password changed successfully\n";
        }
        else {
            data += line; // we add the info of the file to the temp variable data
        }
        if (n == 3) {
            data += "\n";
            n = 0;
        }
        else {
            data += "           ";
            n += 1;
        }
    }
    txtfile.close();
    txtfile.open("users.txt", ios::out);// open the file in the writing mode
    txtfile << data; //write the data variable in the file
    txtfile.close();//close it
}