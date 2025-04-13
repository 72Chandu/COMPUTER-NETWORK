/*
 Do the following task to estimate the optimum delay along with the frame size and physical distance
 between the station of the system—
 (a) Consider there they system only faces transmission delay and propagation delay( neglect the
 queuing delay, processing delay etc.).
 (b) Consider the system using optical fibre as a medium whose channel capacity is 100 Gbps.
 (c) Draw the graph in excel to find the optimum point where delay( in ms/µs) will be plotted
 along x-axis, frame size(in bits) and physical distance( in bits) are plotted along y-axis. We need
 to plot the two y-axis on the two other sides of the x-axis
 (d) Plot the various feasible points of frame size and physical distance
*/
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {
    // Constants
    const double channel_capacity = 1e11;  // 100 Gbps
    const double propagation_speed = 2e8;  // 2 * 10^8 m/s

    // User input
    int frame_start, frame_end, frame_step;
    int distance_start, distance_end, distance_step;

    cout << "Enter frame size range (start end step in bits): ";
    cin >> frame_start >> frame_end >> frame_step;

    cout << "Enter physical distance range (start end step in meters): ";
    cin >> distance_start >> distance_end >> distance_step;

    ofstream file("delay_data.csv");
    if (!file) {
        cerr << "Error opening output file.\n";
        return 1;
    }

    file << "FrameSize(bits),Distance(m),Delay(microseconds)\n";

    for (int frame_size = frame_start; frame_size <= frame_end; frame_size += frame_step) {
        for (int distance = distance_start; distance <= distance_end; distance += distance_step) {
            double transmission_delay = double(frame_size) / channel_capacity;       // seconds
            double propagation_delay = double(distance) / propagation_speed;         // seconds
            double total_delay_us = (transmission_delay + propagation_delay) * 1e6;  // microseconds

            file << frame_size << "," << distance << "," << fixed << setprecision(4) << total_delay_us << "\n";
        }
    }

    file.close();
    cout << "Data written to delay_data.csv successfully.\n";
    return 0;
}
/*
Enter frame size range (start end step in bits): 1000 100000 10000
Enter physical distance range (start end step in meters): 1000 100000 10000

*/
