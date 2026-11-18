import random

movies = []

for i in range(5):
    name = input("Enter movie name: ")
    language = input("Enter language: ")
    price = float(input("Enter ticket price: "))

    movies.append({
        "id": i+1,
        "name": name,
        "language": language,
        "price": price,
        "seats": 10,
        "booked": set()
    })

bookings = []


def display_movies():
    for m in movies:
        print(m)


def calculate_price(price, age):
    if age < 12:
        return price * 0.5
    elif age >= 60:
        return price * 0.7
    else:
        return price


def book_ticket():
    display_movies()

    mid = int(input("Enter movie ID: "))

    movie = next((m for m in movies if m["id"] == mid), None)

    if movie is None:
        print("Invalid movie ID")
        return

    name = input("Customer name: ")
    age = int(input("Enter age: "))
    n = int(input("Number of tickets: "))

    if n <= 0 or n > movie["seats"]:
        print("Seats unavailable")
        return

    available = set(range(1, 11)) - movie["booked"]
    print("Available seats:", available)

    selected = set(map(int, input("Enter seat numbers: ").split()))

    if len(selected) != n or not selected.issubset(available):
        print("Invalid seat selection")
        return

    total = calculate_price(movie["price"], age) * n

    movie["booked"].update(selected)
    movie["seats"] -= n

    bid = random.randint(1000, 9999)

    bookings.append({
        "id": bid,
        "name": name,
        "movie": movie["name"],
        "tickets": n,
        "seats": selected,
        "total": total,
        "status": "Booked"
    })

    print("Booking ID:", bid)
    print("Total amount:", total)


def search_booking():
    bid = int(input("Enter booking ID: "))

    for b in bookings:
        if b["id"] == bid:
            print(b)
            return

    print("Booking not found")


def cancel_booking():
    bid = int(input("Enter booking ID: "))

    for b in bookings:
        if b["id"] == bid:
            if b["status"] == "Cancelled":
                print("Already cancelled")
                return

            movie = next(m for m in movies if m["name"] == b["movie"])

            movie["booked"].difference_update(b["seats"])
            movie["seats"] += b["tickets"]

            b["status"] = "Cancelled"

            print("Booking cancelled")
            return

    print("Booking not found")


while True:
    try:
        print("\n1. Display Movies")
        print("2. Book Ticket")
        print("3. Search Booking")
        print("4. Cancel Booking")
        print("5. Exit")

        ch = int(input("Enter choice: "))

        if ch == 1:
            display_movies()
        elif ch == 2:
            book_ticket()
        elif ch == 3:
            search_booking()
        elif ch == 4:
            cancel_booking()
        elif ch == 5:
            break
        else:
            print("Invalid choice")
            continue

    except (ValueError, TypeError) as e:
        print("Error:", e)

    else:
        print("Operation completed")

    finally:
        print("Thank you!")