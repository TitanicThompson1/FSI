The first step was to find information about the website so we could find vulnerabilities on the software. After a quick look at the website source code ![source code](../img/ctf1.png)  
we were able to find both the WordPress version and also the Woocommerce plugin version.

Following that, we made a search for vunerabilities on both wordpress and the Woocommerce plugin that would affect the specified versions(wordpress 5.8.2 woocommerce 5.7.1).
We were able to find a bug on the woocommerce boost module, described on the CVE-2021-34646.![cve](../img/ctf2.png)  
The bug consisted on the way the url for the recovery password link was being generated. It used a simple md5 hash combining the current time with the user id.![bug source code](../img/ctf3.png)   
After that we went to discover the user id with(admin user is usualy number 1).![source code](../img/ctf5.png)   

We runned the link creator script found on the internet.![source code](../img/ctf4.png) 

The script generated the recovery call with curl. After that, taking in account the response time, created 3 different links that varied the time used for the hash creation(network delays could mean the link was generated with a diferent time from the time the curl call was returned). For example, if the curl call would have returned with a unix time of 45456, the script tried the links with 45454,45455 and 45456 on the time part of the hash.![source code](../img/ctf6.png) 

In our case the first link was the one that worked.  

After that we simply navigated the website and found the internal memo with the flag number.
![source code](../img/ctf7.png) 
