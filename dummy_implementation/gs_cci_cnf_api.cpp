/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2009 by all Contributors.
  All Rights reserved.

  Developed by GreenSocs : http://www.greensocs.com/
   Christian Schroeder, schroeder@eis.cs.tu-bs.de
   Mark Burton, mark@greensocs.com

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License Version 3.0 (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.systemc.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

 *****************************************************************************/


#include "gs_cci_cnf_api.h"

cci::gs_cci_cnf_api::~cci_cnf_api() { 
  SC_REPORT_WARNING("GreenSocs/cci/not_implemented", "not implemented");
}

bool cci::gs_cci_cnf_api::set_init_value(const std::string &parname, const std::string &value) {
  SC_REPORT_WARNING("GreenSocs/cci/not_implemented", "not implemented");
  return false;
}

const std::string cci::gs_cci_cnf_api::get_json_string(const std::string &parname) {
  SC_REPORT_WARNING("GreenSocs/cci/not_implemented", "not implemented");
  return std::string("default");
}

cci::cci_param_base* cci::gs_cci_cnf_api::get_param(const std::string &parname) {
  SC_REPORT_WARNING("GreenSocs/cci/not_implemented", "not implemented");
  return NULL;
}

bool cci::gs_cci_cnf_api::exists_param(const std::string &parname) {
  SC_REPORT_WARNING("GreenSocs/cci/not_implemented", "not implemented");
  return false; 
}

const std::vector<std::string> cci::gs_cci_cnf_api::get_param_list() {
  SC_REPORT_WARNING("GreenSocs/cci/not_implemented", "not implemented");
  std::vector<std::string> vec;
  return vec;
}

boost::shared_ptr< cci::callb_adapt_b> cci::gs_cci_cnf_api::register_callback(const std::string& parname, boost::shared_ptr< cci::callb_adapt_b> callb) {
  SC_REPORT_WARNING("GreenSocs/cci/not_implemented", "not implemented");
  return callb;
}


void cci::gs_cci_cnf_api::unregister_all_callbacks(void* observer) {
  SC_REPORT_WARNING("GreenSocs/cci/not_implemented", "not implemented");
}

bool cci::gs_cci_cnf_api::unregister_param_callback(callb_adapt_b* callb) {
  SC_REPORT_WARNING("GreenSocs/cci/not_implemented", "not implemented");
  return false;
}

bool cci::gs_cci_cnf_api::has_callbacks(const std::string& parname) {
  SC_REPORT_WARNING("GreenSocs/cci/not_implemented", "not implemented");
  return false;
}

bool cci::gs_cci_cnf_api::add_param(cci_param_base* par) {
  SC_REPORT_WARNING("GreenSocs/cci/not_implemented", "not implemented");
  return false;
}

bool cci::gs_cci_cnf_api::remove_param(cci_param_base* par) {
  SC_REPORT_WARNING("GreenSocs/cci/not_implemented", "not implemented");
  return false;
}


void cci::gs_cci_cnf_api::set_alias(std::string& orig_parname, std::string& alias_parname) {
  SC_REPORT_WARNING("GreenSocs/cci/not_implemented", "not implemented");
}
    
const std::vector<std::string> cci::gs_cci_cnf_api::get_param_list(const std::string& pattern) {
  SC_REPORT_WARNING("GreenSocs/cci/not_implemented", "not implemented");
  std::vector<std::string> vec;
  return vec;
}

const std::vector<cci::cci_param_base*> cci::gs_cci_cnf_api::get_params(const std::string& pattern) {
  SC_REPORT_WARNING("GreenSocs/cci/not_implemented", "not implemented");
  std::vector<cci_param_base*> vec;
  return vec;
}

