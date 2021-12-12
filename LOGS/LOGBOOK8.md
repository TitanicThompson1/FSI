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
