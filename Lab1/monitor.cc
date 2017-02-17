#include <cassert>
#include "monitor.h"

Monitor::Monitor(sc_module_name name, char *outfile)
  : sc_module(name)
{
  assert(outfile != 0);
  out = new ofstream(outfile);
  assert(*out);

  //initialize values of variables
  handled = 0;
  direction = 0;

  SC_METHOD(timer_method);
  dont_initialize();
  sensitive << timer;;

  SC_METHOD(event_method);
  dont_initialize();
  sensitive << NS_event << SN_event << EW_event << WE_event;

  SC_METHOD(handle_method);
  dont_initialize();
  sensitive << handle;

}

Monitor::~Monitor()
{
  delete out;
}

void Monitor::event_method()
{
  std::cout << "Handled: " << handled << "\n";
  //if event not handled, determine which direction the car wants to go
  if(!handled)
  {
    if(NS_event.read() || SN_event.read())
    {
        direction = 0;
        handled = 1;
        handle.notify();
    }
    else if(EW_event.read() || WE_event.read())
    {
        direction = 1;
        handled = 1;
        handle.notify();
    }
    std::cout << "Direction at event handler: " << direction << "\n";
  }
}

//timer function to restart the logic
void Monitor::timer_method()
{
    handle.notify(20,SC_SEC);
}

void Monitor::handle_method()
{
  //logic to set the lights depending on which cars wants to go
  if(direction == 1)
  {
    if(NS_event.read() == 0 && SN_event.read() != 0)
    {
      NS_change.write(false);
      SN_change.write(true);
      EW_change.write(false);
      WE_change.write(false);
      direction = 0;
      timer.notify();
    }
    else if(NS_event.read() != 0 && SN_event.read() == 0)
    {

      NS_change.write(true);
      SN_change.write(false);
      EW_change.write(false);
      WE_change.write(false);
      direction = 0;
      timer.notify();
    }
    else if(EW_event.read() == 0 && WE_event.read() != 0)
    {
      NS_change.write(false);
      SN_change.write(false);
      EW_change.write(false);
      WE_change.write(true);
      timer.notify();
    }
    else if(EW_event.read() != 0 && WE_event.read() == 0)
    {
      NS_change.write(false);
      SN_change.write(false);
      EW_change.write(true);
      WE_change.write(false);
      timer.notify();
    }
    else if(NS_event.read() != 0 && SN_event.read() != 0)
    {

      NS_change.write(true);
      SN_change.write(true);
      EW_change.write(false);
      WE_change.write(false);
      direction = 0;
      timer.notify();
    }
    else if(EW_event.read() != 0 && WE_event.read() != 0)
    {
      NS_change.write(false);
      SN_change.write(false);
      EW_change.write(true);
      WE_change.write(true);
      timer.notify();
    }
    else
    {
      NS_change.write(false);
      SN_change.write(false);
      EW_change.write(false);
      WE_change.write(false);
      handle.cancel();
      handled = 0;
    }
  }
  else if(direction == 0)
  {
    if(NS_event.read() == 0 && SN_event.read() != 0)
    {
      NS_change.write(false);
      SN_change.write(true);
      EW_change.write(false);
      WE_change.write(false);
      timer.notify();
    }
    else if(NS_event.read() != 0 && SN_event.read() == 0)
    {
      NS_change.write(true);
      SN_change.write(false);
      EW_change.write(false);
      WE_change.write(false);
      timer.notify();
    }
    else if(EW_event.read() == 0 && WE_event.read() != 0)
    {

      NS_change.write(false);
      SN_change.write(false);
      EW_change.write(false);
      WE_change.write(true);
      direction = 1;
      timer.notify();
    }
    else if(EW_event.read() != 0 && WE_event.read() == 0)
    {

      NS_change.write(false);
      SN_change.write(false);
      EW_change.write(true);
      WE_change.write(false);
      direction = 1;
      timer.notify();
    }
    else if(NS_event.read() != 0 && SN_event.read() != 0)
    {
      NS_change.write(true);
      SN_change.write(true);
      EW_change.write(false);
      WE_change.write(false);
      timer.notify();
    }
    else if(EW_event.read() != 0 && WE_event.read() != 0)
    {

      NS_change.write(false);
      SN_change.write(false);
      EW_change.write(true);
      WE_change.write(true);
      direction = 1;
      timer.notify();
    }
    else
    {
      NS_change.write(false);
      SN_change.write(false);
      EW_change.write(false);
      WE_change.write(false);
      handle.cancel();
      handled = 0;
    }
    std::cout << "Direction at the end: " << direction << "\n" ;
  }

  //writes out which cars are driving
  *out << "Timestamp(" << sc_time_stamp() << ") = " << " NS_driving:" << NS_change.read() << " SN_driving:" << SN_change.read() <<
  " EW_driving:" << EW_change.read() << " WE_driving:" << WE_change.read() << endl;

}
