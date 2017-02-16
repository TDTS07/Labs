#include <cassert>
#include "traficlight.h"

Traficlight::Traficlight(sc_module_name name)
  : sc_module(name)
{
  //assert(datafile != 0);       // An input file should be given.

  //in = new ifstream(datafile); // Open the input file.
  //assert(*in);                 // Check that everything is OK.

  light.initialize(false);
  event.initialize(false);

  outgoing_event = false;

  SC_METHOD(sensor_method);
  dont_initialize();
  sensitive << light << cars;

  SC_METHOD(on_off_method);
  dont_initialize();
  sensitive << change_light << new_car;

}
/*Traficlight::~Traficlight()
{
  delete in;
}
*/
void Traficlight::sensor_method()
{
  bool trafic_light = light->read();
  bool new_trafic = cars->read();

  if(trafic_light)
  {
    outgoing_event = false;
  }
  else if(!outgoing_event && !trafic_light)
  {
    outgoing_event = new_trafic;
    new_car.notify();
  }

  event->write(outgoing_event);

}

void Traficlight::on_off_method()
{
  bool ack_in = change_light->read();
  bool light_out = ack_in && outgoing_event;

  light->write(light_out);
}
