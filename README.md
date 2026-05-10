# Address Book — C++ Console Application

A console-based address book application written in C++ with multi-user support.

## Features

### Authentication
- User registration and login
- Password change option available from within the address book
- User credentials are stored in `users_data.txt`

### Address Book
- Add new contacts (name, surname, phone number, e-mail, address)
- Search contacts by first or last name
- Edit existing records by ID
- Delete contacts by ID
- Display all saved entries
- Each user's contacts are stored and loaded independently based on user ID
- Contact data is stored in `address_book_data.txt`

## Storage format

**users_data.txt**
```
id|login|password|
```

**address_book_data.txt**
```
recordId|userId|name|surname|phone|email|address|
```

## Notes
> Passwords are stored as plain text. In a production application, passwords should be hashed.