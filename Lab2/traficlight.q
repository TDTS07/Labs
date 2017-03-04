//This file was generated from (Commercial) UPPAAL 4.0.14 (rev. 5615), May 2014

/*

*/
A<> NS.wait imply NS.driving

/*

*/
A[] not ((NS.driving or SN.driving) and (WE.driving or EW.driving))

/*

*/
A<> SN.wait imply SN.driving

/*

*/
A<> WE.wait imply WE.driving

/*

*/
A<> EW.wait imply EW.driving

/*

*/
A[] not deadlock\

