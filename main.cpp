/*Title     : Sport Venue Reservation System

SportVenueReservation.cpp : This file contains the 'main' function. Program execution begins and ends there.*/
#include "SportVenue_Reservation.h"
using namespace std;
// Global variables
string currentUser; //Stores the username of the currently logged in user

MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;
int qstate;

//Database connection
void db_response::ConnectionFunction() {
    conn = mysql_init(0);
    if (conn)
        cout << "Database Connected." << endl;
    else
        cout << "Failed To Connect!" << endl;

    conn = mysql_real_connect(conn, "localhost", "root", "", "sport_venue_reservation", 3306, NULL, 0); //Database connector to connect my database
    if (conn)
        cout << "Database Connected To MySQL" << endl; //Success access to database
    else
        cout << "Failed To Connect!" << endl; //Failed access to database
}

//Login and Registration page
int main() {
    system("cls"); //Clear the console screen for a fresh display
    system("title My Project");
    db_response::ConnectionFunction();

    int menu;
    //Display Welcome message for user
    cout << "\n\t\t\t\t\t\t*****************************************************************************" << endl;
    cout << "\t\t\t\t\t\t\t\t\tWELCOME TO LCW SPORT COMPLEX" << endl;
    cout << "\t\t\t\t\t\t*****************************************************************************" << endl;
    //Display Sport Complex information and functions
    cout << "\t\t\t\t\t\t\t\t\t\tABOUT US" << endl;   
    cout << "\t\t\t\t\t\t\t Location      : Jalan Dato Seri Hj Mat Zain, 75350, Melaka " << endl;
    cout << "\t\t\t\t\t\t\t Tel           : +60123345567\n                             " << endl;
    cout << "\t\t\t\t\t\t\t\t--------------Operating Hour----------" << endl;
    cout << "\t\t\t\t\t\t\t    Monday   -   Sunday    10 a.m. to 12 p.m. (10hours)\n   " << endl;
    cout << "\t\t\t\t\t\t\t\t---------------Amenities--------------" << endl;
    cout << "\t\t\t\t\t\t\t    Toilets       Parking(Free)      Food & Beverage     " << endl;
    cout << "\t\t\t\t\t\t\t    Proshop          Surau          Emergency counter\n  " << endl;
    cout << "\t\t\t\t\t\t\t\t-----------Indoor Facilities----------" << endl;
    cout << "\t\t\t\t\t\t\t    Badminton Court           Ping Pong Court         " << endl;
    cout << "\t\t\t\t\t\t\t    Pickle Ball Court         Futsal                  " << endl;
    cout << "\t\t\t\t\t\t*****************************************************************************" << endl;
    cout << "\t\t\t\t\t\t\t\t\t1. User Register    " << endl;
    cout << "\t\t\t\t\t\t\t\t\t2. User Login       " << endl;
    cout << "\t\t\t\t\t\t\t\t\t3. Admin Login      " << endl;
    cout << "\t\t\t\t\t\t\t\t\t4. Exit             " << endl;
    cout << "\t\t\t\t\t\t\t\tOption: ";
    cin >> menu;

    switch (menu)
    {
    case 1:
        userRegistration();//Option 1 direct user to registration if user haven't register
        break;
    case 2:
        userLogin();       //Option 2 will direct user to  user login 
        break;
    case 3:
        adminLogin();      //Option 3 will direct user to admin login
        break;
    case 4:
        cout << "\t\t\t\t\t\tSystem Exiting...^o^ Thank you for using our services!" << endl; //Display exiting message
        exit(0);
    default:
        cout << "\t\t\t\t\t\tPlease choose between 1 - 4. Press Enter To Try Again...";
        _getch();         //Pauses the program until a key is pressed, allowing the user to read the error message.
        system("cls");
        main();           //Return login page if invalid option
        break;
    }

    return 0;
}

//User Registration page
void userRegistration() {
    string name, age, gender, username, password, email, contact;
    char confirmRg;

    system("cls");// Clears the console screen for a clean display of the login prompt
    cout << "\n\t\t\t\t\t\t*****************************************************************************" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\tUSER REGISTRATION                              " << endl;
    cout << "\t\t\t\t\t\t*****************************************************************************\n" << endl;
    cout << "\t\t\t\t\t\t\tALERT!!!Please ensure that your Name, Age, and Gender provided \n\t\t\t\t\t\t\t\tis accurate to your Identity Card!!!" << endl;
    // Input Name
    cout << "\n\t\t\t\t\t\t\t\tEnter your Name: ";
    cin.ignore(); // Clear input buffer
    getline(cin, name);

    //Input age
    cout << "\t\t\t\t\t\t\t\tEnter your Age: ";
    cin >> age;

    //Input Gender
    while (true) {
        cout << "\t\t\t\t\t\t\t\tEnter your Gender(M/F): ";
        cin >> gender;

        if (gender == "M" || gender == "F") {
            break; //Exit loop if gender is valid
        }
        else {
            cout << "\t\t\t\t\t\t\tInvalid input! Please enter M or F only.\n " << endl; //Error message prompted to user if invalid input
        }
    }


    // Check for unique Username
    bool isUnique = false;
    while (!isUnique) {
        cout << "\t\t\t\t\t\t\t\tEnter a Username: "; //Input username
        cin >> username;
        // Prepared query to check the uniqueness of username
        string uniqueUsernameQuery = "SELECT * FROM User WHERE Username = '" + username + "';";
        qstate = mysql_query(conn, uniqueUsernameQuery.c_str());

        if (!qstate) {                                // Check if the query was successful
            res = mysql_store_result(conn);           // Retrieve the result set from the executed query
            if (mysql_num_rows(res) > 0) {            // Check if there are any rows in the result set
                cout << "\t\t\t\t\t\t\tUsername already exists! Please choose another one.\n" << endl; // If the result set contains rows, the username already exists
            }
            else {
                isUnique = true;                      // If no rows are found, the username is unique
            }
        }
        else {
            cout << "\t\t\t\t\t\t\tDatabase Query Failed: " << mysql_error(conn) << endl; // If the query execution failed, print the error message
        }
    }
    //Input password
    cout << "\t\t\t\t\t\t\t\tEnter a Password: ";
    char ch;
    while ((ch = _getch()) != '\r') {   // '\r' is the Enter key. Use _getch() to read user input character by character, rather than directly using cin.
        if (ch == '\b') {               //Handle backspace. Indicates that the user pressed the Backspace key and needs to delete the last character.
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";        //Move cursor back, overwrite with space, move back again.
            }
        }
        else {
            // For password input handling
            password += ch; // Append the character typed by the user (masked as *) to the password string
            cout << "*";    //Display masking symbol.
        }
    }
    cout << endl;

    // Check for unique Email
    bool isEmailUnique = false;
    while (!isEmailUnique) {
        cout << "\t\t\t\t\t\t\t\tEnter your Email(@example.com): "; // Input email
        cin >> email;

        //Prepared query to check the uniqueness of Email
        string uniqueEmailQuery = "SELECT * FROM User WHERE Email = '" + email + "';";
        qstate = mysql_query(conn, uniqueEmailQuery.c_str());

        if (!qstate) {                                // Check if the query was successful
            res = mysql_store_result(conn);           // Retrieve the result set from the executed query
            if (mysql_num_rows(res) > 0) {            // Check if there are any rows in the result set
                cout << "\t\t\t\t\t\t\tEmail already exists! Please choose another one.\n" << endl; // If the result set contains rows, the email already exists
            }
            else {
                isEmailUnique = true;                 // If no rows are found, the email is unique
            }
        }
        else {
            cout << "\t\t\t\t\t\t\tDatabase Query Failed: " << mysql_error(conn) << endl; // If the query execution failed, print the error message
        }
    }

    // Check for unique Phone number
    bool isContactUnique = false;
    while (!isContactUnique) {
        cout << "\t\t\t\t\t\t\t\tEnter your Phone Number: "; // Input phone number
        cin >> contact;

        //Prepared query to check the uniqueness of Email
        string uniqueContactQuery = "SELECT * FROM User WHERE Contact = '" + contact + "';";
        qstate = mysql_query(conn, uniqueContactQuery.c_str());

        if (!qstate) {                                // Check if the query was successful
            res = mysql_store_result(conn);           // Retrieve the result set from the executed query
            if (mysql_num_rows(res) > 0) {            // Check if there are any rows in the result set
                cout << "\t\t\t\t\t\t\tEmail already exists! Please choose another one.\n" << endl; // If the result set contains rows, the email already exists
            }
            else {
                isContactUnique = true;                 // If no rows are found, the email is unique
            }
        }
        else {
            cout << "\t\t\t\t\t\t\tDatabase Query Failed: " << mysql_error(conn) << endl; // If the query execution failed, print the error message
        }
    }
     //Save data into database, user table
     string insertQuery = "INSERT INTO User (Name, Age, Gender, Username, Password, Email, Contact) VALUES ('" + name + "', '" + age + "', '" + gender + "', '" + username + "', '" + password + "', '" + email + "', '" + contact + "');";
     qstate = mysql_query(conn, insertQuery.c_str()); // Exectue the query

     if (!qstate) {
         cout << "\n\t\t\t\t\t\t\tRegistration Successful! Redirecting to Login Page..." << endl;
     }
      else {
         cout << "\n\t\t\t\t\t\t\tRegistration Failed: " << mysql_error(conn) << endl;
      }
      _getch();
      main(); // Return to main menu,login page
}
    
//User Login page
void userLogin() {
    string username, password;
    int attemptCount = 0;
    const int maxAttempts = 3; //Maximum number of attempts

    system("cls"); //Clear the console screen for a fresh display for Welcome message
    cout << "\n\t\t\t\t\t\t*****************************************************************************" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\tUSER LOGIN" << endl;
    cout << "\t\t\t\t\t\t*****************************************************************************\n" << endl;

    while (attemptCount < maxAttempts) {
        cout << "\t\t\t\t\t\tEnter your Username: ";
        cin >> username;

        //Password masking
        password.clear(); 
        cout << "\t\t\t\t\t\tEnter your Password: ";
        char ch;
        while ((ch = _getch()) != '\r') {   // '\r' is the Enter key. Use _getch() to read user input character by character, rather than directly using cin.
            if (ch == '\b') {               //Handle backspace. Indicates that the user pressed the Backspace key and needs to delete the last character.
                if (!password.empty()) {
                    password.pop_back();
                    cout << "\b \b";        //Move cursor back, overwrite with space, move back again.
                }
            }
            else {
                password += ch;
                cout << "*"; //Display masking symbol.
            }
        }
        cout << endl;

        //Check the validation of username and password
        string validationQuery = "SELECT * FROM User WHERE Username = '" + username + "' AND password = '" + password + "';";
        qstate = mysql_query(conn, validationQuery.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);
            if (mysql_num_rows(res) > 0) {
                // Login successful and enter user main menu.
                cout << "\n\t\t\t\t\t\tLogin Successful! Redirecting to User Main Menu..." << endl;
                currentUser = username; //Save the currently logged in username.
                _getch();
                userMainMenu();

            }
            else {
                cout << "\n\t\t\t\t\t\tInvalid username or password. Please try again.\n" << endl;
                attemptCount++; //3 times attempt.
            }
        }
        else {
            cout << "\n\t\t\t\t\t\tDatabase Query Failed: " << mysql_error(conn) << endl;
            return;
        }

        if (attemptCount >= maxAttempts) {
            cout << "\t\t\t\t\t\t\tToo many failed attempts!!! Please try again later." << endl;
            _getch();
            main(); //If the number of attempts is exceeded, display error message and return to the login page.
        }
    }
}

//User main menu 
void userMainMenu() {
    int usermenu;
    while (true) {
        system("cls");// Clears the console screen for a clean display of the login prompt
        //Display page and menu
        cout << "\n\t\t\t\t\t\t*****************************************************************************" << endl;
        cout << "\t\t\t\t\t\t\t\t\tGAME ON. OWN THE THRONE" << endl;
        cout << "\t\t\t\t\t\t\t\t\t    USER MAIN MENU     " << endl;
        cout << "\t\t\t\t\t\t*****************************************************************************\n" << endl;
        cout << "\t\t\t\t\t\t\t\t\t1. Book a Sport Venue" << endl;
        cout << "\t\t\t\t\t\t\t\t\t2. My Booking History" << endl;
        cout << "\t\t\t\t\t\t\t\t\t3. My Profile" << endl;
        cout << "\t\t\t\t\t\t\t\t\t4. Give Feedback" << endl;
        cout << "\t\t\t\t\t\t\t\t\t5. Logout" << endl;
        cout << "\t\t\t\t\t\t\t\tOption: ";
        
        cin >> usermenu;

        switch (usermenu) {
        case 1:
            // Call a function to handle booking
            reservation();
            _getch();
            break;
        case 2:
            // Call a function to view bookings
            myBookingHistory();
            _getch();
            break;
        case 3:
            // Call a function to view account details
            myProfile();
            break;
        case 4:
            // Call a function to give feedback
            giveAFeedback();
            _getch(); 
            break;
        case 5:
            cout << "\t\t\t\t\t\t\tLogging out... Returning to login page." << endl;
            _getch(); //Pauses the program until a key is pressed, allowing the user to read the logging out message.
            main(); // Return to the main menu (login page)
            return;
        default:
            cout << "\t\t\t\t\t\t\tInvalid option. Please choose between 1-5." << endl;
            _getch(); //Pauses the program until a key is pressed, allowing the user to read the error message.
            break;
        }
    }
}

//User function: Book a Sport Venue
void reservation() {
    string facility_code, booking_date, court_name, payment_method, option;
    int duration, startTime, endTime, payChoice;
    double total_price;

    // Display the central policies and rules to user before making a reservation
    system("cls");
    cout << "\n\t\t\t\t\t\t*****************************************************************************" << endl;
    cout << "\t\t\t\t\t\t\t\t\t SPORT VENUE RESERVATION " << endl;
    cout << "\t\t\t\t\t\t*****************************************************************************\n" << endl;
    cout << "\t\t\t\t\t\t\t\t\tCentral Policies and Rules: " << endl;
    cout << "\t\t\t\t\t\t\t1. Confirmed bookings are non-refundable and cannot be canceled.  " << endl;
    cout << "\t\t\t\t\t\t\t2. Sports court bookings must be between 1 to 2 hours.            " << endl;
    cout << "\t\t\t\t\t\t\t3. Only non-marking shoes are allowed.                            " << endl;
    cout << "\t\t\t\t\t\t\t4. Smoke at non-smoking area will be fine RM300.                  " << endl;
    cout << "\t\t\t\t\t\t\t5. Park at your own risk.                                         " << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\tPress (Enter) to continue..." << endl;
    _getch(); //Pause the page to allow user to read the content

    // Give option to user whether they want to book or not
    while (true) {
        cout << "\t\t\t\t\t\t\tProceed to make a reservation? (Y/N): ";
        cin >> option;
        if (option == "Y" || option == "y") {
            break;
        }
        else if (option == "N" || option == "n") {
            userMainMenu(); // Return to the user main menu if No
            return;
        }
        else {
            cout << "\t\t\t\t\t\t\tInvalid input! Please enter 'Y' for Yes or 'N' for No." << endl;
        }
    }

    // Display facility details
    system("cls");
    cout << "\n\t\t\t\t\t\t*****************************************************************************" << endl;
    cout << "\t\t\t\t\t\t\t\t\t SPORT VENUE RESERVATION " << endl;
    cout << "\t\t\t\t\t\t*****************************************************************************\n" << endl;
    cout << "\t\t\t\t\t\t\tCode:          Facilities :           Price/hour(RM)           " << endl;
    cout << "\t\t\t\t\t\t\tBC             Badminton Court            18                   " << endl;
    cout << "\t\t\t\t\t\t\tPPC            Ping Pong Court            12                   " << endl;
    cout << "\t\t\t\t\t\t\tPBC            Pickle Ball Court          20                   " << endl;
    cout << "\t\t\t\t\t\t\tFS             Futsal Court               90                   " << endl;

    // Step 1: Enter Facility Code (BC, PPC, PBC, FS)
    cout << "\n\t\t\t\t\t\t\tEnter Facility Code (e.g. BC): ";
    cin >> facility_code;
    // Input facility code in CAPITAL LETTER
    while (facility_code != "BC" && facility_code != "PBC" && facility_code != "PPC" && facility_code != "FS") {
        cout << "\t\t\t\t\t\t\tInvalid input! Ensure your input match the criteria : ";
        cin >> facility_code;
        cin.ignore(); // Clear input buffer
    }

    // Step 2: Enter Booking Date with format validation
    regex date_regex("^\\d{4}/\\d{2}/\\d{2}$"); // Define a regex pattern to match the date format YYYY/MM/DD
    cout << "\t\t\t\t\t\t\tEnter Booking date (YYYY/MM/DD): ";
    cin >> booking_date;

    // Validate date format (YYYY/MM/DD)
    while (!regex_match(booking_date, date_regex)) {
        cout << "\t\t\t\t\t\t\tInvalid input! Please enter in (YYYY/MM/DD) format: ";
        cin >> booking_date;
    }
    //cout << "\t\t\t\t\t\t\tEnter Booking date (YYYY/MM/DD): ";
    //cin >> booking_date;

    // Step 3: Enter Duration (1 hour or 2 hours)
    do {
        cout << "\t\t\t\t\t\t\tEnter Duration (1 or 2 hours): ";
        cin >> duration;
        if (duration != 1 && duration != 2) {
            cout << "\t\t\t\t\t\t\tInvalid duration! Only 1 or 2 hours are allowed." << endl;
        }
    } while (duration != 1 && duration != 2);

    // Step 4: Enter Start and calculate End Time
    cout << "\t\t\t\t\t\t\tEnter Start Time (e.g.10 for 10:00 AM): ";
    cin >> startTime;
    endTime = startTime + duration;  // Calculate end time based on duration
    cout << "\t\t\t\t\t\t\tEnd Time: " << endTime << endl;

    // Fetch available courts for the selected facility
    string courtQuery = "SELECT court_name, price_per_hour FROM Facility WHERE facility_code = '" + facility_code + "' AND status = 'Available';";
    if (mysql_query(conn, courtQuery.c_str())) {
        cerr << "\t\t\t\t\t\t\tError fetching courts: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_RES* courtResult = mysql_store_result(conn);
    if (mysql_num_rows(courtResult) == 0) {
        cout << "\t\t\t\t\t\t\tNo available courts for the selected facility." << endl;
        mysql_free_result(courtResult);
        return;
    }
    // Display available courts to user
    cout << "\t\t\t\t\t\t\t------------------------------" << endl;
    cout << "\t\t\t\t\t\t\tAvailable Courts:" << endl;
    cout << "\t\t\t\t\t\t\t------------------------------" << endl;
    MYSQL_ROW courtRow;
    while ((courtRow = mysql_fetch_row(courtResult))) {
        cout << "\t\t\t\t\t\t\t  - " << courtRow[0] << endl;
    }
    mysql_free_result(courtResult);

    // Step 5: Select a specific court
    bool courtSelected = false;
    while (!courtSelected) {
        cout << "\t\t\t\t\t\t\tEnter Court Name (e.g., BC01): ";
        cin >> court_name;

        //Check availability of the court
        string checkAvailabilityquery = 
            "SELECT r.ReserveID FROM Reservation r "
            "JOIN Facility f ON r.FaciID = f.FaciID "
            "WHERE f.Court_name = '" + court_name + "' "
            "AND r.Booking_date = '" + booking_date + "' "
            "AND (r.Start_time < '" + to_string(endTime) + ":00' AND r.End_time > '" + to_string(startTime) + ":00');";
        if (mysql_query(conn, checkAvailabilityquery.c_str())) {
            cerr << "\t\t\t\t\t\t\tError checking availability: " << mysql_error(conn) << endl;
            return;
        }

        MYSQL_RES* result = mysql_store_result(conn);
        if (mysql_num_rows(result) > 0) {
            cout << "\t\t\t\t\t\t\tSorry, the court " << court_name << " is already booked during the selected time." << endl;
            mysql_free_result(result);
            cout << "\t\t\t\t\t\t\tPlease select a different court." << endl;
        }
        else {
            courtSelected = true;
            mysql_free_result(result);
        }
    }

    // Calculate total price
    string priceQuery = "SELECT price_per_hour FROM Facility WHERE Court_name = '" + court_name + "';";
    if (mysql_query(conn, priceQuery.c_str())) {
        cerr << "\t\t\t\t\t\t\tError fetching price: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_RES* priceResult = mysql_store_result(conn);
    MYSQL_ROW priceRow = mysql_fetch_row(priceResult);
    if (priceRow) {
        total_price = stod(priceRow[0]) * duration;
    }
    else {
        cout << "\t\t\t\t\t\t\tInvalid Court Selection!" << endl;
        mysql_free_result(priceResult);
        return;
    }
    mysql_free_result(priceResult);

    // Select payment method
    do {
        cout << "\t\t\t\t\t\t\t1. Cash\t\t2. Online Transfer" << endl;
        cout << "\t\t\t\t\t\t\tEnter your payment method: ";
        cin >> payChoice;

        switch (payChoice) {
        case 1:
            payment_method = "Cash";
            break;
        case 2:
            payment_method = "Online Transfer";
            break;
        default:
            cout << "\t\t\t\t\t\t\tInvalid input! Please choose 1 or 2 only." << endl;
        }
    } while (payChoice != 1 && payChoice != 2);

    // Display booking summary
    system("cls");
    cout << "\n\t\t\t\t\t\t*****************************************************************************" << endl;
    cout << "\t\t\t\t\t\t\t\t\t Booking Summary " << endl;
    cout << "\t\t\t\t\t\t*****************************************************************************\n" << endl;
    cout << "\t\t\t\t\t\t\tFacility: " << facility_code << " (" << court_name << ")" << endl;
    cout << "\t\t\t\t\t\t\tBooking Date: " << booking_date << endl;
    cout << "\t\t\t\t\t\t\tStart Time: " << startTime << ":00" << endl;
    cout << "\t\t\t\t\t\t\tEnd Time: " << endTime << ":00" << endl;
    cout << "\t\t\t\t\t\t\tDuration: " << duration << " hour(s)" << endl;
    cout << "\t\t\t\t\t\t\tTotal Price: RM " << total_price << endl;
    cout << "\t\t\t\t\t\t\tPayment Method: " << payment_method << endl;
    cout << "\n\t\t\t\t\t\tFor online banking, Please bank in to this account.no (CIMB:8237491056)" << endl;
    cout << "\n\t\t\t\t\t\t\tand write your booking ID as the references. Thank you!" << endl;
    cout << "\n\t\t\t\t\t\t*****************************************************************************" << endl;

    // Confirm reservation
    cout << "\t\t\t\t\t\t\tDo you want to confirm your reservation? (Y/N): ";
    char confirm;
    cin >> confirm;

    while (confirm != 'Y' && confirm != 'y' && confirm != 'N' && confirm != 'n') {
        cout << "\t\t\t\t\t\t\tInvalid input! Please enter Y/N: ";
        cin >> confirm;
    }

    if (confirm == 'Y' || confirm == 'y') { 
        // Insert booking details into Reservation table
        string insertReservationQuery = "INSERT INTO Reservation (UserID, FaciID, Booking_date, duration, Start_time, End_time, Total_price) "
        "VALUES ((SELECT UserID FROM User WHERE Username = '" + currentUser + "' LIMIT 1) , (SELECT FaciID FROM Facility WHERE Facility_code = '" + facility_code + "' LIMIT 1),'" + booking_date + "', " + to_string(duration) + ", '" + to_string(startTime) + ":00:00', '" + to_string(endTime) + ":00:00', " + to_string(total_price) + ");";

        if (mysql_query(conn, insertReservationQuery.c_str())) {
            cerr << "\t\t\t\t\t\t\tError inserting reservation: " << mysql_error(conn) << endl;
            return;
        }

        cout << "\t\t\t\t\t\t\tReservation made successfully!" << endl;

        // Get the ReserveID of the newly created reservation
        string getReserveIDQuery = "SELECT LAST_INSERT_ID();";
        if (mysql_query(conn, getReserveIDQuery.c_str())) {
            cerr << "\t\t\t\t\t\t\tError fetching ReserveID: " << mysql_error(conn) << endl;
            return;
        }

        MYSQL_RES* reserveIDResult = mysql_store_result(conn);
        MYSQL_ROW reserveIDRow = mysql_fetch_row(reserveIDResult);
        int reserveID = stoi(reserveIDRow[0]);
        mysql_free_result(reserveIDResult);

        // Insert payment details into the Payment table
        string paymentQuery = "INSERT INTO Payment (ReserveID, Payment_date, Payment_amount, Payment_method, Payment_status) "
            "VALUES (" + to_string(reserveID) + ", CURDATE(), " + to_string(total_price) + ", '" + payment_method + "', 'Unpaid');";

        if (mysql_query(conn, paymentQuery.c_str())) {
            cerr << "\t\t\t\t\t\t\tError inserting payment details: " << mysql_error(conn) << endl;
            return;
        }

        cout << "\t\t\t\t\t\t\tPayment details recorded, your reservation is now confirmed!" << endl;

        // Ask the user if they want to make another reservation
        char anotherReserve;
        cout << "\t\t\t\t\t\t\tDo you want to make another reservation? (Y/N): ";
        cin >> anotherReserve;
        if (anotherReserve == 'Y' || anotherReserve == 'y') {
            reservation();  // Call the function again for a new reservation
        }
        else if (anotherReserve == 'N' || anotherReserve == 'n') {
            userMainMenu();  // Return to the user main menu
        }
    }
    else {
        cout << "\t\t\t\t\t\t\tReservation canceled." << endl;
    }
}

//User function: View My Booking History
void myBookingHistory() {
    int menu;
    string query;

    system("cls"); // Clears the console screen for a clean display of the menu
    // Display page and options to the user
    cout << "\n\t\t\t\t\t\t*****************************************************************************" << endl;
    cout << "\t\t\t\t\t\t\t\t\tMY BOOKING HISTORY" << endl;
    cout << "\t\t\t\t\t\t*****************************************************************************\n" << endl;
    cout << "\t\t\t\t\t\t\t\t\t1. All Booking History" << endl;
    cout << "\t\t\t\t\t\t\t\t\t2. Paid Booking History" << endl;
    cout << "\t\t\t\t\t\t\t\t\t3. Unpaid Booking History" << endl;
    cout << "\t\t\t\t\t\t\t\t\t4. Back" << endl;
    cout << "\t\t\t\t\t\t\t\tOption: ";
    cin >> menu;

    switch (menu) {
    case 1:
        // Query to fetch all bookings for the current user
        query = "SELECT r.ReserveID, f.Facility_code, r.Booking_date, r.duration, r.Start_time, r.End_time, r.Total_price, p.Payment_method, p.Payment_status "
            "FROM Reservation r "
            "JOIN User u ON r.UserID = u.UserID "
            "JOIN Facility f ON r.FaciID = f.FaciID "
            "JOIN Payment p ON r.ReserveID = p.ReserveID "
            "WHERE u.Username = '" + currentUser + "';";
        break;
    case 2:
        // Query to fetch paid bookings for the current user
        query = "SELECT r.ReserveID, f.Facility_code, r.Booking_date, r.duration, r.Start_time, r.End_time, r.Total_price, p.Payment_method, p.Payment_status "
            "FROM Reservation r "
            "JOIN User u ON r.UserID = u.UserID "
            "JOIN Facility f ON r.FaciID = f.FaciID "
            "JOIN Payment p ON r.ReserveID = p.ReserveID "
            "WHERE u.Username = '" + currentUser + "' AND p.Payment_status = 'Paid';";
        break;
    case 3:
        // Query to fetch unpaid bookings for the current user
        query = "SELECT r.ReserveID, f.Facility_code, r.Booking_date, r.duration, r.Start_time, r.End_time, r.Total_price, p.Payment_method, p.Payment_status "
            "FROM Reservation r "
            "JOIN User u ON r.UserID = u.UserID "
            "JOIN Facility f ON r.FaciID = f.FaciID "
            "JOIN Payment p ON r.ReserveID = p.ReserveID "
            "WHERE u.Username = '" + currentUser + "' AND p.Payment_status = 'Unpaid';";
        break;
    case 4:
        userMainMenu(); // Back to user main menu
        return;
    default:
        cout << "\t\t\t\t\t\t\tInvalid choice! Please choose between 1 - 4." << endl;
        _getch(); // Pause allow user to read the error message
        myBookingHistory();
        return;
    }

    // Execute the query
    if (mysql_query(conn, query.c_str())) {
        cerr << "\t\t\t\t\t\t\t\t\tError fetching bookings: " << mysql_error(conn) << endl;
        return;
    }

    // Store the result of the query
    res = mysql_store_result(conn);
    if (res == NULL) {
        cout << "\t\t\t\t\t\t\t\t\tNo bookings found." << endl;
        return;
    }

    // Check if there are bookings to display
    bool hasBookings = false;
    while ((row = mysql_fetch_row(res))) {
        hasBookings = true;

        cout << "\t\t\t\t\t\t\t------------------------------------------------------" << endl;
        cout << "\t\t\t\t\t\t\tReserve ID: " << row[0] << endl;
        cout << "\t\t\t\t\t\t\tFacility Name: " << row[1] << endl;
        cout << "\t\t\t\t\t\t\tBooking Date: " << row[2] << endl;
        cout << "\t\t\t\t\t\t\tDuration: " << row[3] << " hour(s)" << endl;
        cout << "\t\t\t\t\t\t\tTimeslot: " << row[4] << " to " << row[5] << endl;
        cout << "\t\t\t\t\t\t\tTotal Price: RM " << row[6] << endl;
        cout << "\t\t\t\t\t\t\tPayment Method: " << row[7] << endl;
        cout << "\t\t\t\t\t\t\tPayment Status: " << row[8] << endl;
        cout << "\t\t\t\t\t\t\t------------------------------------------------------" << endl;
    }

    // If no bookings are found, display a message
    if (!hasBookings) {
        cout << "\t\t\t\t\t\t\t\t\tNo bookings found for the selected option." << endl;
    }

    // Free the result set
    mysql_free_result(res);

    // Return to the user main menu
    cout << "\n\t\t\t\t\t\t\t\t\tPress (Enter) to continue...^o^";
    _getch(); // Pause to allow user to read the message
    myBookingHistory(); // Return to the User Main Menu
}

//User function: View My Profile
void myProfile() {
    int menu, newAge;
    string newName, newEmail, newContact, newPassword;

    system("cls");
    // Display page and options to user
    cout << "\n\t\t\t\t\t\t*****************************************************************************" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\tMY PROFILE" << endl;
    cout << "\t\t\t\t\t\t*****************************************************************************\n" << endl;

    // Prepare SQL query to fetch user information based on the currently logged-in username
    string viewMyProfileQuery = "SELECT Name, Age, Gender, Username, Email, Contact FROM User WHERE Username = '" + currentUser + "';";
    qstate = mysql_query(conn, viewMyProfileQuery.c_str()); // Execute the SQL query

    if (!qstate) { // Check if the query was successful
        res = mysql_store_result(conn);       // Store the result of the query
        if (res && mysql_num_rows(res) > 0) { // If the user exists, display the user details
            (row = mysql_fetch_row(res));     // Fetch each row of the result
            // Display current user's details
            cout << "\t\t\t\t\t\t\t\tName         : " << row[0] << endl;
            cout << "\t\t\t\t\t\t\t\tAge          : " << row[1] << endl;
            cout << "\t\t\t\t\t\t\t\tGender       : " << row[2] << endl;
            cout << "\t\t\t\t\t\t\t\tUsername     : " << row[3] << endl;
            cout << "\t\t\t\t\t\t\t\tEmail        : " << row[4] << endl;
            cout << "\t\t\t\t\t\t\t\tPhone(+60)   : " << row[5] << endl;
        }
        else {
            cout << "\t\t\t\t\t\t\t\tNo account information found." << endl; // Error message for user
        }
    }
    else {
        cout << "\t\t\t\t\t\t\t\tDatabase Query Failed: " << mysql_error(conn) << endl; // Handle query failure
    }

    // Add menu options for additional functionality
    cout << "\n\t\t\t\t\t\t*****************************************************************************" << endl;
    cout << "\t\t\t\t\t\t\t\t\t1. Update My Profile" << endl;
    cout << "\t\t\t\t\t\t\t\t\t2. Back" << endl;
    cout << "\t\t\t\t\t\t\t\tOption: ";
    cin >> menu;

    switch (menu) {
    case 1: {
        cout << "\n\t\t\t\t\t\t\t\tEnter New Name: ";
        cin.ignore();
        getline(cin, newName);
        cout << "\t\t\t\t\t\t\t\tEnter New Age: ";
        cin >> newAge;
        cin.ignore();
        cout << "\t\t\t\t\t\t\t\tEnter New Email: ";
        getline(cin, newEmail);

        // Check email uniqueness
        bool isEmailUnique = false;
        while (!isEmailUnique) {
            string checkEmailQuery = "SELECT * FROM User WHERE Email = '" + newEmail + "' AND Username != '" + currentUser + "';";
            qstate = mysql_query(conn, checkEmailQuery.c_str());
            if (!qstate && mysql_store_result(conn)->row_count > 0) {
                cout << "\t\t\t\t\t\t\tError: Email is already in use. Please enter a different email." << endl;
                cout << "\t\t\t\t\t\t\t\tEnter New Email: ";
                getline(cin, newEmail);
            }
            else {
                isEmailUnique = true; // Email is unique, break out of the loop
            }
        }

        cout << "\t\t\t\t\t\t\t\tEnter New Contact: ";
        getline(cin, newContact);

        // Check contact uniqueness
        bool isContactUnique = false;
        while (!isContactUnique) {
            string checkContactQuery = "SELECT * FROM User WHERE Contact = '" + newContact + "' AND Username != '" + currentUser + "';";
            qstate = mysql_query(conn, checkContactQuery.c_str());
            if (!qstate && mysql_store_result(conn)->row_count > 0) {
                cout << "\t\t\t\t\t\t\tError: Contact number is already in use. Please enter a different contact." << endl;
                cout << "\t\t\t\t\t\t\t\tEnter New Contact: ";
                getline(cin, newContact);
            }
            else {
                isContactUnique = true; // Contact is unique, break out of the loop
            }
        }

        cout << "\t\t\t\t\t\t\t\tEnter New Password: ";
        getline(cin, newPassword);

        // Prompt for confirmation
        char confirm;
        bool validInput = false; //Falg to check if input is valid

        while (!validInput) { //Loop to keep asking for a valid input
            cout << "\n\t\t\t\t\t\t\t\tConfirm to save changes? (Y/N): ";
            cin >> confirm;

            if (confirm == 'Y' || confirm == 'y') { //Check if a valid input to save changes
                validInput = true; //Exit loop after valid input
                // Update profile information in the database
                string updateProfileQuery = "UPDATE User SET Name = '" + newName + "', Age = " + to_string(newAge) +
                    ", Email = '" + newEmail + "', Contact = '" + newContact +
                    "', Password = '" + newPassword + "' WHERE Username = '" + currentUser + "';";
                qstate = mysql_query(conn, updateProfileQuery.c_str()); //Execute the update profile query
                if (!qstate) {
                    cout << "\t\t\t\t\t\t\t\t\tProfile updated successfully!" << endl; // Check if the query was successful
                }
                else {
                    cout << "\t\t\t\t\t\t\t\t\tError updating profile: " << mysql_error(conn) << endl; // Prompt error message for failed query
                }
            }
            else if (confirm == 'N' || confirm == 'n') { //Check if a valid input to discard changes
                validInput = true; //Exit loop after valid input
                cout << "\t\t\t\t\t\t\t\t\tChanges discarded..." << endl;
            }
            else {
                cout << "\t\t\t\t\t\t\t\tInvalid input. Please enter (Y/N)." << endl; // If input not valid, prompt try again 
            }
        }
        system("cls");// Clear screen and 
        myProfile();  // return to the My Profile page
        _getch();
        break;
    }
    case 2:
        userMainMenu(); // Go back to the main menu
        break;

    default:
        // Handle invalid menu input
        cout << "\t\t\t\t\t\t\tPlease choose between 1 - 2. Press Enter To Try Again...";
        _getch();      // Pause the program until a key is pressed
        system("cls"); // Clear the console screen
        myProfile(); // Return to My Profile page if an invalid option is selected
        break;
    }
}

//User function: Give A Feedback
void giveAFeedback() {
    
    string option;
    string userid, svenueCode, comment, rating;
    

        system("cls");
        cout << "\n\t\t\t\t\t\t*****************************************************************************" << endl;
        cout << "\t\t\t\t\t\t\t\t\tYOUR FEEDBACK IS VALUEABLE" << endl;
        cout << "\t\t\t\t\t\t*****************************************************************************" << endl;
        cout << "\n\t\t\t\t\t\t\t\t\tCode:             Sport Venue :                 " << endl;
        cout << "\t\t\t\t\t\t\t\t\tBC                Badminton Court              " << endl;
        cout << "\t\t\t\t\t\t\t\t\tPPC               Ping Pong Court              " << endl;
        cout << "\t\t\t\t\t\t\t\t\tPBC               Pickle Ball Court            " << endl;
        cout << "\t\t\t\t\t\t\t\t\tFS                Futsal Court\n               " << endl;
        
        // Ask if the user wants to give feedback
        while (true) {
            cout << "\t\t\t\t\t\t\t\tDo you want to give feedback? (Y/N): ";
            cin >> option;
            if (option == "Y" || option == "y") {          //Allows user input Y or y for Yes
                break;                                     // Continue to collect feedback
            }
            else if (option == "N" || option == "n") {     //Allows user input N or n for No
                userMainMenu(); // Return to the user main menu if No
                return;
            }
            else {
                cout << "\t\t\t\t\t\t\t\tInvalid input! Please enter Y/y or N/n only." << endl; //Prompt error message to user when invalid input    
            }
        }

        // Input sport venue code
        cout << "\t\t\t\t\t\t\t\tEnter a Code(e.g.BC): ";
        cin >> svenueCode;
        cin.ignore(); // Clear input buffer

        // Validate the facility code
        while (svenueCode != "BC" && svenueCode != "PBC" && svenueCode != "PPC" && svenueCode != "FS") {
            // If the input is not valid, prompt the user for a valid input
            cout << "\t\t\t\t\t\t\t\tInvalid input! Ensure your input match the criteria: ";
            cin >> svenueCode;
            cin.ignore(); // Clear input buffer
        }

        // Input comment
        cout << "\t\t\t\t\t\t\t\tEnter your comments: ";
        getline(cin, comment); // Use getline to handle multi-word input

        // Input rating (1-5)
        do {
            cout << "\t\t\t\t\t\t\t\tEnter rating (1-5): ";
            cin >> rating;
            //Check input validation
            if (rating < "1" || rating > "5") { 
                cout << "\t\t\t\t\t\t\t\tInvalid rating! Please enter a value between 1 and 5." << endl;
            }
        }while (rating < "1" || rating > "5");

        // Query to get UserID from the current user
        string userIDQuery = "SELECT UserID FROM User WHERE Username = '" + currentUser + "'";
        mysql_query(conn, userIDQuery.c_str());
        MYSQL_RES* result = mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(result);
        string userID = row[0];  // Get UserID from the result

        // Check if UserID is valid
        if (userID.empty()) {
            cout << "\t\t\t\t\t\t\t\tError: User not found!" << endl;
            return;
        }

        // Insert feedback into the database
        string Feedbackquery = "INSERT INTO Feedback (UserID, SVenue_code, Comments, Rating, Feedback_date) VALUES (" +
            userID + ", '" + svenueCode + "', '" + comment + "', '" + rating + "', NOW())"; // Now() is used for save current feedback date and time
        
        qstate = mysql_query(conn, Feedbackquery.c_str());

        if (!qstate) {
            // Feedback saved successfully
            cout << "\n\t\t\t\t\t\t\t\tFeedback saved! Thank you." << endl;
        }
        else {
            // Error occurred
            cout << "\t\t\t\t\t\t\t\tFailed to save feedback. Error: " << mysql_error(conn) << endl;
        }

        // Return to User Main Menu
        cout << "\t\t\t\t\t\t\t\tPress (Enter) to return to the User Main Menu...";
        _getch(); //Pause to allow user can read the message
        userMainMenu(); 
}

//Admin Login page
void adminLogin() {
    string username, password;
    int attemptCount = 0;
    const int maxAttempts = 3; //Maximum number of attempts 
    
    system("cls");// Clears the console screen for a clean display of the login prompt
    cout << "\n\t\t\t\t\t\t*****************************************************************************" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\tADMIN LOGIN" << endl;
    cout << "\t\t\t\t\t\t*****************************************************************************\n" << endl;

    while (attemptCount < maxAttempts) {
        //Input admin username
        cout << "\t\t\t\t\t\tEnter your Username: ";
        cin >> username;

        //Input admin password
        password.clear(); //Password masking
        cout << "\t\t\t\t\t\tEnter your Password: ";
        char ch;
        while ((ch = _getch()) != '\r') {   // '\r' is the Enter key. Use _getch() to read admin input character by character, rather than directly using cin.
            if (ch == '\b') {               //Handle backspace. Indicates that the admin pressed the Backspace key and needs to delete the last character.
                if (!password.empty()) {
                    password.pop_back();
                    cout << "\b \b";        //Move cursor back, overwrite with space, move back again.
                }
            }
            else {
                password += ch;
                cout << "*"; //Display masking symbol.
            }
        }
        cout << endl;

        // Check the admin_username and admin_password 
        string query = "SELECT * FROM Admin WHERE admin_username = '" + username + "' AND admin_password = '" + password + "';";
        qstate = mysql_query(conn, query.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);
            if (mysql_num_rows(res) > 0) {
                // Admin login successful
                cout << "\n\t\t\t\t\t\tLogin Successful! Redirecting to Admin Main Menu..." << endl;
                _getch();
                adminMainMenu(); // Navigate to admin main menu

            }
            else {
                cout << "\n\t\t\t\t\t\tInvalid username or password. Please try again.\n" << endl;
                attemptCount++;
            }
        }
        else {
            cout << "\n\t\t\t\t\t\tDatabase Query Failed: " << mysql_error(conn) << endl;
            return;
        }

        if (attemptCount >= maxAttempts) {
            cout << "\t\t\t\t\t\t\t\tToo many failed attempts!!!Please try again later." << endl;
            _getch();
            main(); //If the number of attempts is exceeded, display error message and return to the login page
        }
    }
}

//Admin main menu 
void adminMainMenu() {
    int adminmenu;
    while (true) {
        
        system("cls");
        cout << "\n\t\t\t\t\t\t*****************************************************************************" << endl;
        cout << "\t\t\t\t\t\t\t\t\t  WELCOME BACK,ADMIN!" << endl;
        cout << "\t\t\t\t\t\t\t\t\t    ADMIN MAIN MENU     " << endl;
        cout << "\t\t\t\t\t\t*****************************************************************************\n" << endl;
        cout << "\t\t\t\t\t\t\t\t\t1. Facility Management" << endl;
        cout << "\t\t\t\t\t\t\t\t\t2. Payment Update Management" << endl;
        cout << "\t\t\t\t\t\t\t\t\t3. View All Reservation Records" << endl;
        cout << "\t\t\t\t\t\t\t\t\t4. View Feedbacks" << endl;
        cout << "\t\t\t\t\t\t\t\t\t5. Search User" << endl;
        cout << "\t\t\t\t\t\t\t\t\t6. Reservation Report" << endl;
        cout << "\t\t\t\t\t\t\t\t\t7. Logout" << endl;
        cout << "\t\t\t\t\t\t\t\tOption: ";
        cin >> adminmenu;

        switch (adminmenu) {
        case 1:
            // Call a function to manage facilities
            facilityManagement();
            _getch();
            break;
        case 2:
            // Call a function to 
            updatePaymentStatus();
            _getch();
            break;
        case 3:
            // Call a function to view all reservation records
            viewAllReservation();
            _getch();
            break;
        case 4:
            // Call a function to view feedback
            viewFeedback();
            _getch();
            break;
        case 5:
            // Call a function to search for user
            searchUser();
            _getch();
            break;
        case 6:
            // Call a function to view feedback
            reservationReport();
            _getch();
            break;
        case 7:
            cout << "\t\t\t\t\t\t\tLogging out... Returning to login page." << endl;
            _getch(); //Pause allow user to read the message
            main();   // Return to the main menu (login page)
            return;
        default:
            cout << "\t\t\t\t\t\t\tInvalid option. Please choose between 1-7." << endl;
            _getch();
            break;
        }
    }
}

//Admin function 1: Facility Management System
int facilityManagement() {
    int sportvenuemenu;

    system("cls");
    cout << "\n\t\t\t\t\t\t*****************************************************************************" << endl;
    cout << "\t\t\t\t\t\t\t\t\t FACILITY MANAGEMENT SYSTEM" << endl;
    cout << "\t\t\t\t\t\t*****************************************************************************\n" << endl;
    cout << "\t\t\t\t\t\t\t\t\t1. Add New Facility " << endl;
    cout << "\t\t\t\t\t\t\t\t\t2. Update Facility " << endl;
    cout << "\t\t\t\t\t\t\t\t\t3. Delete Facility " << endl;
    cout << "\t\t\t\t\t\t\t\t\t4. Back" << endl;
    cout << "\t\t\t\t\t\t\t\tOption: ";
    cin >> sportvenuemenu;

    switch (sportvenuemenu) {
    case 1:
        //call add sport venue function
        addFacility();
        _getch();
        break;
    case 2:
        //call update sport venue function
        updateFacility();
        _getch();
        break;
    case 3:
        //call delete sport venue function
        deleteFacility();
        _getch();
        break;
    case 4:
        //call back to admin main menu function
        adminMainMenu();
        break;
    default:
        cout << "\t\t\t\t\t\t\t\t\tInvalid option. Please choose between 1-4." << endl;
        _getch(); //Pause allow user to read error message
        system("cls"); //Clear console screen for a fresh display
        facilityManagement();// Remain on the page
        break;
    } return 0;
}

// Sub menu 1: Add New Facility
void addFacility() {
    string facilityCode, courtName, status;
    double pricePerHour;
    char repeat;
    int statusChoice;

    do {
        system("cls");
        cout << "\n\t\t\t\t\t\t*****************************************************************************" << endl;
        cout << "\t\t\t\t\t\t\t\t\t    ADD NEW FACILITY COURT" << endl;
        cout << "\t\t\t\t\t\t*****************************************************************************\n" << endl;

        cout << "\t\t\t\t\t\t\t\tEnter Facility Code (e.g., BC): ";
        cin >> facilityCode;
        cout << "\t\t\t\t\t\t\t\tEnter Court Name (e.g., BC01): ";
        cin >> courtName;
        cout << "\t\t\t\t\t\t\t\tEnter Price per Hour (RM): ";
        cin >> pricePerHour;

        // Select Status
        do {
            cout << "\t\t\t\t\t\t\t\t1. Available\t\t2. Unavailable" << endl;
            cout << "\t\t\t\t\t\t\t\tEnter the status of the facility: ";
            cin >> statusChoice;

            switch (statusChoice) {
            case 1:
                status = "Available";
                break;
            case 2:
                status = "Unavailable";
                break;
            default:
                cout << "\t\t\t\t\t\t\t\tInvalid input! Please choose 1 or 2 only." << endl;
            }
        } while (statusChoice != 1 && statusChoice != 2);

        string newFacilityquery = "INSERT INTO Facility (Facility_code, Court_name, Status, Price_per_hour) "
            "VALUES ('" + facilityCode + "', '" + courtName + "', '" + status + "', " + to_string(pricePerHour) + ");";

        if (mysql_query(conn, newFacilityquery.c_str())) {
            cerr << "\t\t\t\t\t\t\t\tError adding new facility: " << mysql_error(conn) << endl;
        }
        else {
            cout << "\t\t\t\t\t\t\t\tFacility added successfully!" << endl;
        }

        cout << "\t\t\t\t\t\t\t\tDo you want to add another facility? (Y/N): ";
        cin >> repeat;
    } while (repeat == 'Y' || repeat == 'y');

    facilityManagement(); // Return to Facility Management menu
}

// Sub menu 2: Update Facility
void updateFacility() {
    string courtName, newStatus;
    double newPricePerHour;
    char repeat;
    int statusChoice;

    do {
        system("cls");
        cout << "\n\t\t\t\t\t\t*****************************************************************************" << endl;
        cout << "\t\t\t\t\t\t\t\t\t    UPDATE FACILITY " << endl;
        cout << "\t\t\t\t\t\t*****************************************************************************\n" << endl;

        cout << "\t\t\t\t\t\t\t\tEnter Court Name to Update (e.g., BC01): ";
        cin >> courtName;

        cout << "\t\t\t\t\t\t\t\tEnter New Price per Hour (RM): ";
        cin >> newPricePerHour;

        // Select New Status
        do {
            cout << "\t\t\t\t\t\t\t\t1. Available\t\t2. Unavailable" << endl;
            cout << "\t\t\t\t\t\t\t\tEnter the new status of the facility: ";
            cin >> statusChoice;

            switch (statusChoice) {
            case 1:
                newStatus = "Available";
                break;
            case 2:
                newStatus = "Unavailable";
                break;
            default:
                cout << "\t\t\t\t\t\t\t\tInvalid input! Please choose 1 or 2 only." << endl;
            }
        } while (statusChoice != 1 && statusChoice != 2);

        string updateFacilityquery = "UPDATE Facility SET Price_per_hour = " + to_string(newPricePerHour) +
            ", Status = '" + newStatus + "' WHERE Court_name = '" + courtName + "';";

        if (mysql_query(conn, updateFacilityquery.c_str())) {
            cerr << "\t\t\t\t\t\t\t\tError updating facility: " << mysql_error(conn) << endl;
        }
        else {
            cout << "\t\t\t\t\t\t\t\tFacility updated successfully!" << endl;
        }

        cout << "\t\t\t\t\t\t\t\tDo you want to update another facility? (Y/N): ";
        cin >> repeat;
    } while (repeat == 'Y' || repeat == 'y');

    facilityManagement(); // Return to Facility Management menu
}

// Sub menu 3: Delete Facility
void deleteFacility() {
    string courtName;
    char confirm, repeat;

    do {
        system("cls");
        cout << "\n\t\t\t\t\t\t*****************************************************************************" << endl;
        cout << "\t\t\t\t\t\t\t\t\t   DELETE FACILITY " << endl;
        cout << "\t\t\t\t\t\t*****************************************************************************\n" << endl;

        cout << "\t\t\t\t\t\t\t\tEnter Court Name to Delete (e.g., BC01): ";
        cin >> courtName;

        // Fetch facility details for confirmation
        string fetchQuery = "SELECT * FROM Facility WHERE Court_name = '" + courtName + "';";
        if (mysql_query(conn, fetchQuery.c_str())) {
            cerr << "\t\t\t\t\t\t\t\tError fetching facility details: " << mysql_error(conn) << endl;
            return;
        }

        MYSQL_RES* result = mysql_store_result(conn);
        if (mysql_num_rows(result) == 0) {
            cout << "\t\t\t\t\t\t\t\t\tNo facility found with the specified court name!" << endl;
            mysql_free_result(result);
        }
        else {
            MYSQL_ROW row = mysql_fetch_row(result);
            cout << "\t\t\t\t\t\t\t\tFacility Details:" << endl;
            cout << "\t\t\t\t\t\t\t\t  Facility Code: " << row[1] << endl;
            cout << "\t\t\t\t\t\t\t\t  Court Name: " << row[2] << endl;
            cout << "\t\t\t\t\t\t\t\t  Status: " << row[3] << endl;
            cout << "\t\t\t\t\t\t\t\t  Price per Hour: RM " << row[4] << endl;
            mysql_free_result(result);

            // Ask for confirmation
            cout << "\n\t\t\t\t\t\t\t\tDo you confirm to Delete this facility? (Y/N): ";
            cin >> confirm;

            if (confirm == 'Y' || confirm == 'y') {
                string deleteQuery = "DELETE FROM Facility WHERE Court_name = '" + courtName + "';";
                if (mysql_query(conn, deleteQuery.c_str())) {
                    cerr << "\t\t\t\t\t\t\t\tError deleting facility: " << mysql_error(conn) << endl;
                }
                else {
                    cout << "\t\t\t\t\t\t\t\tFacility deleted successfully!" << endl;
                }
            }
            else {
                cout << "\t\t\t\t\t\t\t\tDeletion canceled." << endl;
            }
        }

        cout << "\n\t\t\t\t\t\t\t\tDo you want to delete another facility? (Y/N): ";
        cin >> repeat;
    } while (repeat == 'Y' || repeat == 'y');

    facilityManagement(); // Return to Facility Management menu
}

// Admin function 2: Payment Management
void updatePaymentStatus() {
    int reserveID, payChoice;
    string paymentMethod, confirm;

    while (true) {
        // Display header
        system("cls");
        cout << "\n\t\t\t\t\t\t*****************************************************************************" << endl;
        cout << "\t\t\t\t\t\t\t\t\t UPDATE PAYMENT STATUS " << endl;
        cout << "\t\t\t\t\t\t*****************************************************************************\n" << endl;

        // Step 1: Enter Reservation ID
        cout << "\t\t\t\t\t\t\t\t\tEnter Reservation ID: ";
        cin >> reserveID;

        // Fetch payment details from the database
        string displayPaymentquery = "SELECT p.Payment_status, p.Payment_amount, r.Booking_date, f.Court_name, p.Payment_method "
            "FROM Payment p "
            "JOIN Reservation r ON p.ReserveID = r.ReserveID "
            "JOIN Facility f ON r.FaciID = f.FaciID "
            "WHERE p.ReserveID = " + to_string(reserveID) + ";";

        if (mysql_query(conn, displayPaymentquery.c_str())) {
            cerr << "\t\t\t\t\t\t\t\t\tError fetching payment details: " << mysql_error(conn) << endl;
            return;
        }

        MYSQL_RES* result = mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(result);

        if (!row) {
            cout << "\t\t\t\t\t\t\t\t\tNo payment record found for Reservation ID: " << reserveID << endl;
            mysql_free_result(result);
            
            // Prompt retry
            while (true) {
                cout << "\t\t\t\t\t\t\t\tYou want re-enter? (Y/N): ";
                cin >> confirm;
                if (confirm == "Y" || confirm == "y" || confirm == "N" || confirm == "n") {
                    break;
                }
                else {
                    cout << "\t\t\t\t\t\t\t\tInvalid input! Please enter Y/N: " << endl;
                }
            }

            if (confirm != "Y" && confirm != "y") {
                cout << "\t\t\t\t\t\t\t\tReturning to admin menu..." << endl;
                break;
            }
            continue;
        }

        string currentStatus = row[0]; //show current payment status ('paid' or 'unpaid')
        double amount = stod(row[1]);
        string bookingDate = row[2];
        string courtName = row[3];
        string currentMethod = row[4]; //show current payment method in case any change made
        mysql_free_result(result);
        // Display current payment details
        cout << "\n\t\t\t\t\t\t*****************************************************************************" << endl;
        cout << "\t\t\t\t\t\t\t\t\tReservation Details:" << endl;
        cout << "\t\t\t\t\t\t\t\t\t  Court Name      : " << courtName << endl;
        cout << "\t\t\t\t\t\t\t\t\t  Booking Date    : " << bookingDate << endl;
        cout << "\t\t\t\t\t\t\t\t\t  Payment Status  : " << currentStatus << endl;
        cout << "\t\t\t\t\t\t\t\t\t  Payment Amount  : RM " << amount << endl;
        cout << "\t\t\t\t\t\t\t\t\t  Payment Method  : " << (currentMethod.empty() ? "N/A" : currentMethod) << endl;
        cout << "\t\t\t\t\t\t*****************************************************************************\n" << endl;

        // Check if already paid
        if (currentStatus == "Paid") {
            cout << "\t\t\t\t\t\t\tThe payment is already marked as 'Paid'. No update needed." << endl;
        }
        else {
            // Step 2: Select Payment Method (in case any transaction part is not working, allow user to make payment by cash)
            do {
                cout << "\t\t\t\t\t\t\t\t\t1. Cash\t\t2. Online Transfer" << endl;
                cout << "\t\t\t\t\t\t\t\t\tEnter your payment method: ";
                cin >> payChoice;
                //Reset or remain payment method, provide flexibility to user when something happened
                switch (payChoice) {
                case 1:
                    paymentMethod = "Cash";
                    break;
                case 2:
                    paymentMethod = "Online Transfer";
                    break;
                default:
                    cout << "\t\t\t\t\t\t\t\t\tInvalid input! Please choose 1 or 2 only." << endl;
                }
            } while (payChoice != 1 && payChoice != 2);

            // Step 3: Confirm Update
            cout << "\t\t\t\t\t\t\tConfirm update payment status to 'Paid'? (Y/N): ";
            cin >> confirm;

            if (confirm == "Y" || confirm == "y") {
                // Update payment status in the database
                string updatePaymentQuery = "UPDATE Payment SET Payment_method = '" + paymentMethod + "', Payment_status = 'Paid' "
                    "WHERE ReserveID = " + to_string(reserveID) + ";";

                if (mysql_query(conn, updatePaymentQuery.c_str())) {
                    cerr << "\t\t\t\t\t\t\t\t\tError updating payment status: " << mysql_error(conn) << endl;
                    return;
                }

                cout << "\n\t\t\t\t\t\t\t\t\tPayment status updated successfully!" << endl;
            }
            else {
                cout << "\t\t\t\t\t\t\t\t\tPayment status update canceled." << endl;
            }
        }

        // Step 4: Ask admin if they want to update another payment
        while (true) {
            cout << "\n\t\t\t\t\t\tDo you want to update another payment? (Y/N): ";
            cin >> confirm;

            if (confirm == "Y" || confirm == "y" || confirm == "N" || confirm == "n") {
                break;
            }
            else {
                cout << "\t\t\t\t\t\tInvalid input! Please enter Y/N: " << endl;
            }
        }

        if (confirm == "N" || confirm == "n") {
            cout << "\t\t\t\t\t\t\t\tReturning to admin menu..." << endl;
            break;
        }
    }
}

//Admin function 3: View all reservation records
void viewAllReservation() {
    int year, month;
    char repeat;

    do {
        system("cls");
        cout << "\n\t\t\t\t******************************************************************************************************" << endl;
        cout << "\t\t\t\t\t\t\t\tVIEW ALL RESERVATION BY FACILITY " << endl;
        cout << "\t\t\t\t******************************************************************************************************\n" << endl;

        // Input year and month
        cout << "\t\t\t\t\t\t\tEnter the year (YYYY): ";
        cin >> year;
        cout << "\t\t\t\t\t\t\tEnter the month (MM): ";
        cin >> month;

        // Validate inputs
        if (year < 2000 || month < 1 || month > 12) {
            cout << "\t\t\t\t\t\t\t\t\tInvalid year or month! Please enter a valid year (>=2000) and month (1-12)." << endl;
            system("pause");
            continue;
        }

        // Fetch all facility codes
        string facilityQuery = "SELECT DISTINCT Facility_code FROM Facility ORDER BY Facility_code;";
        if (mysql_query(conn, facilityQuery.c_str())) {
            cerr << "\t\t\t\t\t\t\t\t\tError fetching facilities: " << mysql_error(conn) << endl;
            return;
        }

        MYSQL_RES* facilityResult = mysql_store_result(conn);
        if (facilityResult == nullptr) {
            cerr << "\t\t\t\t\t\t\t\t\tError processing facility query result: " << mysql_error(conn) << endl;
            return;
        }

        MYSQL_ROW facilityRow;

        // Loop through each facility
        while ((facilityRow = mysql_fetch_row(facilityResult))) {
            string facilityCode = facilityRow[0];

            // Query bookings for the current facility and specified month/year
            string bookingQuery =
                "SELECT r.ReserveID, f.Court_name, r.Booking_date, r.Start_time, r.End_time, r.Duration, "
                "p.Payment_status, p.Payment_amount "
                "FROM Reservation r "
                "JOIN Facility f ON r.FaciID = f.FaciID "
                "JOIN Payment p ON r.ReserveID = p.ReserveID "
                "WHERE f.Facility_code = '" + facilityCode + "' "
                "AND YEAR(r.Booking_date) = " + to_string(year) + " "
                "AND MONTH(r.Booking_date) = " + to_string(month) + " "
                "ORDER BY r.Booking_date, r.Start_time;";

            if (mysql_query(conn, bookingQuery.c_str())) {
                cerr << "\t\t\t\t\t\t\t\t\tError fetching booking data for " << facilityCode << ": " << mysql_error(conn) << endl;
                continue;
            }

            MYSQL_RES* bookingResult = mysql_store_result(conn);
            if (bookingResult == nullptr) {
                cerr << "\t\t\t\t\t\t\t\t\tError processing booking query result: " << mysql_error(conn) << endl;
                continue;
            }

            MYSQL_ROW bookingRow;

            // Display header for the facility
            cout << "\n\t\t\t\t******************************************************************************************************" << endl;
            cout << "\t\t\t\tFACILITY: " << facilityCode << " (" << year << "-" << (month < 10 ? "0" : "") << month << ")" << endl;
            cout << "\t\t\t\t******************************************************************************************************" << endl;
            cout << "\t\t\t\tReserveID | Court_Name | Booking_date | Start_time | End_time | Duration | Payment_status |Amount(RM)" << endl;
            cout << "\t\t\t\t------------------------------------------------------------------------------------------------------" << endl;

            // Display bookings for the facilities
            bool hasBookings = false;
            while ((bookingRow = mysql_fetch_row(bookingResult))) {
                hasBookings = true;
                cout << "\t\t\t\t     " << bookingRow[0] //ReserveID 
                     << "\t  " << bookingRow[1]  // Court name
                     << "\t  " << bookingRow[2]  // Booking date
                     << "\t " << bookingRow[3]  // Start time
                     << "   " << bookingRow[4] // End time
                     << "    " << bookingRow[5] << " hour(s)"  // Duration 
                     << "\t" << bookingRow[6] // Payment status
                    << "\t    "  << bookingRow[7] << endl;  // Amount
            }

            if (!hasBookings) {
                cout << "\t\t\t\t\t\t\tNo bookings found for this facility in the specified month.\n";
            }

            mysql_free_result(bookingResult);
        }

        mysql_free_result(facilityResult);

        // Ask admin if they want to view another month
        cout << "\n\t\t\t\t\t\t\tDo you want to view bookings for another month? (Y/N): ";
        cin >> repeat;

    } while (repeat == 'Y' || repeat == 'y');

    adminMainMenu(); // Return to admin main menu
}

//Admin function 4: View Feedback
void viewFeedback() {
    string svCode, feedbackDate;
    char choice;

    do {
        system("cls");
        cout << "\n\t\t\t\t\t\t*****************************************************************************" << endl;
        cout << "\t\t\t\t\t\t\t\t\t  LISTEN FROM CUSTOMER " << endl;
        cout << "\t\t\t\t\t\t\t\t\t\tFEEDBACKS " << endl;
        cout << "\t\t\t\t\t\t*****************************************************************************\n" << endl;
        cout << "\t\t\t\t\t\t\t\tCode:           Facility Name :    " << endl;
        cout << "\t\t\t\t\t\t\t\t BC              Badminton Court    " << endl;
        cout << "\t\t\t\t\t\t\t\t PPC             Ping Pong Court    " << endl;
        cout << "\t\t\t\t\t\t\t\t PBC             Pickle Ball Court  " << endl;
        cout << "\t\t\t\t\t\t\t\t FS              Futsal Court\n     " << endl;

        // Prompt the admin to enter a sport venue code
        cout << "\t\t\t\t\t\t\tEnter Code: ";
        cin >> svCode;
        cin.ignore(); // Clear the input buffer

        // Prompt the admin to enter the feedback date (in MM/YYYY format)
        cout << "\t\t\t\t\t\t\tEnter feedback date (YYYY/MM): ";
        getline(cin, feedbackDate);

        // Prepared query to filter by sport venue and date
        string viewFeedbackQuery = "SELECT UserID, SVenue_code, Rating, Comments, Feedback_date "
            "FROM Feedback "
            "WHERE SVenue_code = '" + svCode + "' "
            "AND DATE_FORMAT(Feedback_date, '%Y/%m') = '" + feedbackDate + "';";

        // Execute the query
        if (mysql_query(conn, viewFeedbackQuery.c_str())) {
            cout << "\t\t\t\t\t\t\tMySQL query failed: " << mysql_error(conn) << endl;
            return;
        }

        // Store the result
        res = mysql_store_result(conn);
        if (res == NULL) {
            cout << "\t\t\t\t\t\t\tFailed to retrieve feedback." << endl;
            return;
        }

        // Display each feedback record
        bool feedbackFound = false;
        cout << "\t\t\t\t\t\t\t------------------------------------------------------" << endl;
        while ((row = mysql_fetch_row(res))) {
            feedbackFound = true;
            cout << "\t\t\t\t\t\t\tUser ID: " << row[0] << endl;
            cout << "\t\t\t\t\t\t\tSport Venue Code: " << row[1] << endl;
            cout << "\t\t\t\t\t\t\tRating: " << row[2] << endl;
            cout << "\t\t\t\t\t\t\tComments: " << row[3] << endl;
            cout << "\t\t\t\t\t\t\tFeedback Date: " << row[4] << endl;
            cout << "\t\t\t\t\t\t\t------------------------------------------------------" << endl;
        }

        // If no feedback was found
        if (!feedbackFound) {
            cout << "\t\t\t\t\t\t\tNo feedback records found for " << svCode << " on " << feedbackDate << "." << endl;
        }

        // Free the result set
        mysql_free_result(res);

        // Ask if the admin wants to view other feedback
        bool validInput = false;
        while (!validInput) {
            cout << "\n\t\t\t\t\t\t\tDo you want to view other feedback? (Y/y or N/n): ";
            cin >> choice;

            if (choice == 'Y' || choice == 'y' || choice == 'N' || choice == 'n') {
                validInput = true;  // Valid input
            }
            else {
                cout << "\t\t\t\t\t\t\tInvalid input! Please enter Y/N: ";
            }
        }

    } while (choice == 'Y' || choice == 'y');

    // Return to the admin main menu
    cout << "\n\t\t\t\t\t\t\tPress (Enter) to return to Admin Main Menu...";
    cin.ignore();
    cin.get();  // Pause to allow user to read the message
    adminMainMenu();  // Return to the Admin Main Menu
}

//Admin function 5: Search User
void searchUser() {
 
    string searchCriteria, searchValue, query;
    char continueSearch;

    system("cls");
    cout << "\n\t\t\t\t\t\t*****************************************************************************" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\tSEARCH FOR USER                    " << endl;
    cout << "\t\t\t\t\t\t*****************************************************************************\n" << endl;

    // Start of the loop to allow multiple searches
    do {
        // Ask the admin what they want to search by (Name, Email, or Contact)
        cout << "\t\t\t\t\t\t\tSearch by: (1) Name (2) Email (3) Contact: ";
        cin >> searchCriteria;
        cin.ignore();  // Clear the input buffer to avoid reading unwanted characters

        // Validate search criteria input
        if (searchCriteria != "1" && searchCriteria != "2" && searchCriteria != "3") {
            cout << "\t\t\t\t\t\t\tInvalid input! Please enter a valid option." << endl;
            continue;  // Prompt the user again
        }

        // Ask for the value to search for
        cout << "\t\t\t\t\t\t\tEnter the value to search for: ";
        getline(cin, searchValue); // Use getline to allow multi-word input

        // Validate search value input (it should not be empty)
        if (searchValue.empty()) {
            cout << "\t\t\t\t\t\t\tError: You must enter a value to search for!" << endl;
            continue;  // Prompt the user again
        }

        // Construct SQL query based on search criteria
        if (searchCriteria == "1") {
            query = "SELECT UserID,Name, Gender, Email,Contact FROM User WHERE Name LIKE '%" + searchValue + "%';";
        }
        else if (searchCriteria == "2") {
            query = "SELECT UserID,Name, Gender, Email,Contact FROM User WHERE Email LIKE '%" + searchValue + "%';";
        }
        else if (searchCriteria == "3") {
            query = "SELECT UserID,Name, Gender, Email,Contact FROM User WHERE Contact LIKE '%" + searchValue + "%';";
        }

        // Execute the query
        if (mysql_query(conn, query.c_str())) {
            cout << "\t\t\t\t\t\t\tMySQL query failed: " << mysql_error(conn) << endl;
            continue;  // If the query fails, continue the loop
        }

        // Get the result of the query
        res = mysql_store_result(conn);
        if (res == NULL) {
            cout << "\t\t\t\t\t\t\tFailed to retrieve results. Query error: " << mysql_error(conn) << endl;
            continue;  // If the query fails to return results, continue the loop
        }

        // Display the results
        bool userFound = false;
            cout << "\t\t\t\t\t\t\t------------------------------------------------------" << endl;
        while ((row = mysql_fetch_row(res))) {
            userFound = true;
            cout << "\t\t\t\t\t\t\tUser ID: " << row[0] << endl;
            cout << "\t\t\t\t\t\t\tName: " << row[1] << endl;
            cout << "\t\t\t\t\t\t\tGender: " << row[2] << endl;
            cout << "\t\t\t\t\t\t\tEmail: " << row[3] << endl;
            cout << "\t\t\t\t\t\t\tContact: " << row[4] << endl;  // Display the correct field for Contact (e.g., phone number)
            cout << "\t\t\t\t\t\t\t------------------------------------------------------" << endl;
        }

        // If no results were found
        if (!userFound) {
            cout << "\t\t\t\t\t\t\tNo user found with the given criteria." << endl;
        }
        mysql_free_result(res);  // Free the result set

        // Ask the admin if they want to search for another user
        cout << "\t\t\t\t\t\t\tDo you want to search for another criteria? (Y/y or N/n): ";
        cin >> continueSearch;
        cin.ignore();  // Clear the input buffer

        // Validate the continuation input
        if (continueSearch != 'Y' && continueSearch != 'y' && continueSearch != 'N' && continueSearch != 'n') {
            cout << "\t\t\t\t\t\t\tInvalid input! Please enter Y/y to continue or N/n to exit." << endl;
            continue;  // If the input is invalid, prompt again
        }

    } while (continueSearch == 'Y' || continueSearch == 'y');  // If 'Y' or 'y' is entered, continue searching

    // Return to the admin main menu after finishing the search
    cout << "\n\t\t\t\t\t\t\tPress (Enter) to return to Admin Main Menu...";
    _getch();  // Pause to allow user to read the message
    adminMainMenu();  // Return to the Admin Main Menu
}

//Admin function 6: Reservation income analysis
void reservationReport() {
    int year, month;
    char repeat;

    do {
        system("cls"); //Display header
        cout << "\n\t\t\t\t\t\t*****************************************************************************" << endl;
        cout << "\t\t\t\t\t\t\t\t\t RESERVATION REPORT " << endl;
        cout << "\t\t\t\t\t\t*****************************************************************************\n" << endl;

        // Get year and month input from admin
        cout << "\t\t\t\t\t\t\t\tEnter the year (YYYY): ";
        cin >> year;
        cout << "\t\t\t\t\t\t\t\tEnter the month (MM): ";
        cin >> month;

        // Validate year and month input
        if (year < 2000 || month < 1 || month > 12) {
            cout << "\t\t\t\t\t\t\tInvalid year or month! Please enter a valid year (>=2000) and month (1-12)." << endl;
            system("pause");
            continue;
        }

        // Query to calculate total income, paid, and unpaid amounts by facility
        string query =
            "SELECT f.Facility_code, f.Court_name, "
            "SUM(p.Payment_amount) AS Total_Income, "
            "SUM(CASE WHEN p.Payment_status = 'Paid' THEN p.Payment_amount ELSE 0 END) AS Total_Paid, "
            "SUM(CASE WHEN p.Payment_status = 'Unpaid' THEN p.Payment_amount ELSE 0 END) AS Total_Unpaid "
            "FROM Reservation r "
            "JOIN Facility f ON r.FaciID = f.FaciID "
            "JOIN Payment p ON r.ReserveID = p.ReserveID "
            "WHERE YEAR(r.Booking_date) = " + to_string(year) + " AND MONTH(r.Booking_date) = " + to_string(month) + " "
            "GROUP BY f.Facility_code, f.Court_name;";

        if (mysql_query(conn, query.c_str())) {
            cerr << "\t\t\t\t\t\t\tError fetching reservation income data: " << mysql_error(conn) << endl;
            return;
        }

        MYSQL_RES* result = mysql_store_result(conn);
        if (result == nullptr) {
            cerr << "\t\t\t\t\t\t\tError processing query result: " << mysql_error(conn) << endl;
            return;
        }

        // Display income report
        cout << "\n\t\t\t\t\t\t*****************************************************************************" << endl;
        cout << "\t\t\t\t\t\t\t\t\tRESERVATION REPORT (" << year << "-" << (month < 10 ? "0" : "") << month << ")" << endl;
        cout << "\t\t\t\t\t\t*****************************************************************************\n" << endl;
        cout << "\t\t\t\t\t\tFacility Code\tCourt Name\tTotal Income\tPaid Amount\tUnpaid Amount" << endl;
        cout << "\t\t\t\t\t\t-----------------------------------------------------------------------------" << endl;

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result))) {
            cout << "\t\t\t\t\t\t" << setw(16) << left << row[0]
                << setw(5) << left << row[1]
                << setw(15) << right << "RM " << row[2]
                << setw(10) << right << "RM " << row[3]
                << setw(15) << right << "RM " << row[4] << endl;
        }

        mysql_free_result(result);

        // Ask admin if they want to analyze another month
        bool validInput = false;
        while (!validInput) {
            cout << "\n\t\t\t\t\t\t\tDo you want to analyze another month? (Y/N): ";
            cin >> repeat;

            if (repeat == 'Y' || repeat == 'y' || repeat == 'N' || repeat == 'n') {
                validInput = true;
            }
            else {
                cout << "\t\t\t\t\t\t\tInvalid input! Please enter (Y/N)" << endl;
            }
        }

    } while (repeat == 'Y' || repeat == 'y');

    adminMainMenu(); // Return to admin main menu
}
