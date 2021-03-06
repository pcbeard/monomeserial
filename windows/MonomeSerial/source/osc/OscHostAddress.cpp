/*
 * MonomeSerial, a simple MIDI and OpenSoundControl routing utility for the monome 40h
 * Copyright (C) 2007 Joe Lake
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
//--------------------------------------------
/*
 * Current code by Daniel Battaglia and Steve Duda.
 * Released under the original GPL
 */
//--------------------------------------------


#include "../stdafx.h"
#include "OscHostAddress.h"
#include "OscException.h"
#include <string>
#include <iostream>
using namespace std;

using namespace liblointerface;

OscHostAddress::OscHostAddress(const string& host, const string& port) : _retainCount(0)
{
    _hostString = host + ":" + port;
    _hostAddress = lo_address_new(host.c_str(), port.c_str());

    if (_hostAddress == 0)  
       // throw OscException(OscException::kOscExceptionTypeInvalidHostAddressString, lo_address_errstr(_hostAddress));
	   throw OscException(OscException::kOscExceptionTypeInvalidHostAddressString, 
							"Invalid call to lo_address_new: invalid host address or port value");
}    

OscHostAddress::~OscHostAddress()
{
    if (_hostAddress != 0)
        lo_address_free(_hostAddress);
}

void OscHostAddress::retain(void)
{
    _retainCount++;
}

void OscHostAddress::release(void)
{
    _retainCount--;
}

int OscHostAddress::getRetainCount(void)
{
    return _retainCount;
}

const string& OscHostAddress::getHostString(void)
{
    return _hostString;
}

lo_address OscHostAddress::getHostAddress(void)
{
    return _hostAddress;
}
