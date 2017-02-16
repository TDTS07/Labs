#include <systemc.h>
#include "traficlight.h"
#include "input_gen_random.h"
#include "monitor.h"

int sc_main(int argc, char **argv)
{
  // The command-line arguments are as follows:
  // 1. the simulation time (in seconds),
  // 2. Number of time-checks
  //3. the file with input data (see input.txt), and
  // 4. the file to write output data.
  assert(argc == 3);

  sc_time sim_time(atof(argv[1]), SC_SEC);
  char *outfile = argv[2];

  // Create channels.
  sc_signal<bool> NS_light_sig;
  sc_signal<bool> SN_light_sig;
  sc_signal<bool> EW_light_sig;
  sc_signal<bool> WE_light_sig;
  sc_signal<bool> NS_cars_sig;
  sc_signal<bool> SN_cars_sig;
  sc_signal<bool> EW_cars_sig;
  sc_signal<bool> WE_cars_sig;
  sc_signal<bool> NS_event_sig;
  sc_signal<bool> SN_event_sig;
  sc_signal<bool> EW_event_sig;
  sc_signal<bool> WE_event_sig;
  sc_signal<bool> NS_change_sig;
  sc_signal<bool> SN_change_sig;
  sc_signal<bool> EW_change_sig;
  sc_signal<bool> WE_change_sig;
  // Instantiate modules.
  Traficlight lightNS("TraficlightNS");
  Traficlight lightSN("TraficlightSN");
  Traficlight lightEW("TraficlightEW");
  Traficlight lightWE("TraficlightWE");
  Generator gen("Generator");
  Monitor monitor("Monitor", outfile);

  // Connect the channels to the ports.
  lightNS(NS_cars_sig, NS_event_sig, NS_light_sig, NS_change_sig);
  lightSN(SN_cars_sig, SN_event_sig ,SN_light_sig ,SN_change_sig);
  lightEW(EW_cars_sig, EW_event_sig, EW_light_sig, EW_change_sig);
  lightWE(WE_cars_sig, WE_event_sig, WE_light_sig, WE_change_sig);
  //genWE(WE_cars_sig);
  //genEW(EW_cars_sig);
  //genNS(NS_cars_sig);
  gen(NS_cars_sig, SN_cars_sig, EW_cars_sig, WE_cars_sig);
  monitor(NS_event_sig, SN_event_sig, EW_event_sig, WE_event_sig, NS_change_sig, SN_change_sig, EW_change_sig, WE_change_sig);

  // Start the simulation.
  sc_start(sim_time);

  return 0;
}
