/*
 (a) Let us consider that we need to organize a network privately in IPv4 standard (Classless
 addressing mode). We need to develop such a kind of network where the user will provide the
 number of hosts to be accommodated.
 (b) Generate the mask of the given IP address along with the network ID.
 (c) It would also generate all the IP addresses of the network. Identify the first and last IP
 addresses of the network.
 (d) Consider there are m number of subnets ( Consider as user input ) in the network each of
 them can have some certain number of hosts( Consider as user input ) in the subnet. Generate
 the Mask of each subnet and also print the IP addresses in that subnet.
 (e) Consider that simultaneously atmost two hosts in a subnet can connect to any specific public
 host and NAT does not store the port number of the hosts. Also, consider that ISP provides
 atleast 8 Public IPs to any organization on application. Randomly assign Public IP addresses for
 the network of the organization. List the public IP addresses.
 (f) Print the IP addresses in dotted decimal notation as follows: xxx.yyy.tt.pp/n .
*/

#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to convert integer IP to dotted decimal notation
string intToDotted(int ip) {
    return to_string((ip >> 24) & 255) + "." +
           to_string((ip >> 16) & 255) + "." +
           to_string((ip >> 8) & 255) + "." +
           to_string(ip & 255);
}

// Function to calculate subnet mask based on host count
int calculateSubnetMask(int hosts) {
    int bits_needed = ceil(log2(hosts + 2)); // +2 for network & broadcast
    return 32 - bits_needed;
}

// Function to generate all IPs in a subnet
vector<int> generateIPs(int networkID, int mask) {
    int host_bits = 32 - mask;
    int total_hosts = pow(2, host_bits);
    vector<int> ips;
    
    for (int i = 0; i < total_hosts; i++) {
        ips.push_back(networkID + i);
    }
    return ips;
}

int main() {
    srand(time(0)); // Seed for random number generation

    // (a) User input: Number of hosts
    int totalHosts;
    cout << "Enter the number of hosts needed: ";
    cin >> totalHosts;

    // (b) Calculate subnet mask and network ID
    int subnetMask = calculateSubnetMask(totalHosts);
    int networkID = (192 << 24) | (168 << 16) | (1 << 8) | 0; // Example: 192.168.1.0

    cout << "\nNetwork ID: " << intToDotted(networkID) << "/" << subnetMask << endl;

    // (c) Generate all IPs in the network
    vector<int> allIPs = generateIPs(networkID, subnetMask);
    cout << "First IP: " << intToDotted(allIPs[1]) << endl;  // First usable IP
    cout << "Last IP: " << intToDotted(allIPs[allIPs.size() - 2]) << endl;  // Last usable IP

    // (d) Subnet division
    int m;
    cout << "\nEnter number of subnets: ";
    cin >> m;
    vector<int> subnetSizes(m);
    vector<int> subnetMasks(m);
    
    int startNetworkID = networkID;
    for (int i = 0; i < m; i++) {
        cout << "Enter the number of hosts for subnet " << i + 1 << ": ";
        cin >> subnetSizes[i];
        subnetMasks[i] = calculateSubnetMask(subnetSizes[i]);
    }

    cout << "\nSubnet Details:\n";
    for (int i = 0; i < m; i++) {
        cout << "Subnet " << i + 1 << ": " << intToDotted(startNetworkID) << "/" << subnetMasks[i] << endl;
        vector<int> subnetIPs = generateIPs(startNetworkID, subnetMasks[i]);
        cout << "  First IP: " << intToDotted(subnetIPs[1]) << ", Last IP: " << intToDotted(subnetIPs[subnetIPs.size() - 2]) << endl;
        startNetworkID += pow(2, (32 - subnetMasks[i])); // Move to next subnet
    }

    // (e) NAT with Public IPs (At least 8 Public IPs)
    vector<string> publicIPs;
    cout << "\nRandomly Assigned Public IPs:\n";
    for (int i = 0; i < 8; i++) {
        int randIP = (100 + rand() % 155) << 24 | (1 + rand() % 255) << 16 | (1 + rand() % 255) << 8 | (1 + rand() % 255);
        publicIPs.push_back(intToDotted(randIP));
        cout << "  " << publicIPs[i] << endl;
    }

    return 0;
}
/*
Enter the number of hosts needed: 50

Network ID: 192.168.1.0/26
First IP: 192.168.1.1
Last IP: 192.168.1.62

Enter number of subnets: 2
Enter the number of hosts for subnet 1: 25
Enter the number of hosts for subnet 2: 20

Subnet Details:
Subnet 1: 192.168.1.0/27
  First IP: 192.168.1.1, Last IP: 192.168.1.30
Subnet 2: 192.168.1.32/27
  First IP: 192.168.1.33, Last IP: 192.168.1.62

Randomly Assigned Public IPs:
  128.45.67.89
  112.34.123.201
  178.56.78.45
  203.22.45.67
  121.199.200.100
  140.167.178.34
  156.132.176.98
  192.56.43.29

*/
