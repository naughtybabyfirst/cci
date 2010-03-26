//   GreenControl framework
//
// LICENSETEXT
//
//   Copyright (C) 2009 : GreenSocs Ltd
// 	 http://www.greensocs.com/ , email: info@greensocs.com
//
//   Developed by :
//   
//   Michael Ruetz <m.ruetz@tu-bs.de>,
//   Christian Schroeder <schroeder@eis.cs.tu-bs.de>
//     Technical University of Braunschweig, Dept. E.I.S.
//     http://www.eis.cs.tu-bs.de
//
//
//   This program is free software.
// 
//   If you have no applicable agreement with GreenSocs Ltd, this software
//   is licensed to you, and you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
// 
//   If you have a applicable agreement with GreenSocs Ltd, the terms of that
//   agreement prevail.
// 
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
// 
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the Free Software
//   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
//   02110-1301  USA 
// 
// ENDLICENSETEXT

// doxygen comments

#ifndef __CONFIG_FILTER_H__
#define __CONFIG_FILTER_H__

#include "greencontrol/gclog/filter_base.h"

namespace gs {
namespace log {


/// Configurable passthrough filter.
/**
 * This filter passes the transaction to the next filter and output module. A LogConfig can be set before passing the transaction
 * to the output module.
 */
class ConfigFilter : public FilterBase
{
public:
  /// Constructor.
  ConfigFilter() {}

  /// Contructor that gets a LogConfig.
  ConfigFilter(LogConfig config)
  {
    setLogConfig(config);
  }

  /// Destructor.
  ~ConfigFilter() {}

  /// Set a LogConfig that will become activated in the processTransaction() method.
  void setLogConfig(LogConfig config)
  {
    customCfg = config;
  }

  /// Hands the transaction to the filters connected to the filter ports.
  /**
   * Before the second filter port is processed, a LogConfig gets activated.
   */
  void processTransaction(ControlTransactionHandle& th)
  {
/*    if(m_pFilterVec)
      for(unsigned int i=0;i<m_pFilterVec[0].size();i++)
        m_pFilterVec[0][i]->processTransaction(th);
*/
    processFilterPort(0, th);

    // activate the LogConfig for the second filter port
    th->activateConfig(&customCfg);

/*    if(m_pFilterVec)
      for(unsigned int i=0;i<m_pFilterVec[1].size();i++)
        m_pFilterVec[1][i]->processTransaction(th);
*/
    processFilterPort(1, th);

    th->deactivateConfig();
  }

  /// Return the number of filter ports needed by this filter.
  unsigned int numFilterPorts()
  {
    return 2;
  }

protected:
  /// A custom LogConfig object that gets activated before the second filter port is processed.
  LogConfig customCfg;
};

  
} // end namespace log
} // end namespace gs

#endif
