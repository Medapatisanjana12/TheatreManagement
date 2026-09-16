# 🎬 Theatre Ticket Management System

A C++ based Theatre Ticket Management System designed to simulate the core operations of a real-world theatre ticket booking platform. The project focuses on applying **Object-Oriented Programming (OOP), STL, data structures, state management, and modular software design**.

The system is being developed incrementally, starting with seat management and gradually extending toward complete movie, show, booking, payment, and database functionality.

---

## 📌 Project Overview

The Theatre Ticket Management System manages theatre seats, seat categories, pricing, movies, shows, and customer bookings.

The current implementation supports:

- Creating and managing theatre seats
- Seat categories and pricing
- Individual and group seat selection
- Seat booking and cancellation
- Booking creation and confirmation
- Movie management
- Show management
- Show-specific seat representation
- Input validation and duplicate-seat detection
- All-or-nothing validation for multiple-seat operations

The project is structured to be extended later with **seat locking, payments, cancellations/refunds, database persistence, concurrency, REST APIs, and a complete backend architecture**.

---

## 🎯 Objectives

The main objectives of this project are:

1. Build a practical C++ application using OOP principles.
2. Understand how real-world theatre ticket booking systems work.
3. Apply STL containers such as `vector` and `unordered_set`.
4. Implement controlled state transitions for seats and bookings.
5. Practice modular and maintainable software design.
6. Gradually introduce advanced concepts such as databases, concurrency, and design patterns.

---

## 🏗️ Current Architecture

```text
Theatre Ticket Management System
│
├── Seat
│   ├── Seat ID
│   ├── Row & Number
│   ├── Category
│   ├── Price
│   └── Status
│
├── Screen
│   ├── Seat Generation
│   ├── Seat Selection
│   ├── Seat Booking
│   ├── Seat Cancellation
│   └── Price Calculation
│
├── Movie
│   ├── Movie ID
│   ├── Title
│   ├── Genre
│   └── Duration
│
├── Show
│   ├── Show ID
│   ├── Movie
│   ├── Screen
│   └── Show Time
│
├── ShowSeat
│   ├── Seat ID
│   ├── Category
│   ├── Price
│   └── Show-specific Status
│
└── Booking
    ├── Booking ID
    ├── Selected Seats
    ├── Total Amount
    └── Booking Status
````

---

## 🪑 Seat Management

Seats are represented using the `Seat` class.

Each seat contains:

* Seat ID
* Row
* Seat number
* Seat category
* Price
* Current status

### Seat Categories

| Category | Price |
| -------- | ----- |
| Regular  | ₹200  |
| Premium  | ₹300  |
| VIP      | ₹450  |

The current row-based configuration assigns:

* Row A → VIP
* Rows B & C → Premium
* Remaining rows → Regular

---

## 🔄 Seat State Management

Seats follow controlled state transitions:

```text
AVAILABLE
    ↓
SELECTED
    ↓
BOOKED
```

Seats can also return to the available state:

```text
SELECTED → AVAILABLE
BOOKED   → AVAILABLE
```

A `LOCKED` state is included in the design for future implementation of temporary seat reservation during the payment process.

---

## 🎟️ Booking Management

The `Booking` class represents a customer's booking.

Each booking contains:

* Unique booking ID
* List of selected seat IDs
* Total booking amount
* Booking status

### Booking States

```text
CREATED
   ↓
CONFIRMED
   ↓
CANCELLED
```

This separates the **booking lifecycle** from the **seat lifecycle**.

---

## 🎥 Movie & Show Management

The system includes separate `Movie` and `Show` entities.

A movie represents the actual film:

```text
Movie
 ├── Movie ID
 ├── Title
 ├── Genre
 └── Duration
```

A show represents a particular screening of a movie:

```text
Show
 ├── Show ID
 ├── Movie
 ├── Screen
 └── Show Time
```

This allows the same movie to have multiple shows at different times.

---

## 💺 Show Seats

`ShowSeat` represents a seat's availability for a particular show.

This is important because the physical seat and its availability are separate concepts.

For example:

```text
Show 1 - 10:00 AM
A1 → BOOKED

Show 2 - 6:00 PM
A1 → AVAILABLE
```

The `ShowSeat` concept is being introduced to support this show-specific availability model.

---

## 🛡️ Validation & Error Handling

The system performs validation before modifying multiple seats.

For example, when booking:

```text
Validate all seats
       ↓
Check duplicates
       ↓
Check seat existence
       ↓
Check availability
       ↓
Perform operation
```

This prevents partially completed group operations.

For example, if a user requests:

```text
A1, A2, B5
```

and `B5` is unavailable, the system does not modify the other requested seats.

---

## 🧰 Technologies Used

* **C++**
* Object-Oriented Programming
* STL

  * `vector`
  * `unordered_set`
* C++ Exception Handling
* Modular Class Design
* State-based modelling

---

## 📂 Project Structure

The current project is maintained as a C++ application:

```text
TheatreManagement/
│
├── main.cpp
├── .gitignore
└── README.md
```

The project will gradually be refactored into separate header and source files as the architecture grows.

---

## 🚀 Planned Features

The project is being developed in multiple stages.

### Completed / Current

* [x] Seat management
* [x] Seat categories
* [x] Seat pricing
* [x] Individual seat selection
* [x] Multiple seat selection
* [x] Seat booking
* [x] Seat cancellation
* [x] Booking management
* [x] Movie model
* [x] Show model
* [x] ShowSeat model
* [x] Input validation

### Planned

* [ ] Theatre management
* [ ] Proper show-specific seat availability
* [ ] BookingService
* [ ] Seat locking and timeout
* [ ] Payment management
* [ ] Ticket generation
* [ ] Cancellation and refund management
* [ ] File-based persistence
* [ ] SQLite database
* [ ] Multithreading and concurrency
* [ ] Design patterns
* [ ] Unit testing
* [ ] REST API backend
* [ ] Complete layered architecture

---

## 🧠 Concepts Practiced

This project is being used to practice and understand:

### Object-Oriented Programming

* Classes and Objects
* Encapsulation
* Constructors
* References
* Pointers
* `const` correctness
* Composition
* State management

### Data Structures & STL

* `vector`
* `unordered_set`
* Iteration
* Searching
* Dynamic collections

### Software Design

* Separation of responsibilities
* Validation before modification
* Entity modelling
* Service-layer architecture
* State machines
* Transaction-like operations

---

## 🔮 Future Architecture

The planned architecture will evolve toward:

```text
User Interface
      ↓
Controller
      ↓
Service Layer
      ↓
Repository Layer
      ↓
Database
```

The final system is intended to support a complete booking workflow:

```text
Customer
   ↓
Select Movie
   ↓
Select Theatre
   ↓
Select Show
   ↓
View Available Seats
   ↓
Select Seats
   ↓
Lock Seats
   ↓
Calculate Price
   ↓
Payment
   ↓
Confirm Booking
   ↓
Generate Ticket
```

---

## 📚 Learning Purpose

This project is primarily a **learning and portfolio project** developed to understand how a real-world ticket booking system can be designed using C++.

Rather than implementing everything at once, the system is being developed incrementally so that each stage introduces new concepts in **OOP, DSA, system design, persistence, databases, concurrency, and backend development**.

---

## 👩‍💻 Author

**Sanjana Medapati**
