# Week 8

## Task 1

After setting up the configuration for this lab, we executed the commands `docker ps` to get access to the sql container ID, and with it we could execute a shell inside that very same container using `docker exec -it <Contianer ID> bash`.

In the container's shell we could thereafter open a MySql CLI by executing the command `mysql -u root -pdees`, which allowed us to load the existing database `use sqllab_users;` and take a look at the create data: `show tables;`; `SELECT * FROM credential`; `SELECT * from credential WHERE ID=1`;

Here are the results of those queries:
![task 1 results](../Week8/img/task1.png)

***

## Task 2

***

### Task 2.1

The goal of this task was to log into the application as the administrator from the login page, assuming all we know is the admin's account name: `admin`. In the `Username` input field, after typing a `admin'` we get the following result:

![task 2_1 results](../Week8/img/task2_1.png)

This indicates to us that the website is vulnerable to SQL injection attacks as the extra char `'` after the username created a syntax error in the query.

Now, there are multiple ways we can access the application at admin level. The simplest way we can achieve this is by simply commenting out everything in the WHERE clause of the SQL query **after** the username condition.
*i.e.* in the Usermane input fiel: `admin'; -- `;
By inputing this in the username field we are essencially modifying the original query to accept only the name field as a conditional check: `SELECT ... FROM Table WHERE name='admin'; -- ' and password=...;`.

![task 2_1_2 results](../Week8/img/task2_2.png)

If the assumption of knowing the username `admin` to exist was invalid we could always input the following in the Username field to gain access as user level: `foo' or 1=1; -- `;

![task 2_1_3 results](../Week8/img/task2_3.png)

### Task 2.2

In this task we use a curl request to gain access to the app's content at admin level. For that we needed to open up a shell in the www container and execute the following command: `'http://www.seed-server.com/unsafe_home.php?username=admin%27+--+&Password='`.

![task 2_2 results](../Week8/img/task2_4.png)

Above we see the result of our http request: the html data resulting of the curl.

### Task 2.3

A different approach to task 2.1, would be to use an update statement to change the value of the password: `';UPDATE credential SET Password='chicken' WHERE name='admin'; -- `. This approach is harder to execute as the attacker would need to know what the table name is, if there is any encryption being used and if so what the encryption algorithm is.

Besides all that there is a big limitation that sets us back, and it has to do with the php implementation of the query runner in this application. Essencially to run the queries, they use the `query()` method which allows for single query runs on sql engine. If we wanted to do multiple queries with one function call they would have to have used the `multi_query()` method instead. This is done as a security measure to prevent the code illustrated in the first paragraph to be executed.

***

## Task 3

### Task 3.1

Changing the salary from within authentication walls is a trivial task. Since we are already authorised to change our values in the database, then all we need to do is in the nickname input field type the following data: `Alice', Salary=25000 -- `. This will set the values of name and Salary collumns.

![task 3_1 results](../Week8/img/task3_1.png)

Of course if we didn't want to raise any suspitions we would have to set the values for the remaining collumns as well. But this delivers the point we were trying to make.

### Task 3.2

Much like in the previous task, since we're already executing an UPDATE statement, it's quite easy to inject some malicious SQL to change other people's data (namely our hypothetical horrible boss Boby).
In the first input field (nickname) do: `Be a better boss!', Salarry=1 where name='Boby'; -- `.

And when he logs in he shall have a very unpleasant surprise:

![task 3_2 results](../Week8/img/task3_2.png)

### Task 3.3

Given that we know the encryption algorithm used in this application (that being SHA1), altering someone's password is no different than the previous exercises. We login with our credentials or hack someone's account as shown in 2.1; then in the edit profile page we type the following sql in the nickname input field: `Boby', Password=SHA('frango') where name='Boby' -- `.

And the end result would be catastrophic:

![task 3_3 results](../Week8/img/task3_3.png)


## CTF

### Part 1

Given the website, the first step was to investigate possible vulnerabilities on the site and discover what the website allowed us to do.
The identified point of failure was the login form. After that we analysed the code and dicovered that the user input concatenated with the query to the database. That allowed us to introduce sql that would render the code useless. Th efollowing code is the one used in the sql injection.
It closed the parentheses and put a "or true" and commented the rest of the query. As the condition was true, a user was returned. If that didn't work we could intrudce admin as the user and make the "or true" part in the password to force the returned user to be the admin.

![Sql injection code](../Week8/img/ctf_1.png)

![Part 1 Flag](../Week8/img/ctf_2.png)

### Part 2

The second part worked as a blackbox. We analysed the website and found the interesting feature of "Ping". Ping could be done multiple ways but teh one we figured it was being used was the "ping" utility. As that was the case, the website was making a call to the shell and possibly in a non secure way. To test that we used the following command.

![Part 2 First command](../Week8/img/ctf_3.png)

Since the code was being called in a non secure way it allowed us to pass extra commands ans input. In this case we passed the && to allow us to run another command, followed by the echo command that prints the to the shell. The result of the echo command was retrieved to the webpage: 

![Part 2 First command result](../Week8/img/ctf_4.png)

, showing we could use other commands and seee the result on the website. Since our goal was to get the flag contained in the file /flag.txt we used the utility "cat" that prints the content of a file to the stdout.

![Part 2 Second command](../Week8/img/ctf_5.png)

After that, the result showed, as previously, the result of the ping command but also the content of the "cat" call.


![Part 2 Second command Result](../Week8/img/ctf_6.png)
