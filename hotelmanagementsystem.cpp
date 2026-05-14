#include <iostream>
#include <string>
using namespace std;
class Hotel
{
private:
    struct Customer
    {
        string name, address, aadhar, phone;
        int bookingID, roomNo, days;
        string checkInDate, checkOutDate, roomType;
        double foodCharges;
        bool checkedOut;
    };
    struct Room {
        int roomNo;
        string type;
        double price;
        bool available;
    };
    Customer customers[100];
    Room rooms[10];
    int customerCount;
    bool isValidNumber(string str, int length)
    {
        if (str.length() != length)
            return false;
        for (int i = 0; i < str.length(); i++)
        {
            if (!isdigit(str[i]))
                return false;
        }
        return true;
    }
public:
    Hotel(){
        customerCount = 0;

        rooms[0] = {101, "AC", 2000, true};
        rooms[1] = {102, "AC", 2000, true};
        rooms[2] = {103, "AC", 2000, true};
        rooms[3] = {104, "AC", 2000, true};
        rooms[4] = {105, "AC", 2000, true};
        rooms[5] = {201, "Non-AC", 1200, true};
        rooms[6] = {202, "Non-AC", 1200, true};
        rooms[7] = {203, "Non-AC", 1200, true};
        rooms[8] = {204, "Non-AC", 1200, true};
        rooms[9] = {205, "Non-AC", 1200, true};
    }
    void customerRegistration()
    {
        if (customerCount >= 100)
        {
            cout << "\nCustomer limit reached!\n";
            return;
        }
  cout << "\n----- Customer Registration -----\n";
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, customers[customerCount].name);
        cout << "Enter Address: ";
        getline(cin, customers[customerCount].address);
        do
        {
            cout << "Enter Aadhar Number (12 digits): ";
            getline(cin, customers[customerCount].aadhar);
            if (!isValidNumber(customers[customerCount].aadhar, 12))
                cout << "Invalid Aadhar! Must be exactly 12 digits.\n";
        } while (!isValidNumber(customers[customerCount].aadhar, 12));
        do
        {
            cout << "Enter Phone Number (10 digits): ";
            getline(cin, customers[customerCount].phone);
            if (!isValidNumber(customers[customerCount].phone, 10))
                cout << "Invalid Phone Number! Must be exactly 10 digits.\n";

        } while (!isValidNumber(customers[customerCount].phone, 10));

        customers[customerCount].bookingID = -1;
        customers[customerCount].roomNo = -1;
        customers[customerCount].checkInDate = "";
        customers[customerCount].checkOutDate = "";
        customers[customerCount].roomType = "";
        customers[customerCount].days = 0;
        customers[customerCount].foodCharges = 0;
        customers[customerCount].checkedOut = false;
        customerCount++;
        cout << "\nCustomer Registered Successfully!\n";
    }
    void roomAvailability()
    {
        cout << "\n----- Room Availability -----\n";
        cout << "Room No\tType\tPrice\tAvailability\n";
        for (int i = 0; i < 10; i++)
        {
            cout << rooms[i].roomNo << "\t" << rooms[i].type << "\t"
                 << rooms[i].price << "\t";

            if (rooms[i].available)
                cout << "Available\n";
            else
                cout << "Booked\n";
        }
    }
    void roomBooking()
    {
        if (customerCount == 0)
        {
            cout << "\nNo customer registered!\n";
            return;
        }
        int bookingID, roomNo, days;
        string date;
        cout << "\n----- Room Booking -----\n";
        cout << "Enter Booking ID: ";
        cin >> bookingID;
        cout << "Enter Room Number: ";
        cin >> roomNo;
        cout << "Enter Check-in Date (DD/MM/YYYY): ";
        cin >> date;
        cout << "Enter Number of Days: ";
        cin >> days;
        int roomIndex = -1;
        for (int i = 0; i < 10; i++)
        {
            if (rooms[i].roomNo == roomNo)
            {
                roomIndex = i;
                break;
            }
        }
        if (roomIndex == -1)
        {
            cout << "\nInvalid Room Number!\n";
            return;
        }
        if (!rooms[roomIndex].available)
        {
            cout << "\nRoom already booked!\n";
            return;
        }
        customers[customerCount - 1].bookingID = bookingID;
        customers[customerCount - 1].roomNo = roomNo;
        customers[customerCount - 1].checkInDate = date;
        customers[customerCount - 1].roomType = rooms[roomIndex].type;
        customers[customerCount - 1].days = days;
        rooms[roomIndex].available = false;
        cout << "\nRoom Booked Successfully!\n";
    }
    void billingAndCheckout()
    {
        int id;
        cout << "\n----- Billing and Checkout -----\n";
        cout << "Enter Booking ID: ";
        cin >> id;
        for (int i = 0; i < customerCount; i++)
        {
            if (customers[i].bookingID == id)
            {
                if (customers[i].checkedOut)
                {
                    cout << "\nCustomer already checked out!\n";
                    return;
                }
                cout << "Enter Checkout Date (DD/MM/YYYY): ";
                cin >> customers[i].checkOutDate;
                cout << "Enter Food Charges (Rs): ";
                cin >> customers[i].foodCharges;
                double roomPrice = 0;
                for (int j = 0; j < 10; j++)
                {
                    if (rooms[j].roomNo == customers[i].roomNo)
                    {
                        roomPrice = rooms[j].price;
                        rooms[j].available = true;
                        break;
                    }
                }
                double roomCharges = roomPrice * customers[i].days;
                double subTotal = roomCharges + customers[i].foodCharges;
                double gst = subTotal * 0.12;
                double totalBill = subTotal + gst;
                cout << "\n----- BILL RECEIPT -----\n";
                cout << "Hotel Name: TAJ HOTEL\n";
                cout << "Customer Name: " << customers[i].name << endl;
                cout << "Room No: " << customers[i].roomNo << endl;
                cout << "Room Type: " << customers[i].roomType << endl;
                cout << "Check-in Date: " << customers[i].checkInDate << endl;
                cout << "Check-out Date: " << customers[i].checkOutDate << endl;
                cout << "Days Stayed: " << customers[i].days << endl;
                cout << "Room Charges: Rs " << roomCharges << endl;
                cout << "Food Charges: Rs " << customers[i].foodCharges << endl;
                cout << "----------------------------\n";
                cout << "Sub Total: Rs " << subTotal << endl;
                cout << "GST (12%): Rs " << gst << endl;
                cout << "----------------------------\n";
                cout << "Total Bill: Rs " << totalBill << endl;
                cout << "----------------------------\n";
                customers[i].checkedOut = true;
                cout << "\nCheckout Successful! Thank you for visiting TAJ HOTEL.\n";
                return;
            }
        }
        cout << "\nBooking ID not found!\n";
    }
    void customerRecord()
    {
        int id;
        cout << "\n----- Customer Record Management -----\n";
        cout << "Enter Booking ID: ";
        cin >> id;
        int found = 0;
        for (int i = 0; i < customerCount; i++)
        {
            if (customers[i].bookingID == id)
            {
                found = 1;
                cout << "\nCustomer Details:\n";
                cout << "Name: " << customers[i].name << endl;
                cout << "Address: " << customers[i].address << endl;
                cout << "Aadhar: " << customers[i].aadhar << endl;
                cout << "Phone: " << customers[i].phone << endl;
                cout << "Booking ID: " << customers[i].bookingID << endl;
                cout << "Room No: " << customers[i].roomNo << endl;
                cout << "Room Type: " << customers[i].roomType << endl;
                cout << "Check-in Date: " << customers[i].checkInDate << endl;
                cout << "Check-out Date: " << customers[i].checkOutDate << endl;
                cout << "Days Stayed: " << customers[i].days << endl;
                cout << "Food Charges: Rs " << customers[i].foodCharges << endl;
                if (customers[i].checkedOut)
                    cout << "Status: Checked Out\n";
                else
                    cout << "Status: Staying\n";
                break;
            }
        }
        if (found == 0)
            cout << "\nCustomer not found!\n";
    }
    void menu()
    {
        int choice;
        cout << "========================================\n";
        cout << "      TAJ HOTEL MANAGEMENT SYSTEM       \n";
        cout << "========================================\n";
        do
        {
            cout << "\n1. Customer Registration";
            cout << "\n2. Room Availability";
            cout << "\n3. Room Booking";
            cout << "\n4. Billing and Checkout";
            cout << "\n5. Add New Customer";
            cout << "\n6. Customer Record Management";
            cout << "\n7. Exit";
            cout << "\nEnter your choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                customerRegistration();
                break;
            case 2:
                roomAvailability();
                break;
            case 3:
                roomBooking();
                break;
            case 4:
                billingAndCheckout();
                break;
            case 5:
                customerRegistration();
                break;
            case 6:
                customerRecord();
                break;
            case 7:
                cout << "\nThank You for using TAJ HOTEL MANAGEMENT SYSTEM!\n";
                break;
            default:
                cout << "\nInvalid choice! Try again.\n";
            }
        } while (choice != 7);
    }
};
int main()
{
    Hotel h;
    h.menu();
    return 0;
}
