#include <bits/stdc++.h>
using namespace std;

string blood_groups[] = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};

void display_intro() {
    cout << "\t\t\t\t\t  When hope is low and time is tight,\n";
    cout << "\t\t\t\t\tYour blood can bring the gift of light.\n";
    cout << "\t\t\t\t\t   So take a moment, lend your vein,\n";
    cout << "\t\t\t\t\t    A life restored is endless gain.\n\n";
    cout << "\t\t  So what are you waiting for? Just share your blood and be the reason someone smiles.\n";
}

void show_blood_groups() {
    for (int i = 0; i < 8; i++) {
        cout << i + 1 << ". " << blood_groups[i] << endl;
    }
}

void donor_section() {
    ofstream DonorList("Donor.txt", ios::app);
    string name, gender, address, lastDonate, phone;
    int age, group_choice, weight;

    cout << "\nName: ";
    getline(cin, name);

    cout << "Gender (Male/Female/Other): ";
    getline(cin, gender);

    cout << "Age: ";
    cin >> age;
    cin.ignore();

    cout << "Please select your blood group:\n";
    show_blood_groups();
    cin >> group_choice;
    cin.ignore();

    string blood_group = (group_choice >= 1 && group_choice <= 8) ? blood_groups[group_choice - 1] : "Unknown";

    cout << "Weight (in Kg): ";
    cin >> weight;
    cin.ignore();

    if (weight < 55) {
        cout << "Sorry! You're underweight to donate blood. Minimum weight: 56kg.\n";
        return;
    }

    cout << "Phone Number: ";
    getline(cin, phone); 

    cout << "Present Address: ";
    getline(cin, address);

    cout << "When did you last donate blood? (e.g. March 2024): ";
    getline(cin, lastDonate);

    DonorList << "-----------------------------------\n";
    DonorList << "Name: " << name << "\n";
    DonorList << "Gender: " << gender << "\n";
    DonorList << "Age: " << age << "\n";
    DonorList << "Blood Group: " << blood_group << "\n";
    DonorList << "Weight: " << weight << " kg\n";
    DonorList << "Phone Number: " << phone << "\n";
    DonorList << "Address: " << address << "\n";
    DonorList << "Last Donated: " << lastDonate << "\n";
    DonorList << "-----------------------------------\n";
    DonorList.close();

    cout << "\nThank you for being a donor. You're a real-life hero!\n";
}

void receiver_section() {
    ifstream DonorFile("Donor.txt");
    if (!DonorFile.is_open()) {
        cerr << "Error: Unable to show donor list.\n";
        return;
    }

    cout << "\nSo you are a blood receiver.\nWhich blood group do you need?\n";
    show_blood_groups();

    int group_choice;
    cin >> group_choice;
    cin.ignore();

    if (group_choice < 1 || group_choice > 8) {
        cout << "No donors found. Invalid blood group selected.\n";
        return;
    }

    string needed_blood = blood_groups[group_choice - 1];

    int bags;
    cout << "How many bags of blood do you need?\n";
    cin >> bags;
    cin.ignore();

    string location;
    cout << "Please enter your location:\n";
    getline(cin, location);

    cout << "\nSearching for donors with blood group: " << needed_blood << "\n\n";

    string line, block;
    bool found = false, match = false;

    while (getline(DonorFile, line)) {
        block += line + "\n";
        if (line.find("Blood Group: " + needed_blood) != string::npos)
            found = true;

        if (line.find("-----------------------------------") != string::npos) {
            if (found) {
                cout << block << endl;
                match = true;
            }
            block.clear();
            found = false;
        }
    }

    DonorFile.close();
    if (!match) {
        cout << "Sorry, no donors found with blood group " << needed_blood << ".\n";
    }
}

int main() {
    display_intro();

    cout << "\nAre you:\n1. Blood Donor\n2. Blood Receiver\n";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 1) donor_section();
    else if (choice == 2) receiver_section();
    else cout << "Invalid input.\n";

    return 0;
}
