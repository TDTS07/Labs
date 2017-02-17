#include <cassert>
#include "traficlight.h"

Traficlight::Traficlight(sc_module_name name)
  : sc_module(name)
{

  //initialize all lights to red and no cars at the signal
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

void Traficlight::sensor_method()
{
  bool trafic_light = light->read();
  bool new_trafic = cars->read();

  //if the light is green, no notification needs to be sent to the controller
  if(trafic_light)
  {
    outgoing_event = false;
  }
  //else the read cars from input file and wait for response from controller
  else if(!outgoing_event && !trafic_light)
  {
    outgoing_event = new_trafic;
    new_car.notify();
  }
  //send request to controller
  event->write(outgoing_event);

}

//if car wants to go and gets ok from controller, turn the light green
void Traficlight::on_off_method()
{
  bool ack_in = change_light->read();
  bool light_out = ack_in && outgoing_event;

  light->write(light_out);
}
