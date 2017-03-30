//This file was generated from (Commercial) UPPAAL 4.0.14 (rev. 5615), May 2014

/*

*/
E<> (message_dropped == true and ack_dropped == true)

/*

*/
E<> Sender.wait1

/*

*/
A<> Sender.wait0 imply Receiver.wait0

/*

*/
A[] not deadlock
