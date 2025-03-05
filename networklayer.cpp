/*
 (a) Let us consider that we need to develop a routing technique in IPv4 standard. As a part of
 that Source and Destination IP addresses are to be identified from the received IP datagram. We
 need to develop such kind of system where user input will provide dotted decimal value of IP
 address in classful addressing scheme.
 (b) It would be able to identify the class of the IP address along with the network ID of the given
 IP address.
 (c) It would also generate all the IP addresses of the network. Identify the first and last IP
 addresses of the network.
 (c) Example: Input: 124.25.12.100 Output: Class: A, etc.
 (d) You have to convert the dotted decimal into 32 bits IP address before checking the Class of
 the IP address.
 (e) Also consider that if the user mentions the possible number of hosts required in the network,
 whether this IP class is suitable or not. Let say, required number of host(n)=45 ( Justify your
 answer
*/

#include<bits/stdc++.h>
using namespace std;

// Function to convert dotted decimal to binary
string decimalToBinary(string ip) {
    stringstream ss(ip);
    string octet;
    string binaryIP = "";
    while (getline(ss, octet, '.')) {
        binaryIP += bitset<8>(stoi(octet)).to_string();
    }
    return binaryIP;
}

// Function to determine class and network ID
void identifyClassAndNetwork(string ip, int requiredHosts) {
    vector<int> octets;
    stringstream ss(ip);
    string octet;
    while (getline(ss, octet, '.')) {
        octets.push_back(stoi(octet));
    }
    
    char ipClass;
    int subnetMask;
    string networkID;
    int maxHosts;

    if (octets[0] >= 1 && octets[0] <= 126) {
        ipClass = 'A';
        subnetMask = 8;
        networkID = to_string(octets[0]) + ".0.0.0";
        maxHosts = pow(2, 24) - 2;
    } else if (octets[0] >= 128 && octets[0] <= 191) {
        ipClass = 'B';
        subnetMask = 16;
        networkID = to_string(octets[0]) + "." + to_string(octets[1]) + ".0.0";
        maxHosts = pow(2, 16) - 2;
    } else if (octets[0] >= 192 && octets[0] <= 223) {
        ipClass = 'C';
        subnetMask = 24;
        networkID = to_string(octets[0]) + "." + to_string(octets[1]) + "." + to_string(octets[2]) + ".0";
        maxHosts = pow(2, 8) - 2;
    } else {
        cout << "Invalid or Reserved IP Address" << endl;
        return;
    }

    cout << "Class: " << ipClass << endl;
    cout << "Network ID: " << networkID << endl;
    cout << "Subnet Mask: " << subnetMask << " bits" << endl;
    cout << "Total Hosts Possible: " << maxHosts << endl;
    
    string firstIP = networkID.substr(0, networkID.size() - 1) + "1";
    string lastIP = networkID.substr(0, networkID.size() - 1) + to_string(pow(2, 32 - subnetMask) - 2);
    
    cout << "First IP Address: " << firstIP << endl;
    cout << "Last IP Address: " << lastIP << endl;
    
    if (requiredHosts <= maxHosts) {
        cout << "The given IP class is suitable for " << requiredHosts << " hosts." << endl;
    } else {
        cout << "The given IP class is NOT suitable for " << requiredHosts << " hosts." << endl;
    }
}

int main() {
    string ip;
    int requiredHosts;
    cout << "Enter IP Address (dotted decimal): ";
    cin >> ip;
    cout << "Enter required number of hosts: ";
    cin >> requiredHosts;
    
    string binaryIP = decimalToBinary(ip);
    cout << "Binary Representation: " << binaryIP << endl;
    
    identifyClassAndNetwork(ip, requiredHosts);
    
    return 0;
}

/*
Enter IP Address (dotted decimal): 124.25.12.100
Enter required number of hosts: 45

Binary Representation: 01111100.00011001.00001100.01100100
Class Determination: First octet 124 falls under Class A (1-126).
Network ID: 124.0.0.0
Subnet Mask: 8 bits (Class A default)
Total Hosts Possible: 2^24 - 2 = 16,777,214
First IP: 124.0.0.1
Last IP: 124.255.255.254
Suitability Check: Since 45 < 16,777,214, Class A is suitable.

----------------------------------------------------------------
stringstream ss(ip);

Creates a stringstream object ss initialized with the input string ip (e.g., "192.168.1.1").
This helps in splitting the IP address using "." as a delimiter.
string octet;

Declares a string variable octet to store each extracted octet (e.g., "192", "168", "1", "1").
string binaryIP = "";

Initializes an empty string binaryIP to store the final binary representation.
while (getline(ss, octet, '.'))

Reads each octet (separated by ".") from the stringstream and stores it in octet.
Example: For "192.168.1.1", the loop iterates 4 times:
1st iteration: octet = "192"
2nd iteration: octet = "168"
3rd iteration: octet = "1"
4th iteration: octet = "1"
stoi(octet)

Converts the extracted octet string into an integer.
Example: "192" → 192
bitset<8>(stoi(octet)).to_string();

Converts the integer into an 8-bit binary representation.
Example Conversions:
192 → "11000000"
168 → "10101000"
1 → "00000001"
1 → "00000001"
binaryIP += bitset<8>(stoi(octet)).to_string();

Appends the 8-bit binary string to binaryIP.
return binaryIP;

Returns the complete binary string representation of the IP.
*/
