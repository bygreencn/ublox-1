//
// Copyright 2015 - 2016 (C). Alex Robenko. All rights reserved.
//

// This file is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "NavVelecef.h"

#include <cassert>

#include "cc_plugin/field/nav.h"

template class ublox::message::NavVelecef<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavVelecef<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavVelecef>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::nav::props_iTOW());
    props.append(cc_plugin::field::nav::props_ecefVX());
    props.append(cc_plugin::field::nav::props_ecefVY());
    props.append(cc_plugin::field::nav::props_ecefVZ());
    props.append(cc_plugin::field::nav::props_sAcc());

    assert(props.size() == NavVelecef::FieldIdx_numOfValues);
    return props;
}

}  // namespace

NavVelecef::NavVelecef() = default;
NavVelecef::~NavVelecef() = default;

NavVelecef& NavVelecef::operator=(const NavVelecef&) = default;
NavVelecef& NavVelecef::operator=(NavVelecef&&) = default;


const char* NavVelecef::nameImpl() const
{
    static const char* Str = "NAV-VELECEF";
    return Str;
}

const QVariantList& NavVelecef::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

