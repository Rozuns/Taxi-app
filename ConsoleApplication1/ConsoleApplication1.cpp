#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include <cstdlib> 
using namespace std;

class Taxi {
private:
     string brand;
     string model;
    int year;
    int capacity;
    double fuel_consumption;
    double load; 


public:
    Taxi( string brand,  string model, int year, int capacity, double load, double fuel_consumption)
        : brand(brand), model(model), year(year), capacity(capacity),load(load), fuel_consumption(fuel_consumption) {}

    // Getters and setters
     string getBrand() const { return brand; }
    void setBrand( string newBrand) { brand = newBrand; }

     string getModel() const { return model; }
    void setModel( string newModel) { model = newModel; }

    int getYear() const { return year; }
    void setYear(int newYear) { year = newYear; }

    int getCapacity() const { return capacity; }
    void setCapacity(int newCapacity) { capacity = newCapacity; }

    double getLoad() const { return load; }
    void setLoad(double newLoad) { load = newLoad; }

    double getFuelConsumption() const { return fuel_consumption; }
    void setFuelConsumption(double newFuelConsumption) { fuel_consumption = newFuelConsumption; }

    friend  ostream& operator<<( ostream& os, const Taxi& taxi);
};

class Route {
private:
     vector< string> waypoints;
    double distance;
    int dailyFrequency;

public:
    Route( vector< string> waypoints, double distance, int dailyFrequency)
        : waypoints(waypoints), distance(distance), dailyFrequency(dailyFrequency) {}

    // Getters and setters
    const  vector< string>& getWaypoints() const { return waypoints; }
    void setWaypoints(const  vector< string>& newWaypoints) { waypoints = newWaypoints; }

    double getDistance() const { return distance; }
    void setDistance(double newDistance) { distance = newDistance; }

    int getDailyFrequency() const { return dailyFrequency; }
    void setDailyFrequency(int newDailyFrequency) { dailyFrequency = newDailyFrequency; }

    friend  ostream& operator<<( ostream& os, const Route& route);
};

class TaxiApp {
private:
     vector<Taxi> taxis;
     vector<Route> routes;

public:
    void addTaxi(const Taxi& taxi) { taxis.push_back(taxi); }
    void addRoute(const Route& route) { routes.push_back(route); }

    void displayTaxis() const;
    void displayRoutes() const;
    void calculateFuelNeeded() const;

    void saveDataToFile(const  string& filename) const;
    void readDataFromFile(const  string& filename);
};

 ostream& operator<<( ostream& os, const Taxi& taxi) {
     os << "Brand: " << taxi.brand << ", Model: " << taxi.model << ", Year: " << taxi.year
         << ", Capacity: " << taxi.capacity << ", Maximum load: "<<taxi.load<<", Fuel Consumption : " << taxi.fuel_consumption << endl;
    return os;
}

 ostream& operator<<(ostream& os, const Route& route) {
     os << "Waypoints: ";
     const vector<string>& waypoints = route.getWaypoints();
     for (size_t i = 0; i < waypoints.size(); ++i) {
         os << waypoints[i];
         if (i < waypoints.size() - 1) {
             os << ", ";
         }
     }
     os << "\nDistance: " << route.getDistance() << " km\n";
     os << "Daily Frequency: " << route.getDailyFrequency() << "\n";

     return os;
 }


 void inputTaxiData(string& brand, string& model, int& year, int& capacity,double&load, double& fuelConsumption) {
     cout << "Enter brand: ";
     cin >> brand;
     cout << "Enter model: ";
     cin >> model;
     cout << "Enter year: ";
     // Validate and get input for year (integer within a specific range)
     while (!(cin >> year) || year < 1950 || year > 2025) {
         cout << "Invalid input. Please enter a valid year" << endl;
         cin.clear(); // Clear the error flag
         cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
         cout << "Enter year (between 1950 and 2024): ";
     }

     cout << "Enter capacity: ";
     // Validate and get input for capacity (integer within a specific range)
     while (!(cin >> capacity) || capacity > 10 || capacity < 2) {
         cout << "Invalid input. Please enter a valid capacity amount" << endl;
         cin.clear(); // Clear the error flag
         cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Disgcard invalid input
         cout << "Enter capacity (between 2 and 10): ";
     }
     //cout << "enter MAX load: ";
    // cin >> load;
     //cout << Taxiget.load();
     cin.ignore();
     cout << "Enter MAX load: ";
     while (true) {
         string input;
         getline(cin, input);

         istringstream iss(input);
         if (iss >> load && iss.eof()) {
             cout << "1";
             // Successfully parsed as a double
             break;
             
         }
         else {
             cout << "Invalid input." << endl;
             cout << "Enter MAX load: ";
             cout << "2";
             cin.clear(); // Clear the error flag
         }
     }
     cout << "3";
     //cin.ignore();

     cout << "Enter fuel consumption: ";
     while (true) {
          string input;
          getline( cin, input);

          istringstream iss(input);
         if (iss >> fuelConsumption && iss.eof()) {
             // Successfully parsed as a double
             break;
         }
         else {
              cout << "Invalid input." <<  endl;
              cout << "Enter fuel consumption (integer or double): ";
              cin.clear(); // Clear the error flag
         }
     }
 }

 void inputRouteData( vector< string>& waypoints, double& distance, int& dailyFrequency) {
      cout << "Enter waypoints (space-separated): ";
      while (true) {
          string waypointInput;
          getline(cin, waypointInput);

          istringstream iss(waypointInput);
          string waypoint;

          while (iss >> waypoint) {
              waypoints.push_back(waypoint);
          }

          if (waypoints.size() >= 2) {
              // At least two waypoints entered, break out of the loop
              break;
          }
          else {
              cout << "Invalid input. Please enter at least two waypoints." << endl;
              cout << "Enter waypoints (at least 2, space-separated): ";
              waypoints.clear(); // Clear the vector for retry
          }
      }
      
      cout << "Enter distance (in km): ";
      while (true) {
          string input;
          getline(cin, input);

          istringstream iss(input);
          if (iss >> distance && iss.eof() && distance >= 0.01 && distance <= 100) {
              // Successfully parsed as a double
              break;
          }
          else {
              cout << "Invalid input." << endl;
              cout << "Enter distance (in km between 0.01 and 100): ";
              cin.clear(); // Clear the error flag
          }
      }

      cout << "Enter daily frequency: ";
      while (true) {
           string input;
           getline( cin, input);

           istringstream iss(input);
          if (iss >> dailyFrequency && iss.eof() && dailyFrequency >= 1 && dailyFrequency <= 100) {
              // Successfully parsed as an integer and within the desired range
              break;
          }
          else {
               cout << "Invalid input." <<  endl;
               cout << "Enter daily frequency (between 1 and 100): ";
               cin.clear(); // Clear the error flag
          }
      }
 }

void TaxiApp::displayTaxis() const {
   // system("cls");
    for (const auto& taxi : taxis) {
         cout << taxi <<  endl;
    }
    cout << "1\n";
}

void TaxiApp::displayRoutes() const {
    system("cls");
    for (const auto& route : routes) {
         cout << route <<  endl;
    }
    system("pause");
}

void TaxiApp::calculateFuelNeeded() const {
    system("cls");
    int taxiIndex, routeIndex,Tsize,Rsize;
    Tsize = taxis.size();
    Rsize = routes.size();
    cout << "Amount of available Taxis: " << Tsize <<"\n" << endl;
    for (int i = 0; i < Tsize; ++i) {
        cout << i + 1 << ". " << taxis[i] << endl;
    }

    cout << "Amount of available Routes:" <<Rsize <<"\n" << endl;
    for (int i = 0; i < Rsize; ++i) {
        cout << i + 1 << ". " << routes[i] << endl;
    }
     cout << "Enter the index of the taxi: ";
     cin >> taxiIndex;
     cin.ignore();
     taxiIndex--;
     cout << "Enter the index of the route: ";
     cin >> routeIndex;
     cin.ignore();
     routeIndex--;
     

    if (taxiIndex >= 0 && taxiIndex < taxis.size() && routeIndex >= 0 && routeIndex < routes.size()) {
        const Taxi& selectedTaxi = taxis[taxiIndex];
        const Route& selectedRoute = routes[routeIndex];

        double fuelNeeded = selectedRoute.getDistance() * selectedTaxi.getFuelConsumption();
         cout << "Fuel needed for the daily route: " << fuelNeeded << " liters" <<  endl;
    }
    else {
         cout << "Invalid taxi or route index." <<  endl;
         cout << "Please choose from the available ("<<Tsize<<") taxis and ("<<Rsize<<") routes" << endl;
    }
    system("pause");
}

void TaxiApp::saveDataToFile(const  string& filename) const {
     ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& taxi : taxis) {
            outFile <<"Car;"<< taxi.getBrand() << "," << taxi.getModel() << "," << taxi.getYear() << ","
                << taxi.getCapacity() << "," <<taxi.getLoad()<<","<< taxi.getFuelConsumption() << "\n";
        }

        for (const auto& route : routes) {
            const  vector< string>& waypoints = route.getWaypoints();
            outFile << "Route;";
            for (const auto& waypoint : waypoints) {
                outFile << waypoint << " ";
            }
            double distance = route.getDistance();
            if (distance == static_cast<int>(distance)) {
                // Check if the distance has no fractional part
                outFile << "," << static_cast<int>(distance) << ".0"<<","
                    << route.getDailyFrequency() << "\n";
            }
            else {
                outFile << "," << distance << "," << route.getDailyFrequency() << "\n";
            }
        }
        
        outFile.close();
    }
    else {
         cerr << "Unable to open file: " << filename <<  endl;
    }
}

void TaxiApp::readDataFromFile(const string& filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        taxis.clear();
        routes.clear();

        string line;
        while (getline(inFile, line)) {
            // Split the line into tokens
            istringstream iss(line);
            string token;

            // Read the type of entry (Car or Route)
            string entryType;
            getline(iss, entryType, ';');

            if (entryType == "Car") {
                string brand, model;
                int year, capacity;
                double fuelConsumption, load;
                

                // Read Car entry data
                getline(iss, brand, ',');
                getline(iss, model, ',');
                getline(iss, token, ',');
                year = stoi(token);
                getline(iss, token, ',');
                capacity = stoi(token);
                getline(iss, token, ',');
                load = stod(token);
                getline(iss, token, '\n');
                fuelConsumption = stod(token);

                Taxi taxi(brand, model, year, capacity,load, fuelConsumption);
                taxis.push_back(taxi);
            }
            else if (entryType == "Route") {
                vector<string> waypoints;
                double distance = 0.0; // Initialize to a default value
                int dailyFrequency = 0; // Initialize to a default value
                string token;
                // Read Route entry data
                while (getline(iss, token, ',')) {
                    if (token.find_first_not_of("0123456789.") == string::npos) {
                        // If the token is a number (distance or daily frequency)
                        if (token.find('.') != string::npos) {
                            // If the token contains a dot, it's a double (distance)
                            distance = stod(token);
                        }
                        else {
                            // Otherwise, it's an integer (daily frequency)
                            dailyFrequency = stoi(token);
                        }
                    }
                    else {
                        // If the token is not a number, it's a waypoint
                        waypoints.push_back(token);
                    }
                }
                if (!waypoints.empty()) {
                    Route route(waypoints, distance, dailyFrequency);
                    routes.push_back(route);
                }
            }
            else {
                cerr << "Error: Unknown entry type." << endl;
            }
        }
        }

        inFile.close();
    }


void displayMenu() {
     cout << "1. Add Taxi" <<  endl;
     cout << "2. Add Route" <<  endl;
     cout << "3. Display Taxis" <<  endl;
     cout << "4. Display Routes" <<  endl;
     cout << "5. Calculate Fuel Needed" <<  endl;
     cout << "6. File options" <<  endl;
     cout << "7. Exit" <<  endl;
     cout << "Enter your choice: ";
}
  
void fileOptionsMenu(TaxiApp& taxiApp, string& filename) {
    // Add a sub-menu for file operations
    system("cls");
    int fileOption;
    cout << "File Operations Menu:" << endl;
    cout << "1. Save to File" << endl;
    cout << "2. Read from File" << endl;
    cout << "3. Delete Contents of File" << endl;
    cout << "4. Change File" << endl;
    cout << "5. Return to main menu" << endl;
    cout << "Enter your choice: ";
    cin >> fileOption;
    cin.ignore();

    ofstream file;  // Move the declaration outside the switch statement

    switch (fileOption) {
    case 1:
        file.open(filename);
        if (file.is_open()) {
            taxiApp.saveDataToFile(filename);
            file.close();
        }
        else {
            cerr << "Unable to open file: " << filename << endl;
        }
        break;
    case 2:
        file.open(filename);
        if (file.is_open()) {
            taxiApp.readDataFromFile(filename);
            file.close();
        }
        else {
            cerr << "Unable to open file: " << filename << endl;
        }
        break;
    case 3:
        // Delete contents of the file
        file.open(filename, ofstream::trunc);
        file.close();
        cout << "Contents of the file deleted." << endl;
        break;
    case 4:
        cout << "Enter new file name: ";
        cin >> filename;
        cin.ignore();
        break;
    case 5:
        return;
    default:
        cout << "Invalid file operation choice. Please try again." << endl;
        break;
    }
}


int main() {
    TaxiApp taxiApp;
     string filename = "taxis.txt";
    // cout << "Which file to open: ";
       //  cin >> filename;
       //  cin.ignore();
     taxiApp.readDataFromFile(filename);

    while (true) {
        system("cls");
        displayMenu();
         string choice;
         cout << "Enter your choice: ";

        if ( getline( cin, choice)) {
            try {
                size_t pos;
                int menuChoice =  stoi(choice, &pos);

                if (pos == choice.size()) {
                    // Conversion successful, and the entire string was consumed
                    // Now 'menuChoice' contains the integer value
                  
                    switch (menuChoice) {
                    case 1: {
                        string brand, model;
                        int year, capacity;
                        double fuelConsumption,load;
                        inputTaxiData(brand, model, year, capacity,load, fuelConsumption);
                        Taxi newTaxi(brand, model, year, capacity,load, fuelConsumption);
                        taxiApp.addTaxi(newTaxi);
                        break;
                    }
                    case 2: {
                        vector<string> waypoints;
                        double distance;
                        int dailyFrequency;
                        inputRouteData(waypoints, distance, dailyFrequency);
                        Route newRoute(waypoints, distance, dailyFrequency);
                        taxiApp.addRoute(newRoute);
                        break;
                    }
                    case 3:
                        taxiApp.displayTaxis();
                        system("pause");
                        break;
                    case 4:
                        taxiApp.displayRoutes();
                        break;
                    case 5:
                        taxiApp.calculateFuelNeeded();
                        break;
                    case 6:
                        fileOptionsMenu(taxiApp, filename);
                        break;
                    case 7:
                        cout << "Exiting the application." << endl;
                        return 0;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                        system("pause");
                        break;
                    }
                }
                else {
                     cout << "Invalid input. Please enter a valid integer." <<  endl;
                     system("pause");
                }
            }
            catch (const  out_of_range& e) {
                 cout << "Invalid input. Please enter a valid integer within the range." <<  endl;
                 system("pause");
            }
            catch (const  invalid_argument& e) {
                 cout << "Invalid input. Please enter a valid integer." <<  endl;
                 system("pause");
            }
        }
        else {
             cout << "Error reading input. Exiting the program." <<  endl;
             system("pause");
            break;
        }
    }

    return 0;
}

