#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

const int theta_max = 360;
const int half_theta_max = theta_max / 2;

// Function to convert degrees to radians
double degreesToRadians(double degrees) { return degrees * M_PI / half_theta_max; }

int main() {
    // Print the header for the table
    cout << "const double Polar_trig::polar_cos[" << theta_max << "] = {" << endl;

    // Loop through angles from 0 to 359 degrees
    for (int degrees = 0; degrees < theta_max; ++degrees) {
        // Convert the degree value to radians
        double radians = degreesToRadians(degrees);

        // Calculate the cosine of the angle
        double cosineValue = cos(radians);

        // Print the degree and its corresponding cosine value, formatted for readability
        cout << "    " << setw(7) << fixed << setprecision(6) << cosineValue << (degrees < theta_max - 1 ? ", " : "  ")
             << "// " << degrees << endl;
    }

    cout << "};" << endl;
    cout << endl;

    cout << "const double Polar_trig::polar_sin[" << theta_max << "] = {" << endl;

    // Loop through angles from 0 to 359 degrees
    for (int degrees = 0; degrees < theta_max; ++degrees) {
        // Convert the degree value to radians
        double radians = degreesToRadians(degrees);

        // Calculate the sine of the angle
        double sineValue = sin(radians);

        // Print the degree and its corresponding sine value, formatted for readability
        cout << "    " << setw(7) << fixed << setprecision(6) << sineValue << (degrees < theta_max - 1 ? ", " : "  ")
             << "// " << degrees << endl;
    }

    cout << "};" << endl;
    cout << endl;
    return 0;
}
