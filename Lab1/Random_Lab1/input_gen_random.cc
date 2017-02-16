#include "input_gen_random.h"


Generator::Generator(sc_module_name name)
  : sc_module(name)
{

  SC_THREAD(generate_thread);

  NS_cars.initialize(false);
  SN_cars.initialize(false);
  EW_cars.initialize(false);
  WE_cars.initialize(false);
}


void Generator::generate_thread()
{
  sc_time gen_time = sc_time(200, SC_SEC);

  while ( sc_time_stamp() < gen_time )
  {
    NS_cars.write(rand() % 2 == 1);
    SN_cars.write(rand() % 2 == 1);
    EW_cars.write(rand() % 2 == 1);
    WE_cars.write(rand() % 2 == 1);
    wait(15,SC_SEC);
  }
  
  NS_cars.write(false);
  SN_cars.write(false);
  EW_cars.write(false);
  WE_cars.write(false);
}
