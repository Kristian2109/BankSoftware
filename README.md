# BankSoftware
Student project for the first semester at FMI

**The project strives to imitate a bank software.**

- Not important note: I've begun the project too early and didn't use any more complex functionalities, as vectors, structures and so on...

**Prerequisites**:
  - The project is build without usage of only arrays and primite datatypes. Exception are hashing function, round function and one function with string.

**Notes**:
    - Every user has three features - name, password and ballance.
    - The program will detect always incorrect input.
    - The data for the users is stored in txt file, with colons as delimiters.
    - If you want to go back from every action you've choosen. Type only **-1** at the action and you will go to the previous menu.
    - The data for everything unless the registration will be overwritten only after you quit the file.
    - The programm accepts also low letters for the actions.

##Functionality

1. Beginning Menu
    - You can choose from the current options: Register, Login or Quit.

2. Login
    - First you enter your name. If the name is not right, you have three attempts, after this you will go to the beginning menu.
    - The same is with the password.
  
3. Register
    - The name should have only lattin letters and symbols without a colon.
    - In the password you should have at least 1 low letter, 1 high letter, 1 digit and 1 symbol and the length should be at least 5 characters.
    - After you've successfuly registered, the data will be stored in txt file with the hashed password.
    - After successful registration, you should login to your profile.

4. Deposit
    - You can deposit a positive sum up to 100000 BGN.

5. Withdraw
    - You can withdraw without limits, unless you exceed your max overdraft which is 10000 BGN.

6. Transfer
    - You can transfer to a user who is in the database. It isn't correct to try to transfer to yourself. Also your overdraft should be in limits.

7. Cancel account
    - You can cansel your account after successfuly giving your password. The ballance should be 0 to do this.

8. Logout 
    - Go back to the beginning menu.
