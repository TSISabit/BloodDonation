#include <bits/stdc++.h>
using namespace std;

string blood_groups[] = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};

string normalize(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
    return str;
}

string get_field(const string& block, const string& field) {
    size_t pos = block.find(field + ": ");
    if (pos == string::npos) return "";
    size_t end = block.find('\n', pos);
    return block.substr(pos + field.length() + 2, end - pos - field.length() - 2);
}

void display_intro() {
    cout << "\t\t\t\t\t  When hope is low and time is tight,\n";
    cout << "\t\t\t\t\tYour blood can bring the gift of light.\n";
    cout << "\t\t\t\t\t   So take a moment, lend your vein,\n";
    cout << "\t\t\t\t\t   A life restored is endless gain.\n\n";
    cout << "\t\t  So what are you waiting for? Just share your blood and be the reason someone smiles.\n";
}

void show_blood_groups() {
    for (int i = 0; i < 8; i++) {
        cout << i + 1 << ". " << blood_groups[i] << endl;
    }
}

void register_donor() {
    ofstream DonorList("Donor.txt", ios::app);
    string name, gender, address, phone, password, lastDonate;
    string street, thana, district, division;
    int age, group_choice, weight;

    cout << "\n--- Registration ---\n";
    cout << "Name: ";
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

    while (true) {
        cout << "Set a 6-character password: ";
        getline(cin, password);
        if (password.length() == 6) break;
        cout << "Password must be exactly 6 characters long. Try again.\n";
    }

    cout << "Street/Lane: ";
    getline(cin, street);
    cout << "Thana: ";
    getline(cin, thana);
    cout << "District: ";
    getline(cin, district);
    cout << "Division: ";
    getline(cin, division);

    cout << "When did you last donate blood? (e.g. March 2024): ";
    getline(cin, lastDonate);

    DonorList << "-----------------------------------\n";
    DonorList << "Name: " << name << "\n";
    DonorList << "Gender: " << gender << "\n";
    DonorList << "Age: " << age << "\n";
    DonorList << "Blood Group: " << blood_group << "\n";
    DonorList << "Weight: " << weight << " kg\n";
    DonorList << "Phone Number: " << phone << "\n";
    DonorList << "Password: " << password << "\n";
    DonorList << "Street: " << street << "\n";
    DonorList << "Thana: " << thana << "\n";
    DonorList << "District: " << district << "\n";
    DonorList << "Division: " << division << "\n";
    DonorList << "Last Donated: " << lastDonate << "\n";
    DonorList << "-----------------------------------\n";
    DonorList.close();

    cout << "\nThank you for registering. You're a real-life hero!\n";
}

void login_update_donation() {
    string name, password;
    cout << "\n--- Donor Login ---\n";
    cout << "Enter your name: ";
    getline(cin, name);
    cout << "Enter your 6-character password: ";
    getline(cin, password);

    ifstream in("Donor.txt");
    ofstream temp("Temp.txt");
    string line, block;
    bool found = false;

    while (getline(in, line)) {
        block += line + "\n";
        if (line.find("-----------------------------------") != string::npos) {
            string dname = get_field(block, "Name");
            string dpass = get_field(block, "Password");
            if (dname == name && dpass == password) {
                found = true;
                string newDate;
                cout << "Enter updated last donation date: ";
                getline(cin, newDate);
                size_t pos = block.find("Last Donated: ");
                if (pos != string::npos) {
                    size_t end = block.find('\n', pos);
                    block.replace(pos, end - pos, "Last Donated: " + newDate);
                }
            }
            temp << block;
            block.clear();
        }
    }
    in.close();
    temp.close();

    remove("Donor.txt");
    rename("Temp.txt", "Donor.txt");

    if (found) cout << "Last donation date updated successfully.\n";
    else cout << "Login failed.\n";
}

void donor_section() {
    cout << "\n1. Register as a donor\n2. Login to update last donation date\n";
    int choice;
    cin >> choice;
    cin.ignore();
    if (choice == 1) register_donor();
    else if (choice == 2) login_update_donation();
    else cout << "Invalid choice.\n";
}

void receiver_section() {
    ifstream DonorFile("Donor.txt");
    ofstream History("SearchHistory.txt", ios::app);
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

    string thana, district, division, hospital;
    cout << "Enter your Thana: "; getline(cin, thana);
    cout << "Enter your District: "; getline(cin, district);
    cout << "Enter your Division: "; getline(cin, division);
    cout << "Enter hospital name: "; getline(cin, hospital);

    History << "Receiver Blood Group: " << needed_blood << "\nThana: " << thana
            << "\nDistrict: " << district << "\nDivision: " << division
            << "\nHospital: " << hospital << "\n---\n";
    History.close();

    cout << "\nSearching for donors in district: " << district << " with blood group: " << needed_blood << "\n\n";

    string line, block;
    bool found = false;
    while (getline(DonorFile, line)) {
        block += line + "\n";
        if (line.find("-----------------------------------") != string::npos) {
            string donor_district = get_field(block, "District");
            string donor_blood = get_field(block, "Blood Group");
            if (normalize(donor_district) == normalize(district) && donor_blood == needed_blood) {
                size_t pass_pos = block.find("Password: ");
                if (pass_pos != string::npos) {
                    size_t pass_end = block.find('\n', pass_pos);
                    block.erase(pass_pos, pass_end - pass_pos + 1);
                }
                cout << block << endl;
                found = true;
            }
            block.clear();
        }
    }
    DonorFile.close();

    if (!found) cout << "Sorry, no matching donors found.\n";
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
