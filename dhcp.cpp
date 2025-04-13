#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

// Function to generate a random MAC address
string generateMAC() {
    stringstream mac;
    for (int i = 0; i < 6; ++i) {
        int byte = rand() % 256;
        mac << hex << setw(2) << setfill('0') << byte;
        if (i != 5)
            mac << ":";
    }
    return mac.str();
}

// Function to generate IP address as a string (using simple IPv4 logic)
string generateIP(int base, int offset, int subnet = 24) {
    int a = (base + offset) / (256 * 256);
    int b = ((base + offset) / 256) % 256;
    int c = (base + offset) % 256;
    return to_string(192 + a) + "." + to_string(168 + b) + "." + to_string(1 + c / 256) + "." + to_string(c % 256) + "/" + to_string(subnet);
}

int main() {
    srand(time(0));
    int totalHosts, initiallyAllocated;

    cout << "Enter total number of hosts: ";
    cin >> totalHosts;
    cout << "Enter number of initially allocated hosts: ";
    cin >> initiallyAllocated;

    unordered_map<string, string> macToIP; // Mapping MAC -> IP
    unordered_set<string> usedIPs;
    vector<string> ipPool;

    // Generate the pool of IP addresses
    for (int i = 0; i < totalHosts; ++i) {
        string ip = generateIP(0, i); // Simple way to get unique IPs
        ipPool.push_back(ip);
    }

    // Assign initially allocated hosts
    for (int i = 0; i < initiallyAllocated; ++i) {
        string mac = generateMAC();
        string ip = ipPool[i];
        macToIP[mac] = ip;
        usedIPs.insert(ip);
    }

    int remainingHosts = totalHosts - initiallyAllocated;

    // Assign IPs to remaining hosts
    for (int i = 0; i < remainingHosts; ++i) {
        string mac = generateMAC();

        // Ensure unique MAC address
        while (macToIP.find(mac) != macToIP.end()) {
            mac = generateMAC();
        }

        // Assign a random IP from the pool that is not used
        string ip;
        for (const string& candidate : ipPool) {
            if (usedIPs.find(candidate) == usedIPs.end()) {
                ip = candidate;
                break;
            }
        }

        if (!ip.empty()) {
            macToIP[mac] = ip;
            usedIPs.insert(ip);
        } else {
            cout << "No available IPs to assign.\n";
            break;
        }
    }

    // Print the final DHCP table
    cout << "\nDHCP Allocation Table:\n";
    for (const auto& entry : macToIP) {
        cout << entry.first << " | " << entry.second << endl;
    }

    return 0;
}
/*
Enter total number of hosts: 5
Enter number of initially allocated hosts: 2

DHCP Allocation Table:
6c:5e:aa:9e:bd:53 | 192.168.1.0/24
c1:11:e2:cb:f1:36 | 192.168.1.1/24
12:a9:4e:9b:34:6d | 192.168.1.2/24
a4:90:9b:65:0b:07 | 192.168.1.3/24
4c:4e:7c:ed:7b:e0 | 192.168.1.4/24
*/
