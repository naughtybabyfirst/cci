/*****************************************************************************
  Copyright 2016 Accellera Systems Initiative Inc.
  All rights reserved.

  Copyright 2010 GreenSocs
  All rights reserved.
  Authors:
      Christian Schroeder <schroeder@eis.cs.tu-bs.de>

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


#ifndef __TEST_DATATYPE_H__
#define __TEST_DATATYPE_H__

#include <iostream>
#include <string.h> 

class test_datatype
{
public:
  
  friend std::istream& operator >>(std::istream &is,test_datatype &obj);
  friend std::ostream& operator <<(std::ostream &os,const test_datatype &obj);
  
  std::string strVal;
};

// implementation see library cpp gs_cci_symbols_b.cpp
/*std::istream& operator >>(std::istream &is,test_datatype &obj)
{
  is>>obj.strVal;
  return is;
}
std::ostream& operator <<(std::ostream &os,const test_datatype &obj)
{
  os<<obj.strVal;
  return os;
}
bool operator==(test_datatype const& lhs, test_datatype const& rhs) {
  return lhs.strVal.compare(rhs.strVal);
}
 */
#endif
