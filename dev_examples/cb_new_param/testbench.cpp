/*****************************************************************************
  Copyright 2016 Accellera Systems Initiative Inc.
  All rights reserved.

  Copyright 2009-2010 GreenSocs
  All rights reserved.
  Authors:
      Christian Schroeder <schroeder@eis.cs.tu-bs.de>
      Mark Burton <mark@greensocs.com>

  Copyright 2016 Ericsson
  All rights reserved.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
 *****************************************************************************/


#include <systemc>
#include "cci_configuration"

#include "ParameterOwnerModule.h"
#include "ObserverModule.h"

/// Testbench for the CCI example application which uses the GreenSocs demo implemenation
int sc_main(int argc, char *argv[]) {
  //sc_core::sc_report_handler::set_actions(sc_core::SC_ERROR, sc_core::SC_ABORT);
  //sc_core::sc_report_handler::set_actions(sc_core::SC_WARNING, sc_core::SC_ABORT);

  // Note: this prevents from catching the error!!
  //sc_core::sc_report_handler::set_actions("/ASI/CCI/set_param_failed",  sc_core::SC_DISPLAY);
  sc_core::sc_report_handler::set_actions("/ASI/CCI/cci_value_failure", sc_core::SC_DISPLAY);


  ObserverModule        observer   ("Observer");
  ParameterOwnerModule  owner      ("Owner");

  std::cout << std::endl << "------ sc_start() ----------------" << std::endl;
  sc_core::sc_start(); 
  std::cout << std::endl << "------ sc_start() returned -------" << std::endl;
  
  return EXIT_SUCCESS; 
  
}
