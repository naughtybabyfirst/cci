//   GreenControl framework
//
// LICENSETEXT
//
//   Copyright (C) 2008 : GreenSocs Ltd
//      http://www.greensocs.com/ , email: info@greensocs.com
//
//   Developed by :
//   
//   Marius Montón <marius.monton@uab.cat>,
//     Hardware-Software Prototypes and Solutions Lab (CEPHIS). 
//     Microelectronics and Electronics SystemS Dpt. UAB.
//     http://cephis.uab.cat
//
//   Christian Schroeder <schroeder@eis.cs.tu-bs.de>,
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


using std::istringstream;


// /////////////////////////////////////////////////////////////////////////////// //
// /////////////////// gs_param< std::vector<std::string> > ////////////////////// //
// /////////////////////////////////////////////////////////////////////////////// //

/// Template specialization for gs_param< std::vector<std::string> >.
/**
 * Default value = empty vector.
 */
// TODO: maybe template<typename T>
//             class gs_param< std::vector<T> >
// issue: (de)serialization of T
template<>
class gs_param< std::vector<std::string> >
: public gs_param_t< std::vector<std::string> >
{
  /// Typedef for the value.
  typedef std::vector<std::string> val_type;

public:
  GS_PARAM_HEAD;

  // ///////////////////////
  //  additional functions
  
  bool empty() const { return my_value.empty(); }
  // TODO optional: More of the vector functions

  // ///////////////////////
  //  overloaded functions

  /// Overloads gs_param_base::getTypeString
  const std::string getTypeString() const {
    return std::string("std::vector<std::string>");
  }

  /// Overloads gs_param_base::getType
  const Param_type getType() const {
    return PARTYPE_NOT_AVAILABLE;
  }
  
  /// Overloads gs_param_t<T>::convertValueToString
  /**
   * Serializes the vector to a single line comma separated list 
   * of the members.<br>
   * Members surrounded by quotes (").
   * The whole string surrounded by { }
   */
  std::string convertValueToString(const val_type &val) const{
    return static_convertValueToString(val);
  }  
  inline static std::string static_convertValueToString(const val_type &val) {
    std::ostringstream ss;
    ss << "{";
    bool first = true;
    val_type::const_iterator iter;

    for (iter = val.begin(); iter != val.end(); iter++) {
      if (!first) ss << ',';
      first= false;
      // make sure included "s are handled
      
      std::string::size_type loc = iter->find('"');
      std::string aux = *iter;

      while( loc != std::string::npos) {
        if (aux[loc-1] != '\\') {
          aux = aux.substr(0, loc) + "\\" + aux.substr(loc, aux.npos);
        }
        loc = aux.find('"', loc+1);
      }

      ss << '"' << aux << '"'; // not nescessarily quotes    
    }
    ss << "}";
    return ss.str();
  }
  
  /// Static convertion function called by virtual deserialize and others (e.g. GCnf_API)
  /**
   * Deserializes a single-line string into a vector.
   * - The string has to look like: "{"value1","value 2","value 3"}"
   * - Optionally there may be spaces between the values and the comma.
   * - so far the value must not contain quotes: TODO!!
   */
   inline static bool static_deserialize(val_type &target_val, const std::string& str) {

    std::istringstream ss(str);

    GS_PARAM_DUMP_WITHNAME("gs_param", "deserialize: string='"<< ss.str().c_str()<<"'");
    if (ss.str().length() == 0) {
      target_val.clear();
      GS_PARAM_DUMP_WITHNAME("gs_param", "vector<string> deserialize: set default value");
      return true;
    }
    else {
      target_val.clear();
      
      std::string::size_type index = str.find("{");
      if (index == str.npos) {
        SC_REPORT_ERROR("gs_param", "vector<string> deserialize error!");
      }
      std::string my_string = str;
      std::string value;
      std::string word;
      std::string::size_type indexB, indexC;
      do {
      
        if (my_string=="}") break;

        index = 0;
        do {
          index = my_string.find("\"", index);
        } while(my_string[index-1] == '\\'  && index != std::string::npos);

        indexB = index;
        do {
          indexB = my_string.find("\"", indexB+1);
        } while(my_string[indexB-1] == '\\' && indexB != std::string::npos);

        if (index == std::string::npos || indexB == std::string::npos) break;

        value = my_string.substr(index+1, indexB-index-1);

        // now we must handle \" that can be inside the string, and transform them to single "
        indexC = value.find("\\\"");
        while (indexC != std::string::npos) {
          value = value.substr(0, indexC) + value.substr(indexC+1,value.npos);
          indexC= value.find("\\\"", indexC);
        }

        target_val.push_back(value);
        my_string = my_string.substr(indexB+1, word.npos);
      } while(index != std::string::npos);
      return true;
    }
    return true;
  }    

};
