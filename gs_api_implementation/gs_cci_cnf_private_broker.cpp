// LICENSETEXT
//
//   Copyright (C) 2010 : GreenSocs Ltd
// 	 http://www.greensocs.com/ , email: info@greensocs.com
//
//   Developed by:
//    Christian Schroeder <schroeder@eis.cs.tu-bs.de>,
//    Mark Burton, mark@greensocs.com
//
//
// The contents of this file are subject to the licensing terms specified
// in the file LICENSE. Please consult this file for restrictions and
// limitations that may apply.
// 
// ENDLICENSETEXT


#include "gs_cci_cnf_private_broker.h"

cci::cnf::gs_cci_private_broker::gs_cci_private_broker(sc_core::sc_module* owner, std::vector<std::string> pub_params) 
: gs::cnf::GCnf_private_Api(owner, pub_params) { 
  //m_gcnf_api = new gs::cnf::GCnf_private_Api(owner, pub_params);
}

cci::cnf::gs_cci_private_broker::gs_cci_private_broker(sc_core::sc_module* owner_module, const char* pub_par ...)
: gs::cnf::GCnf_private_Api(owner_module, pub_par) {
/*  std::vector<std::string> pub_param_lst;
  va_list list;
  va_start(list, pub_par);
  const char* p = pub_par;
  for(;;) { 
    if(std::string(p) == std::string(END_OF_PUBLIC_PARAM_LIST))
      break;
    pub_param_lst.push_back(p);
    p = va_arg(list, char*);
  }
  va_end(list);

  m_gcnf_api = new gs::cnf::GCnf_private_Api(owner_module, pub_param_lst);*/
}

cci::cnf::gs_cci_private_broker::~gs_cci_private_broker() { 
  //delete m_gcnf_api; m_gcnf_api = NULL;
}

void cci::cnf::gs_cci_private_broker::set_init_value(const std::string &parname, const std::string &json_value) {
  // TODO: use JSON
  if ( !gs::cnf::GCnf_private_Api::setInitValue(parname, json_value) ) {
    CCI_THROW_ERROR(cci::cnf::cci_report::set_param_failed().get_type(), "Setting initial value failed.");
  }
}

void cci::cnf::gs_cci_private_broker::lock_init_value(const std::string &parname) {
  if ( !gs::cnf::GCnf_private_Api::lockInitValue(parname) ) {
    CCI_THROW_ERROR(cci::cnf::cci_report::set_param_failed().get_type(), "Locking initial value failed.");
  }
}

const std::string cci::cnf::gs_cci_private_broker::get_json_string(const std::string &parname) {
  // TODO: use JSON
  return gs::cnf::GCnf_private_Api::getValue(parname);
}

const std::string cci::cnf::gs_cci_private_broker::get_json_string_keep_unused(const std::string &parname) {
  // TODO: use JSON
  return gs::cnf::GCnf_private_Api::getValue(parname, "", true);
}

cci::cnf::cci_base_param* cci::cnf::gs_cci_private_broker::get_param(const std::string &parname) {
  std::map<std::string,cci_base_param*>::iterator iter = m_mirrored_registry.find(parname);
  if( iter != m_mirrored_registry.end() )
    return iter->second;
  else return NULL;
}

bool cci::cnf::gs_cci_private_broker::exists_param(const std::string &parname) {
  return gs::cnf::GCnf_private_Api::existsParam(parname);
}

bool cci::cnf::gs_cci_private_broker::is_used(const std::string &parname) {
  return gs::cnf::GCnf_private_Api::is_used(parname);
}

const std::vector<std::string> cci::cnf::gs_cci_private_broker::get_param_list() {
  return gs::cnf::GCnf_private_Api::getParamList();
}

cci::shared_ptr<cci::cnf::callb_adapt_b> cci::cnf::gs_cci_private_broker::register_callback(const std::string& parname, const callback_type type, cci::shared_ptr<cci::cnf::callb_adapt_b> callb) {
  // TODO
  SC_REPORT_WARNING("GreenSocs/cci/not_implemented", "not implemented");
  return callb;
}

void cci::cnf::gs_cci_private_broker::unregister_all_callbacks(void* observer) {
  // TODO
  SC_REPORT_WARNING("GreenSocs/cci/not_implemented", "not implemented");
}

bool cci::cnf::gs_cci_private_broker::unregister_param_callback(cci::cnf::callb_adapt_b* callb) {
  // TODO
  SC_REPORT_WARNING("GreenSocs/cci/not_implemented", "not implemented");
  return false;
}

bool cci::cnf::gs_cci_private_broker::has_callbacks(const std::string& parname) {
  // TODO
  SC_REPORT_WARNING("GreenSocs/cci/not_implemented", "not implemented");
  return false;
}

void cci::cnf::gs_cci_private_broker::add_param(cci_base_param* par) {
  //cci::cnf::cci_base_param* bpar = dynamic_cast<cci::cnf::cci_base_param*>(par);
  //assert(bpar != NULL && "This should never happen, a cci_base_param shall be a cci_base_param!");

  m_mirrored_registry.insert(std::pair<std::string, cci_base_param*>(par->get_name(), par));
}

void cci::cnf::gs_cci_private_broker::remove_param(cci::cnf::cci_base_param* par) {
  m_mirrored_registry.erase(par->get_name());
}

const std::vector<std::string> cci::cnf::gs_cci_private_broker::get_param_list(const std::string& pattern) {
  SC_REPORT_WARNING("GreenSocs/cci/not_implemented", "pattern limited to GreenConfig capabilities");
  return gs::cnf::GCnf_private_Api::getParamList(pattern);
}

const std::vector<cci::cnf::cci_base_param*> cci::cnf::gs_cci_private_broker::get_params(const std::string& pattern) {
  SC_REPORT_WARNING("GreenSocs/cci/not_implemented", "pattern limited to GreenConfig capabilities");
  std::vector<cci::cnf::cci_base_param*> parvec;
  std::vector<std::string> strvec;
  strvec = get_param_list(pattern);
  std::vector<std::string>::iterator striter;
  for (striter = strvec.begin(); striter != strvec.end(); striter++) {
    cci::cnf::cci_base_param* p = get_param(*striter);
    if (p) parvec.push_back(p);
  }
  return parvec;
}

/*gs::cnf::cnf_api* cci::cnf::gs_cci_private_broker::get_gcnf_api() {
  return m_gcnf_api;
}*/

