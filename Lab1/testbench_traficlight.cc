#include <systemc.h>
#include "traficlight.h"
#include "input_gen.h"
#include "monitor.h"

int sc_main(int argc, int argd, char **argv)
{
  // The command-line arguments are as follows:
  // 1. the simulation time (in seconds),
  // 2. Number of time-checks
  //3. the file with input data (see input.txt), and
  // 4. the file to write output data.
  assert(argc == 4);

  sc_time sim_time(atof(argv[1]), SC_SEC);
  char *infile = argv[3];
  char *outfile = argv[4];

  // Create channels.
  sc_signal<bool> NS_light_sig;
  sc_signal<bool> SN_light_sig;
  sc_signal<bool> EW_light_sig;
  sc_signal<bool> WE_light_sig;
  sc_signal<int> NS_cars_sig;
  sc_signal<int> SN_cars_sig;
  sc_signal<int> EW_cars_sig;
  sc_signal<int> WE_cars_sig;

  // Instantiate modules.
  Traficlight lightNS("TraficlightNS");
  Traficlight lightSN("TraficlightSN");
  Traficlight lightEW("TraficlightEW");
  Traficlight lightWE("TraficlightWE");
  Generator genNS("GeneratorNS", infile);
  Generator genSN("GeneratorSN", infile);
  Generator genEW("GeneratorEW", infile);
  Generator genWE("GeneratorWE", infile);
  Monitor monitor("Monitor", outfile);

  // Connect the channels to the ports.
  lightNS(NS_light_sig, NS_cars_sig);
  lightSN(SN_light_sig, SN_cars_sig);
  lightEW(EW_light_sig, EW_cars_sig);
  lightWE(WE_light_sig, WE_cars_sig);
  genWE(WE_cars_sig);
  genEW(EW_cars_sig);
  genNS(NS_cars_sig);
  genSN(SN_cars_sig);
  monitor(NS_light_sig, SN_light_sig, EW_light_sig, WE_light_sig, WE_cars_sig, EW_cars_sig, NS_cars_sig, SN_cars_sig);

  // Start the simulation.
  sc_start(sim_time);

  return 0;
}
