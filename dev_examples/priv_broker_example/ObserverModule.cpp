/*****************************************************************************

  Licensed to Accellera Systems Initiative Inc. (Accellera) under one or
  more contributor license agreements.  See the NOTICE file distributed
  with this work for additional information regarding copyright ownership.
  Accellera licenses this file to you under the Apache License, Version 2.0
  (the "License"); you may not use this file except in compliance with the
  License.  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
  implied.  See the License for the specific language governing
  permissions and limitations under the License.

 ****************************************************************************/

/**
 * @file   ObserverModule.cpp
 * @author Christian Schroeder, GreenSocs
 * @author Mark Burton, GreenSocs
 */

#include "ObserverModule.h"
#include <systemc.h>

ObserverModule::ObserverModule(sc_core::sc_module_name name)
: sc_core::sc_module(name)
{ 
  // get the config broker which is responsible for this module
  mBroker = &cci::cci_broker_manager::get_current_broker(cci::cci_originator(*this));
  SC_THREAD(main_action);
}

void ObserverModule::main_action() {

  cout << "----------------------------" << endl<< endl;

  // show a parameter list
  cout << endl << "**** Parameter list (visible in "<<name()<<"): " << endl;
  std::vector<std::string> vec = mBroker->get_param_list();
  std::vector<std::string>::iterator iter;
  std::stringstream ss_show;
  for (iter = vec.begin() ; iter < vec.end(); iter++) {
    ss_show << "   " << *iter << std::endl;
  }
  std::cout << ss_show.str() << std::endl<<std::endl;
  
  cout << "----------------------------" << endl;
  std::cout << std::endl;

}

/// Callback function with default signature showing changes.
void ObserverModule::config_callback(const cci::cci_param_write_event<> & ev) {
  DEMO_DUMP(name(), "Callback for parameter '" << ev.param_handle.get_name() << "' changed to value '"<<ev.new_value<<"'");
}

/// Callback function with default signature rejecting all changes.
bool ObserverModule::config_callback_reject_changes(const cci::cci_param_write_event<> & ev) {
  DEMO_DUMP(name(), "Callback method called (which rejects changes):");
  cout << "  Parameter '" << ev.param_handle.get_name() << "' type " << "reject" << endl;
  cout << "  REJECT VALUE CHANGE!!" << endl;
  cout << endl;
  return false;
}
