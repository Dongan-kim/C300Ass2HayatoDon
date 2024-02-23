# s-talk

SFU CMPT 300 Spring 2023 Assignment 2

Dongan Kim(301441678), Hayato Koyama(301423217)

## The possible errors we have in the program:

#### When you try to use this program with a public wifi or in any public facilities(e.g. Cafe, Library etc), the UDP traffic might be blocked by the firewall or network traffic configuration managed by the wifi owner, and you might not be able to send/receive any message using ID address. (The program we wrote works fine in CSIL on SFU).

#### If you are using your personal computer and have some firewall configurations, you may need to allow UDP traffic to pass in order to use this s-talk program. For troubleshooting regarding Firewall configuration, please try tips below or refer to the URLs below:

- Firewall Settings:

Ensure that the firewall on both machines allows incoming and outgoing UDP traffic on the specified ports. Check the firewall settings on both machines and make sure that the rules allow communication on these ports.

- IP Address and Port Configuration:

Double-check that the IP addresses and port numbers are correct on both ends. It's essential that you use the correct IP address and port for each machine.

- Network Connectivity:

Confirm that there is a network route between the two machines. You can use tools like ping to check if the machines can communicate with each other over the network.

- Firewall Logs:

Check the firewall logs on both machines to see if any blocked connections or denied requests are logged. This can provide more information about whether the firewall is causing the issue.

- Debugging Output:

Add debug prints or logs to your code to check if the UDP sockets are being created successfully, and if the messages are being sent and received. This can help identify if there are any issues with the communication process.

- Try Different Ports:

If possible, try using different port numbers in case there is a conflict or an issue with the specific port numbers you are currently using.

- Network Devices Configuration:

If there are routers or other network devices between the two machines, check their configurations to ensure that they are not blocking UDP traffic on the specified ports.

- Temporary Disable Firewall:

As a troubleshooting step, you can temporarily disable the firewall on both machines to see if it resolves the issue. If it does, then you know that the firewall settings need adjustment.

 ##### trouble shooting links:
https://stackoverflow.com/questions/13905724/udp-message-blocked-by-firewall-despite-port-exception

https://learn.microsoft.com/en-us/troubleshoot/windows-server/networking/windows-fireware-rule-block-udp-communication

<!-- All threads communcicate with one another using a static array of nodes and heads.
The number of heads and nodes can be edited in list.h.
Setting node number to one and having all lists share just that one node
is fully supported. -->
