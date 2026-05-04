#ifndef SPORTVENUE_RESERVATION_H
#define SPORTVENUE_RESERVATION_H

#include <iostream>       // For input and output operations (e.g., cout, cin)
#include <string>         // For using the string data type
#include <iomanip>        // For formatting output (e.g., setting precision, width)
#include <mysql.h>        // For MySQL database operations (e.g., connecting to database)
#include <conio.h>        // For console input/output (e.g., _getch() for capturing keyboard input without echo)
#include <regex>          // For define a regex pattern to match the date format in (YYYY/MM/DD)

// Database Connection
extern MYSQL* conn;
extern MYSQL_ROW row;
extern MYSQL_RES* res;
extern int qstate;

class db_response {
public:
    static void ConnectionFunction();
};

// Function Declaration
int main();                 //Starting page of the program
void userRegistration();    //User registration page
void userLogin();           //User login page
void adminLogin();          //Admin login page
void userMainMenu();        //User main menu page
void reservation();         //User function: Booking page
void myBookingHistory();    //User function: View user's booking
void myProfile();           //User function: View profile
void giveAFeedback();       //User function: Give a feedback
void adminMainMenu();       //Admin main menu page
int facilityManagement();   //Admin function: Facility management 
void addFacility();         //Sub menu: Add new Facility
void updateFacility();      //Sub menu: Update Facility
void deleteFacility();      //Sub menu: Delete Facility
void updatePaymentStatus(); //Admin function: View all booking records change to manage bookings
void searchUser();          //Admin function: Search for user
void viewFeedback();        //Admin function: View feedback
void reservationReport();   //Admin function: Reservation income analysis
void viewAllReservation();  //Admin function: View all reservation records

#endif // SPORTVENUE_RESERVATION_H
