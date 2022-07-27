# ONOS-Controller
This is a project of an application to control routing in MININET/ONOS topologies.

Unlike built-in in ONOS reactive forwarding app (org.onosproject.fwd), this program allows user to choose how to create routing tables for switches. User will be able to choose from options like:
* Static routing using Dijkstra's algorithm
* Adaptive routing using Dijkstra's algorithm
* User defined paths between hosts
* many more

Other less important features can help user to speed up some processes:
* Fast deleting of flows in routing tables
* Fast access to informations about topology elements using special defined commands instead of using applications like Postman or ONOS CLI (ONOS REST API will be used under the hood)

# Status
Project is still in the phase of production and it is not currently working. Expect first working version on August/September.

# Future updates
I am planning to add:
* More than one routing algorithm to compare behaviours (Belmann-Ford algorithm ...)
* GUI for easier usage. (which hosts to connect, info about topology elements, ...) 
