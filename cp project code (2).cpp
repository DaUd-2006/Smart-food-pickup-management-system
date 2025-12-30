#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// Store latitude and longitude
struct Location {
    double latitude;
    double longitude;
};

// Customer information
class Customer {
private:
    string name;
    Location location;

public:
    Customer(string n, double lat, double lon) {
        name = n;
        location.latitude = lat;
        location.longitude = lon;
    }

    void updateLocation(double lat, double lon) {
        location.latitude = lat;
        location.longitude = lon;
    }

    Location* getLocation() {
        return &location;
    }

    string getName() {
        return name;
    }
};

// Food order information
class FoodOrder {
private:
    bool ready;

public:
    FoodOrder() {
        ready = true;
    }

    void pause() {
        ready = false;
    }

    void resume() {
        ready = true;
    }

    string status() {
        return ready ? "READY" : "PAUSED";
    }
};

// Calculate distance in kilometers (simulated)
double getDistance(Location* customer, Location* shop) {
    return sqrt(pow(customer->latitude - shop->latitude, 2) +
                pow(customer->longitude - shop->longitude, 2));
}

int main() {

    // 🔧 Customer and safe pickup distance
    Location shopLocation = {10.0, 10.0};
    double safePickupDistance = 6.0;   // 6 km
    Customer customer("Danial", 12.0, 12.0);

    FoodOrder order;

    // Path of 8 situations
    double path[8][2] = {
        {11.0, 11.0},  // Situation 1
        {13.0, 13.0},  // Situation 2
        {16.0, 16.0},  // Situation 3
        {14.0, 14.0},  // Situation 4
        {10.5, 10.5},  // Situation 5
        {9.0, 9.0},    // Situation 6
        {10.0, 16.0},  // Situation 7
        {10.0, 10.0}   // Situation 8 (at the restaurant)
    };

    cout << "\n=============================================\n";
    cout << "     SMART FOOD PICKUP TRACKING SYSTEM\n";
    cout << "=============================================\n";
    cout << "Customer Name        : " << customer.getName() << endl;
    cout << "Safe Pickup Distance : " << safePickupDistance << " km\n";

    for (int i = 0; i < 8; i++) {

        customer.updateLocation(path[i][0], path[i][1]);
        double distance = getDistance(customer.getLocation(), &shopLocation);

        cout << "\n---------------------------------------------\n";
        cout << "Situation " << i + 1 << endl;
        cout << "---------------------------------------------\n";

        cout << "Customer is currently "
             << distance << " km away from the restaurant.\n";

        // Check geofence
        if (distance < safePickupDistance) {
            order.resume();
            cout << "Customer is INSIDE the geofence.\n";
            cout << "Food status: Food is READY for pickup.\n";
        } 
        else if (distance == safePickupDistance) {
            order.resume();
            cout << "Customer has REACHED the edge of the geofence!\n";
            cout << "Food status: Food is READY for pickup.\n";
        }
        else {
            order.pause();
            cout << "Customer is FAR from the restaurant.\n";
            cout << "Food status: Food preparation is PAUSED to avoid waste.\n";
        }

        cout << "Current system state: " << order.status() << endl;
    }

    cout << "\n=============================================\n";
    cout << "Tracking finished. Thank you!\n";
    cout << "=============================================\n";

    return 0;
}
