/**********************************************************\ 
Original Author: Richard Bateman and Georg Fritzsche 

Created:    December 3, 2009
License:    Dual license model; choose one of two:
            Eclipse Public License - Version 1.0
            http://www.eclipse.org/legal/epl-v10.html
            - or -
            GNU Lesser General Public License, version 2.1
            http://www.gnu.org/licenses/lgpl-2.1.html

Copyright 2009 PacketPass Inc, Georg Fritzsche,
               Firebreath development team
\**********************************************************/

#include "BrowserObjectAPI.h"
#include "DOM/JSAPI_DOMDocument.h"
#include <boost/assign.hpp>
using boost::assign::list_of;
#include "SimpleMathAPI.h"

#include "FBTestPluginAPI.h"

FBTestPluginAPI::FBTestPluginAPI(FB::BrowserHost host) : m_host(host)
{
    registerMethod("add",  make_method(this, &FBTestPluginAPI::add));
    registerMethod("echo",  make_method(this, &FBTestPluginAPI::echo));
    registerMethod("asString",  make_method(this, &FBTestPluginAPI::asString));
    registerMethod("asBool",  make_method(this, &FBTestPluginAPI::asBool));
    registerMethod("asInt",  make_method(this, &FBTestPluginAPI::asInt));
    registerMethod("asDouble",  make_method(this, &FBTestPluginAPI::asDouble));
    registerMethod("listArray",  make_method(this, &FBTestPluginAPI::listArray));
    registerMethod("reverseArray",  make_method(this, &FBTestPluginAPI::reverseArray));

    // Read-write property
    registerProperty("testString",
                     make_property(this, 
                        &FBTestPluginAPI::get_testString,
                        &FBTestPluginAPI::set_testString));

    registerProperty("simpleMath",
                     make_property(this,
                        &FBTestPluginAPI::get_simpleMath));
    // Read-only property
    registerProperty("someInt", 
                     make_property(this,
                        &FBTestPluginAPI::get_someInt));

    m_simpleMath = new SimpleMathAPI(m_host);
}

FBTestPluginAPI::~FBTestPluginAPI()
{
}

// Read/Write property someInt
std::string FBTestPluginAPI::get_testString()
{
    return m_testString;
}
void FBTestPluginAPI::set_testString(std::string val)
{
    m_testString = val;
}

// Read-only property someInt
long FBTestPluginAPI::get_someInt()
{
    return 12;
}

// add Method
long FBTestPluginAPI::add(long a, long b)
{
    return a+b;
}

FB::variant FBTestPluginAPI::echo(FB::variant a)
{
    return a;
}

std::string FBTestPluginAPI::asString(FB::variant a)
{
    return a.convert_cast<std::string>();
}

bool FBTestPluginAPI::asBool(FB::variant a)
{
    return a.convert_cast<bool>();
}

long FBTestPluginAPI::asInt(FB::variant a)
{
    return a.convert_cast<long>();
}

double FBTestPluginAPI::asDouble(FB::variant a)
{
    return a.convert_cast<double>();
}

FB::JSOutArray FBTestPluginAPI::reverseArray(std::vector<std::string> arr)
{
    FB::JSOutArray outArr;
    bool start(true);
    for (std::vector<std::string>::reverse_iterator it = arr.rbegin(); it != arr.rend(); it++)
    {
        outArr.push_back(*it);
    }
    return outArr;
}

std::string FBTestPluginAPI::listArray(std::vector<std::string> arr)
{
    std::string outStr;
    bool start(true);
    for (std::vector<std::string>::iterator it = arr.begin(); it != arr.end(); it++)
    {
        if (!start) {
            outStr += ", ";
        }
        start = false;
        outStr += *it;
    }
    return outStr;
}

FB::JSOutObject FBTestPluginAPI::get_simpleMath()
{
    return m_simpleMath;
}