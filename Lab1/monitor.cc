#include <cassert>
#include "monitor.h"

Monitor::Monitor(sc_module_name name, char *outfile)
  : sc_module(name)
{
  assert(outfile != 0);
  out = new ofstream(outfile);
  assert(*out);

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
  }
}

void Monitor::timer_method()
{
    handle.notify(15,SC_SEC);
}

void Monitor::handle_method()
{
  if(direction == 1)
  {
    if(NS_event.read() == 0 && SN_event.read() != 0)
    {
      direction = 0;
      NS_change.write(false);
      SN_change.write(true);
      EW_change.write(false);
      WE_change.write(false);
      timer.notify();
    }
    else if(NS_event.read() != 0 && SN_event.read() == 0)
    {
      direction = 0;
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
      direction = 0;
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
      timer.notify();
    }
    else
    {
      NS_change.write(false);
      SN_change.write(false);
      EW_change.write(false);
      WE_change.write(false);
      timer.cancel();
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
      direction = 1;
      NS_change.write(false);
      SN_change.write(false);
      EW_change.write(false);
      WE_change.write(true);
      timer.notify();
    }
    else if(EW_event.read() != 0 && WE_event.read() == 0)
    {
      direction = 1;
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
      timer.notify();
    }
    else if(EW_event.read() != 0 && WE_event.read() != 0)
    {
      direction = 1;
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
      timer.cancel();
      handled = 0;
    }
  }
  *out << "Timestamp(" << sc_time_stamp() << ") = " << " NS_driving:" << NS_change.read() << " SN_driving:" << SN_change.read() <<
  " EW_driving:" << EW_change.read() << " WE_driving:" << WE_change.read() << endl;

}
