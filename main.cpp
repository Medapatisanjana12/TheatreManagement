#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <cctype>
#include <iomanip>
#include <stdexcept>

using namespace std;


// ==================================================
// SEAT STATUS
// ==================================================

enum class SeatStatus
{
    AVAILABLE,
    SELECTED,
    BOOKED,
    LOCKED
};


// ==================================================
// SEAT CATEGORY
// ==================================================

enum class SeatCategory
{
    REGULAR,
    PREMIUM,
    VIP
};


// ==================================================
// SEAT CLASS
// ==================================================

class Seat
{
private:
    string seatId;
    char row;
    int number;
    SeatCategory category;
    double price;
    SeatStatus status;

public:

    Seat(
        string id,
        char r,
        int n,
        SeatCategory cat,
        double p
    );

    string getSeatId() const;
    SeatStatus getStatus() const;
    SeatCategory getCategory() const;
    double getPrice() const;

    void select();
    void book();
    void deselect();
    void cancel();

    void display() const;
};


// ==================================================
// SEAT CONSTRUCTOR
// ==================================================

Seat::Seat(
    string id,
    char r,
    int n,
    SeatCategory cat,
    double p
)
    : seatId(id),
      row(r),
      number(n),
      category(cat),
      price(p),
      status(SeatStatus::AVAILABLE)
{
}


// ==================================================
// SEAT GETTERS
// ==================================================

string Seat::getSeatId() const
{
    return seatId;
}


SeatStatus Seat::getStatus() const
{
    return status;
}


SeatCategory Seat::getCategory() const
{
    return category;
}


double Seat::getPrice() const
{
    return price;
}


// ==================================================
// SELECT
// AVAILABLE -> SELECTED
// ==================================================

void Seat::select()
{
    if (status == SeatStatus::AVAILABLE)
    {
        status = SeatStatus::SELECTED;
    }
}


// ==================================================
// BOOK
// SELECTED -> BOOKED
// ==================================================

void Seat::book()
{
    if (status == SeatStatus::SELECTED)
    {
        status = SeatStatus::BOOKED;
    }
}


// ==================================================
// DESELECT
// SELECTED -> AVAILABLE
// ==================================================

void Seat::deselect()
{
    if (status == SeatStatus::SELECTED)
    {
        status = SeatStatus::AVAILABLE;
    }
}


// ==================================================
// CANCEL
// BOOKED -> AVAILABLE
// ==================================================

void Seat::cancel()
{
    if (status == SeatStatus::BOOKED)
    {
        status = SeatStatus::AVAILABLE;
    }
}


// ==================================================
// DISPLAY SEAT
// ==================================================

void Seat::display() const
{
    char statusChar;

    switch (status)
    {
        case SeatStatus::AVAILABLE:
            statusChar = 'A';
            break;

        case SeatStatus::SELECTED:
            statusChar = 'S';
            break;

        case SeatStatus::BOOKED:
            statusChar = 'B';
            break;

        case SeatStatus::LOCKED:
            statusChar = 'L';
            break;
    }

    cout << "["
         << seatId
         << ":"
         << statusChar
         << "] ";
}


// ==================================================
// BOOKING STATUS
// ==================================================

enum class BookingStatus
{
    CREATED,
    CONFIRMED,
    CANCELLED
};


// ==================================================
// BOOKING CLASS
// ==================================================

class Booking
{
private:
    int bookingId;
    vector<string> seatIds;
    double totalAmount;
    BookingStatus status;

public:

    Booking(
        int id,
        const vector<string>& seats,
        double amount
    );

    int getBookingId() const;

    const vector<string>& getSeatIds() const;

    double getTotalAmount() const;

    BookingStatus getStatus() const;

    void confirm();

    void cancel();

    void display() const;
};


// ==================================================
// BOOKING CONSTRUCTOR
// ==================================================

Booking::Booking(
    int id,
    const vector<string>& seats,
    double amount
)
    : bookingId(id),
      seatIds(seats),
      totalAmount(amount),
      status(BookingStatus::CREATED)
{
}


// ==================================================
// BOOKING GETTERS
// ==================================================

int Booking::getBookingId() const
{
    return bookingId;
}


const vector<string>& Booking::getSeatIds() const
{
    return seatIds;
}


double Booking::getTotalAmount() const
{
    return totalAmount;
}


BookingStatus Booking::getStatus() const
{
    return status;
}


// ==================================================
// CONFIRM BOOKING
// CREATED -> CONFIRMED
// ==================================================

void Booking::confirm()
{
    if (status == BookingStatus::CREATED)
    {
        status = BookingStatus::CONFIRMED;
    }
}


// ==================================================
// CANCEL BOOKING
// CONFIRMED -> CANCELLED
// ==================================================

void Booking::cancel()
{
    if (status == BookingStatus::CONFIRMED)
    {
        status = BookingStatus::CANCELLED;
    }
}


// ==================================================
// DISPLAY BOOKING
// ==================================================

void Booking::display() const
{
    cout << "\n========== BOOKING ==========\n";

    cout << "Booking ID : "
         << bookingId
         << "\n";

    cout << "Seats      : ";

    for (const string& seatId : seatIds)
    {
        cout << seatId << " ";
    }

    cout << "\n";

    cout << "Amount     : Rs. "
         << fixed
         << setprecision(2)
         << totalAmount
         << "\n";

    cout << "Status     : ";

    switch (status)
    {
        case BookingStatus::CREATED:
            cout << "CREATED";
            break;

        case BookingStatus::CONFIRMED:
            cout << "CONFIRMED";
            break;

        case BookingStatus::CANCELLED:
            cout << "CANCELLED";
            break;
    }

    cout << "\n";
}


// ==================================================
// SCREEN CLASS
// ==================================================

class Screen
{
private:

    int rows;
    int seatsPerRow;

    vector<vector<Seat>> seats;


    // Helper functions

    Seat* findSeat(
        const string& seatId
    );

    bool isValidSeatId(
        const string& seatId
    ) const;

    SeatCategory getCategoryForRow(
        char row
    ) const;

    double getPriceForCategory(
        SeatCategory category
    ) const;


public:

    Screen(
        int r,
        int s
    );

    void generateSeats();

    void displaySeats();


    bool selectSeat(
        const string& seatId
    );


    bool selectSeats(
        const vector<string>& seatIds
    );


    bool deselectSeats(
        const vector<string>& seatIds
    );


    bool bookSeat(
        const string& seatId
    );


    bool bookSeats(
        const vector<string>& seatIds
    );


    bool cancelSeat(
        const string& seatId
    );


    bool cancelSeats(
        const vector<string>& seatIds
    );


    double calculateTotal(
        const vector<string>& seatIds
    );
};


// ==================================================
// SCREEN CONSTRUCTOR
// ==================================================

Screen::Screen(
    int r,
    int s
)
    : rows(r),
      seatsPerRow(s)
{
}


// ==================================================
// CATEGORY FOR ROW
// ==================================================

SeatCategory Screen::getCategoryForRow(
    char row
) const
{
    if (row == 'A')
    {
        return SeatCategory::VIP;
    }

    if (row == 'B' || row == 'C')
    {
        return SeatCategory::PREMIUM;
    }

    return SeatCategory::REGULAR;
}


// ==================================================
// PRICE FOR CATEGORY
// ==================================================

double Screen::getPriceForCategory(
    SeatCategory category
) const
{
    switch (category)
    {
        case SeatCategory::REGULAR:
            return 200.0;

        case SeatCategory::PREMIUM:
            return 300.0;

        case SeatCategory::VIP:
            return 450.0;
    }

    return 0.0;
}


// ==================================================
// VALIDATE SEAT ID
// ==================================================

bool Screen::isValidSeatId(
    const string& seatId
) const
{
    if (seatId.length() < 2)
    {
        return false;
    }


    // First character must be alphabetic

    if (!isalpha(
            static_cast<unsigned char>(seatId[0])
        ))
    {
        return false;
    }


    // Remaining characters must be digits

    for (size_t i = 1;
         i < seatId.length();
         ++i)
    {
        if (!isdigit(
                static_cast<unsigned char>(seatId[i])
            ))
        {
            return false;
        }
    }


    char rowChar =
        toupper(
            static_cast<unsigned char>(seatId[0])
        );


    int seatNumber;

    try
    {
        seatNumber =
            stoi(
                seatId.substr(1)
            );
    }
    catch (const invalid_argument&)
    {
        return false;
    }
    catch (const out_of_range&)
    {
        return false;
    }


    // Validate row

    if (rowChar < 'A' ||
        rowChar >= 'A' + rows)
    {
        return false;
    }


    // Validate seat number

    if (seatNumber < 1 ||
        seatNumber > seatsPerRow)
    {
        return false;
    }


    return true;
}


// ==================================================
// FIND SEAT
// ==================================================

Seat* Screen::findSeat(
    const string& seatId
)
{
    if (seatId.empty())
    {
        return nullptr;
    }


    // Normalize first character

    string normalizedId = seatId;

    normalizedId[0] =
        toupper(
            static_cast<unsigned char>(
                normalizedId[0]
            )
        );


    for (auto& rowSeats : seats)
    {
        for (auto& seat : rowSeats)
        {
            if (seat.getSeatId() ==
                normalizedId)
            {
                return &seat;
            }
        }
    }


    return nullptr;
}


// ==================================================
// GENERATE SEATS
// ==================================================

void Screen::generateSeats()
{
    seats.clear();


    for (int i = 0;
         i < rows;
         ++i)
    {
        vector<Seat> rowSeats;


        char rowChar =
            'A' + i;


        SeatCategory category =
            getCategoryForRow(
                rowChar
            );


        double price =
            getPriceForCategory(
                category
            );


        for (int j = 1;
             j <= seatsPerRow;
             ++j)
        {
            string id =
                string(1, rowChar)
                +
                to_string(j);


            rowSeats.push_back(
                Seat(
                    id,
                    rowChar,
                    j,
                    category,
                    price
                )
            );
        }


        seats.push_back(
            rowSeats
        );
    }
}


// ==================================================
// DISPLAY SEATS
// ==================================================

void Screen::displaySeats()
{
    cout << "\n";

    cout << "                    SCREEN\n";

    cout << "------------------------------------------------------------\n";


    for (const auto& rowSeats : seats)
    {
        for (const auto& seat : rowSeats)
        {
            seat.display();
        }

        cout << "\n";
    }


    cout << "------------------------------------------------------------\n";

    cout << "A = Available   ";
    cout << "S = Selected   ";
    cout << "B = Booked   ";
    cout << "L = Locked\n";


    cout << "\nPrices:\n";

    cout << "Regular : Rs.200\n";
    cout << "Premium : Rs.300\n";
    cout << "VIP     : Rs.450\n";
}


// ==================================================
// SELECT ONE SEAT
// ==================================================

bool Screen::selectSeat(
    const string& seatId
)
{
    if (!isValidSeatId(seatId))
    {
        cout << "Invalid seat ID: "
             << seatId
             << "\n";

        return false;
    }


    Seat* seat =
        findSeat(seatId);


    if (seat == nullptr)
    {
        cout << "Seat does not exist.\n";

        return false;
    }


    if (seat->getStatus() !=
        SeatStatus::AVAILABLE)
    {
        cout << "Seat "
             << seatId
             << " is not available.\n";

        return false;
    }


    seat->select();

    return true;
}


// ==================================================
// SELECT MULTIPLE SEATS
// ==================================================

bool Screen::selectSeats(
    const vector<string>& seatIds
)
{
    if (seatIds.empty())
    {
        cout << "No seats were selected.\n";

        return false;
    }


    unordered_set<string> uniqueSeats;


    // ----------------------------------------------
    // VALIDATION
    // ----------------------------------------------

    for (const string& seatId : seatIds)
    {
        if (!isValidSeatId(seatId))
        {
            cout << "Invalid seat ID: "
                 << seatId
                 << "\n";

            return false;
        }


        // Normalize ID for duplicate checking

        string normalizedId =
            seatId;

        normalizedId[0] =
            toupper(
                static_cast<unsigned char>(
                    normalizedId[0]
                )
            );


        if (uniqueSeats.find(
                normalizedId
            ) != uniqueSeats.end())
        {
            cout << "Duplicate seat: "
                 << seatId
                 << "\n";

            return false;
        }


        uniqueSeats.insert(
            normalizedId
        );


        Seat* seat =
            findSeat(seatId);


        if (seat == nullptr)
        {
            cout << "Seat does not exist: "
                 << seatId
                 << "\n";

            return false;
        }


        if (seat->getStatus() !=
            SeatStatus::AVAILABLE)
        {
            cout << "Seat "
                 << seatId
                 << " is not available.\n";

            return false;
        }
    }


    // ----------------------------------------------
    // SELECT ALL
    // ----------------------------------------------

    for (const string& seatId : seatIds)
    {
        Seat* seat =
            findSeat(seatId);


        if (seat != nullptr)
        {
            seat->select();
        }
    }


    cout << "All requested seats selected successfully.\n";

    return true;
}


// ==================================================
// DESELECT MULTIPLE SEATS
// ==================================================

bool Screen::deselectSeats(
    const vector<string>& seatIds
)
{
    if (seatIds.empty())
    {
        cout << "No seats provided.\n";

        return false;
    }


    unordered_set<string> uniqueSeats;


    // ----------------------------------------------
    // VALIDATION
    // ----------------------------------------------

    for (const string& seatId : seatIds)
    {
        if (!isValidSeatId(seatId))
        {
            cout << "Invalid seat ID: "
                 << seatId
                 << "\n";

            return false;
        }


        string normalizedId =
            seatId;

        normalizedId[0] =
            toupper(
                static_cast<unsigned char>(
                    normalizedId[0]
                )
            );


        if (uniqueSeats.find(
                normalizedId
            ) != uniqueSeats.end())
        {
            cout << "Duplicate seat: "
                 << seatId
                 << "\n";

            return false;
        }


        uniqueSeats.insert(
            normalizedId
        );


        Seat* seat =
            findSeat(seatId);


        if (seat == nullptr)
        {
            cout << "Seat does not exist: "
                 << seatId
                 << "\n";

            return false;
        }


        if (seat->getStatus() !=
            SeatStatus::SELECTED)
        {
            cout << "Seat "
                 << seatId
                 << " is not selected.\n";

            return false;
        }
    }


    // ----------------------------------------------
    // DESELECT ALL
    // ----------------------------------------------

    for (const string& seatId : seatIds)
    {
        Seat* seat =
            findSeat(seatId);


        if (seat != nullptr)
        {
            seat->deselect();
        }
    }


    cout << "All seats deselected successfully.\n";

    return true;
}


// ==================================================
// BOOK ONE SEAT
// ==================================================

bool Screen::bookSeat(
    const string& seatId
)
{
    if (!isValidSeatId(seatId))
    {
        cout << "Invalid seat ID.\n";

        return false;
    }


    Seat* seat =
        findSeat(seatId);


    if (seat == nullptr)
    {
        return false;
    }


    if (seat->getStatus() !=
        SeatStatus::SELECTED)
    {
        cout << "Seat "
             << seatId
             << " must be selected first.\n";

        return false;
    }


    seat->book();

    return true;
}


// ==================================================
// BOOK MULTIPLE SEATS
// ==================================================

bool Screen::bookSeats(
    const vector<string>& seatIds
)
{
    if (seatIds.empty())
    {
        cout << "No seats provided.\n";

        return false;
    }


    unordered_set<string> uniqueSeats;


    // ----------------------------------------------
    // VALIDATION
    // ----------------------------------------------

    for (const string& seatId : seatIds)
    {
        if (!isValidSeatId(seatId))
        {
            cout << "Invalid seat ID: "
                 << seatId
                 << "\n";

            return false;
        }


        string normalizedId =
            seatId;

        normalizedId[0] =
            toupper(
                static_cast<unsigned char>(
                    normalizedId[0]
                )
            );


        if (uniqueSeats.find(
                normalizedId
            ) != uniqueSeats.end())
        {
            cout << "Duplicate seat: "
                 << seatId
                 << "\n";

            return false;
        }


        uniqueSeats.insert(
            normalizedId
        );


        Seat* seat =
            findSeat(seatId);


        if (seat == nullptr)
        {
            return false;
        }


        if (seat->getStatus() !=
            SeatStatus::SELECTED)
        {
            cout << "Seat "
                 << seatId
                 << " is not selected.\n";

            return false;
        }
    }


    // ----------------------------------------------
    // BOOK ALL
    // ----------------------------------------------

    for (const string& seatId : seatIds)
    {
        Seat* seat =
            findSeat(seatId);


        if (seat != nullptr)
        {
            seat->book();
        }
    }


    cout << "All seats booked successfully.\n";

    return true;
}


// ==================================================
// CANCEL ONE SEAT
// ==================================================

bool Screen::cancelSeat(
    const string& seatId
)
{
    if (!isValidSeatId(seatId))
    {
        cout << "Invalid seat ID.\n";

        return false;
    }


    Seat* seat =
        findSeat(seatId);


    if (seat == nullptr)
    {
        return false;
    }


    if (seat->getStatus() !=
        SeatStatus::BOOKED)
    {
        cout << "Seat "
             << seatId
             << " is not booked.\n";

        return false;
    }


    seat->cancel();

    return true;
}


// ==================================================
// CANCEL MULTIPLE SEATS
// ==================================================

bool Screen::cancelSeats(
    const vector<string>& seatIds
)
{
    if (seatIds.empty())
    {
        cout << "No seats provided.\n";

        return false;
    }


    unordered_set<string> uniqueSeats;


    // ----------------------------------------------
    // VALIDATION
    // ----------------------------------------------

    for (const string& seatId : seatIds)
    {
        if (!isValidSeatId(seatId))
        {
            cout << "Invalid seat ID: "
                 << seatId
                 << "\n";

            return false;
        }


        string normalizedId =
            seatId;

        normalizedId[0] =
            toupper(
                static_cast<unsigned char>(
                    normalizedId[0]
                )
            );


        if (uniqueSeats.find(
                normalizedId
            ) != uniqueSeats.end())
        {
            cout << "Duplicate seat: "
                 << seatId
                 << "\n";

            return false;
        }


        uniqueSeats.insert(
            normalizedId
        );


        Seat* seat =
            findSeat(seatId);


        if (seat == nullptr)
        {
            return false;
        }


        if (seat->getStatus() !=
            SeatStatus::BOOKED)
        {
            cout << "Seat "
                 << seatId
                 << " is not booked.\n";

            return false;
        }
    }


    // ----------------------------------------------
    // CANCEL ALL
    // ----------------------------------------------

    for (const string& seatId : seatIds)
    {
        Seat* seat =
            findSeat(seatId);


        if (seat != nullptr)
        {
            seat->cancel();
        }
    }


    cout << "All seats cancelled successfully.\n";

    return true;
}


// ==================================================
// CALCULATE TOTAL
// ==================================================

double Screen::calculateTotal(
    const vector<string>& seatIds
)
{
    if (seatIds.empty())
    {
        cout << "No seats provided.\n";

        return -1;
    }


    unordered_set<string> uniqueSeats;

    double total = 0.0;


    for (const string& seatId : seatIds)
    {
        // ------------------------------------------
        // VALIDATE
        // ------------------------------------------

        if (!isValidSeatId(seatId))
        {
            cout << "Invalid seat ID: "
                 << seatId
                 << "\n";

            return -1;
        }


        string normalizedId =
            seatId;

        normalizedId[0] =
            toupper(
                static_cast<unsigned char>(
                    normalizedId[0]
                )
            );


        // ------------------------------------------
        // DUPLICATE
        // ------------------------------------------

        if (uniqueSeats.find(
                normalizedId
            ) != uniqueSeats.end())
        {
            cout << "Duplicate seat: "
                 << seatId
                 << "\n";

            return -1;
        }


        uniqueSeats.insert(
            normalizedId
        );


        // ------------------------------------------
        // FIND SEAT
        // ------------------------------------------

        Seat* seat =
            findSeat(seatId);


        if (seat == nullptr)
        {
            cout << "Seat does not exist: "
                 << seatId
                 << "\n";

            return -1;
        }


        // ------------------------------------------
        // ADD PRICE
        // ------------------------------------------

        total +=
            seat->getPrice();
    }


    return total;
}


// ==================================================
// MOVIE CLASS
// ==================================================

class Movie
{
private:

    int movieId;
    string title;
    string genre;
    int durationMinutes;


public:

    Movie(
        int id,
        const string& t,
        const string& g,
        int duration
    );


    int getMovieId() const;

    string getTitle() const;

    string getGenre() const;

    int getDuration() const;


    void display() const;
};


// ==================================================
// MOVIE CONSTRUCTOR
// ==================================================

Movie::Movie(
    int id,
    const string& t,
    const string& g,
    int duration
)
    : movieId(id),
      title(t),
      genre(g),
      durationMinutes(duration)
{
}


// ==================================================
// MOVIE GETTERS
// ==================================================

int Movie::getMovieId() const
{
    return movieId;
}


string Movie::getTitle() const
{
    return title;
}


string Movie::getGenre() const
{
    return genre;
}


int Movie::getDuration() const
{
    return durationMinutes;
}


// ==================================================
// MOVIE DISPLAY
// ==================================================

void Movie::display() const
{
    cout << "\n========== MOVIE ==========\n";

    cout << "Movie ID : "
         << movieId
         << "\n";

    cout << "Title    : "
         << title
         << "\n";

    cout << "Genre    : "
         << genre
         << "\n";

    cout << "Duration : "
         << durationMinutes
         << " minutes\n";
}


// ==================================================
// SHOW CLASS
// ==================================================

class Show
{
private:

    int showId;

    Movie movie;

    Screen& screen;

    string showTime;


public:

    Show(
        int id,
        const Movie& m,
        Screen& s,
        const string& time
    );


    int getShowId() const;

    const Movie& getMovie() const;

    Screen& getScreen();

    string getShowTime() const;


    void display() const;
};


// ==================================================
// SHOW CONSTRUCTOR
// ==================================================

Show::Show(
    int id,
    const Movie& m,
    Screen& s,
    const string& time
)
    : showId(id),
      movie(m),
      screen(s),
      showTime(time)
{
}

// ==================================================
// SHOW GETTERS
// ==================================================

int Show::getShowId() const{
    return showId;
}

const Movie& Show::getMovie() const{
    return movie;
}

Screen& Show::getScreen(){
    return screen;
}

string Show::getShowTime() const{
    return showTime;
}

// ==================================================
// SHOW DISPLAY
// ==================================================

void Show::display() const
{
    cout << "\n========== SHOW ==========\n";

    cout << "Show ID   : "<< showId<< "\n";

    cout << "Movie     : "<< movie.getTitle()<< "\n";

    cout << "Show Time : "<< showTime<< "\n";
}


// ==================================================
// SHOW SEAT STATUS
// ==================================================

enum class ShowSeatStatus
{
    AVAILABLE,
    SELECTED,
    BOOKED
};
// ==================================================
// SHOW SEAT CLASS
// ==================================================

class ShowSeat
{
private:
    string seatId;
    SeatCategory category;
    double price;
    ShowSeatStatus status;
public:

    ShowSeat(
        string id,SeatCategory cat,double p
    );
    string getSeatId() const;
    SeatCategory getCategory() const;
    double getPrice() const;
    ShowSeatStatus getStatus() const;
    bool select();
    bool book();
    bool deselect();
    bool cancel();
    void display() const;
};

// ==================================================
// SHOW SEAT CONSTRUCTOR
// ==================================================

ShowSeat::ShowSeat(
    string id,SeatCategory cat,double p
)
    : seatId(id),category(cat),price(p), status(ShowSeatStatus::AVAILABLE)
{
}

// ==================================================
// SHOW SEAT GETTERS
// ==================================================

string ShowSeat::getSeatId() const{
    return seatId;
}

SeatCategory ShowSeat::getCategory() const{
    return category;
}

double ShowSeat::getPrice() const{
    return price;
}


ShowSeatStatus ShowSeat::getStatus() const{
    return status;
}


// ==================================================
// SELECT SHOW SEAT
// AVAILABLE -> SELECTED
// ==================================================

bool ShowSeat::select()
{
    if (status != ShowSeatStatus::AVAILABLE){
        return false;
    }

    status =ShowSeatStatus::SELECTED;

    return true;
}

// ==================================================
// BOOK SHOW SEAT
// SELECTED -> BOOKED
// ==================================================

bool ShowSeat::book()
{
    if (status != ShowSeatStatus::SELECTED){
        return false;
    }
    status = ShowSeatStatus::BOOKED;
    return true;
}


// ==================================================
// DESELECT SHOW SEAT
// SELECTED -> AVAILABLE
// ==================================================

bool ShowSeat::deselect()
{
    if (status != ShowSeatStatus::SELECTED){
        return false;
    }

    status =
        ShowSeatStatus::AVAILABLE;
    return true;
}

// ==================================================
// CANCEL SHOW SEAT
// BOOKED -> AVAILABLE
// ==================================================

bool ShowSeat::cancel()
{
    if (status != ShowSeatStatus::BOOKED){
        return false;
    }

    status =
        ShowSeatStatus::AVAILABLE;
    return true;
}


// ==================================================
// DISPLAY SHOW SEAT
// ==================================================

void ShowSeat::display() const
{
    cout << seatId<< " - ";

    if (status == ShowSeatStatus::AVAILABLE){
        cout << "AVAILABLE";
    }
    else if (status == ShowSeatStatus::SELECTED){
        cout << "SELECTED";
    }
    else if (status == ShowSeatStatus::BOOKED){
        cout << "BOOKED";
    }

    cout << " - Rs. "<< fixed<< setprecision(2)<< price<< "\n";
}

int main()
{
    // ----------------------------------------------
    // CREATE SCREEN
    // ----------------------------------------------

    Screen screen(
        5,8
    );
    screen.generateSeats();
    cout << "\n========== INITIAL ==========\n";
    screen.displaySeats();

    // ----------------------------------------------
    // CREATE MOVIE
    // ----------------------------------------------

    Movie movie(
        101,"Avatar","Sci-Fi",162
    );


    movie.display();

    // ----------------------------------------------
    // CREATE SHOW
    // ----------------------------------------------

    Show show(
        501,movie,screen,"6:00 PM"
    );

    show.display();
    // ----------------------------------------------
    // SELECT SEATS
    // ----------------------------------------------

    vector<string> selectedSeats ={
        "A1","A2", "B3"
    };


    cout << "\nSelecting seats...\n";
    if (!screen.selectSeats(selectedSeats)){
        cout << "Seat selection failed.\n";

        return 0;
    }

    // ----------------------------------------------
    // CALCULATE PRICE
    // ----------------------------------------------

    double total =
        screen.calculateTotal(
            selectedSeats
        );
    if (total < 0){
        cout << "Price calculation failed.\n";
        return 0;
    }
    cout << "\nTotal amount: Rs. "<< fixed<< setprecision(2)<< total<< "\n";
    // ----------------------------------------------
    // CREATE BOOKING
    // ----------------------------------------------

    Booking booking(
        1001,selectedSeats,total
    );
    cout << "\nBooking created:\n";

    booking.display();


    // ----------------------------------------------
    // BOOK SEATS
    // ----------------------------------------------

    if (screen.bookSeats(selectedSeats)){
        cout << "\nSeats successfully booked.\n";

        booking.confirm();
    }
    else{
        cout << "\nSeat booking failed.\n";

        screen.deselectSeats(
            selectedSeats
        );
    }
    // ----------------------------------------------
    // DISPLAY AFTER BOOKING
    // ----------------------------------------------

    cout << "\n========== AFTER BOOKING ==========\n";

    screen.displaySeats();

    booking.display();

    // ----------------------------------------------
    // CANCEL BOOKING
    // ----------------------------------------------

    cout << "\nCancelling booking...\n";

    if (screen.cancelSeats(selectedSeats)){
        booking.cancel();

        cout << "Booking cancelled successfully.\n";
    }
    else{
        cout << "Booking cancellation failed.\n";
    }

    cout << "\n========== FINAL STATE ==========\n";
    screen.displaySeats();
    booking.display();
    return 0;
}