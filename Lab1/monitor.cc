#include <cassert>
#include "monitor.h"

Monitor::Monitor(sc_module_name name, char *outfile)
  : sc_module(name)
{
  assert(outfile != 0);
  out = new ofstream(outfile);
  assert(*out);

  SC_METHOD(monitor_method);
  dont_initialize();
  sensitive << NS_event << SN_event << EW_event << WE_event;

  SC_METHOD(check_constraints_method);
  dont_initialize();
  sensitive << NS_light << SN_light << EW_light << WE_light;
}

Monitor::~Monitor()
{
  delete out;
}

void Monitor::monitor_method()
{
  bool NS_cars_event = NS_event->read();
  bool SN_cars_event = SN_event->read();
  bool EW_cars_event = EW_event->read();
  bool WE_cars_event = WE_event->read();
  if((NS_cars_event == 1)&&(SN_cars_event == 0)&&(EW_cars_event == 0)&&(WE_cars_event==0)){
    NS_light = 1;
  }
  else if((NS_cars_event == 0)&&(SN_cars_event == 1)&&(EW_cars_event == 0)&&(WE_cars_event==0)){
    SN_light = 1;
  }
  else if((NS_cars_event == 0)&&(SN_cars_event == 0)&&(EW_cars_event == 1)&&(WE_cars_event==0)){
    EW_light = 1;
  }
  else if((NS_cars_event == 0)&&(SN_cars_event == 0)&&(EW_cars_event == 0)&&(WE_cars_event==1)){
    WE_light = 1;
  }
  else if((NS_cars_event == 1)&&(SN_cars_event == 1)&&(EW_cars_event == 0)&&(WE_cars_event==0)){
    SN_light = 1;
    NS_light = 1;
  }
  else if((NS_cars_event == 0)&&(SN_cars_event == 0)&&(EW_cars_event == 1)&&(WE_cars_event==1)){
    EW_light = 1;
    WE_light = 1;
  }
  else{

  }


  *out << "time(" << sc_time_stamp() << ") = " << "NS_ok to drive" << NS_light << "NS_cars detected: " << NS_cars_event << endl << "SN_ok to drive" << SN_light << "SN_cars detected" << SN_cars_event << endl
  << "EW_ok to drive" << EW_light << "EW_cars detected" << EW_cars_event << endl << "WE_ok to drive" << WE_light << "WE_cars detected" << WE_cars_event << endl;
}

void Monitor::check_constraints_method()
{
  assert((NS_light == 1 && WE_light == 1)||(SN_light == 1 && EW_light == 1)||(NS_light == 1 && EW_light == 1)|| (SN_light == 1 && WE_light==1));
}
