//
// Copyright 2015 (C). Alex Robenko. All rights reserved.
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

#include "NavTimegps.h"

#include <cassert>

#include "cc_plugin/field/common.h"
#include "cc_plugin/field/nav.h"

template class ublox::message::NavTimegps<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavTimegps<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavTimegps>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createProps_valid()
{
    QVariantList bitNames;
    bitNames.append("towValid");
    bitNames.append("weekValid");
    bitNames.append("leapSValid");
    assert(bitNames.size() == ublox::message::NavTimegpsField_valid_numOfValues);

    return cc::Property::createPropertiesMap("valid", std::move(bitNames));
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::nav::props_iTOW());
    props.append(cc_plugin::field::nav::props_fTOW());
    props.append(cc_plugin::field::nav::props_week());
    props.append(cc::Property::createPropertiesMap("leapS"));
    props.append(createProps_valid());
    props.append(cc_plugin::field::nav::props_tAcc());

    assert(props.size() == NavTimegps::FieldIdx_numOfValues);
    return props;
}

}  // namespace

NavTimegps::NavTimegps() = default;
NavTimegps::~NavTimegps() = default;

NavTimegps& NavTimegps::operator=(const NavTimegps&) = default;
NavTimegps& NavTimegps::operator=(NavTimegps&&) = default;

const char* NavTimegps::nameImpl() const
{
    static const char* Str = "NAV-TIMEGPS";
    return Str;
}

const QVariantList& NavTimegps::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

