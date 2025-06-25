# 📚 Library Management System
A C++ Library Management System built using the Qt framework. It includes features such as resource management, borrowing and reservation system, user management , and an automated email notifications using SMTP.


---

## 📦 Features

- 📘 Manage resources (add, edit, delete, display, find, sort)
- 🧭 Track borrowed/reserved items
- 👥 User management (add, delete, edit users)
- ✉️ Email notifications via Gmail SMTP for events and resource updates
- 📅 Library events & opening schedule management
- 💾 Uses CSV files to manage the data


---

## 🛠️ Tech Stack

- **C++ (Qt 6)**
- **Qt Widgets / Qt GUI** Available [Here](https://www.qt.io/download-dev)
- **SMTP (SmtpClient-for-Qt)** Available [Here](https://github.com/bluetiger9/SmtpClient-for-Qt#)

---

## ✅ Dependencies

To build and run this project, you'll need:

- Qt 6.2 or higher (with `qmake` or Qt Creator)
(Ensure that Qt Creator is configured to create the build folder inside the project's directory (./build) rather than a parent directory (../build). So that CSV files can be accessed correctly.)
- C++17 compiler (GCC, Clang, or MSVC)
- SmtpClient-for-Qt (included in the sent file)

---

## 🚀 Use

IMPORTANT NOTES:
    -This GUI does NOT save change automatically to allow testing without altering the data files each time.
        Make sure to click on the SAVE button (located at the main window) if you want to save any changes.


1. **Login Window**:

When you first start the application, make sure to login with one of these users: (You can remove them later)

- to login as Admin: ID: 1 USERNAME: admin PASSWORD: admin123
- to login as Regular User: ID: 2 USERNAME: user PASSWORD: user123

You can also sign up as a new REGULAR user.

Note that admins have some extra privileges: adding/editing/deleting resources, editing/deleting users, adding/deleting emails, sending emails, adding an event, and editing the opening schedule.

Also new users should follow these rules regarding their usernames and passwords:
- **Usernames:** must start with an alphabetic character, can't contain uppercase letters, can't contain non-alphabetic or non-numeric characters, can't exceed 10 characters, and must not match another existing user's username.
- **Passwords:** must contain a number of characters greater than 4 and less than 12, must contain at least one numberic and one alphabetic character, can't contain special characters other than ?!;.@&%_-,

2. **Main Window**:

After successfully logging in, you will be in the Main Window that has buttons to all other windows, some windows will only be accessible if you were logged in as an Admin (you can always log out and log back in).

Please make sure to always SAVE before closing the application if you want to save any modifications in the library.

3. **Adding Window**:

This window is only accessible for admins, and can be accessed through the "Add a New Resource" button.

This window allows you to add a new resource to the library resources by entering the information related to that resource (some information may be left empty to use default values like author name).

If the resource you want to add already exists, its quantity will be incremented.

Note that by adding a new resource an email will be sent automatically to all saved emails.

//DEV: the type of the resource will determine the row it will be stored in.

4. **Editting Window**:

This window is only accessible for admins, and can be accessed through the "Edit an Existing Resource" button.

This window allows you to edit resource's information (Type, Title, Author, Publication Year, Quantity) by entering the ID of the resource (the first ID is the resource's type, the ID of a resource can be found when first adding that resource or when displaying the  resource), and then check the check box related to the information you want to change.

Note that an unchecked check box will make the application ignore the changes related to that information

5. **Finding Window**:

This window is accessible for all type of users, and can be accessed through the "Display and Find Resources" button.

This window shows all the library resources in a table, you can look for a specific resource by entering its full ID or all its information (this will give you one match only), or by entering some information (or keywords), then by clicking the button "Find" the table will be updated with the matching results.

Also, you can sort the entire library by a specific information by checking one of the sorting radio boxes (you can reverse the order aswell).

Note that the information are sorted decreasingly by default.

6. **Removing Window**:

This window is only accessible for admins, and can be accessed through the "Remove a Resource" button.

This window allows you to delete a resource by entering its full ID (to prevent confusions) then clicking the button "Remove the Resource".

You can also clear the library (delete all its resources) using the "Clear Library" button.

7. **About The Library Window**:

This window is accessible for all type of users, and can be accessed through the "About The Library" button.

This window shows in two different tables, the library events and the opening schedule.

the Edit window can be used BY ADMINS to modify the events or the opening schedule.

Note that by adding a new event, or modifying the opening schedule an email will be sent to all saved emails.

8. **Borrowing Window**:

This window is accessible for all type of users, and can be accessed through the "Borrowing System" button.

Note that only regular users (not admins) are allowed to borrow resources.

To borrow a resource, you must either enter the information related to the borrowing user (if the logged-in user is an admin then entering the borrowing user's password won't be necessary), or use logged-in user information (if the logged-in user isn't an admin), then enter the resource related information(or full ID), the due date (the last date to return the resource), and check/uncheck the check box related to physical borrows.

This window allows you to renew a borrow, return a borrowed resource and display all currently & previously borrowed resources.

Note that the quantity & number of reservations of a resource will determine whether it can be borrowed or not.
borrowed resources can't be deleted.

9. **Reserving Window**:

This window is accessible for all type of users, and can be accessed through the "Reserve a Resource" button.

Note that only regular users (not admins) are allowed to reserve resources.

To reserve a resource, you must either enter the information related to the reserving user (if the logged-in user is an admin then entering the reserving user's password won't be necessary), or use logged-in user information (if the logged-in user isn't an admin), then enter the resource related information(or full ID).

If the resource doesn't exist, you will be able to add it directly from this window.

This window also allows you to delete a reservation, and check current reservations.

reserved resources can't be deleted.

10. **Users Window**:

This window is accessible for all type of users, and can be accessed through the "User Management" button.

Even though this window can be open by all users, you will need to enter an admin's information (username/ID and password) to be able to access its features.

This window allows you to see all users (& add filters : displaying borrowing/reserving users only), add a new user, edit an existing user's information, and delete an existing user.

11. **Emails Window**:

This window is only accessible for admins, and can be accessed through the "Email Management" button.

This window allows you to see all emails concerned by email sending feature, add a new email, delete an existing email and send a customized email to all the library emails.

Note that emails are sent automatically to all the library emails by : librarymanagementsystem.norep@gmail.com, whenever a resource is added, an event is added, or the opening schedule is altered.

If the user doesn't receive the email in the primary inbox, they need to check the spam.
